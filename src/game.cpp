#include "game.hpp"

const int cGame::MIN_X = -100;
const int cGame::MIN_Y = -100;
const int cGame::MAX_X =  100;
const int cGame::MAX_Y =  100;
const int cGame::SCALE =  100;

cGame::cGame( void )
  : gameObjects()
  , gameWindow( 800U, 800U, gameObjects )
{
  std::unique_ptr<cObject> loc_pPlayerPad( new cPlayerPad( MIN_X, 0, 10, 50 ) );
  std::unique_ptr<cObject> loc_pPad( new cPad( MAX_X - 10, 0, 10, 50 ) );
  std::unique_ptr<cObject> loc_pBall( new cBall( 0, 50, 10, 10 ) );

  gameObjects.push_back( std::move( loc_pPlayerPad ) );
  gameObjects.push_back( std::move( loc_pPad ) );
  gameObjects.push_back( std::move( loc_pBall ) );

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
  for ( int i = 0; i < gameObjects.size(); ++i )
  {
    for ( int j = i + 1; j < gameObjects.size(); ++j )
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

  for ( auto& loc_pObj : gameObjects ) 
  {
    loc_pObj->update();
  }
}