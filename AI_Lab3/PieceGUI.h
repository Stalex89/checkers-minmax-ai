#pragma once
#include "stdafx.h"
#include "Piece.h"


class PieceGUI
{
	sf::Texture *m_texture;
	sf::Sprite *m_sprite;
	int m_size = 56;


public:
	PieceGUI(sf::IntRect rect, sf::Vector2f position);
	~PieceGUI();

	void move(sf::Vector2f position);
	void capture(sf::Vector2f newPos, PieceGUI &attackedPiece);
	void promote(Piece::Color color);

	sf::Sprite& getSprite() { return *m_sprite; }
	int getSize() { return m_size; }
};

