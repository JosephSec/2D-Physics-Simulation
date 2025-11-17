#include <Simulation.hpp>
#include <System.hpp>
#include <User.hpp>
#include <Renderer.hpp>

#include <random>


int Simulation::bodyCount;

float Simulation::Gravity = 1;
float Simulation::bounceDamp;

Vec2 Simulation::WorldSize;
Vec2 Simulation::SpaceGrid;

std::vector<Vec2> Simulation::position;
// std::vector<float> Simulation::mass;
std::vector<Vec2> Simulation::velocity;

Vec2* Simulation::posAddr;
Vec2* Simulation::velAddr;

std::vector<Body> Simulation::bodies;

Vec2 Simulation::blackHolePos;
float Simulation::blackHoleMass;
bool Simulation::blackHoleActive;


void Simulation::reset() {
  Renderer::WorldZoom = 1;
  Renderer::cameraPosition = Vec2();
}
void Simulation::init(int count, float damp) {
  bodyCount = count;
  bounceDamp = damp;

  position = std::vector<Vec2>(bodyCount, Renderer::cameraPosition);
  // mass = std::vector<float>(bodyCount, 1);
  velocity = std::vector<Vec2>(bodyCount);

  bodies = std::vector<Body>();

  std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
  std::uniform_real_distribution<float> dist(-.1f, .1f);
  for(int i = 0; i < bodyCount; i++)
    velocity[i] = Vec2(dist(rng), dist(rng)).normalize();

  blackHoleMass = 1092;

  update(true);
}

void Simulation::clear(bool doSimulated, bool doStatic) {
  bodyCount = 0;

  if(doSimulated) {
    position.clear();
    // mass.clear();
    velocity.clear();
  }

  if(doStatic) {
    bodies.clear();
    blackHoleActive = false;
  }

  update(true);
}


void Simulation::step(unsigned int i) {
  Vec2 dir;
  float length;

  for(const Body& planet : bodies) {
    dir = planet.position-posAddr[i];
    length = dir.x*dir.x+dir.y*dir.y;
    velAddr[i] += length != 0? dir/sqrt(length)*(Gravity*(planet.mass/length)) : Vec2();
  }

  dir = User::WorldMousePos-posAddr[i];
  length = dir.x*dir.x+dir.y*dir.y;
  const float mass = (User::cursorMass/(System::ScaleByWorld? Renderer::WorldZoom : 1));
  velAddr[i] += (length != 0 && User::cursorForce != Off)? dir/sqrt(length)*(Gravity*(mass/length)) * User::cursorForce : Vec2();

  dir = blackHolePos-posAddr[i];
  length = dir.x*dir.x+dir.y*dir.y;
  velAddr[i] += (length != 0 && blackHoleActive)? dir/sqrt(length)*(Gravity*(blackHoleMass/length)) : Vec2();

  velAddr[i] += (System::EarthGravity? -Vec2up*EARTH_MASS*Gravity : Vec2());
  posAddr[i] += velAddr[i];

  if(!System::WindowBounds) return;

  if(posAddr[i].x < -WorldSize.x && velAddr[i].x < 0 || posAddr[i].x > WorldSize.x && velAddr[i].x > 0)
    velAddr[i].x *= -bounceDamp;
  else if(posAddr[i].y < -WorldSize.y && velAddr[i].y < 0 || posAddr[i].y > WorldSize.y && velAddr[i].y > 0)
    velAddr[i].y *= -bounceDamp;
}

void Simulation::update(bool forceSpaceVis) {
  if(forceSpaceVis || SpaceVisualizer::DoUpdate()) {
    SpaceVisualizer::update();
  }
}