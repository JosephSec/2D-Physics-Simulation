#pragma once

#include <SFML/Window/Event.hpp>

#include <System/Vec2.hpp>

using Event = sf::Event;
namespace Keyboard = sf::Keyboard;
namespace Mouse = sf::Mouse;


enum ForceState {
  Negative = -1,
  Off = 0,
  Positive = 1
};

class User {
public:
  static ForceState cursorForce;
  static float cursorMass;

  static Vec2 mousePos;
  static Vec2 mouseDelta;
  static Vec2 WorldMousePos;

  static bool focused;

  static bool controlPressed;


  static void handle(const Event& event);

  static void update();
};