#ifndef _Player_
#define _Player_

#include "I_GameObject.h"
#include "GameObject.h"
#include "Game.h"
#include "Vector2D.h"
#include "InputHandler.h"
#include "PlayerProjectile.h";

#include <iostream>

class Player : public GameObject {

public:
  Player(int x, int y, unsigned p_numFrames, unsigned p_currentRow, unsigned p_currentFrame);

  virtual void update();
  virtual void draw();
  virtual void clean();
  void handleInput();
  
public:

  PlayerProjectile* bullet;

};

#endif
