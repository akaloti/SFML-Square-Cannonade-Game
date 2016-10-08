#include <Game/World.hpp>

#include <SFML/Window/Event.hpp>

const float World::BorderWidth = 10.f;

World::World(sf::RenderWindow &window, const TextureHolder &textures)
  : mWindow(window)
  , mIsPaused(false)
  , mBackgroundSprite()
  , mPlayer()
  , mCoin1()
  , mCoin2()
{
  loadTextures();

  // Set up background texture to repeat
  sf::Texture& backgroundTexture = mTextures.get(Textures::Background);
  backgroundTexture.setRepeated(true);
  mBackgroundSprite.setTexture(backgroundTexture);
  sf::Vector2u windowSize = mWindow.getSize();
  mBackgroundSprite.setTextureRect(
    sf::IntRect(0, 0, windowSize.x, windowSize.y));

  mPlayer.setPosition(sf::Vector2f(15, 15));

  mCoin1.setPosition(sf::Vector2f(30, 30));
  mCoin2.setPosition(sf::Vector2f(85, 20));
}

void World::draw()
{
  mWindow.draw(mBackgroundSprite);

  mWindow.draw(mPlayer);
  mWindow.draw(mCoin1);
  mWindow.draw(mCoin2);
}

void World::update(sf::Time dt)
{
  mPlayer.update(dt);
}

bool World::handleEvent(const sf::Event& event)
{
  if (event.type == sf::Event::KeyPressed)
  {
    if (event.key.code == sf::Keyboard::P)
      mIsPaused = !mIsPaused;
  }

  return true;
}

void World::handleRealTimeInput()
{
  if (!mIsPaused)
  {
    mPlayer.setIsMovingUp(sf::Keyboard::isKeyPressed(sf::Keyboard::Up));
    mPlayer.setIsMovingDown(sf::Keyboard::isKeyPressed(sf::Keyboard::Down));
    mPlayer.setIsMovingLeft(sf::Keyboard::isKeyPressed(sf::Keyboard::Left));
    mPlayer.setIsMovingRight(sf::Keyboard::isKeyPressed(sf::Keyboard::Right));
  }

  return;
}

void World::loadTextures()
{
  mTextures.load(Textures::Background, "Media/Metal.PNG");
}