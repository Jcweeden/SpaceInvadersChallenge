#ifndef _PlayerProjectile_
#define _PlayerProjectile_

#include "I_GameObject.h"
#include "GameObject.h"
#include "Projectile.h"
#include "Game.h"
#include "Vector2D.h"

#include <iostream>


class PlayerProjectile : public Projectile {

public:

  PlayerProjectile(int x, int y);

  void update();

  //no need for draw
  
public:

  bool toBeDeleted;

};

#endif
