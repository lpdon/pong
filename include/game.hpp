#ifndef GAME_HPP
#define GAME_HPP

#include "window.hpp"
#include "object.hpp"
#include "pad.hpp"

#include <vector>
#include <memory>

class cGame 
{
private:
  std::vector<std::unique_ptr<cObject>> gameObjects;
  cWindow gameWindow;

  void initObjects( void );
  void updateObjects( void );

public:
  cGame( void );
  void run( void );
};

#endif