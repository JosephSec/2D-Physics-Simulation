#pragma once

#include <SFML/System/Clock.hpp>
#include <iostream>


class CallTimer {
public:
  sf::Clock clock;

  CallTimer(bool write = false) {
    if(write) std::cout << "start...\n";
  }

  inline float end(bool micro = false) {
    if(micro) return clock.restart().asMicroseconds();
    return clock.restart().asMilliseconds() * .001f;
  }
};