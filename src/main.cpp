
/*
using namespace sf;
int main()
{
	RenderWindow window(sf::VideoMode(640, 480), "Lesson 6. kychka-pc.ru");

	Texture herotexture;
	herotexture.loadFromFile("images/hero.png");

	Sprite herosprite;
	herosprite.setTexture(herotexture);
	herosprite.setTextureRect(IntRect(0, 192, 96, 96));
	herosprite.setPosition(250, 250);

	float heroteleporttimer = 0; //������� ��� ������� ������������ ����� ����� 3 �������
	Clock clock; //������� ���������� �������, �.�. �������� �� �������(� �� ��������/������������� ����������). 

	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds(); //���� ��������� ����� � �������������
		clock.restart(); //������������� �����
		time = time / 800; // �������� ����
		//std::cout << time << "\n";//������� ��� ����� ����� (���������������, ��� �����)

		heroteleporttimer += time;//���������� � ����� ���������� time

		//if (heroteleporttimer > 3000) { herosprite.setPosition(0, 120); heroteleporttimer = 0; } //���� ��������������� ������ 3000 (��� �������� 3 �������), �� ������������� ����� � �������� ������ ������������


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		std::cout << time << std::endl;
		if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) { herosprite.move(-0.1 * time, 0); herosprite.setTextureRect(IntRect(0, 96, 96, 96)); } //-0,1 ��� ��������, �������� � �� ���� ����� � �������� ���������� ����������
		if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) { herosprite.move(0.1 * time, 0); herosprite.setTextureRect(IntRect(0, 192, 96, 96)); } // �� ������� ����
		if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) { herosprite.move(0, -0.1 * time); herosprite.setTextureRect(IntRect(0, 288, 96, 96)); }// �� ����
		if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) { herosprite.move(0, 0.1 * time); herosprite.setTextureRect(IntRect(0, 0, 96, 96)); }// �� ����


		window.clear();
		window.draw(herosprite);
		window.display();
	}

	return 0;
}
*/

#include "Engine.h"

int WinMain()
{
	Engine engine;
	return engine.Start();
}