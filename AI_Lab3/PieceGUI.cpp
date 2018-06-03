#include "stdafx.h"
#include "PieceGUI.h"


PieceGUI::PieceGUI(sf::IntRect rect, sf::Vector2f position)
{
	m_texture = new sf::Texture();
	m_texture->loadFromFile("../images/pieces_all.png");
	m_sprite = new sf::Sprite();
	m_sprite->setTexture(*m_texture);
	m_sprite->setTextureRect(rect);
	m_sprite->setPosition(position);
}


PieceGUI::~PieceGUI()
{
	delete m_sprite;
	m_sprite = nullptr;
	delete m_texture;
	m_texture = nullptr;
}

void PieceGUI::move(sf::Vector2f position)
{
	m_sprite->setPosition(position);
}

void PieceGUI::capture(sf::Vector2f newPos, PieceGUI &attackedPiece)
{
	move(newPos);
	attackedPiece.move(sf::Vector2f(-100.0f, -100.0f));

}

void PieceGUI::promote(Piece::Color color)
{
	if (color == Piece::Color::BLACK)
		m_sprite->setTextureRect(sf::IntRect(0, m_size, m_size, m_size)); //promote to black king
	else if (color == Piece::Color::WHITE)
		m_sprite->setTextureRect(sf::IntRect(m_size, m_size, m_size, m_size)); // promote to white king
}