#include "stdafx.h"
#include "BoardGUI.h"
#include "PieceGUI.h"


BoardGUI::BoardGUI()
{
	m_texture = new sf::Texture();
	m_texture->loadFromFile("../images/board.png");
	m_sprite = new sf::Sprite();
	m_sprite->setTexture(*m_texture);
	m_pieces.reserve(24);
}


BoardGUI::~BoardGUI()
{
	delete m_sprite;
	m_sprite = nullptr;
	delete m_texture;
	m_texture = nullptr;
}

void BoardGUI::loadPosition(std::vector<Piece> pieces)
{
	// clear pieces array
	m_pieces.clear();

	for (int i = 0; i < pieces.size(); i++)
	{
		sf::IntRect rect = (pieces.at(i).getColor() == Piece::Color::WHITE ) ? sf::IntRect(m_pieceSize, 0, m_pieceSize, m_pieceSize) :
			sf::IntRect(0, 0, m_pieceSize, m_pieceSize);
		m_pieces.emplace_back(rect, pieces.at(i).getPosition());
	}
}

int BoardGUI::getPieceIdxBySprite(sf::Vector2i mousePos)
{
	for (int i = 0; i < m_pieces.size(); i++)
	{
		if (m_pieces.at(i).getSprite().getGlobalBounds().contains(float(mousePos.x), float(mousePos.y)))
			return i;
	}
	return -1;
}