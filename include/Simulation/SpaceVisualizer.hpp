#pragma once

#include <vector>

#include <System/Vec2.hpp>

#include <SFML/Graphics/VertexArray.hpp>


class SpaceVisualizer {
public:
  static void update(bool values = true);

  static void resize(int x, int y);

  static bool DoUpdate();


  static bool IsActive;

  static Vec2 sampleGrid;
  static int resolution;
  static float sensitivity;

  static sf::VertexArray gridShape;
  

private:
  static const Vec2 GetSamplePoint(int x, int y);
  static const Vec2 SampleSpace(Vec2 world);
};