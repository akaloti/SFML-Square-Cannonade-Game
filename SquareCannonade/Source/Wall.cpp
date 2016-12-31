#include <Game/Wall.hpp>


Wall::Wall(int left, int top, int width, int height)
  : mRect(left, top, width, height)
{
}

auto Wall::getBoundingRect() const
{
  return mRect;
}

bool Wall::entityCollidesWithWall(sf::IntRect entityRect)
{
  return mRect.intersects(entityRect);
}
