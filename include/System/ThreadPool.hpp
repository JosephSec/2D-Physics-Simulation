#pragma once

#include <atomic>
#include <mutex>
#include <thread>
#include <functional>
#include <condition_variable>


class ThreadPool {
public:
  static std::atomic<bool> running;
  static std::atomic<int> waitingThreads;
  static std::mutex jobsMutex;
  static std::vector<std::function<void()>> jobs;
  static std::vector<std::thread> threads;
  static std::condition_variable jobsCond;

  static unsigned int threadCount;


  static void init(unsigned int _threadCount);
  static void end();


  static void DoJobs(std::function<void(unsigned int)> job, unsigned int _n);


private:
  static void ThreadWorker(unsigned int id);
};