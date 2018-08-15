#ifndef _Barricade_
#define _Barricade_

#include "Game.h"
#include "Vector2D.h"
#include "InputHandler.h"

#include <iostream>
#include <vector>

class BarricadeBlock;

class Barricade {

public:
  Barricade(int x, int y);

  void setupBarricade();
  
  void draw();

  void setX(int p_x) { posX = p_x; }
  void setY(int p_y) { posY = p_y; }
  
public:
  std::vector<std::vector<BarricadeBlock*> > blocks;

  unsigned posX, posY;
  unsigned blockWidth, blockHeight;
};

#endif
