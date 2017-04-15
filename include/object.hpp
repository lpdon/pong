#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <inttypes.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW\glfw3.h>

class cObject
{
protected:
  float x, y;
  float width, height;
  GLuint vertexArray;
  GLuint vertexBuffer;
  GLuint shaderProgram;

  cObject( float arg_x, float arg_y, float arg_width, float arg_height )
  : x( arg_x )
  , y( arg_y )
  , width( arg_width )
  , height( arg_height )
  {

  }

public:
  virtual ~cObject()
  {

  }

  virtual void init( void ) = 0;
  virtual void update( void ) = 0;
  virtual void draw( void ) = 0;

  inline virtual void setX( float arg_x )
  {
    this->x = arg_x;
  }

  inline virtual void setY( float arg_y )
  {
    this->y = arg_y;
  }

  inline virtual float getX( void )
  {
    return x;
  }

  inline virtual float getY( void )
  {
    return y;
  }
  
  virtual void keyInputCallback( int arg_key, int arg_scancode, int arg_action, int arg_mode )
  {

  }

};



#endif
