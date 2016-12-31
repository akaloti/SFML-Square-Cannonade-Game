#include <Game/Player.hpp>
#include <Utility/Utility.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

#include <cassert>



const float Player::PlayerLength = 30.f;
const float Player::PlayerSpeed = 100.f;

Player::Player()
  : mSprite(sf::RectangleShape(sf::Vector2f(PlayerLength, PlayerLength)))
  // the four movement booleans are initialized in the constructor's body
{
  mIsMovingDown = mIsMovingLeft = mIsMovingRight = mIsMovingUp = false;

  centerOrigin(mSprite);
  mSprite.setFillColor(sf::Color::Blue);
}

float Player::getLength() const
{
  assert(mSprite.getSize().x == mSprite.getSize().y);
  return mSprite.getSize().x;
}

sf::IntRect Player::getBoundingRect() const
{
  // Position is centered because centerOrigin() is called in constructor
  sf::Vector2f centeredPosition = getPosition();

  return sf::IntRect(centeredPosition.x - PlayerLength / 2,
    centeredPosition.y - PlayerLength / 2,
    PlayerLength,
    PlayerLength);
}

void Player::setIsMovingLeft(bool b)
{
  mIsMovingLeft = b;
}

void Player::setIsMovingRight(bool b)
{
  mIsMovingRight = b;
}

void Player::setIsMovingUp(bool b)
{
  mIsMovingUp = b;
}

void Player::setIsMovingDown(bool b)
{
  mIsMovingDown = b;
}

void Player::update(sf::Time dt)
{
  sf::Vector2f movement;
  if (mIsMovingLeft)
    movement.x -= PlayerSpeed;
  if (mIsMovingRight)
    movement.x += PlayerSpeed;
  if (mIsMovingUp)
    movement.y -= PlayerSpeed;
  if (mIsMovingDown)
    movement.y += PlayerSpeed;
  move(movement * dt.asSeconds());
}

void Player::drawSprite(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(mSprite, states);
}