#include "BarricadeBlock.h"

BarricadeBlock::BarricadeBlock(int x, int y)
    : GameObject::GameObject(x,y,5,5,"barricade",1,1,0), health(100)
{
}

void BarricadeBlock::draw()
{
  GameObject::draw();
}
