#include "PlayState.h"

#include "Game.h"
#include "Player.h"
#include "Invaders.h"


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
  invaders = new Invaders(1);
}

void PlayState::update()
{
  invaders->update();
  player->update();
}

void PlayState::render()
{
  invaders->draw();
  player->draw();
}


void PlayState::handleInput()
{

  player->handleInput();

}

void PlayState::clean()
{
  invaders->clean();
  delete invaders;
  
  delete player;
}
