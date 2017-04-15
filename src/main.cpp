//============================================================================
// Name        : pong.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>

#include "window.hpp"
#include "pad.hpp"

using namespace std;

int main() {
  cPad pad( 0, 0, 0.5, 0.5 );

  vector<cObject *> loc_vec;
  loc_vec.push_back( &pad );

  cWindow loc_window( 800U, 600U, loc_vec );

  if ( loc_window.init() )  
  {
    loc_window.update();
  }

  //system( "PAUSE" );
	return 0;
}
