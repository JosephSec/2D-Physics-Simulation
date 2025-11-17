#pragma once

#include <sstream>
#include <string>
#include <iostream>

using string = std::string;


class Debug {
public:
  static inline void log() {
    std::cout << '\n';
  }

  static inline const string BoolStr(bool val) {
    return val? "True" : "False";
  }

  static void log(const string& debug, bool line = true) {
    std::cout << debug;
    if(line) log();
  }

  template <typename T>
  static void log(const string& debug, const T& val, bool line = true) {
    std::ostringstream out;
    out << debug << ": " << val;
    std::cout << out.str();
    if(line) log();
  }


  static void error(const string& debug) {
    std::cout << "[Error] " << debug << '\n';
  }
};