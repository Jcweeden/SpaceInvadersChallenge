#include "PlayerProjectile.h"


PlayerProjectile::PlayerProjectile(int x, int y)
    :Projectile(x,y,1,10,0,-5.0f), toBeDeleted(false), deletionTimer(0)
{
  
}

void PlayerProjectile::update()
{
  GameObject::update();

  if (position.getY() < 100)
  {
    toBeDeleted = true;
  }
  else if (deletionTimer <= 0)
  {
    checkForCollisions();
  }
  else if (deletionTimer+700 > SDL_GetTicks())
  {
    toBeDeleted = true;
  }
  
}

void PlayerProjectile::checkForCollisions()
{
  GameObject* enemyHit = nullptr;

  if (position.getY() > 0)
  {
    for (size_t i = 0; i < ThePlayState::Instance()->barricades.size(); i++)
    {
      Vector2D hitPos = ThePlayState::Instance()->barricades[i]->checkForCollisions(this);

      if (hitPos.getY() != 0)
      {        
        //set bullet to blown up sprite
        setRow(5); setFrame(1);

        //set position to block
        setPosition(hitPos);

        //stop moving           
        velocity.setY(0);

        //set proj to be deleted
        deletionTimer = SDL_GetTicks();

        //no further collisions
        return;
      }
    }
  }
  
  //if enemy saucer
  if (ThePlayState::Instance()->invaders->saucer != nullptr)
  {
    //check coll with it
    if (TheCollManager::Instance()->isCollidingBulletSaucer(this, ThePlayState::Instance()->invaders->saucer))
    {
      TheSoundMixer::Instance()->playSound("killedEnemy",0);

      //set bullet to blown up sprite
      setRow(5); setFrame(1);

      //set to pos of enemy
      setPosition(Vector2D(ThePlayState::Instance()->invaders->saucer->getPosition().getX(),
                           ThePlayState::Instance()->invaders->saucer->getPosition().getY()));
          
      //stop moving           
      velocity.setY(0);

      //increase score
      int randSaucerIndex = rand() % 4;

      if (randSaucerIndex == 0)
        ThePlayState::Instance()->addScore(50);
      else if (randSaucerIndex == 1)
        ThePlayState::Instance()->addScore(100);
      else if (randSaucerIndex == 2)
        ThePlayState::Instance()->addScore(150);
      else if (randSaucerIndex == 3)
        ThePlayState::Instance()->addScore(300);
        
      //delete enemy
      ThePlayState::Instance()->invaders->saucer->toBeDeleted = true;

      //set proj to be deleted
      deletionTimer = SDL_GetTicks();
    }
  }
  
  
  //if have not hit saucer
  if (enemyHit == nullptr)
  {
    //check against invaders
    for (size_t y = 0; y < 5; y++)
    {
      for (size_t x = 0; x < 11; x++)
      {
        if (ThePlayState::Instance()->invaders->invaders[x][y] != nullptr)
          if (TheCollManager::Instance()->isCollidingBulletInvader(this, ThePlayState::Instance()->invaders->invaders[x][y]))
          {
            //set bullet to blown up sprite
            setRow(5); setFrame(1);

            //set to pos of enemy
            setPosition(Vector2D(ThePlayState::Instance()->invaders->invaders[x][y]->getPosition().getX(),
                                 ThePlayState::Instance()->invaders->invaders[x][y]->getPosition().getY()));
          
            //stop moving           
            velocity.setY(0);

            //increase score
          
            if (ThePlayState::Instance()->invaders->invaders[x][y]->getRow() == 1)
              ThePlayState::Instance()->addScore(30);
            else if (ThePlayState::Instance()->invaders->invaders[x][y]->getRow() == 2)
              ThePlayState::Instance()->addScore(10);
            else if (ThePlayState::Instance()->invaders->invaders[x][y]->getRow() == 3)
              ThePlayState::Instance()->addScore(20);
            
            //delete enemy
            delete ThePlayState::Instance()->invaders->invaders[x][y];
            ThePlayState::Instance()->invaders->invaders[x][y] = nullptr;

            //decrement enemy counter
            ThePlayState::Instance()->invaders->numInvadersRemaining--;
          
            //decrement enemy number in that column
            ThePlayState::Instance()->invaders->numSurvivingInEachCol[x]--;

            //update game speed
            ThePlayState::Instance()->updateGameSpeed();

            //set proj to be deleted
            deletionTimer = SDL_GetTicks();

            TheSoundMixer::Instance()->playSound("killedEnemy",0);
          }
      }
    }
  }
}
