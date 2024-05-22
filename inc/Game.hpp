#pragma once
#include <string>
#include <thread>
#include <iostream>
#include <Ship.hpp>
#include <Bullet.hpp>
#include <SpaceObject.hpp>
#include <UFO.hpp>
#include <Destroyer.hpp>
#include <Comet.hpp>

namespace mt
{

	const float pi = acos(-1);

	class Game
	{
		int m_width;
		int m_height;
		std::string m_capture;
		mt::Circle* m_c;
		int m_n;
		sf::RenderWindow m_window;
		sf::Texture m_textureBackground;
		sf::Sprite m_spriteBackground;
		sf::Font m_font;
		sf::Text m_fpsText;
		Ship m_ship;
		bool isVisible = true;
		bool isTouchBorder = true;

		UFO ufo;
		Destroyer destroyer;
		Comet comet;

		std::vector<SpaceObject*> m_spaceObjects;

	public:
		Game(int width, int height, const std::string& capture)
		{
			m_width = width;
			m_height = height;
			m_capture = capture;
		}

		~Game()
		{
			for (int i = 0; i < m_spaceObjects.size(); i++)
			{
				delete m_spaceObjects[i];
			}

			delete[] m_c;
		}

		bool Setup(int n)
		{
			m_n = n;
			// Создание окна
			m_window.create(sf::VideoMode(m_width, m_height), m_capture);

			// Загрузка текстуры фона
			if (!m_textureBackground.loadFromFile("assets\\background.jpg"))
			{
				std::cout << "Error while loading background.jpg" << std::endl;
				return false;
			}
			m_spriteBackground.setTexture(m_textureBackground);

			/*// ЗАгрузка шрифта
			if (!m_font.loadFromFile("assets\\icons.ttf"))
			{
				std::cout << "Error while loading arial.ttf" << std::endl;
				return false;
			}
			m_fpsText.setFont(m_font);*/

			// Создание корабля
			if (!m_ship.Setup(100, 100)) // координаты корабля
				return false;

			srand(time(0));

			m_c = new mt::Circle[m_n];
			for (int i = 0; i < m_n; i++)
			{
				int r = rand() % 100 + 10;
				int x = rand() % (1000 - 2 * r) + r;
				int y = rand() % (600 - 2 * r) + r;
				int v = rand() % 50 + 100;
				float alfa = rand() % 7;
				m_c[i].Setup(x, y, r, v, alfa);
			}

			m_spaceObjects.push_back(new UFO);
			m_spaceObjects[0]->Setup(400, 400, 1, 0, 0, "assets\\ufo.png", 1.0f);

			m_spaceObjects.push_back(new Destroyer);
			m_spaceObjects[1]->Setup(600, 600, 0, 1, 0, "assets\\destroyer.png", 0.3f);

			m_spaceObjects.push_back(new Destroyer);
			m_spaceObjects[2]->Setup(200, 200, 0, 1, 0, "assets\\destroyer.png", 0.3f);

			m_spaceObjects.push_back(new Comet);
			m_spaceObjects[2]->Setup(100, 100, 0, 1,  0,"assets\\comet.png", 0.3f);
		}

		void TouchBorder(Circle& obj)
		{
			float x = obj.X();
			float y = obj.Y();
			float r = obj.R();

			//std::cout << x << " " << y << std::endl;

			if (isTouchBorder)
			{
				isTouchBorder = false;

				if (x + r >= m_width || x - r <= 0)
				{
					obj.Alfa(pi - obj.Alfa());
				}

				if (y + r >= m_height || y - r <= 0)
				{
					obj.Alfa(2 * pi - obj.Alfa());
				}

			}
			else
			{
				if (x + r + 20 <= m_width || x - r - 20 >= 0)
				{
					isTouchBorder = true;
				}

				if (y + r + 20 <= m_height || y - r - 20 >= 0)
				{
					isTouchBorder = true;
				}
			}

		}

