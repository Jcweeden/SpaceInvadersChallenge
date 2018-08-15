#ifndef _EnemyProjectile_
#define _EnemyProjectile_

#include "I_GameObject.h"
#include "GameObject.h"
#include "Projectile.h"
#include "Game.h"


#include "Invaders.h"
#include "Vector2D.h"
#include "CollisionManager.h"

#include <iostream>

class Player;

class EnemyProjectile : public Projectile {

public:

  EnemyProjectile(int x, int y);

  void update();

  //no need for draw

  void checkForCollisions();
  
public:

  bool hitPlayer;
  
  bool toBeDeleted;

  unsigned deletionTimer;

};

#endif
