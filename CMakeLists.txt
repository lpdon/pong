cmake_minimum_required (VERSION 2.6)

if ( UNIX )
enable_testing()
endif ()

if ( UNIX )
set ( CMAKE_C_COMPILER gcc )
set ( CMAKE_CXX_COMPILER g++ )
set ( CMAKE_BUILD_TYPE Debug )
set ( CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread" )

add_definitions( "-DHAVE_STRUCT_TIMESPEC -Wall -pthread" )
endif ()

project ( pong C CXX )


#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_BINARY_DIR}/bin")
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_BINARY_DIR}/bin")

add_subdirectory ( ${PROJECT_SOURCE_DIR}/lib/glfw/ )  

add_subdirectory ( src )

#add_custom_target(
#  build_glew ALL
#  COMMAND ${CMAKE_MAKE_PROGRAM}
#  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/glew/
#  COMMENT "Build GLEW"
#)

if ( UNIX )
#add_subdirectory ( ${QUEUE_SOURCE_DIR}/lib/googletest/googletest/ )
#add_subdirectory ( test )
#add_test (NAME ut COMMAND run_test WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)
endif ()