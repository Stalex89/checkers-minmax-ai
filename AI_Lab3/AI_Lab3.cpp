// AI_Lab3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace sf;

int size = 56;

Sprite pieces[24];

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
			pieces[k].setPosition(size*j + size/2, size*i + size/2);
			k++;
		}
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
	int n = 0;

	while (window.isOpen())
	{
		Vector2i pos = Mouse::getPosition(window);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		
			// drag and drop
			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left)
					for (int i = 0; i < 24; i++)
						if (pieces[i].getGlobalBounds().contains(pos.x, pos.y))
						{
							isMove = true; n = i;
							dx = pos.x - pieces[i].getPosition().x;
							dy = pos.y - pieces[i].getPosition().y;

						}

			if (event.type == Event::MouseButtonReleased)
				if (event.key.code == Mouse::Left)
				{
					isMove = false;
					Vector2f p = pieces[n].getPosition();
					Vector2f newPos = Vector2f((size * int(p.x / size)) + size / 2, (size*int(p.y / size)) + size / 2);
					pieces[n].setPosition(newPos);
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