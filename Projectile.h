#ifndef _Projectile_
#define _Projectile_

#include "I_GameObject.h"
#include "GameObject.h"
#include "Game.h"
#include "Vector2D.h"

#include <iostream>


class Projectile : public GameObject {

public:

  Projectile(int x, int y, unsigned p_numFrames, unsigned p_currentRow, unsigned p_currentFrame, float p_projectileVelocityY);
  
public:


};

#endif
