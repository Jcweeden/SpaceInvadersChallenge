#include "Player.h"


Player::Player(int x, int y, unsigned p_numFrames, unsigned p_currentRow, unsigned p_currentFrame)
    : GameObject::GameObject(x,y,32,32,"spaceInvaders",p_numFrames,p_currentRow,p_currentFrame), bullet(nullptr)
{

}

void Player::update()
{

  if (bullet != nullptr)
  {
    if (bullet->toBeDeleted)
    {
      delete bullet;
      bullet = nullptr;
    }
    else
      bullet->update();
  }
  
  GameObject::update();

  velocity.setX(0.0f);
}

void Player::draw()
{
  if (bullet != nullptr) bullet->draw();
  
  GameObject::draw();
}

void Player::clean()
{
  if (bullet != nullptr)
  {
    delete bullet;
  }
  
  GameObject::clean();
}

void Player::handleInput()
{
  if (TheInputHandler::Instance()->getIsSpaceKeyPressed())
  {
    //shoot if no existing bullet
    if (bullet == nullptr) bullet = new PlayerProjectile(GameObject::position.getX(), GameObject::position.getY());
  }

  if (GameObject::position.getX() < 432 &&
      TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
  {
    //move right
    velocity.setX(1.8f);
  }

  if (GameObject::position.getX() > 80 &&
      TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
  {
    //move left
    velocity.setX(-1.8f);
  }
}
