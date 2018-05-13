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
	bool isPlayerTurn = true;
	float dx = 0, dy = 0;
	Vector2f oldPos, newPos;
	int selectedPieceIdx = -1;

	std::string str = "";

	bool isSelected = true;

	Board *board = new Board();
	board->loadPosition();

	while (window.isOpen())
	{
		Vector2i mousePos = Mouse::getPosition(window);
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonReleased && isPlayerTurn)
			{
				if (event.key.code == Mouse::Left)
				{
					int i = board->getPieceIdxBySprite(mousePos); // get the index of piece clicked by mouse
					if (i != -1) // if we clicked on piece
					{
						if (selectedPieceIdx != i) // if the same piece was clicked
						{
							if (selectedPieceIdx != -1) // if there was a piece selected before
								board->getPieceByIdx(selectedPieceIdx).clearPossibleMoves(); // clear possible move of piece selected before
							selectedPieceIdx = i;
							isSelected = true;
							std::cout << "isSelected = " << isSelected << std::endl;
							std::cout << "Selected piece = " << selectedPieceIdx << std::endl;
							board->calculatePossibleMoves(board->getPieceByIdx(selectedPieceIdx));
							board->getPieceByIdx(selectedPieceIdx).printPossibleMoves();

						}
						else
						{
							selectedPieceIdx = -1;
							isSelected = false;
							std::cout << "isSelected = " << isSelected << std::endl;
							board->getPieceByIdx(i).clearPossibleMoves();
						}
					}
					else if (selectedPieceIdx != -1) // else if we clicked on empty field
					{
						sf::Vector2f snapedPos = sf::Vector2f(mousePos.x - (mousePos.x - int(board->getOffset().x)) % board->getPieceSize(),
							mousePos.y - ((mousePos.y - int(board->getOffset().y)) % board->getPieceSize()));

						std::string finalPos = board->toChessNote(snapedPos);

						int m = board->getPieceByIdx(selectedPieceIdx).getPossibleMoveIdx(finalPos); // get index of move containing final position
						if (m != -1)
						{
							//std::cout << "isSelected = " << isSelected << std::endl;
							std::cout << "Selected move: <" << board->getPieceByIdx(selectedPieceIdx).getPossibleMove(m).first
								<< ", " << board->getPieceByIdx(selectedPieceIdx).getPossibleMove(m).second << ">" << std::endl;

							sf::Vector2f oldPos = board->toCoord(board->getPieceByIdx(selectedPieceIdx).getPossibleMove(m).second[0],
								board->getPieceByIdx(selectedPieceIdx).getPossibleMove(m).second[1]);

							sf::Vector2f newPos = board->toCoord(board->getPieceByIdx(selectedPieceIdx).getPossibleMove(m).second[2],
								board->getPieceByIdx(selectedPieceIdx).getPossibleMove(m).second[3]);

							if (board->isMoveforOneField(oldPos, newPos))
							{
								board->getPieceByIdx(selectedPieceIdx).move(newPos);
								board->addPosition(board->getPieceByIdx(selectedPieceIdx).getPossibleMove(m));
								board->getPieceByIdx(selectedPieceIdx).clearPossibleMoves();
								std::cout << "Move to position " << std::endl;
								board->printPositions();
								isPlayerTurn = false;
								selectedPieceIdx = -1;
								isSelected = false;
							}
							else
							{
								for (int idx = 0; idx < board->getPieceByIdx(selectedPieceIdx).getPossibleMove(m).first; idx++)
								{

									sf::Vector2f newPos = board->toCoord(board->getPieceByIdx(selectedPieceIdx).getPossibleMove(m).second[idx * 5 + 2],
										board->getPieceByIdx(selectedPieceIdx).getPossibleMove(m).second[idx * 5 + 3]);
									sf::Vector2f attackPos = Vector2f((newPos.x + board->getPieceByIdx(selectedPieceIdx).getPosition().x) / 2, (newPos.y + board->getPieceByIdx(selectedPieceIdx).getPosition().y) / 2);
									board->getPieceByIdx(selectedPieceIdx).attack(newPos, board->getPieceByIdx(board->getPieceIdxOnPosition(attackPos)));
								}
								board->addPosition(board->getPieceByIdx(selectedPieceIdx).getPossibleMove(m));
								board->getPieceByIdx(selectedPieceIdx).clearPossibleMoves();
								std::cout << "Attacked position " << std::endl;
								board->printPositions();
								isPlayerTurn = false;
								selectedPieceIdx = -1;
								isSelected = false;
							}

						}
						else
						{
							//std::cout << "isSelected = " << isSelected << std::endl;
							std::cout << "Selected empty field" << std::endl;
						}
					}

				}

				// Undo move (undo 2 moves - one for computer and one for player)
				if (event.key.code == Mouse::Right)
					if (board->getPositionsSize() > 1)
					{
						board->deleteLastPosition();
						board->deleteLastPosition();
						board->loadPosition();
						board->printPositions();
					}
			}


		}

		if (/*Keyboard::isKeyPressed(Keyboard::Space) && */!isPlayerTurn)
		{
			//str = "f2g1";

			//oldPos = board->toCoord(str[0], str[1]);
			//newPos = board->toCoord(str[2], str[3]);

			//board->getPieceByIdx(board->getPieceIdxOnPosition(oldPos)).move(newPos);
			//board->addPosition(std::make_pair(1, str));
			//board->printPositions();
			std::cout << "Computer's turn\n";
			isPlayerTurn = true;
		}

		window.clear();
		window.draw(board->getSprite());
		for (int i = 0; i < board->getPiecesNum(); i++) window.draw(board->getPieceByIdx(i).getSprite());
		window.display();
	}



	return 0;
}

#pragma region unused

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

#pragma endregion
