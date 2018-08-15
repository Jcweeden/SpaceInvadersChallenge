#include "PlayerProjectile.h"


PlayerProjectile::PlayerProjectile(int x, int y)
    :Projectile(x,y,1,10,0,-5.0f), toBeDeleted(false)
{
  
}

void PlayerProjectile::update()
{
  GameObject::update();

  if (position.getY() < 100) toBeDeleted = true;
}
