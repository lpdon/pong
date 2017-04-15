#include "game.hpp"

cGame::cGame( void )
  : gameObjects()
  , gameWindow( 800U, 600U, gameObjects )
{
  std::unique_ptr<cObject> loc_pPlayerPad( new cPlayerPad( -1.0F, 0.0F, 0.1F, 0.5F ) );
  std::unique_ptr<cObject> loc_pPad( new cPad( 0.9F, 0.0F, 0.1F, 0.5F ) );
  //std::unique_ptr<cObject> loc_pObj( make_unique<> cPlayerPad( 0, 0, 0.5, 0.5 ) );
  gameObjects.push_back( std::move( loc_pPlayerPad ) );
  gameObjects.push_back( std::move( loc_pPad ) );
  //std::shared_ptr<cObject> loc_pObj( &playerPad );
  //gameObjects.push_back( loc_pObj );

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