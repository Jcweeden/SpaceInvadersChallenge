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
    : score(0), highScore(0), player(nullptr), invaders(nullptr), levelNumber(1), timeBetweenInvadersMove(1000), lastFrameTicks(0), gameOver(false)
{
  TheTextureManager::Instance()->load("Assets/spaceInvaderSprites.png", "spaceInvaders", TheGame::Instance()->getRenderer());

  setupLevel();
}

void PlayState::setupLevel()
{
  std::cout << "setupLevel()\n";
  gameOver = false;
  score = 0;
  clean();
  player = new Player(32,450,1,9,0);
  invaders = new Invaders(levelNumber, player->getPosition().getY());
  countDownTimerToNextInvadersMove = timeBetweenInvadersMove = 1000;
  std::cout << "setupLevel() complete\n";
}

void PlayState::lostGame()
{
  std::cout << "lostGame()\n";
  if (score > highScore) highScore = score;
  levelNumber = 1;
  setupLevel();
}

void PlayState::update()
{
  std::cout << "update()\n";
  
  countDownTimerToNextInvadersMove -= SDL_GetTicks() - lastFrameTicks;
  
  //if has surpassed time
  if (countDownTimerToNextInvadersMove <= 0)
  {
    if (!gameOver && invaders != nullptr)
      invaders->moveInvaders();

    countDownTimerToNextInvadersMove = timeBetweenInvadersMove;
  }

  if (invaders != nullptr)
  invaders->update();
  
  if (player != nullptr)
    player->update();
  
  lastFrameTicks = SDL_GetTicks();
  std::cout << "update() complete\n";
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
  if (!gameOver)
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

