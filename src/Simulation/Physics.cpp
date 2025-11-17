#include <Simulation.hpp>
#include <Renderer.hpp>
#include <User.hpp>


inline const float dist(const Vec2& v) {
  return v.x*v.x+v.y*v.y;
}
const Vec2 Simulation::GetVelocity(int index, const Vec2& p) {
  Vec2 val;
  Vec2 dir;
  float length;

  for(const Body& planet : bodies) {
    dir = planet.position-p;
    length = dir.x*dir.x+dir.y*dir.y;
    val += length != 0? dir/sqrt(length)*(Gravity*(planet.mass/length)) : Vec2();
  }

  dir = User::WorldMousePos-p;
  length = dir.x*dir.x+dir.y*dir.y;
  const float mass = (User::cursorMass/(System::ScaleByWorld? Renderer::WorldZoom : 1));
  val += (length != 0 && User::cursorForce != Off)? dir/sqrt(length)*(Gravity*(mass/length)) * User::cursorForce : Vec2();

  dir = blackHolePos-p;
  length = dir.x*dir.x+dir.y*dir.y;
  val += (length != 0 && blackHoleActive)? dir/sqrt(length)*(Gravity*(blackHoleMass/length)) : Vec2();

  return val + (System::EarthGravity? (0, -EARTH_MASS * Gravity) : Vec2());

  // if(!System::IsolatedSimulation) {
  //   const int bodyCount = bodies.size();
  //   for(int i = 0; i < bodyCount; i++) {
  //     if(index == i) continue;
  //     const float dist = Vec2::distance(p, position[i]);
  //     val += Vec2(position[i] - p).normalize()*(Gravity*(1/(dist*dist)));
  //   }
  // }
  return val;
}