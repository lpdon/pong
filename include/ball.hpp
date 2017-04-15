#ifndef BALL_HPP
#define BALL_HPP

#include "object.hpp"

class cBall : public cObject
{
private:
  bool stateUp, stateRight;
  int speedX, speedY;

public:
  explicit cBall( int arg_x, int arg_y, int arg_width, int arg_height )
  : cObject( arg_x, arg_y, arg_width, arg_height )
  , stateUp( true )
  , speedX( 1 )
  , speedY( 1 )
  {
  
  }

  virtual void init( void );
  virtual void update( void );
  virtual void draw( void ); 
};

#endif