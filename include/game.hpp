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
  cPlayerPad playerPad;
  cPad botPad;
  cBall ball;

  void initObjects( void );
  void updateObjects( void );
  void checkCollisions( void );
  void resetObjects( void );
  void remotePad( void );

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