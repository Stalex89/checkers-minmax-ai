#pragma once
#include "stdafx.h"
#include "Board.h"
#include "PieceGUI.h"
#include "Piece.h"

class BoardGUI
{
	sf::Texture *m_texture;
	sf::Sprite *m_sprite;
	std::vector<PieceGUI> m_pieces;
	int m_pieceSize = 56;
	int m_width = 504;
	int m_height = 504;
	sf::Vector2f m_offset = sf::Vector2f(28, 28);

public:

	BoardGUI();
	~BoardGUI();

	void loadPosition(std::vector<Piece> pieces);

	int getXBound() { return (int)(m_sprite->getGlobalBounds().width); }
	int getYBound() { return (int)(m_sprite->getGlobalBounds().height); }
	PieceGUI& getPieceByIdx(int idx) { return m_pieces.at(idx); }
	int getPieceIdxBySprite(sf::Vector2i mousePos);

	sf::Sprite& getSprite() { return *m_sprite; };
	int getPieceSize() { return m_pieceSize; }
	std::vector<PieceGUI>& getPieces() { return m_pieces; }
	sf::Vector2f getOffset() { return m_offset; }


};

