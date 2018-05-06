#pragma once
#include "stdafx.h"
#include "Piece.h"

Piece::Piece() {}

Piece::Piece(Color color, sf::IntRect rect, sf::Vector2f position)
	: m_color(color), m_position(position)
{
	m_texture = new sf::Texture();
	m_texture->loadFromFile("../images/pieces_all.png");
	m_sprite = new sf::Sprite();
	m_sprite->setTexture(*m_texture);
	m_sprite->setTextureRect(rect);
	m_sprite->setPosition(m_position);
	m_possibleMoves = new std::vector<sf::Vector2f>();
}

// Move the piece to newPos
void Piece::move(sf::Vector2f newPos)
{
	m_position = newPos;
	m_sprite->setPosition(newPos);
}

void Piece::attack(sf::Vector2f newPos, Piece &attackedPiece)
{
	move(newPos);
	attackedPiece.move(sf::Vector2f(-100.0f, -100.0f));
}

void Piece::promote()
{
	if (m_sprite->getTextureRect() == sf::IntRect(0, 0, m_size, m_size)) // if is black man
		m_sprite->setTextureRect(sf::IntRect(0, m_size, m_size, m_size)); // promote to black king
	else if (m_sprite->getTextureRect() == sf::IntRect(m_size, 0, m_size, m_size)) // if is white man
		m_sprite->setTextureRect(sf::IntRect(m_size, m_size, m_size, m_size)); // romote bo white king
}

void Piece::unpromote()
{
	if (m_sprite->getTextureRect() == sf::IntRect(0, m_size, m_size, m_size)) // if is black king
		m_sprite->setTextureRect(sf::IntRect(0, 0, m_size, m_size)); // unpromote to black man
	else if (m_sprite->getTextureRect() == sf::IntRect(m_size, m_size, m_size, m_size)) // if is white king
		m_sprite->setTextureRect(sf::IntRect(m_size, 0, m_size, m_size)); // romote bo white king
}



Piece::~Piece()
{

}
