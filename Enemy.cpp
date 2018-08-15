#include "Enemy.h"


Enemy::Enemy(int x, int y, unsigned p_numFrames, unsigned p_currentRow, unsigned p_currentFrame)
    : GameObject::GameObject(x,y,32,32,"spaceInvaders",p_numFrames,p_currentRow,p_currentFrame)
{

}

void Enemy::update()
{

}

void Enemy::draw()
{
  GameObject::draw();
}
