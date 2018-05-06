#pragma once
#include "stdafx.h"
#include "Piece.h"


Piece::Piece(Color color, sf::Sprite sprite, sf::Vector2f position)
	: m_color(color), m_sprite(sprite), m_position(position)
{
	m_possibleMoves = new std::vector<sf::Vector2f>();
}

// Move the piece to newPos
void Piece::move(sf::Vector2f newPos)
{

}


Piece::~Piece()
{

}
