#include "Invaders.h"
#include "EnemyProjectile.h"
#include "Player.h"


Invaders::Invaders(unsigned rowNumber, unsigned playerY)
    :shiftDownBy(16), shiftSidewaysBy(8), moveLeft(false), numInvadersRemaining(55), numSurvivingInEachCol(11, 5), invaderBoundaryLeft(32), invaderBoundaryRight(480), playerPosY(playerY)
{

  invaders = std::vector<std::vector<Enemy*> > (11, std::vector<Enemy*>(5));
  setupInvaders(rowNumber);
}

void Invaders::setupInvaders(unsigned startingRow)
{
  //variables holding starting position of the swarm
  int startPosX = 96;
  int startPosY = 160;
  
  //variables holding distance between each invader
  int distX = 32;
  int distY = 32;

  //add for each addition row down the spawn is starting at
  startPosY += shiftDownBy * startingRow;

  //create and spawn invaders
  for (size_t y = 0; y < 5; y++)
  {
    for (size_t x = 0; x < 11; x++)
    {
      Enemy* newInvader = new Enemy(0,0,0,0,0);

      //set sprite according to row
      if (y == 0) newInvader->setRow(1);
      else if (y == 1 || y == 2) newInvader->setRow(3);
      else if (y >= 3) newInvader->setRow(2);

      newInvader->setPosition(Vector2D(x*distX+startPosX, y*distY+startPosY));

      invaders[x][y] = newInvader;
    }
  }
}

void Invaders::update()
{
  if (numInvadersRemaining > 0 )
  {
    if (enemyBullets.size() == 0)
    {
      //either fire randomly, or fire closest to player, with 50/50 chance
      int randFireIndex = rand() % 2;
      
      if (randFireIndex == 0)
      {
        shootFromRandomColumn(); //fire randomly
      }
      else
      {
        shootAtPlayer(); //fire at player
      }
    }
    else
    {
      //update bullets
      for (size_t i = 0; i < enemyBullets.size(); i++)
      {
        enemyBullets[i]->update();

        if (enemyBullets[i]->toBeDeleted)
        {
          delete enemyBullets[i];
          enemyBullets.erase(enemyBullets.begin()+i);
        }
      }
    }
  }
}

void Invaders::draw()
{
  //update bullets
  for (EnemyProjectile* proj : enemyBullets)
  {
    proj->draw();
  }
      
  for (size_t y = 0; y < 5; y++)
  {
    for (size_t x = 0; x < 11; x++)
    {
      if (invaders[x][y] != nullptr) invaders[x][y]->draw();
    }
  }
}

void Invaders::clean()
{
  for (size_t i = 0; i < enemyBullets.size(); i++)
  {
    delete enemyBullets[i];
  }


  
  for (size_t y = 0; y < 5; y++)
  {
    for (size_t x = 0; x < 11; x++)
    {
      if (invaders[x][y] != nullptr) delete invaders[x][y];
    }
  }
}


void Invaders::moveInvaders()
{
  animateSprites();

  checkIfShiftDown();//check if need to move down
  
  for (size_t y = 0; y < 5; y++)
  {
    for (size_t x = 0; x < 11; x++)
    {
      if (invaders[x][y] != nullptr)
      {
        if (moveLeft) invaders[x][y]->setPositionX(invaders[x][y]->getPosition().getX()-shiftSidewaysBy);
        else invaders[x][y]->setPositionX(invaders[x][y]->getPosition().getX()+shiftSidewaysBy); //else move right
      }
    }
  }
}

void Invaders::checkIfShiftDown()
{
  bool atEdge = false;

  if (moveLeft)
  {
    //get furthest col on left that has a surviving invader
    int furthestLeftColumn = -1;
    for (size_t i = 0; i < numSurvivingInEachCol.size(); i++)
    {
      if (numSurvivingInEachCol[i] != 0)
      {
        furthestLeftColumn = i;
        break;
      }
    }
    
    //get the x position of invader in that column
    unsigned xPos = getBottomInvaderInColumn(furthestLeftColumn)->getPosition().getX();

    //if past boundary
    if (xPos <= invaderBoundaryLeft)
    {
      moveLeft = !moveLeft; //switch position that invaders are moving
      atEdge = true;
    }
  }
  ///MOVE RIGHT
  else //if (!moveLeft) //moving right
  {
    //get furthest col on right that has a surviving invader
    int furthestRightColumn = -1;
    for (size_t i = 10; i < numSurvivingInEachCol.size(); i--)
    {
      if (numSurvivingInEachCol[i] > 0)
      {
        furthestRightColumn = i;
        break;
      }
    }
    
    //get the x position of invader in that column
    unsigned xPos = getBottomInvaderInColumn(furthestRightColumn)->getPosition().getX();

    //if past boundary
    if (xPos >= invaderBoundaryRight)
    {
      moveLeft = !moveLeft; //switch position that invaders are moving
      atEdge = true;
    }
  }

  if (atEdge)
  {
    //move all space invaders down
    for (size_t y = 0; y < 5; y++)
    {
      for (size_t x = 0; x < 11; x++)
      {
        if (invaders[x][y] != nullptr)
        {
          invaders[x][y]->setPositionY(invaders[x][y]->getPosition().getY()+shiftDownBy);

          //todo: if at player pos then lose
          if (invaders[x][y]->getPosition().getY() >= playerPosY)
          {
            //lose
            return;
          }
        }
      }
    }    
  }
}


void Invaders::animateSprites()
{
  for (size_t y = 0; y < 5; y++)
  {
    for (size_t x = 0; x < 11; x++)
    {
      if (invaders[x][y] != nullptr)
      {
        if (invaders[x][y]->getFrame() == 0) invaders[x][y]->setFrame(1);
        else invaders[x][y]->setFrame(0);
      }
    }
  }
}


Enemy* Invaders::getBottomInvaderInColumn(unsigned colIndex)
{
  for (int y = 4; y >= 0; y--)
  {
    if (invaders[colIndex][y] != nullptr) return invaders[colIndex][y];
  }
  //none found
  return nullptr;
}


void Invaders::shoot(unsigned colIndexToShootFrom)
{
  Vector2D spawnPos = getBottomInvaderInColumn(colIndexToShootFrom)->getPosition();
  
  EnemyProjectile* proj = new EnemyProjectile(spawnPos.getX(), spawnPos.getY());
  enemyBullets.push_back(proj);
}


void Invaders::shootFromRandomColumn()
{
  unsigned randColumnIndex;

  //get a column that contains at least one invader 
  do {
    randColumnIndex = rand() % 11;
  } while (numSurvivingInEachCol[randColumnIndex] == 0);
  
  shoot(randColumnIndex);
}


void Invaders::shootAtPlayer()
{
  unsigned firstSurvivingColumn = 0;

  //find first col with invaders in it
  while (true)
  {
    if (numSurvivingInEachCol[firstSurvivingColumn] > 0)
      break; //found a col with invaders
    else
      firstSurvivingColumn++; //iterate and try again
  }
  //get x pos of first col with invaders in it
  unsigned xPos = getBottomInvaderInColumn(firstSurvivingColumn)->getPosition().getX();
  //get player x
  unsigned playerXPos = ThePlayState::Instance()->player->getPosition().getX();

  //calc number of rows difference between the two
  unsigned diffX = (playerXPos - xPos) / 32;

  //if within row boundaries, and there is an invader in selected row
  if (diffX >= 0 && diffX <= 10)
  {
    if (numSurvivingInEachCol[diffX] > 0)
    {
      shoot(diffX);
      return;
    }
  }
  else
  {
    shootFromRandomColumn();
  }

  //shoot from it
}
