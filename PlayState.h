#ifndef _PlayState_
#define _PlayState_

#include "SDL2/SDL2_gfxPrimitives.h"
#include <SDL2/SDL_ttf.h>

//coll
//sound

#include "Vector2D.h"

#include <string>
#include <iostream>
#include <vector>

class GameObject;
class Player;
class Invaders;
class Barricade;

class PlayState {

public:
  static PlayState* Instance();

  PlayState();

  void update();
  void render();
  void handleInput();
  void clean();

  void initText();

  void setupLevel();
  void lostGame();
  void nextLevel();


  void updateGameSpeed();

  void addScore(unsigned val);
  void updateHighScoreText();
  
public:

  bool gameOver;
  bool playerMovementDisabled;
  unsigned levelNumber;
  unsigned score;
  unsigned highScore;
  
  Player* player;
  Invaders* invaders;
  std::vector<Barricade*> barricades;

  int countDownTimerToNextInvadersMove;
  unsigned timeBetweenInvadersMove;
  unsigned lastFrameTicks;

private:

  static PlayState* s_pInstance;


  //text
  TTF_Font* fontTTF;
  SDL_Color textColour = {255,255,255};

  SDL_Surface* scoreMessage;
  SDL_Texture* scoreText; 
  SDL_Rect scoreRect;

  SDL_Surface* scoreLabelMessage;
  SDL_Texture* scoreLabelText; 
  SDL_Rect scoreLabelRect;

  SDL_Surface* highscoreMessage;
  SDL_Texture* highscoreText; 
  SDL_Rect highscoreRect;

  SDL_Surface* highscoreLabelMessage;
  SDL_Texture* highscoreLabelText; 
  SDL_Rect highscoreLabelRect;
  
};

typedef PlayState ThePlayState;

#endif
