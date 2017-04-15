#include "window.hpp"
#include <iostream>

bool cWindow::init( void )
{
  glfwInit();
  glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
  glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
  glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
  glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );

  glfwWindow = glfwCreateWindow( static_cast<int>( width ), static_cast<int>( height ), "LearnOpenGL", nullptr, nullptr );
  if ( glfwWindow == nullptr )
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return false;
  }
  glfwMakeContextCurrent( glfwWindow );

  glewExperimental = GL_TRUE;
  if ( glewInit() != GLEW_OK )
  {
    std::cout << "Failed to initialize GLEW" << std::endl;
    return false;
  }

  const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
  const GLubyte* version = glGetString(GL_VERSION); // version as a string
  printf("Renderer: %s\n", renderer);
  printf("OpenGL version supported %s\n", version);

  int loc_width, loc_height;
  glfwGetFramebufferSize( glfwWindow, &loc_width, &loc_height );

  glViewport( 0, 0, loc_width, loc_height );

  glEnable(GL_DEPTH_TEST); // enable depth-testing
  glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

  glfwSetWindowUserPointer( glfwWindow, this );

  auto func = []( GLFWwindow * arg_window, int arg_key, int arg_scancode, int arg_action, int arg_mode )
  {
    static_cast<cWindow*>( glfwGetWindowUserPointer( arg_window ) )->inputCallback( arg_window, arg_key, arg_scancode, arg_action, arg_mode );
  };

  //auto func = []() { cout << "Hello world"; };
  /*glfwSetKeyCallback( glfwWindow, inputCallback );*/
  glfwSetKeyCallback( glfwWindow, func );

  //glfwSetWindowUserPointer(glfwWindow, myWindow);

  //auto func = [](GLFWwindow* w, int, int, int)
  //{
  //  static_cast<MyGlWindow*>(glfwGetWindowUserPointer(w))->mouseButtonPressed( /* ... */ );
  //}

  //glfwSetMouseButtonCallback(glfwWindow, func);



  //glfwSetMouseButtonCallback(glfwWindow, func);

  initObjects();

  return true;
}

void cWindow::initObjects( void )
{
  for ( auto loc_pObj : gameObjects ) 
  {
    loc_pObj->init();
  }
}

void cWindow::update( void )
{
  while ( !glfwWindowShouldClose( glfwWindow ) )
  {
    glfwPollEvents();

    // rendeeer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    for ( auto loc_pObj : gameObjects )
    {
      loc_pObj->draw();
    }

    glfwSwapBuffers( glfwWindow );
  }

  glfwTerminate();
}

void cWindow::inputCallback( GLFWwindow * arg_window, int arg_key, int arg_scancode, int arg_action, int arg_mode )
{
  // When a user presses the escape key, we set the WindowShouldClose property to true, 
  // closing the application

  switch( arg_key )
  {
    case GLFW_KEY_ESCAPE: 
    {
      if ( arg_action == GLFW_PRESS )
      {
        glfwSetWindowShouldClose( arg_window, GL_TRUE );
      }
      break;
    }
    case GLFW_KEY_UP:
    {
      auto loc_y = gameObjects.front()->getY();
      gameObjects.front()->setY( loc_y + 0.01 );
      break;
    }
    case GLFW_KEY_DOWN:
    {
      auto loc_y = gameObjects.front()->getY();
      gameObjects.front()->setY( loc_y - 0.01 );
      break;
    }
    default:
    {

    }
  } 
}