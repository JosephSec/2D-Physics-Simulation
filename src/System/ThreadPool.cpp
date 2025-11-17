#include <System/ThreadPool.hpp>

#include <iostream>


std::atomic<bool> ThreadPool::running;
std::atomic<int>  ThreadPool::waitingThreads = 0;

std::mutex ThreadPool::jobsMutex;
std::condition_variable ThreadPool::jobsCond;

std::vector<std::function<void()>> ThreadPool::jobs;
std::vector<std::thread> ThreadPool::threads;

unsigned int ThreadPool::threadCount;


void ThreadPool::init(unsigned int _threadCount) {
  const unsigned int maxThreads = std::thread::hardware_concurrency();
  if(_threadCount > maxThreads) {
    std::cout << "requested too many threads\n";
    return;
  }

  threadCount = _threadCount;

  running = true;
  for(unsigned int i = 0; i < threadCount; i++)
    threads.emplace_back(ThreadWorker, i);
}
void ThreadPool::end() {
  running = false;
  jobsCond.notify_all();
  
  for(auto& t : threads) t.join();
  
  threads.clear();
  jobs.clear();
}


void ThreadPool::DoJobs(std::function<void(unsigned int)> job, unsigned int _n) {
  {
    std::unique_lock<std::mutex> lock(jobsMutex);
    const unsigned int threadChunk = _n/threadCount;
    for(unsigned int thread = 0; thread < threadCount; thread++) {
      const unsigned int start = threadChunk*thread;
      const unsigned int end = thread+1 == threadCount? _n : start+threadChunk;
      jobs.push_back([start, end, job] {
        for(unsigned int i = start; i < end; i++) job(i);
      });
    }
  }
  jobsCond.notify_all();

  while(waitingThreads.load() != threadCount) std::this_thread::yield();
}


void ThreadPool::ThreadWorker(unsigned int id) {
  while(running) {
    std::function<void()> job;
    {
      std::unique_lock<std::mutex> lock(jobsMutex);
      waitingThreads++;
      jobsCond.wait(lock, [] {return !jobs.empty() || !running; });
      waitingThreads--;

      if(!running && jobs.empty()) return;

      job = jobs.back();
      jobs.pop_back();
    }
    job();
  }
}