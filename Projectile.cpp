#include "Projectile.h"

Projectile::Projectile(int x, int y, unsigned p_numFrames, unsigned p_currentRow, unsigned p_currentFrame, float p_projectileVelocityY)
    : GameObject::GameObject(x,y,32,32,"spaceInvaders",p_numFrames,p_currentRow,p_currentFrame)
{
  velocity.setY(p_projectileVelocityY);
}
