#ifndef GAME_HPP
#define GAME_HPP

#include "window.hpp"
#include "object.hpp"
#include "pad.hpp"
#include "ball.hpp"

#include <vector>

class cGame 
{
private:
  std::vector<cObject *> gameObjects;
  cWindow gameWindow;
  cBall ball;
  cPlayerPad playerPad;
  cPad botPad;

  void initObjects( void );
  void updateObjects( void );
  void checkCollisions( void );
  void resetObjects( void );

public:
  static constexpr int MIN_X = -100;
  static constexpr int MIN_Y = -100;
  static constexpr int MAX_X =  100;
  static constexpr int MAX_Y =  100;
  static constexpr int SCALE =  100;

  cGame( void );
  void run( void );
};

#endif