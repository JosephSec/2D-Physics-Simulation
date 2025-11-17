#pragma once

#include <vector>

#include <System.hpp>
#include <Simulation/SpaceVisualizer.hpp>


static constexpr float WORLDSCALE = 50;

static constexpr float EARTH_MASS = .006552f;
static constexpr float SOLAR_MASS = 218.4f;
// static constexpr float LIGHT_SPEED = 299792458;

static constexpr float BLACKHOLE_RADIUS = .01f;

#include <System.hpp>
#include <User.hpp>
#include <Renderer.hpp>
#include <Simulation.hpp>


struct Body {
  Vec2 position;
  float mass;
};



class Simulation {
public:
  static int bodyCount;

  static float Gravity;
  static float bounceDamp;

  static Vec2 WorldSize;
  static Vec2 SpaceGrid;

  static std::vector<Vec2> position;
  // static std::vector<float> mass;
  static std::vector<Vec2> velocity;

  static Vec2* posAddr;
  static Vec2* velAddr;
  
  static std::vector<Body> bodies;

  static Vec2 blackHolePos;
  static float blackHoleMass;
  static bool blackHoleActive;


  static void reset();
  static void init(int count, float damp);

  static void clear(bool doSimulated = true, bool doStatic = true);
  static void step(unsigned int i);

  static void update(bool forceSpaceVis = false);

  //BodyManager.cpp
  static void SpawnBurst(const Vec2& _pos, float _force);

  static void CreateSimulated();
  static void DeleteSimulated(int index = -1);

  static void CreateBody(const Vec2& position, float mass);
  static void DeleteBody();

  //Physics.cpp
  static const Vec2 GetVelocity(int index, const Vec2& p);
};