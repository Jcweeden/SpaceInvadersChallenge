#include "CollisionManager.h"

#include <iostream>
#include "GameObject.h"
#include "Saucer.h"



CollisionManager* CollisionManager::s_pInstance = 0;

CollisionManager* CollisionManager::Instance()
  {
    if(s_pInstance == 0)
    {
      s_pInstance = new CollisionManager();
      return s_pInstance;
    }

    return s_pInstance;
  }

bool CollisionManager::isCollidingRectRect(GameObject* rectA, GameObject* rectB, int buffer)
{
  //calculate buffers that reduce the hitbox size of the rects
  int aHBuf = rectA->getHeight() / buffer;
  int aWBuf = rectA->getWidth() / buffer;
    
  int bHBuf = rectB->getHeight() / buffer;
  int bWBuf = rectB->getWidth() / buffer;
  
  //if the bottom of rectA is lower than the top of rectB - no collision
  if((rectA->getPosition().getY() + rectA->getHeight()) - aHBuf <= rectB->getPosition().getY() + bHBuf)
  { return false; }
    
  //if the top of rectA is higher than the bottom of rectB - no collision
  if(rectA->getPosition().getY() + aHBuf >= (rectB->getPosition().getY() + rectB->getHeight()) - bHBuf)
  { return false; }
    
  //if the right of rectA does not meet the left of rectB - no collision
  if((rectA->getPosition().getX() + rectA->getWidth()) - aWBuf <= rectB->getPosition().getX() +  bWBuf)
  { return false; }
    
  //if the left of rectA is further away than the right of rectB - no collision
  if(rectA->getPosition().getX() + aWBuf >= (rectB->getPosition().getX() + rectB->getWidth()) - bWBuf)
  { return false; }
    
  //else, a collision
  return true;
}

//additions and subtractions represent white space within the bullet and invader sprites
//this is not adjusted for within the use of GameObject width and heights
bool CollisionManager::isCollidingBulletInvader(GameObject* rectA, GameObject* rectB)
{
  //if the bottom of rectA is lower than the top of rectB - no collision
  if((rectA->getPosition().getY()-8 + rectA->getHeight()-8) <= rectB->getPosition().getY()+13)
  { return false; }
    
  //if the top of rectA is higher than the bottom of rectB - no collision
  if(rectA->getPosition().getY()+13  >= (rectB->getPosition().getY()-8 + rectB->getHeight()-8))
  { return false; }
    
  //if the right of rectA does not meet the left of rectB - no collision
  if((rectA->getPosition().getX() + rectA->getWidth())-20 <= rectB->getPosition().getX())
  { return false; }
    
  //if the left of rectA is further away than the right of rectB - no collision
  if(rectA->getPosition().getX()+20 >= (rectB->getPosition().getX() + rectB->getWidth()))
  { return false; }
    
  //else, a collision
  return true;
}

//additions and subtractions represent white space within the bullet and invader sprites
//this is not adjusted for within the use of GameObject width and heights
bool CollisionManager::isCollidingBulletSaucer(GameObject* rectA, Saucer* rectB)
{
  //if the bottom of rectA is lower than the top of rectB - no collision
  if((rectA->getPosition().getY()-8 + rectA->getHeight()-8) <= rectB->getPosition().getY()+13)
  { return false; }
    
  //if the top of rectA is higher than the bottom of rectB - no collision
  if(rectA->getPosition().getY()+13  >= (rectB->getPosition().getY()-8 + rectB->getHeight()-8))
  { return false; }
    
  //if the right of rectA does not meet the left of rectB - no collision
  if((rectA->getPosition().getX() + rectA->getWidth())-20 <= rectB->getPosition().getX())
  { return false; }
    
  //if the left of rectA is further away than the right of rectB - no collision
  if(rectA->getPosition().getX()+20 >= (rectB->getPosition().getX() + rectB->getWidth()))
  { return false; }
    
  //else, a collision
  return true;
}

bool CollisionManager::isCollidingBulletBlock(GameObject* rectA, GameObject* rectB)
{
  std::cout << rectA->getPosition().getY() << " + " << rectA->getHeight() <<
      " <= " << rectB->getPosition().getY() << "\n";

  //if the bottom of rectA is lower than the top of rectB - no collision
  if((rectA->getPosition().getY() + rectA->getHeight()) <= rectB->getPosition().getY())
  { return false; }
    
  //if the top of rectA is higher than the bottom of rectB - no collision
  if(rectA->getPosition().getY() >= (rectB->getPosition().getY() + rectB->getHeight()))
  { return false; }
    
  //if the right of rectA does not meet the left of rectB - no collision
  if((rectA->getPosition().getX() + rectA->getWidth()) <= 23 + rectB->getPosition().getX())
  { return false; }
    
  //if the left of rectA is further away than the right of rectB - no collision
  if(rectA->getPosition().getX()  >= (rectB->getPosition().getX() + rectB->getWidth()))
  { return false; }
    
  //else, a collision
  return true;
}
    
