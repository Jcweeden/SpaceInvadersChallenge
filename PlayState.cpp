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

PlayState::PlayState() //1000 in ms
    : player(nullptr), invaders(nullptr), levelNumber(1), timeBetweenInvadersMove(1000), lastFrameTicks(0)
{
  TheTextureManager::Instance()->load("Assets/spaceInvaderSprites.png", "spaceInvaders", TheGame::Instance()->getRenderer());

  setupLevel();
}

void PlayState::setupLevel()
{
  clean();
  player = new Player(32,450,1,9,0);
  invaders = new Invaders(levelNumber, player->getPosition().getY());
  countDownTimerToNextInvadersMove = timeBetweenInvadersMove = 1000;
}

void PlayState::update()
{
  invaders->update();
  player->update();

  countDownTimerToNextInvadersMove -= SDL_GetTicks() - lastFrameTicks;
  
  //if has surpassed time
  if (countDownTimerToNextInvadersMove <= 0)
  {
    invaders->moveInvaders();

    countDownTimerToNextInvadersMove = timeBetweenInvadersMove;
  }
  lastFrameTicks = SDL_GetTicks();
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
  if (invaders != nullptr)
  {
    invaders->clean();
    delete invaders;
  }
  
  if (player != nullptr) delete player;
}
