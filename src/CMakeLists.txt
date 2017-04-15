#SRC

include_directories ( 
  ${PROJECT_SOURCE_DIR}/include/
  ${PROJECT_SOURCE_DIR}/lib/glfw/include
  ${PROJECT_SOURCE_DIR}/lib/glew-2.0.0/include
)

#find_package (Threads REQUIRED)

set (
  pong_include_dir 
  ${PROJECT_SOURCE_DIR}/include/
)

set (
  pong_headers
  ${pong_include_dir}/object.hpp
  ${pong_include_dir}/pad.hpp
  ${pong_include_dir}/window.hpp
  ${pong_include_dir}/game.hpp
)

set (
  pong_src
  main.cpp
  pad.cpp
  window.cpp
  game.cpp
)

add_executable ( 
  pong
  ${pong_src}
  ${pong_headers}
) 

target_compile_features( 
  pong PRIVATE 
  cxx_auto_type 
  cxx_nullptr 
  cxx_lambdas 
)

set (
  glew_lib
  ${PROJECT_SOURCE_DIR}/lib/glew-2.0.0/lib/Release/Win32/glew32s.lib
)

find_package(OpenGL REQUIRED)

#find_library(glew_lib ${PROJECT_SOURCE_DIR}/lib/glew-2.0.0/lib/Release/x64/glew32s.lib)

target_link_libraries ( 
  pong 
  ${CMAKE_THREAD_LIBS_INIT}
  glfw 
  ${GLFW_LIBRARIES}
  ${glew_lib}
  ${OPENGL_gl_LIBRARY}
 )