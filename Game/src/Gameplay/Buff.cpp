#include "Gameplay/Buff.h"

#include "Core/Config.h"

Buff::Buff(sf::Vector2f startPosition, BuffType buffType)
	: position(startPosition), type(buffType)
{
	shape.setSize({ 24.f, 24.f });
	shape.setPosition(position);

	switch (type)
	{
	case BuffType::Speed:     shape.setFillColor(sf::Color::Cyan);    break;
	case BuffType::Dammage:   shape.setFillColor(sf::Color::Magenta); break;
	case BuffType::Shield:    shape.setFillColor(sf::Color::Blue);    break;
	case BuffType::ExtraLife: shape.setFillColor(sf::Color::Green);   break;
	}
}

void Buff::Update(float deltaTime)
{
	position.y += speed * deltaTime;
	shape.setPosition(position);

	if (isOffScreen())
		alive = false;
}

void Buff::Render(sf::RenderWindow& window)
{
	window.draw(shape);
}

void Buff::OnCollision(Entity* other)
{
	if (other->getType() == EntityType::PLAYER)
		alive = false;
}

sf::FloatRect Buff::getBounds() const
{
	return shape.getGlobalBounds();
}

EntityType Buff::getType() const
{
	return EntityType::BUFF;
}

bool Buff::isOffScreen() const
{
	const sf::FloatRect bounds = shape.getGlobalBounds();
	return bounds.position.y + bounds.size.y > static_cast<float>(cfg::WindowHeight);
}
