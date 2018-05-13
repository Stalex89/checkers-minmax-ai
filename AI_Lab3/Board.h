#pragma once
#include "stdafx.h"
#include "Piece.h"

class Board
{
	sf::Texture *m_texture;
	sf::Sprite *m_sprite;

	std::vector<std::pair<int, std::string>> m_positions;
	std::vector<Piece> m_pieces;

	int m_pieceSize = 56;
	sf::Vector2f m_offset = sf::Vector2f(28,28);

public:
	Board();
	void loadPosition();

	std::string toChessNote(sf::Vector2f position);
	sf::Vector2f toCoord(char a, char b);

	int getPiecesNum() { return m_pieces.size(); }
	Piece& getPieceByIdx(int idx) { return m_pieces.at(idx); }
	int getPieceIdxOnPosition(sf::Vector2f position);
	int getPieceIdxBySprite(sf::Vector2i mousePos);

	void addPosition(std::pair<int, std::string> position) { m_positions.push_back(position); }
	void deleteLastPosition() { m_positions.pop_back(); }
	int getPositionsSize() { return m_positions.size(); }
	void printPositions();

	void calculatePossibleMoves(Piece &piece);
	bool isMoveforOneField(sf::Vector2f oldPos, sf::Vector2f newPos);
	bool isInPlayfield(sf::Vector2f position);
	bool isAttackPossible(sf::Vector2f position, Piece &enemyPiece);
	bool isInAttackChain(sf::Vector2f position, std::pair<int, std::string> attackChain);
	void AttackRecursiveSearch(Piece &piece, sf::Vector2f position, std::pair<int, std::string> attackChain);
	std::string getLegalMoves(Piece &piece, sf::Vector2f position);



	sf::Sprite& getSprite() { return *m_sprite; };
	int getPieceSize() { return m_pieceSize; }
	sf::Vector2f getOffset() { return m_offset; }
	
	bool isGameOver(Piece::Color color);

	~Board();
};