		void Collision(int i)
		{
			Circle& c = m_c[i];
			float dist = sqrt(pow(m_ship.X() - c.X(), 2) + pow(m_ship.Y() - c.Y(), 2));
			if (m_ship.R() + c.R() >= dist)
			{
				std::cout << "Collision " << m_ship.V() << std::endl;
				isVisible = false;
			}
		}

		void LifeCycle()
		{
			sf::Clock clock;


			while (m_window.isOpen())
			{
				// Обработка событий
				sf::Event event;
				while (m_window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						m_window.close();
				}

				// Обработка клавиатуры
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					m_ship.setVelocity(1);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					m_ship.setVelocity(-1);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					m_ship.Rotate(-0.5);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					m_ship.Rotate(0.5);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					if (!m_ship.BulletAvailable()) //если пули не существует
						m_ship.Attack();
					destroyer.Attack();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
				{
					m_ship.BulletReset();
					ufo.Attack();
					comet.Attack();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					for (int i = 0; i < m_spaceObjects.size(); i++)
					{
						m_spaceObjects[i]->Rotate(0.5);
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					for (int i = 0; i < m_spaceObjects.size(); i++)
					{
						m_spaceObjects[i]->Rotate(-0.5);
					}
				}
			
				float dt = clock.getElapsedTime().asSeconds();
				clock.restart();
				// Логика
				/*if (1 / fps > dt)
				{
					sf::Time t = sf::seconds(1 / fps - dt);
					sf::sleep(t);
				}*/
				//dt = clock.getElapsedTime().asSeconds();
				//clock.restart();

				// ??????????? ??????

				//for (int i = 0; i < m_n; i++)
				//	TouchBorder(m_c[i]);

				for (int i = 0; i < m_n; i++)
				{
					// параметры шарика
					float x = m_c[i].X();
					float y = m_c[i].Y();
					float r = m_c[i].R(); // радиус
					float v = m_c[i].V(); // скорость
					float alfa = m_c[i].Alfa();

					// считаем куда переместиться шарик за время
					float x_s = x + v * cos(alfa) * dt;
					float y_s = y + v * sin(alfa) * dt;


					bool collision = false;
					if (x_s + r >= m_width) // удар о правую стенку
					{
						m_c[i].Alfa(pi - m_c[i].Alfa());
						m_c[i].X(m_width - r); // задаем ему кординату x
						collision = true;
					}

					if (x_s - r <= 0) // удар о левую границу
					{
						m_c[i].Alfa(pi - m_c[i].Alfa());
						m_c[i].X(r);
						collision = true;
					}

					if (y_s + r >= m_height)
					{
						m_c[i].Alfa(2 * pi - m_c[i].Alfa());
						m_c[i].Y(m_height - r);
						collision = true;
					}

					if (y_s - r <= 0)
					{
						m_c[i].Alfa(2 * pi - m_c[i].Alfa());
						m_c[i].Y(r);
						collision = true;
					}

					if (!collision)
					{
						m_c[i].X(x_s);
						m_c[i].Y(y_s);
					}
				}

				//for (int i = 0; i < m_n; i++)
				//	m_c[i].Move(dt);

				//for (int i = 0; i < m_n; i++)
				//	Collision(i);

				// Перемещение корабля
				m_ship.Move(dt);

				/**or (int i = 0; i < m_spaceObjects.size(); i++)
				{
					m_spaceObjects[i]->Move(dt);
				}*/

				m_fpsText.setString(std::to_string(1 / dt));

				// Отображение
				m_window.clear();
				m_window.draw(m_spriteBackground);
				m_window.draw(m_fpsText);
				for (int i = 0; i < m_n; i++)
					m_window.draw(m_c[i].Get());

				for (int i = 0; i < m_spaceObjects.size(); i++)
				{
					m_window.draw(m_spaceObjects[i]->Get());
				}

				if (m_ship.BulletAvailable()) // если пуля вылетела
					m_window.draw(m_ship.GetBullet());
				if (isVisible)
					m_window.draw(m_ship.Get());
				m_window.display();
			}
		}
	};

}
