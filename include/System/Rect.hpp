#pragma once

#include <System/Vec2.hpp>


struct Rect {
public:
  float x,y,w,h;

  inline Rect(float _x = 0, float _y = 0, float _w = 0, float _h = 0) :
    x(_x), y(_y), w(_w), h(_h) {}


  inline void setPosition(const Vec2& vec) {
    x = vec.x; y = vec.y;
  }
  inline void setSize(const Vec2& vec) {
    w = vec.x; h = vec.y;
  }

  inline Vec2 getPosition() const {
    return Vec2(x,y);
  }
  inline Vec2 getSize() const {
    return Vec2(w,h);
  }

  inline bool getInBounds(const Vec2& vec) const {
    Vec2 v = vec - getPosition();
    return v.x >= 0 && v.x < w  &&
           v.y >= 0 && v.y < h;
  }

  inline friend std::ostream& operator<<(std::ostream& os, const Rect& rect) {
    os << "(" << rect.x << ", " << rect.y << ", " << rect.w << ", " << rect.h << ")";
    return os;
  }
};