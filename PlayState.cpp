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

  initText();
  
  TheTextureManager::Instance()->load("Assets/spaceInvaderSprites.png", "spaceInvaders", TheGame::Instance()->getRenderer());

  setupLevel();
}

void PlayState::setupLevel()
{
  gameOver = false;
  playerMovementDisabled = false;
  score = 0;
  addScore(0); //reset score text
  clean();
  player = new Player(80,441,1,9,0);
  invaders = new Invaders(levelNumber, player->getPosition().getY());
  countDownTimerToNextInvadersMove = timeBetweenInvadersMove = 1000;
}

void PlayState::lostGame()
{
  if (score > highScore) highScore = score;
  updateHighScoreText();
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
  //green line across bottom
  lineRGBA(TheGame::Instance()->getRenderer(),
           32, 477,
           480, 477,
           52, 252, 60, 255);
  lineRGBA(TheGame::Instance()->getRenderer(),
           32, 478,
           480, 478,
           52, 252, 60, 255);
  
  if (invaders != nullptr)
    invaders->draw();

  if (player != nullptr)
    player->draw();

  //text

  SDL_RenderCopy(TheGame::Instance()->getRenderer(), scoreLabelText, NULL, &scoreLabelRect); 
  SDL_RenderCopy(TheGame::Instance()->getRenderer(), scoreText, NULL, &scoreRect);
  SDL_RenderCopy(TheGame::Instance()->getRenderer(), highscoreLabelText, NULL, &highscoreLabelRect); 
  SDL_RenderCopy(TheGame::Instance()->getRenderer(), highscoreText, NULL, &highscoreRect);
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

  //text
  /*
  if( scoreText != NULL ) SDL_DestroyTexture( scoreText );
  if( scoreLabelText != NULL ) SDL_DestroyTexture( scoreLabelText );
  if( highscoreText != NULL ) SDL_DestroyTexture( highscoreText );
  if( highscoreLabelText != NULL ) SDL_DestroyTexture( highscoreLabelText );
  */
}


void PlayState::updateGameSpeed()
{
  timeBetweenInvadersMove = 50 + (950 / 55) * (invaders->numInvadersRemaining + invaders->numInvadersRemaining/5);
}


void PlayState::addScore(unsigned val)
{
  score += val;

  if( scoreText != NULL ) SDL_DestroyTexture( scoreText );
  
  std::string scoreStr = std::to_string(score);
  
  if (score < 10)
    scoreStr.insert(0,"000");
  else if (score < 100)
    scoreStr.insert(0,"00");
  else if (score < 1000)
    scoreStr.insert(0,"0");
  
  scoreMessage = TTF_RenderText_Blended(fontTTF,
                                        scoreStr.c_str(),
                                        textColour);
  scoreText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), scoreMessage);
  SDL_FreeSurface( scoreMessage );
}

void PlayState::updateHighScoreText()
{
  if( highscoreText != NULL ) SDL_DestroyTexture( highscoreText );
  
  std::string scoreStr = std::to_string(highScore);
  
  if (highScore < 10)
    scoreStr.insert(0,"000");
  else if (highScore < 100)
    scoreStr.insert(0,"00");
  else if (highScore < 1000)
    scoreStr.insert(0,"0");
  
  highscoreMessage = TTF_RenderText_Blended(fontTTF,
                                        scoreStr.c_str(),
                                        textColour);
  highscoreText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), highscoreMessage);
  SDL_FreeSurface( highscoreMessage );
}

void PlayState::initText()
{

  if(TTF_Init()==-1) {
    printf("TTF_Init: %s\n", TTF_GetError());
    exit(2);
  }
  
  fontTTF = TTF_OpenFont("Assets/space_invaders.ttf", 48);
  if (fontTTF == NULL) {
    fprintf(stderr, "error: font not found\n");
  }

  scoreMessage = TTF_RenderText_Solid(fontTTF, "0000", textColour);
  scoreText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), scoreMessage); 
  scoreRect.x = 65;
  scoreRect.y = 55;
  scoreRect.w = 80; 
  scoreRect.h = 30;

  scoreLabelMessage = TTF_RenderText_Solid(fontTTF, " YOUR-SCORE ", textColour);
  scoreLabelText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), scoreLabelMessage); 
  scoreLabelRect.x = 15;
  scoreLabelRect.y = 15;
  scoreLabelRect.w = 180;
  scoreLabelRect.h = 30;

  highscoreMessage = TTF_RenderText_Solid(fontTTF, "0000", textColour);
  highscoreText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), scoreMessage); 
  highscoreRect.x = 360;
  highscoreRect.y = 55;
  highscoreRect.w = 80; 
  highscoreRect.h = 30;

  highscoreLabelMessage = TTF_RenderText_Solid(fontTTF, "HIGH-SCORE", textColour);
  highscoreLabelText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), highscoreLabelMessage); 
  highscoreLabelRect.x = 310;
  highscoreLabelRect.y = 15;
  highscoreLabelRect.w = 180;
  highscoreLabelRect.h = 30;
}
