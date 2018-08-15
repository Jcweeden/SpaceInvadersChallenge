#include "Saucer.h"

Saucer::Saucer(int x, int y, bool p_moveLeft)
    : Enemy::Enemy(x,y,1,4,0), moveLeft(p_moveLeft)
{
  if (moveLeft)
    velocity.setX(-1.4f);
  else
    velocity.setX(1.4f);
}

void Saucer::update()
{
  std::cout << "X: " << getPosition().getX() << " Y: " << getPosition().getY() << "\n";
  if (!moveLeft)
  {
    if (getPosition().getX() > 512)
    {
      std::cout << "saucer to be deleted RIGHT\n";
      toBeDeleted = true;
    }
  }
  else if (moveLeft)
  {
    if (getPosition().getX() < -32)
    {
      std::cout << "saucer to be deleted LEFT\n";
      toBeDeleted = true;
    }
  }
  GameObject::update();
}

void Saucer::draw()
{
  GameObject::draw();
}
