#ifndef PAD_HPP
#define PAD_HPP

#include "object.hpp"
#include "ball.hpp"
#include <thread>

class cPad : public cObject
{
private:
  bool stateUp;

protected:
  int speedY;
  const cBall& ref_ball;

public:
  explicit cPad( int arg_x, int arg_y, int arg_width, int arg_height, const cBall& arg_ref_ball )
  : cObject( arg_x, arg_y, arg_width, arg_height )
  , stateUp( true )
  , speedY( 2 )
  , ref_ball( arg_ref_ball )
  {

  }

  virtual void init( void );
  virtual void update( void );
  virtual void draw( void );  

  virtual void collision( void )
  {
  
  }

  virtual void reset( void )
  {

  }
};

class cPlayerPad : public cPad
{
private:
  std::thread socketThread;

  void remoteControl( void );

public:
  explicit cPlayerPad( int arg_x, int arg_y, int arg_width, int arg_height, const cBall& arg_ref_ball )
  : cPad( arg_x, arg_y, arg_width, arg_height, arg_ref_ball )
  {

  }

  virtual void init( void );

  virtual void update( void )
  {
    // do nothing...
  }

  virtual void keyInputCallback( int arg_key, int arg_scancode, int arg_action, int arg_mode );

  inline void moveUp( void )
  {
    y += speedY;
  }

  inline void moveDown( void )
  {
    y -= speedY;
  }
};


#endif
