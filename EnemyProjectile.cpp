#include "EnemyProjectile.h"
#include "Player.h"

EnemyProjectile::EnemyProjectile(int x, int y)
    :Projectile(x,y,2,10,0,2.0f), toBeDeleted(false), deletionTimer(0), hitPlayer(false)
{
  //randomly selects missile type
  currentRow = rand() % 3 + 6;
}

void EnemyProjectile::update()
{
  GameObject::update();

  if (position.getY() > 460 && deletionTimer <= 0)
  {
    //is now out of bounds
    deletionTimer = SDL_GetTicks();

    //blow up
    setRow(5); setFrame(1);

    velocity.setY(0);
  }
  else if (deletionTimer <= 0)
  {
    checkForCollisions();
  }
  else if (SDL_GetTicks() > deletionTimer + 700)
  {
    toBeDeleted = true;
    if (hitPlayer) ThePlayState::Instance()->gameOver = true;
  }
  
}

void EnemyProjectile::checkForCollisions()
{

  //check against player
  if (TheCollManager::Instance()->isCollidingBulletInvader(this, ThePlayState::Instance()->player))
  {
    //update to stop player movement
    ThePlayState::Instance()->playerMovementDisabled = true;
    
    //set player to blown up player sprite
    ThePlayState::Instance()->player->setRow(11);
    ThePlayState::Instance()->player->setNumFrames(2);

    //set bullet to no sprite
    setRow(0); setFrame(3); setNumFrames(1);
    
    //stop it moving           
    velocity.setY(0);

    //will reset the game
    hitPlayer = true;
    
    //set proj to be deleted
    deletionTimer = SDL_GetTicks();

    std::cout << "collided with player fine\n";
  }
}
