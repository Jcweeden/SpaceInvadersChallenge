#ifndef _Invaders_
#define _Invaders_


#include "Enemy.h"
#include "Game.h"
#include "Vector2D.h"

#include <vector>
#include <iostream>

class Invaders {

public:
  Invaders(unsigned rowNumber);
  
  void update();
  void draw();
  void clean();

  void setupInvaders(unsigned startingRow);
  
public:

  std::vector<std::vector<Enemy*> > invaders;

  //shiftDownBy is val invaders will shift down once reaching edge of screen
  unsigned shiftDownBy;
  
};

#endif
