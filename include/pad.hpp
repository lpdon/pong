#ifndef PAD_HPP
#define PAD_HPP

#include "object.hpp"

class cPad : public cObject
{
private:

public:
  explicit cPad( float arg_x, float arg_y, float arg_width, float arg_height )
  : cObject( arg_x, arg_y, arg_width, arg_height )
  {
  }

  virtual void init( void );
  virtual void update( void );
  virtual void draw( void );
  virtual GLuint getVertexArray( void );
  virtual GLuint getShaderProgram( void );
};


#endif
