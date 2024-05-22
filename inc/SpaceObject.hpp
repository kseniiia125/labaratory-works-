#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

namespace mt
{
	class SpaceObject
	{
	protected:
		float m_x, m_y;
		float m_vx, m_vy;
		float m_r;
		float m_alpha;
		sf::Texture m_textureShip;
		sf::Sprite m_spriteShip;

	public:
		SpaceObject() = default;
		virtual ~SpaceObject() {}
		bool Setup(float x, float y, float vx, float vy, float alpha, const std::string& textureRath, float scaleFactor)
		{
			m_x = x;
			m_y = y;
			m_vx = vx;
			m_vy = vy;
			m_alpha = 0;

			// Загрузка текстуры фона
			if (!m_textureShip.loadFromFile(textureRath))
			{
				std::cout << "Error while loading" << textureRath << std::endl;
				return false;
			}
			m_spriteShip.setTexture(m_textureShip);

			m_spriteShip.setScale(scaleFactor, scaleFactor);
			m_spriteShip.setOrigin(m_textureShip.getSize().x / 2, m_textureShip.getSize().y / 2);
			m_spriteShip.setPosition(m_x, m_y);
			m_spriteShip.setRotation(m_alpha);

			if (m_textureShip.getSize().x > m_textureShip.getSize().y)
				m_r = scaleFactor * m_textureShip.getSize().x / 2;
			else
				m_r = scaleFactor * m_textureShip.getSize().y / 2;

			//bullet.Setup(100, 100, 20, 10, 10);
		}

		sf::Sprite Get() // эта ф-ция возвращает сам корабль
		{
			return m_spriteShip;
		}

		void Move(float dt)
		{
			m_x += m_vx * dt;
			m_y += m_vy * dt;
			m_spriteShip.setPosition(m_x, m_y);
		}

		void Rotate(float dt)
		{
			m_alpha += dt;
			m_spriteShip.setRotation(m_alpha);
		}

		virtual void Attack() = 0;
		virtual void SpecialAbility() = 0;

	};
}