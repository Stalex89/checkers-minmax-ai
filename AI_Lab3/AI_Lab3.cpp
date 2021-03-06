// AI_Lab3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace sf;

// size of piece
int size = 56;
//offset from border to the gamefield
Vector2f offset(28, 28);
// pieces
Sprite pieces[24];
// recorded movements of pieces
std::string position = "";


time_t now;
time_t oldTime;

// game board matrix
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

// transform vector coordinates to chess notation
std::string toChessNote(Vector2f p)
{
	std::string  s = "";
	s += char(p.x / size + 97);
	s += char(8 - p.y / size + 49);
	return s;
}

// transform chess notation to vector coordinates
Vector2f toCoord(char a, char b)
{
	int x = int(a) - 97;
	int y = 7 - int(b) + 49;
	return Vector2f(float(x*size), float(y*size)) + offset;
}

// move the piece
void move(std::string str)
{
	Vector2f oldPos = toCoord(str[0], str[1]);
	Vector2f newPos = toCoord(str[2], str[3]);

	// remove the piece on new position if piece is attacked
	for (int i = 0; i < 24; i++)
		if (pieces[i].getPosition() == newPos) pieces[i].setPosition(-100, -100);

	// place a piece at the new position
	for (int i = 0; i < 24; i++)
		if(pieces[i].getPosition() == oldPos) pieces[i].setPosition(newPos);
}

// Is new position of piece out of play field?
bool isInPlayfield(Vector2f &position, Sprite &borders)
{
	return (position.x >= offset.x && position.x <= borders.getGlobalBounds().width - offset.x
		&& position.y >= offset.y && position.y <= borders.getGlobalBounds().height - offset.y);
}


bool isMoveforOneField(Vector2f &move)
{
	return (sqrt(move.x*move.x + move.y*move.y) <= size * 2);
}

bool isMovefortwoFields(Vector2f &move)
{
	return (sqrt(move.x*move.x + move.y*move.y) <= size * 3);
}


bool isManLegalMove(Sprite &piece, Vector2f &move)
{
	if (piece.getTextureRect() == IntRect(0, 0, size, size)) // if piece is black
		return ((move.x < 0 && move.y > 0) || (move.x > 0 && move.y > 0)); // if southwest or southeast 
	
	else if (piece.getTextureRect() == IntRect(size, 0, size, size)) // if piece is white
		return ((move.x < 0 && move.y < 0) || (move.x > 0 && move.y < 0)); // if northwest or northeast
	
	else if (piece.getTextureRect() == IntRect(0, size, size, size) ||
		piece.getTextureRect() == IntRect(size, size, size, size)) // if piece is queen
		return ((move.x < 0 && move.y > 0) || (move.x > 0 && move.y > 0) ||
		(move.x < 0 && move.y < 0) || (move.x > 0 && move.y < 0)); // in any diagonal direction
	
	else return false;
}


bool isLegalMove(Vector2f &oldPos, Vector2f &newPos, int n)
{
	Vector2f p = newPos - oldPos;

	if (isMoveforOneField(p) && isManLegalMove(pieces[n], p))
		return true;

	return false;
}

// load inital positions of pieces
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

	for (int i = 0; i < position.length(); i += 5)
		move(position.substr(i, 4));
}

int main()
{
	RenderWindow window(VideoMode(504, 504), "AI Draughts");

	Texture tBoard;
	tBoard.loadFromFile("../images/board.png");
	Texture tPieces;
	tPieces.loadFromFile("../images/pieces_all.png");

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
			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::BackSpace)
				{
					if (position.length() > 6)
						position.erase(position.length() - 6, 5);

					else if (position.length() == 5)
						position.erase();
					
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

					if (oldPos != newPos && isInPlayfield(newPos, sBoard) && isLegalMove(oldPos, newPos, n))
					{
						str = toChessNote(oldPos) + toChessNote(newPos);
						move(str);
						position += str + " ";
						std::cout << position << std::endl;
						pieces[n].setPosition(newPos);
					}
					else pieces[n].setPosition(oldPos);
				}
		
		}

		// computer move
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			str = "d6d5";

			oldPos = toCoord(str[0], str[1]);
			newPos = toCoord(str[2], str[3]);

			for (int i = 0; i < 24; i++)
				if (pieces[i].getPosition() == oldPos) n = i;

			// animation
			time(&now);

			for (int k = 0; k < 50; k++)
			{
				oldTime = now;
				time(&now);
				Vector2f p = newPos - oldPos;
				pieces[n].move(p.x / 50, p.y / 50);
				window.draw(sBoard);
				for (int i = 0; i < 24; i++)
					window.draw(pieces[i]);
				window.draw(pieces[n]);
				window.display();
			}

			move(str);
			position += str + " ";
			pieces[n].setPosition(newPos);
		}

		if (isMove) pieces[n].setPosition(pos.x - dx, pos.y - dy);

	window.clear();
	window.draw(sBoard);
	for (int i = 0; i < 24; i++) window.draw(pieces[i]);
	window.display();
	}

	return 0;
}