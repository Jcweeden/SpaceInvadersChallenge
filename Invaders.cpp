#include "Invaders.h"


Invaders::Invaders(unsigned rowNumber)
    :shiftDownBy(16)
{

  invaders = std::vector<std::vector<Enemy*> > (11, std::vector<Enemy*>(5));
  setupInvaders(rowNumber);
}

void Invaders::setupInvaders(unsigned startingRow)
{
  std::cout << "setting up invaders\n";
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
  std::cout << "setup invaders\n";
}

void Invaders::update()
{

}

void Invaders::draw()
{
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
  for (size_t y = 0; y < 5; y++)
  {
    for (size_t x = 0; x < 11; x++)
    {
      if (invaders[x][y] != nullptr) delete invaders[x][y];
    }
  }
}
