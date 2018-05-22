#pragma once
#include "stdafx.h"



class Piece
{
public:
	enum Color
	{
		BLACK,
		WHITE,
		MAX_COLOR,
	};

private:
	Color m_color;
	sf::Texture *m_texture;
	sf::Sprite *m_sprite;
	int m_size = 56;
	bool m_isKing = false;
	sf::Vector2f m_position;
	std::vector<std::pair<int, std::string>> m_possibleMoves;

public:
	
	Piece();
	Piece(Color color, sf::IntRect rect, sf::Vector2f position);

	void move(sf::Vector2f newPos);
	void capture(sf::Vector2f newPos, Piece &capturedPiece);
	void promote();

	bool hasPossibleMoves() { return !m_possibleMoves.empty(); }
	void addPossibleMove(std::pair<int, std::string> move) { m_possibleMoves.push_back(move); }
	void printPossibleMoves();
	void clearPossibleMoves() { m_possibleMoves.clear(); }

	int getPossibleMoveIdx(std::string &move);
	std::pair<int, std::string> getPossibleMove(int idx);
	std::vector<std::pair<int, std::string>> getAllPossibleMoves() { return m_possibleMoves; }
	sf::Sprite& getSprite() { return *m_sprite; }
	int getSize() { return m_size; }
	Color getColor() { return m_color; }
	bool isKing() { return m_isKing; }
	sf::Vector2f getPosition() { return m_position; }

	~Piece();
};

