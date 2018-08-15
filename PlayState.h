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

class PlayState {

public:
  static PlayState* Instance();

  PlayState();

  void update();
  void render();
  void handleInput();

  void clean();

  void setupLevel();
  
public:

  unsigned levelNumber;
  
  Player* player;
  Invaders* invaders;

  int countDownTimerToNextInvadersMove;
  unsigned timeBetweenInvadersMove;
  unsigned lastFrameTicks;

private:

  static PlayState* s_pInstance;

};

typedef PlayState ThePlayState;

#endif
