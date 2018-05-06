#include "stdafx.h"
#include "Board.h"
#include "Piece.h"


Board::Board()
{
	m_texture = new sf::Texture();
	m_texture->loadFromFile("../images/board.png");
	m_sprite = new sf::Sprite();
	m_sprite->setTexture(*m_texture);
	init();
}


void Board::init()
{
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			m_board.at(i).at(j) = sf::Vector2f(float(i * m_pieceSize), float(j * m_pieceSize)) + m_offset;
}

void Board::loadPosition()
{
	int board[8][8] =
	{
		0, -1,  0, -1,  0, -1,  0, -1,
		-1,  0, -1,  0, -1,  0, -1,  0,
		0, -1,  0, -1,  0, -1,  0, -1,
		0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,
		1,  0,  1,  0,  1,  0,  1,  0,
		0,  1,  0,  1,  0,  1,  0,  1,
		1,  0,  1,  0,  1,  0,  1,  0,
	};



	int k = 0;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{

			int n = board[i][j];
			// check if position is not 0
			if (!n) continue;
			int x = (n > 0) ? 1 : 0;
			Piece::Color color = (n > 0) ? Piece::Color::WHITE : Piece::Color::BLACK;
			sf::IntRect rect = (n > 0) ? sf::IntRect(m_pieceSize, 0, m_pieceSize, m_pieceSize) :
				sf::IntRect(0, 0, m_pieceSize, m_pieceSize);
			// set part of pieces texture depending on the argument on board 
			sf::Vector2f position = sf::Vector2f(float(m_pieceSize * j), float(m_pieceSize * i)) + m_offset;
			m_pieces.at(k) = Piece(color, rect, position);
			k++;
		}

	for (int i = 0; i < m_positions.length(); i += 5)
	{
		std::string substr = m_positions.substr(i, 4);
		sf::Vector2f oldPos = toCoord(substr[0], substr[1]);
		sf::Vector2f newPos = toCoord(substr[2], substr[3]);
		std::for_each(m_pieces.begin(), m_pieces.end(), [&oldPos, &newPos](Piece &p)
		{ if (p.getPosition() == oldPos)
			p.move(newPos); 
		});
	}

}

// transform vector coordinates to chess notation
std::string Board::toChessNote(sf::Vector2f position)
{
	std::string  s = "";
	s += char(position.x / m_pieceSize + 97);
	s += char(8 - position.y / m_pieceSize + 49);
	return s;
}

sf::Vector2f Board::toCoord(char a, char b)
{
	int x = int(a) - 97;
	int y = 7 - int(b) + 49;
	return sf::Vector2f(float(x * m_pieceSize), float(y * m_pieceSize)) + m_offset;
}

// Is new position of piece out of play field?
bool Board::isInPlayfield(sf::Vector2f &position)
{
	return (position.x >= m_offset.x && position.x <= m_sprite->getGlobalBounds().width - m_offset.x
		&& position.y >= m_offset.y && position.y <= m_sprite->getGlobalBounds().height - m_offset.y);
}

bool Board::isLegalMove(sf::Vector2f &oldPos, sf::Vector2f &newPos, int n)
{
	return true;
}

Board::~Board()
{
	delete m_sprite;
	m_sprite = nullptr;
}
