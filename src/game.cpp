#include "game.hpp"

cGame::cGame( void )
  : gameObjects()
  , gameWindow( 800U, 800U, gameObjects )
  , ball( 0, 50, 10, 10 )
  , playerPad( MIN_X, 0, 2, 50, ball ) 
  , botPad( MAX_X - 2, 0, 2, 50, ball )
{
  gameObjects.push_back( &playerPad );
  gameObjects.push_back( &botPad );
  gameObjects.push_back( &ball );

  gameWindow.init();
  initObjects();
}

void cGame::initObjects( void )
{
  for ( auto& loc_pObj : gameObjects ) 
  {
    loc_pObj->init();
  }
}

void cGame::run( void )
{
  while ( gameWindow.getStatus() )
  { 
    updateObjects();
    checkCollisions();
    gameWindow.update();
  }
}

void cGame::updateObjects( void )
{
  for ( auto& loc_pObj : gameObjects ) 
  {
    loc_pObj->update();
  }
}

void cGame::checkCollisions( void )
{
  for ( unsigned int i = 0; i < gameObjects.size(); ++i )
  {
    for ( unsigned int j = i + 1; j < gameObjects.size(); ++j )
    {
      auto& loc_pObj1 = gameObjects[ i ];
      auto& loc_pObj2 = gameObjects[ j ];

      const bool loc_xCol1 = ( loc_pObj1->getX() >= loc_pObj2->getX() ) && ( loc_pObj1->getX() <= ( loc_pObj2->getX() + loc_pObj2->getWidth() ) );
      const bool loc_xCol2 = ( loc_pObj2->getX() >= loc_pObj1->getX() ) && ( loc_pObj2->getX() <= ( loc_pObj1->getX() + loc_pObj1->getWidth() ) );
      const bool loc_yCol1 = ( loc_pObj1->getY() >= loc_pObj2->getY() ) && ( loc_pObj1->getY() <= ( loc_pObj2->getY() + loc_pObj2->getHeight() ) );
      const bool loc_yCol2 = ( loc_pObj2->getY() >= loc_pObj1->getY() ) && ( loc_pObj2->getY() <= ( loc_pObj1->getY() + loc_pObj1->getHeight() ) );

      if ( ( loc_xCol1 || loc_xCol2 ) && ( loc_yCol1 || loc_yCol2 ) )
      {
        //std::cout << "kapps" << std::endl;
        loc_pObj1->collision();
        loc_pObj2->collision();
      }
    }
  }

  // out of bounds
  for ( auto& loc_pObj : gameObjects ) 
  {
    if ( ( loc_pObj->getX() < MIN_X ) || ( loc_pObj->getX() + loc_pObj->getWidth() > MAX_X ) )
    {
      loc_pObj->reset();
    }
  }
}

void cGame::resetObjects( void )
{
  for ( auto& loc_pObj : gameObjects ) 
  {
    loc_pObj->reset();
  }
}