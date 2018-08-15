#include "PlayState.h"

#include "Game.h"
#include "Player.h"


PlayState* PlayState::s_pInstance = 0;

PlayState* PlayState::Instance()
{
  if (s_pInstance == 0)
  {
    s_pInstance = new PlayState();
    return s_pInstance;
  }

  return s_pInstance;
}

PlayState::PlayState()
    // :
{
  std::cout << "run\n";

  TheTextureManager::Instance()->load("Assets/spaceInvaderSprites.png", "spaceInvaders", TheGame::Instance()->getRenderer());
  
  player = new Player(32,400,1,9,0);
}

void PlayState::update()
{
  player->update();
}

void PlayState::render()
{
  player->draw();
}


void PlayState::handleInput()
{

  player->handleInput();

}

void PlayState::clean()
{

  delete player;
  
}
