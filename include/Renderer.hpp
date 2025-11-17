#pragma once

#include <string>
using string = std::string;
#include <SFML/Graphics.hpp>

#include <System/Vec2.hpp>
#include <System/Rect.hpp>

using VertexArray = sf::VertexArray;
using Color = sf::Color;


class Renderer {
public:
  static sf::RenderWindow* window;
  static const string windowName;
  static Vec2 windowSize;

  static float WorldToScreenScale;
  static float WorldZoom;

  static Vec2 windowCenter;
  static Vec2 cameraPosition;

  static sf::VertexArray starShape;
  static Color StarColor;

  static Color SlowColor;
  static Color FastColor;
  static float VelocitySensitivity;

  static Color SpaceGridColor;


  static void init();
  static void update();
  static void draw();


  static inline const bool InWindow(const Vec2& pos) {
    return !(pos.x < 0 || pos.x > windowSize.x || pos.y < 0 || pos.y >= windowSize.y);
  }
  static inline const Vec2 WorldToScreen(const Vec2& world) {
    return windowCenter + Vector2f(world.x-cameraPosition.x, -world.y+cameraPosition.y) * WorldToScreenScale;
  }
  static inline const Vec2 ScreenToWorld(const Vec2& screen) {
    const Vec2 val = (screen-windowCenter) / WorldToScreenScale;
    return Vec2(val.x,-val.y)+cameraPosition;
  }
};