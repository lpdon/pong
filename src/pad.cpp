#include "pad.hpp"

void cPad::init( void )
{
  const GLfloat loc_x = static_cast<GLfloat>( x );
  const GLfloat loc_y = static_cast<GLfloat>( y );

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

  //GLfloat vertices[] = {
  //  -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-left
  //  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top-right
  //  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
  //  -0.5f, -0.5f, 1.0f, 1.0f, 1.0f  // Bottom-left
  //};

  const GLfloat vertices[] = {
    x,         y,           0.0f, 0.0f, 0.0f, // Top-left
    x,         y + height,  0.0f, 1.0f, 0.0f, // Top-right
    x + width, y + height,  0.0f, 0.0f, 1.0f, // Bottom-right
    x + width, y,           0.0f, 1.0f  // Bottom-left
  };

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Create an element array
  GLuint ebo;
  glGenBuffers(1, &ebo);

  const GLuint elements[] = {
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

}

void cPad::draw( void )
{
  glUseProgram( shaderProgram );
  glBindVertexArray( vertexArray );
  
  const GLfloat vertices[] = {
    x,         y,           0.0f, 0.0f, 0.0f, // Top-left
    x,         y + height,  0.0f, 1.0f, 0.0f, // Top-right
    x + width, y + height,  0.0f, 0.0f, 1.0f, // Bottom-right
    x + width, y,           0.0f, 1.0f  // Bottom-left
  };

  glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
  glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

  // draw points 0-3 from the currently bound VAO with current in-use shader
  //glDrawArrays( GL_QUADS, 0, 4 );
  //glDrawArrays( GL_TRIANGLES, 0, 6 );
  glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
}

GLuint cPad::getVertexArray( void )
{
  return this->vertexArray;
}

GLuint cPad::getShaderProgram( void )
{
  return this->shaderProgram;
}
