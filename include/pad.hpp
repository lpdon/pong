#ifndef PAD_HPP
#define PAD_HPP

#include "object.hpp"

class cPad : public cObject
{
private:
  bool stateUp;

protected:
  int speedY;

public:
  explicit cPad( int arg_x, int arg_y, int arg_width, int arg_height )
  : cObject( arg_x, arg_y, arg_width, arg_height )
  , stateUp( true )
  , speedY( 2 )
  {

  }

  virtual void init( void );
  virtual void update( void );
  virtual void draw( void );  

  virtual void collision( void )
  {
  
  }
};

class cPlayerPad : public cPad
{
public:
  explicit cPlayerPad( int arg_x, int arg_y, int arg_width, int arg_height )
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
