// AI_Lab3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace sf;

int size = 56;
Vector2f offset(28, 28);
Sprite pieces[24];
std::string position = "";

int board[8][8] =
{
	 0, -1,  0, -1,  0, -1,  0, -1,
	-1,  0, -1,  0, -1,  0, -1,  0,
	 0, -1,  0, -1,  0, -1,  0, -1,
	 0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,
	 1,  0,  1,  0,  1,  0,  1,  0,
	 0,  1,  0,  1,  0,  1,  0,  1,
	 1,  0,  1,  0,  1,  0,  1,  0,
};

std::string toChessNote(Vector2f p)
{
	std::string  s = "";
	s += char(p.x / size + 97);
	s += char(8 - p.y / size + 49);
	return s;
}

Vector2f toCoord(char a, char b)
{
	int x = int(a) - 97;
	int y = 7 - int(b) + 49;
	return Vector2f(float(x*size), float(y*size)) + offset;
}

void move(std::string str)
{
	Vector2f oldPos = toCoord(str[0], str[1]);
	Vector2f newPos = toCoord(str[2], str[3]);

	for (int i = 0; i < 24; i++)
		if (pieces[i].getPosition() == newPos) pieces[i].setPosition(-100, -100);

	for (int i = 0; i < 24; i++)
		if(pieces[i].getPosition() == oldPos) pieces[i].setPosition(newPos);
}

bool isInBorder(Vector2f &position, Sprite &borders)
{
	return (position.x > offset.x && position.x < borders.getGlobalBounds().width - offset.x
		&& position.y > offset.y && position.y < borders.getGlobalBounds().height - offset.y);
}

void loadPosition()
{
	int k = 0;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{ 

			int n = board[i][j];
			// check if position is not 0
			if (!n) continue;
			int x = (n > 0) ? 1 : 0;
			// set part of pieces texture depending on the argument on board 
			pieces[k].setTextureRect(IntRect(size*x, 0, size, size));
			// set position of the sprite
			pieces[k].setPosition(Vector2f(float(size*j), float(size*i)) + offset);
			k++;
		}

	for (int i = 0; i < position.length(); i += 4)
		move(position.substr(i, 3));
}

int main()
{
	RenderWindow window(VideoMode(504, 504), "AI Draughts");

	Texture tBoard;
	tBoard.loadFromFile("../images/board.png");
	Texture tPieces;
	tPieces.loadFromFile("../images/pieces.png");

	Sprite sBoard(tBoard);
	Sprite sPieces(tPieces);

	for (int i = 0; i < 24; i++) pieces[i].setTexture(tPieces);
	loadPosition();

	bool isMove = false;
	float dx = 0, dy = 0;
	Vector2f oldPos, newPos;
	std::string str;
	int n = 0;

	while (window.isOpen())
	{
		Vector2i pos = Mouse::getPosition(window);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			// move back
			if(event.type == Event::KeyPressed)
				if (event.type == Keyboard::BackSpace)
				{
					position.erase(position.length() - 6, 5);
					loadPosition();
				}
		
			// drag and drop
			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left)
					for (int i = 0; i < 24; i++)
						if (pieces[i].getGlobalBounds().contains(float(pos.x), float(pos.y)))
						{
							isMove = true; n = i;
							dx = pos.x - pieces[i].getPosition().x;
							dy = pos.y - pieces[i].getPosition().y;
							oldPos = pieces[i].getPosition();
						}

			if (event.type == Event::MouseButtonReleased)
				if (event.key.code == Mouse::Left)
				{
					isMove = false;
					Vector2f p = pieces[n].getPosition();
					Vector2f newPos = Vector2f(float(size * int(p.x / size)),
						float(size*int(p.y / size))) + offset;
					if (oldPos != newPos && isInBorder(newPos, sBoard))
					{
						str = toChessNote(oldPos) + toChessNote(newPos);
						move(str);
						position += str + " ";
						std::cout << str << std::endl;
						pieces[n].setPosition(newPos);
					}
					else pieces[n].setPosition(oldPos);
				}
		
		}

		if (isMove) pieces[n].setPosition(pos.x - dx, pos.y - dy);

	window.clear();
	window.draw(sBoard);
	for (int i = 0; i < 24; i++) window.draw(pieces[i]);
	window.display();
	}

	return 0;
}