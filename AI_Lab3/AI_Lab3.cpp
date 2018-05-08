// AI_Lab3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Piece.h"
#include "Board.h"

using namespace sf;


int main()
{
	RenderWindow window(VideoMode(504, 504), "AI Draughts");
	int pieceSize = 56;
	bool isMove = false;
	float dx = 0, dy = 0;
	Vector2f oldPos, newPos;
	int n = -1;

	std::string str = "";

	bool isSelected = true;

	Board *board = new Board();
	board->loadPosition();

	//while (window.isOpen())
	//{
	//	Vector2i mousePos = Mouse::getPosition(window);
	//	sf::Event event;

	//	while (window.pollEvent(event))
	//	{
	//		if (event.type == sf::Event::Closed)
	//			window.close();

	//		if (event.type == Event::MouseButtonPressed)
	//			if (event.key.code == Mouse::Right)
	//			{
	//				if (board->getPositions().length() > 6)
	//					board->getPositions().erase(board->getPositions().length() - 6, 5);

	//				else if (board->getPositions().length() == 5)
	//					board->getPositions().erase();
	//								
	//				board->loadPosition();


	//			}


	//		if (event.type == Event::MouseButtonPressed)
	//			if (event.key.code == Mouse::Left)
	//				for (int i = 0; i < 24; i++)
	//					if (board->getPiece(i).getSprite().getGlobalBounds().contains(float(mousePos.x), float(mousePos.y)))
	//					{
	//						isMove = true; n = i;
	//						dx = mousePos.x - board->getPiece(i).getPosition().x;
	//						dy = mousePos.y - board->getPiece(i).getPosition().y;
	//						oldPos = board->getPiece(i).getPosition();
	//					}

	//		if (event.type == Event::MouseButtonReleased)
	//			if (event.key.code == Mouse::Left)
	//			{
	//				isMove = false;
	//				Vector2f p = board->getPiece(n).getSprite().getPosition();
	//				Vector2f newPos = Vector2f(float(pieceSize * int(p.x / pieceSize)),
	//					float(pieceSize*int(p.y / pieceSize))) + board->getOffset();
	//				if(board->isInPlayfield(newPos) && board->isLegalMove(oldPos,newPos,n))
	//				{
	//					str = board->toChessNote(oldPos) + board->toChessNote(newPos);
	//					board->getPiece(n).move(newPos);
	//					board->getPositions() += str + " ";
	//					std::cout << board->getPositions() << std::endl;
	//				}
	//				else board->getPiece(n).getSprite().setPosition(oldPos);
	//			}
	//	}
	//	if (isMove) board->getPiece(n).getSprite().setPosition(mousePos.x - dx, mousePos.y - dy);

	//	window.clear();
	//	window.draw(board->getSprite());
	//	for (int i = 0; i < 24; i++) window.draw(board->getPiece(i).getSprite());
	//	window.display();
	//}

	while (window.isOpen())
	{
		Vector2i mousePos = Mouse::getPosition(window);
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonReleased)
				if (event.key.code == Mouse::Left)
				{

					for (int i = 0; i < 24; i++)
						if (board->getPiece(i).getSprite().getGlobalBounds().contains(float(mousePos.x), float(mousePos.y)))
						{
							if (n != i)
							{
								n = i;
								isSelected = true;
								std::cout << "isSelected = " << isSelected << std::endl;
								std::cout << "Selected piece = " << i << std::endl;
								board->calculatePossibleMoves(board->getPiece(i));
								board->getPiece(i).printPossibleMoves();
								board->getPiece(i).clearPossibleMoves();
							}
							else
							{
								n = -1;
								isSelected = false;
								std::cout << "isSelected = " << isSelected << std::endl;
							}
						}

				}
		}

	window.clear();
	window.draw(board->getSprite());
	for (int i = 0; i < 24; i++) window.draw(board->getPiece(i).getSprite());
	window.display();
	}



	return 0;
}