#include "GameObject.h"

GameObject::GameObject( int x, int y, int p_width, int p_height, std::string p_textureID, int p_numFrames, int p_currentRow, int p_currentFrame, int p_animationSpeed) :
    position(x,y), width(p_width), height(p_height), textureID(p_textureID), numFrames(p_numFrames), velocity(0,0), acceleration(0,0), currentFrame(p_currentFrame), currentRow(p_currentRow), animationSpeed(p_animationSpeed)
{

}

void GameObject::draw()
{
  TheTextureManager::Instance()->draw(textureID, (int)position.getX()- width/2, (int)position.getY() -height/2, width, height, TheGame::Instance()->getRenderer(), currentRow, currentFrame, SDL_FLIP_NONE);
}

void GameObject::drawFrame()
{
  TheTextureManager::Instance()->drawFrame(textureID, (int)position.getX()- width/2, (int)position.getY() -height/2, width, height, /*m_currentFrame,*/ currentFrame, TheGame::Instance()->getRenderer(), currentRow);
}

void GameObject::update()
{
  if (numFrames > 1) setFrame(int(((SDL_GetTicks() / animationSpeed) % numFrames)));
  
  velocity += acceleration;
  position += velocity;
};

void GameObject::clean()
{
}
