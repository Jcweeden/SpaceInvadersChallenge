#ifndef _Saucer_
#define _Saucer_

#include "I_GameObject.h"
#include "GameObject.h"
#include "Enemy.h"
#include "Game.h"
#include "Vector2D.h"
#include "InputHandler.h"

#include <iostream>

class Saucer : public Enemy {

public:
  Saucer(int x, int y, bool p_moveLeft);

  virtual void update();
  virtual void draw();
  
public:

  bool moveLeft;
  bool toBeDeleted;
  
};

#endif
