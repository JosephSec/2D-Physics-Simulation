#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include <System/Debug.hpp>

#include <System/Rect.hpp>


const float FIXED_TIMESTEP = 1.0f/60.0f;

class System {
public:
  static string PATH;

  static float time;
  static int FpsCounter;
  static float drawTime;
  static float moveTime;
  static float deltaTime;
  static int UsedThreads;

  static bool Paused;
  static bool WindowBounds;
  static bool EarthGravity;
  static bool IsolatedSimulation;
  static bool ScaleByWorld;
  static bool VisualizeVelocity;
  static bool MultiThreading;

  static bool FillScreen;


  static void init();
  static void update();
  static int end();
};