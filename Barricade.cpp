#include "Barricade.h"

#include "BarricadeBlock.h"

Barricade::Barricade(int x, int y)
    : posX(x), posY(y), blockWidth(5), blockHeight(5)
{
  setupBarricade();
}


void Barricade::setupBarricade()
{
  blocks = std::vector<std::vector<BarricadeBlock*> > (9, std::vector<BarricadeBlock*>(6));


  for (size_t y = 0; y < 6; y++)
  {
    for (size_t x = 0; x < 9; x++)
    {
      BarricadeBlock* newBlock = new BarricadeBlock(0,0);

      newBlock->setPosition(Vector2D(blockWidth * x + posX,
                                     blockHeight * y+ posY));

      blocks[x][y] = newBlock;
    }
  }

  delete blocks[0][0]; blocks[0][0] = nullptr;
  delete blocks[1][0]; blocks[1][0] = nullptr;
  delete blocks[0][1]; blocks[0][1] = nullptr;

  delete blocks[8][0]; blocks[8][0] = nullptr;
  delete blocks[7][0]; blocks[7][0] = nullptr;
  delete blocks[8][1]; blocks[8][1] = nullptr;

  delete blocks[3][5]; blocks[3][5] = nullptr;
  delete blocks[4][5]; blocks[4][5] = nullptr;
  delete blocks[5][5]; blocks[5][5] = nullptr;

}

void Barricade::draw()
{
  for (size_t y = 0; y < 6; y++)
  {
    for (size_t x = 0; x < 9; x++)
    {
      if (blocks[x][y] != nullptr)
        blocks[x][y]->draw();
    }
  }
}

Vector2D Barricade::checkForCollisions(GameObject* bullet)
{
  //std::cout << "checking block cols\n";
  for (size_t y = 0; y < 6; y++)
  {
    for (size_t x = 0; x < 9; x++)
    {
      if (blocks[x][y] != nullptr)
      {
        if (TheCollManager::Instance()->isCollidingBulletBlock(bullet, blocks[x][y]))
        {
          //return position of block for bullet to animate on
          Vector2D hitPos = Vector2D(blocks[x][y]->getPosition().getX(),
                                     blocks[x][y]->getPosition().getY());
          //delete block
          delete blocks[x][y];
          blocks[x][y] = nullptr;
          
          std::cout << "returning hitPos\n";
          return hitPos;
        }
      }
    }
  }
}



void Barricade::clean()
{
  for (size_t y = 0; y < 6; y++)
  {
    for (size_t x = 0; x < 9; x++)
    {
      if (blocks[x][y] != nullptr)
      {
        delete blocks[x][y];
      }
    }
  }
}
