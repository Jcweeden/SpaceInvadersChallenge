#ifndef _BarricadeBlock_
#define _BarricadeBlock_

#include "I_GameObject.h"
#include "GameObject.h"
#include "Game.h"
#include "Vector2D.h"

#include <iostream>
#include <vector>

class BarricadeBlock : public GameObject {

public:
  BarricadeBlock(int x, int y);
  
  void draw();
  
public:

  int health;

};

#endif
