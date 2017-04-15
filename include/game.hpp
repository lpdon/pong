#ifndef GAME_HPP
#define GAME_HPP

#include "window.hpp"
#include "object.hpp"
#include "pad.hpp"
#include "ball.hpp"

#include <vector>
#include <memory>

class cGame 
{
private:
  std::vector<std::unique_ptr<cObject>> gameObjects;
  cWindow gameWindow;

  void initObjects( void );
  void updateObjects( void );
  void checkCollisions( void );

public:
  static const int MIN_X, MAX_X;
  static const int MIN_Y, MAX_Y;
  static const int SCALE;

  cGame( void );
  void run( void );
};

#endif