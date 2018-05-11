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
	//std::vector<sf::Vector2f> m_possibleMoves;
	std::vector<std::pair<int, std::string>> m_possibleMoves;

public:
	
	Piece();
	Piece(Color color, sf::IntRect rect, sf::Vector2f position);

	void move(sf::Vector2f newPos);
	void attack(sf::Vector2f newPos, Piece attackedPiece);
	void promote();
	void unpromote();
	bool hasPossibleMoves() { return !m_possibleMoves.empty(); }
	//bool possibleMovesContains(std::string &move);
	//void addPossibleMoves(sf::Vector2f move) { m_possibleMoves.push_back(move); }
	void addPossibleMove(std::pair<int, std::string> move) { m_possibleMoves.push_back(move); }
	void printPossibleMoves();
	void clearPossibleMoves() { m_possibleMoves.clear(); }
	int getPossibleMoveIdx(std::string &move);
	std::pair<int, std::string> getPossibleMove(int idx);
	sf::Sprite& getSprite() { return *m_sprite; }
	int getSize() { return m_size; }
	Color getColor() { return m_color; }
	bool isKing() { return m_isKing; }
	//std::vector<sf::Vector2f> getPossibleMoves() { return m_possibleMoves; }
	sf::Vector2f getPosition() { return m_position; }

	~Piece();
};

