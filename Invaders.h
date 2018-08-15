#ifndef _Invaders_
#define _Invaders_


#include "Enemy.h"
#include "Game.h"
#include "Vector2D.h"

#include <vector>
#include <iostream>

class EnemyProjectile;
class Player;

class Invaders {
public:
  Invaders(unsigned rowNumber, unsigned playerY);
  
  void update();
  void draw();
  void clean();

  void setupInvaders(unsigned startingRow);

  void moveInvaders();
  void checkIfShiftDown();
  
  void animateSprites();

  Enemy* getBottomInvaderInColumn(unsigned colIndex);


  void shoot(unsigned colIndexToShootFrom);
  void shootFromRandomColumn();
  void shootAtPlayer();
  
public:

  std::vector<std::vector<Enemy*> > invaders;

  std::vector<EnemyProjectile*> enemyBullets;
  
  std::vector<int> numSurvivingInEachCol;
  
  unsigned numInvadersRemaining;

  //shiftDownBy is val invaders will shift down once reaching edge of screen
  unsigned shiftDownBy;
  
  //shiftDownBy is val invaders will shift across on each move  
  unsigned shiftSidewaysBy;

  bool moveLeft;

  //edge of screen - once invader meets this will move down
  unsigned invaderBoundaryLeft, invaderBoundaryRight;

  //players position that if reached you lose
  unsigned playerPosY;
};

#endif
