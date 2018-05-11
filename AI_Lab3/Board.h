#pragma once
#include "stdafx.h"
#include "Piece.h"

class Board
{

	//std::array<std::array<sf::Vector2f,8>,8> m_board;
	sf::Texture *m_texture;
	sf::Sprite *m_sprite;
	int m_pieceSize = 56;
	std::string m_positions = "";
	std::vector<Piece> m_pieces;
	sf::Vector2f m_offset = sf::Vector2f(28,28);

public:
	Board();
	//void init();
	void loadPosition();
	std::string toChessNote(sf::Vector2f position);
	sf::Vector2f toCoord(char a, char b);
	int getPiecesNum() { return m_pieces.size(); }
	Piece& getPieceByIdx(int idx) { return m_pieces.at(idx); }
	int getPieceIdxOnPosition(std::string position);
	sf::Sprite& getSprite() { return *m_sprite; };
	int getPieceSize() { return m_pieceSize; }
	sf::Vector2f getOffset() { return m_offset; }
	std::string& getPositions() { return m_positions; }
	void calculatePossibleMoves(Piece &piece);

	//bool isInPlayfield(sf::Vector2f &position);
	bool isMoveforOneField(sf::Vector2f oldPos, sf::Vector2f newPos);
	//bool isManLegalMove(Piece &piece, sf::Vector2f &move);
	//bool isLegalMove(sf::Vector2f &oldPos, sf::Vector2f &newPos, int n);

	int getPieceIdxBySprite(sf::Vector2i mousePos);
	//void MovesSearch(Piece &piece, sf::Vector2f position, bool hasAttacked, std::pair<int, std::string> attackChain);
	void AttackRecursiveSearch(Piece &piece, sf::Vector2f position, std::pair<int, std::string> attackChain);
	std::string getLegalMoves(Piece &piece, sf::Vector2f position);
	//bool isFreePosition(std::string position);
	bool isInPlayfield(std::string position);
	bool isAttackPossible(sf::Vector2f position, Piece &enemyPiece);
	
	~Board();
};

