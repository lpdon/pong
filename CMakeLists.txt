cmake_minimum_required (VERSION 2.6)

if ( UNIX )
set ( CMAKE_C_COMPILER gcc )
set ( CMAKE_CXX_COMPILER g++ )
set ( CMAKE_BUILD_TYPE Debug )
set ( CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread" )

add_definitions( "-DHAVE_STRUCT_TIMESPEC -Wall -pthread" )
endif ()

project ( pong C CXX )

add_subdirectory ( ${PROJECT_SOURCE_DIR}/lib/glfw/ )  

add_subdirectory ( src )