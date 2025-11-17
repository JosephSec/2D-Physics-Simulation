#include <System.hpp>
#include <System/ThreadPool.hpp>
#include <System/CallTimer.hpp>

#include <User.hpp>
#include <Renderer.hpp>
#include <Simulation.hpp>
#include <UI.hpp>

#include <filesystem>
#include <Windows.h>



string System::PATH;

float System::time = 1;
int System::FpsCounter;
float System::drawTime;
float System::moveTime;
float System::deltaTime;
int System::UsedThreads;

bool System::Paused             = false;
bool System::WindowBounds       = true;
bool System::EarthGravity       = false;
bool System::IsolatedSimulation = true;
bool System::ScaleByWorld       = true;
bool System::VisualizeVelocity  = false;
bool System::MultiThreading     = false;

bool System::FillScreen = false;


static sf::Clock deltaClock;
static sf::Clock fpsClock;


static int spawncommand() {
  std::cout << "Spawn Count: ";
  std::string str;
  std::getline(std::cin, str);
  system("cls");
  try {
    const int count = std::stoi(str);
    if(count < 0) return 0;
    return count;
  } catch (const std::invalid_argument&) { return 0; }
    catch (const std::out_of_range&)     { return 0; }
}
static bool yesornoCommand(const string& q) {
  std::cout << q+"? (default Y/n): ";
  std::string str;
  std::getline(std::cin, str);
  system("cls");
  return str.find('n') == string::npos;
}

void System::init() {
  SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_DISPLAY_REQUIRED);
  char buffer[MAX_PATH]; GetModuleFileNameA(NULL, buffer, MAX_PATH);
  PATH = std::filesystem::path(buffer).parent_path().parent_path().string();

  if(std::thread::hardware_concurrency() > 1) MultiThreading = yesornoCommand("Do Multi-Threading");

  ThreadPool::init(MultiThreading? std::thread::hardware_concurrency() : 1);
  Simulation::init(spawncommand(), .65f);  
  Renderer::init();
  Renderer::window->setActive(true);  
  UI::Manager::init(PATH, Renderer::window, true);
}
void System::update() {
  if(FillScreen) {
    FillScreen = false;

    const int start = Simulation::bodyCount;
    int index = 0;
    float scalar = 3;
    const Vec2 grid = Renderer::windowSize/scalar;
    Simulation::bodyCount += grid.x*grid.y;
    Simulation::position.resize(Simulation::bodyCount);
    Simulation::velocity.resize(Simulation::bodyCount);
    for(unsigned int x = 0; x < grid.x; x++) {
      for(unsigned int y = 0; y < grid.y; y++) {
        Simulation::position[start+index] = Renderer::ScreenToWorld(Vec2(x, y)*scalar);
        index++;
      }
    }
  }

  Simulation::posAddr = Simulation::position.data();
  Simulation::velAddr = Simulation::velocity.data();

  FpsCounter = 1.0f/fpsClock.restart().asSeconds();
  deltaTime += deltaClock.restart().asMilliseconds() * .001f * time;
  while(deltaTime >= FIXED_TIMESTEP) {
    deltaTime -= FIXED_TIMESTEP;
    if(!Paused) {
      Simulation::WorldSize = Renderer::ScreenToWorld(Renderer::windowSize);
      Simulation::WorldSize.y = -Simulation::WorldSize.y;
      CallTimer timer;
      ThreadPool::DoJobs(Simulation::step, Simulation::bodyCount);
      moveTime = timer.end();
    }
  }
  // UsedThreads = ThreadPool::threadCount - ThreadPool::waitingThreads;
  UsedThreads = ThreadPool::threadCount;

  if(time < 0) time = 0;

  Renderer::update();
  User::update();
  Simulation::update();
  UI::Manager::update();
}
int System::end() {
  UI::Manager::clear();
  ThreadPool::end();

  SetThreadExecutionState(ES_CONTINUOUS);

  return 0;
}