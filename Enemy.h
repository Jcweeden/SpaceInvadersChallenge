#ifndef _Enemy_
#define _Enemy_

#include "I_GameObject.h"
#include "GameObject.h"
#include "Game.h"
#include "Vector2D.h"
#include "InputHandler.h"

#include <iostream>

class Enemy : public GameObject {

public:
  Enemy(int x, int y, unsigned p_numFrames, unsigned p_currentRow, unsigned p_currentFrame);

  virtual void update();
  virtual void draw();
  
public:

};

#endif
#ifndef _Enemy_
#define _Enemy_

#include "I_GameObject.h"
#include "GameObject.h"
#include "Game.h"
#include "Vector2D.h"
#include "InputHandler.h"

#include <iostream>

class Enemy : public GameObject {

public:
  Enemy(int x, int y, unsigned p_numFrames, unsigned p_currentRow, unsigned p_currentFrame);

  virtual void update();
  virtual void draw();
  
public:

};

#endif
