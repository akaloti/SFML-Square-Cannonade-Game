#pragma once

#include <States/State.hpp>
#include <Utility/ResourceIdentifiers.hpp>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace sf
{
  class RenderWindow;
}

class TitleState : public State
{
  sf::Texture mBackgroundTexture;
  sf::Sprite mBackgroundSprite;

  // Instructional texts
  sf::Text mInstruction1;
  sf::Text mInstruction2;
  sf::Text mInstruction3;
public:
  TitleState(sf::RenderWindow &window, const FontHolder &fonts,
    const TextureHolder &textures);

  virtual void draw();
  virtual void update();
  virtual bool handleEvent(const sf::Event& event);
  virtual void handleRealTimeInput();
};