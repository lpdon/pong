#ifndef PAD_HPP
#define PAD_HPP

#include "object.hpp"

class cPad : public cObject
{
private:
  bool state_up;

protected:
  float speedY;

public:
  explicit cPad( float arg_x, float arg_y, float arg_width, float arg_height )
  : cObject( arg_x, arg_y, arg_width, arg_height )
  , state_up( true )
  , speedY( 0.2F )
  {

  }

  virtual void init( void );
  virtual void update( void );
  virtual void draw( void );  
};

class cPlayerPad : public cPad
{
public:
  explicit cPlayerPad( float arg_x, float arg_y, float arg_width, float arg_height )
  : cPad( arg_x, arg_y, arg_width, arg_height )
  {

  }

  virtual void update( void )
  {
    // do nothing...
  }

  virtual void keyInputCallback( int arg_key, int arg_scancode, int arg_action, int arg_mode );
};


#endif
