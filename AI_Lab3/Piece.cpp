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
}

// Move the piece to newPos
void Piece::move(sf::Vector2f newPos)
{
	m_position = newPos;
	m_sprite->setPosition(newPos);
}


void Piece::capture(sf::Vector2f newPos, Piece &attackedPiece)
{
	move(newPos);
	attackedPiece.move(sf::Vector2f(-100.0f, -100.0f));
	
}

void Piece::promote()
{
	if (m_sprite->getTextureRect() == sf::IntRect(0, 0, m_size, m_size)) // if is black man
	{
		m_sprite->setTextureRect(sf::IntRect(0, m_size, m_size, m_size)); // promote to black king
		m_isKing = true;
	}
	else if (m_sprite->getTextureRect() == sf::IntRect(m_size, 0, m_size, m_size)) // if is white man
	{
		m_sprite->setTextureRect(sf::IntRect(m_size, m_size, m_size, m_size)); // romote bo white king
		m_isKing = true;
	}
}


void Piece::printPossibleMoves()
{
	std::cout << "Possible moves: ";
	for (int i = 0; i < m_possibleMoves.size(); i++)
		std::cout << "<" << m_possibleMoves.at(i).first << ", " << m_possibleMoves.at(i).second << ">, ";
	std::cout << '\n';
}


int Piece::getPossibleMoveIdx(std::string &move)
{
	for (int i = 0; i < m_possibleMoves.size(); i++)
		if (m_possibleMoves.at(i).second.find(move) != std::string::npos)
			return i;
	
	return -1;
}

std::pair<int, std::string> Piece::getPossibleMove(int idx)
{
	return m_possibleMoves.at(idx);
}

Piece::~Piece()
{

	//delete m_sprite;
	//m_sprite = nullptr;
	//delete m_texture;
	//m_texture = nullptr;
}
