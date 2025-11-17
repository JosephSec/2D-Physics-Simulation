#include <Simulation.hpp>
#include <User.hpp>
#include <random>


void Simulation::SpawnBurst(const Vec2& _pos, float _force) {
  std::mt19937 randgen(std::time(nullptr));
  std::uniform_real_distribution<float> range(-_force, _force);

  Simulation::bodyCount += 1000;
  Simulation::position.resize(Simulation::bodyCount);
  Simulation::velocity.resize(Simulation::bodyCount);

  for(unsigned int i = Simulation::bodyCount-1000; i < Simulation::bodyCount; i++) {
    Simulation::position[i] = _pos;
    Simulation::velocity[i] = Vec2(range(randgen), range(randgen)).normalize();
  }
}

void Simulation::CreateSimulated() {
  position.push_back(User::WorldMousePos);
  // mass.push_back(User::cursorMass);
  velocity.push_back(Vec2());

  bodyCount++;
}
void Simulation::DeleteSimulated(int index) {
  if(index == -1 && bodyCount > 0) index = bodyCount - 1;
  else return;

  position[index] = position.back(); position.pop_back();
  // mass[index]     = mass.back();     mass.pop_back();
  velocity[index] = velocity.back(); velocity.pop_back();

  bodyCount--;
}

void Simulation::CreateBody(const Vec2& position, float mass) {
  bodies.push_back(Body{position, mass}); update(true);
}
void Simulation::DeleteBody() {
  if(bodies.size() == 0) return;
  bodies.pop_back(); update(true);
}