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
    : score(0), highScore(0), player(nullptr), invaders(nullptr), levelNumber(1), timeBetweenInvadersMove(1000), lastFrameTicks(0), gameOver(false), playerMovementDisabled(false)
{
  TheTextureManager::Instance()->load("Assets/spaceInvaderSprites.png", "spaceInvaders", TheGame::Instance()->getRenderer());

  setupLevel();
}

void PlayState::setupLevel()
{
  gameOver = false;
  playerMovementDisabled = false;
  score = 0;
  clean();
  player = new Player(32,450,1,9,0);
  invaders = new Invaders(levelNumber, player->getPosition().getY());
  countDownTimerToNextInvadersMove = timeBetweenInvadersMove = 1000;
}

void PlayState::lostGame()
{
  if (score > highScore) highScore = score;
  levelNumber = 1;
  setupLevel();
}

void PlayState::update()
{
  if (gameOver)
    lostGame();
  
  countDownTimerToNextInvadersMove -= SDL_GetTicks() - lastFrameTicks;
  
  //if has surpassed time
  if (countDownTimerToNextInvadersMove <= 0)
  {
    if (!gameOver)
      invaders->moveInvaders();

    countDownTimerToNextInvadersMove = timeBetweenInvadersMove;
  }
  player->update();
  
  invaders->update();
  
  lastFrameTicks = SDL_GetTicks();
}

void PlayState::render()
{
  if (invaders != nullptr)
    invaders->draw();

  if (player != nullptr)
    player->draw();
}


void PlayState::handleInput()
{
  if (!playerMovementDisabled)
    player->handleInput();
}

void PlayState::clean()
{
  if (invaders != nullptr)
  {
    invaders->clean();
    delete invaders;
  }
  
  if (player != nullptr)
  {
    player->clean();
    delete player;
  }
}


void PlayState::updateGameSpeed()
{
  timeBetweenInvadersMove = 50 + (950 / 55) * (invaders->numInvadersRemaining + invaders->numInvadersRemaining/5);
}


void PlayState::addScore(unsigned val)
{
  score += val;
}

