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
	int m_size = 56;
	sf::Sprite m_sprite;
	bool m_isKing = false;
	sf::Vector2f m_position;
	std::vector<sf::Vector2f> *m_possibleMoves;


public:
	Piece(Color color, sf::Sprite sprite, sf::Vector2f position);
	

	void move(sf::Vector2f newPos);
	void promote();
	bool hasPossibleMoves();
	void attack();
	void removePiece();
	
	Color getColor() { return m_color; }
	int getSize() { return m_size; }
	sf::Sprite getSprite() { return m_sprite; }
	bool isKing() { return m_isKing; }
	std::vector<sf::Vector2f>* getPossibleMoves() { return m_possibleMoves; }
	sf::Vector2f getPosition() { return m_position; }

	~Piece();
};

