#include "pad.hpp"
#include "game.hpp"

#include "zmq.hpp"
#include <string>
#include <iostream>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>

#define sleep(n)	Sleep(n)
#endif

void cPad::init( void )
{
  // https://open.gl/drawing

  // Shader sources
  const GLchar* vertexSource = R"glsl(
    #version 150 core
    in vec2 position;
    in vec3 color;
    out vec3 Color;
    void main()
    {
        Color = color;
        gl_Position = vec4(position, 0.0, 1.0);
    }
)glsl";

  const GLchar* fragmentSource = R"glsl(
    #version 150 core
    in vec3 Color;
    out vec4 outColor;
    void main()
    {
        //outColor = vec4(Color, 1.0);
        outColor = vec4(0.5, 0.0, 0.5, 1.0);
    }
)glsl";

  // Create Vertex Array Object
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  vertexArray = vao;

  // Create a Vertex Buffer Object and copy the vertex data to it
  GLuint vbo;
  glGenBuffers(1, &vbo);
  vertexBuffer = vbo;

  const GLfloat loc_x = static_cast<GLfloat>( x )/static_cast<GLfloat>( cGame::SCALE );
  const GLfloat loc_y = static_cast<GLfloat>( y )/static_cast<GLfloat>( cGame::SCALE );
  const GLfloat loc_width = static_cast<GLfloat>( width )/static_cast<GLfloat>( cGame::SCALE );
  const GLfloat loc_height = static_cast<GLfloat>( height )/static_cast<GLfloat>( cGame::SCALE );

  const GLfloat vertices[] =
  {
    loc_x,             loc_y,               0.0f, 0.0f, 0.0f, // Top-left
    loc_x,             loc_y + loc_height,  0.0f, 1.0f, 0.0f, // Top-right
    loc_x + loc_width, loc_y + loc_height,  0.0f, 0.0f, 1.0f, // Bottom-right
    loc_x + loc_width, loc_y,               0.0f, 1.0f  // Bottom-left
  };

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Create an element array
  GLuint ebo;
  glGenBuffers(1, &ebo);

  const GLuint elements[] = 
  {
    0, 1, 2,
    2, 3, 0
  };

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

  // Create and compile the vertex shader
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  glCompileShader(vertexShader);

  // Create and compile the fragment shader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
  glCompileShader(fragmentShader);

  // Link the vertex and fragment shader into a shader program
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glBindFragDataLocation(shaderProgram, 0, "outColor");
  glLinkProgram(shaderProgram);
  glUseProgram(shaderProgram);

  // Specify the layout of the vertex data
  GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

  //GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
  //glEnableVertexAttribArray(colAttrib);
  //glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
}

void cPad::update( void )
{
  if ( stateUp )
  {
    const int loc_posTest = y + speedY + height; 

    if ( loc_posTest < ref_ball.getY() )
    {
      y += speedY;
    }
    else
    {
      stateUp = false;
    }
  }
  else
  {
    const int loc_posTest = y - speedY; 

    if ( loc_posTest > ref_ball.getY() )
    {
      y -= speedY;
    }
    else
    {
      stateUp = true;
    }
  }
}

void cPad::draw( void )
{
  glUseProgram( shaderProgram );
  glBindVertexArray( vertexArray );
  
  const GLfloat loc_x = static_cast<GLfloat>( x )/static_cast<GLfloat>( cGame::SCALE );
  const GLfloat loc_y = static_cast<GLfloat>( y )/static_cast<GLfloat>( cGame::SCALE );
  const GLfloat loc_width = static_cast<GLfloat>( width )/static_cast<GLfloat>( cGame::SCALE );
  const GLfloat loc_height = static_cast<GLfloat>( height )/static_cast<GLfloat>( cGame::SCALE );

  const GLfloat vertices[] =
  {
    loc_x,             loc_y,               0.0f, 0.0f, 0.0f, // Top-left
    loc_x,             loc_y + loc_height,  0.0f, 1.0f, 0.0f, // Top-right
    loc_x + loc_width, loc_y + loc_height,  0.0f, 0.0f, 1.0f, // Bottom-right
    loc_x + loc_width, loc_y,               0.0f, 1.0f  // Bottom-left
  };

  glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
  glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

  // draw points 0-3 from the currently bound VAO with current in-use shader
  //glDrawArrays( GL_TRIANGLES, 0, 6 );
  glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
}

void cPlayerPad::init( void )
{
  cPad::init();
  socketThread = std::thread( [ this ] { remoteControl(); } );
}

void cPlayerPad::keyInputCallback( int arg_key, int arg_scancode, int arg_action, int arg_mode )
{
  switch( arg_key )
  {
    case GLFW_KEY_UP:
    {
      //if ( arg_action == GLFW_PRESS )
      {        
        moveUp();
      }
      break;
    }
    case GLFW_KEY_DOWN:
    {
      //if ( arg_action == GLFW_PRESS )
      {
        moveDown();
      }      
      break;
    }
    default:
    {

    }
  } 
}

void cPlayerPad::remoteControl( void )
{
  zmq::context_t context ( 1 );
  zmq::socket_t socket ( context, ZMQ_REP );
  socket.bind ( "tcp://*:5555" );

  while ( true ) {
    zmq::message_t loc_request;

    //  Wait for next request from client
    socket.recv ( &loc_request );
    std::string loc_msg = std::string( static_cast<char *>( loc_request.data() ), loc_request.size() );
    std::cout << "Received " << loc_msg << std::endl;

    struct posData
    {
      int ballPos[ 2U ];
      int padPos[ 2U ];
    };

    posData loc_data { ref_ball.getX(), ref_ball.getY(), this->x, this->y };

    //  Send reply back to client
    zmq::message_t reply( sizeof( loc_data ) );
    memcpy ( reply.data (), &loc_data, sizeof( loc_data ) );

    socket.send (reply);

    zmq::message_t loc_cmd;
    socket.recv( &loc_cmd );
    loc_msg = std::string( static_cast<char *>( loc_cmd.data() ), loc_cmd.size() );

    if ( loc_cmd.size() == 2U )
    {
      this->moveUp();
    }
    else
    {
      this->moveDown();
    }

    socket.send (reply); // dummy
  }
}