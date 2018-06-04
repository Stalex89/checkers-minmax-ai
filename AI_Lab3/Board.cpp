#include "stdafx.h"
#include "Board.h"
#include "Piece.h"


Board::Board()
{
	//m_texture = new sf::Texture();
	//m_texture->loadFromFile("../images/board.png");
	//m_sprite = new sf::Sprite();
	//m_sprite->setTexture(*m_texture);
	m_pieces.reserve(24);
}

Board::Board(Board &board)
{
	//m_texture = new sf::Texture();
	//m_texture->loadFromFile("../images/board.png");
	//m_sprite = new sf::Sprite();
	//m_sprite->setTexture(*m_texture);
	m_pieces = board.getPieces();
	m_positions = board.getPositions();
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

	//int board[8][8] =
	//{
	//	0,  0,  0,  0,  0,  0,  0,  0,
	//	0,  0,  0,  0,  0,  0,  0,  0,
	//	0,  0,  0,  0,  0, -1,  0,  0,
	//	0,  0,  0,  0,  0,  0,  0,  0,
	//	0,  0,  0,  0,  0,  0,  0,  0,
	//	0,  0,  0,  0,  0,  0,  0,  0,
	//	0,  1,  0,  0,  0,  0,  0,  0,
	//	0,  0,  0,  0,  0,  0,  0,  0,
	//};

	//int board[8][8] =
	//{
	//	0, 0, 0, 0, 0, 0, 0, 0,
	//	0, 0, 0, 0, 0, 0, 0, 0,
	//	0, 0, 0, 0, 0, 0, 0, 0,
	//	0, 0, 0, 0, 0, 0, 0, 0,
	//	0, -1, 0, -1, 0, 0, 0, 0,
	//	0, 0, 0, 0, 0, 0, 0, 0,
	//	0, 0, 0, -1, 0, -1, 0, 0,
	//	0, 0, 0, 0, 1, 0, 0, 0,
	//};

	//int board[8][8] =
	//{
	//	0, 0, 0, 0, 0, 0, 0, 0,
	//	0, 0, 1, 0, 0, 0, 0, 0,
	//	0, -1, 0, 0, 0, 0, 0, 0,
	//	0, 0, 0, 0, 0, 0, 0, 0,
	//	0, -1, 0, 0, 0, 0, 0, 0,
	//	0, 0, 0, 0, 0, 0, 0, 0,
	//	0, 0, 0, -1, 0, -1, 0, 0,
	//	0, 0, 0, 0, 0, 0, 0, 0,
	//};

	// clear pieces array
	m_pieces.clear();

	//int k = 0;
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
			//m_pieces.at(k) = Piece(color, rect, position);
			//k++;
			//m_pieces.push_back(Piece(color, rect, position));
			m_pieces.emplace_back(color, position);
		}


	// do all movements
	for (int i = 0; i < m_positions.size(); i ++)
	{
		std::string moves = m_positions.at(i).second;
		for (int j = 0; j < moves.length(); j += 5)
		{
			sf::Vector2f oldPos = toCoord(moves[j], moves[j + 1]);
			sf::Vector2f newPos = toCoord(moves[j+2], moves[j+3]);
		
			if (isMoveforOneField(oldPos, newPos))
			{
				m_pieces.at(getPieceIdxOnPosition(oldPos)).move(newPos);
				if (m_pieces.at(getPieceIdxOnPosition(newPos)).getPosition().y == m_offset.y && !m_pieces.at(getPieceIdxOnPosition(newPos)).isKing())
				{
					//std::cout << "Promoted to king " << std::endl;
					m_pieces.at(getPieceIdxOnPosition(newPos)).promote();
				}
			}
			else
			{
				sf::Vector2f attackPos = sf::Vector2f((newPos.x + oldPos.x) / 2, (newPos.y + oldPos.y) / 2);
				m_pieces.at(getPieceIdxOnPosition(oldPos)).capture(newPos, m_pieces.at(getPieceIdxOnPosition(attackPos)));		
			}
			
		}
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
//bool Board::isInPlayfield(sf::Vector2f &position)
//{
//	return (position.x >= m_offset.x && position.x <= m_sprite->getGlobalBounds().width - m_offset.x - m_pieceSize
//		&& position.y >= m_offset.y && position.y <= m_sprite->getGlobalBounds().height - m_offset.y - m_pieceSize);
//}



//bool Board::isMoveforOneField(sf::Vector2f &move)
//{
//	return (sqrt(move.x*move.x + move.y*move.y) <= m_pieceSize * 2);
//}

//
//bool isMovefortwoFields(Vector2f &move)
//{
//	return (sqrt(move.x*move.x + move.y*move.y) <= size * 3);
//}


//bool Board::isManLegalMove(Piece &piece, sf::Vector2f &move)
//{
//	if(piece.isKing())
//		return ((move.x < 0 && move.y > 0) || (move.x > 0 && move.y > 0) ||
//		(move.x < 0 && move.y < 0) || (move.x > 0 && move.y < 0)); // in any diagonal direction
//	else 
//	{
//		if (piece.getColor() == Piece::Color::BLACK) // if piece is black
//			return ((move.x < 0 && move.y > 0) || (move.x > 0 && move.y > 0)); // if southwest or southeast 
//
//		else if (piece.getColor() == Piece::Color::WHITE) // if piece is white
//			return ((move.x < 0 && move.y < 0) || (move.x > 0 && move.y < 0)); // if northwest or northeast
//	}
//	
//	return false;
//}


//bool Board::isLegalMove(sf::Vector2f &oldPos, sf::Vector2f &newPos, int n)
//{
//	sf::Vector2f p = newPos - oldPos;
//
//	if (!m_pieces.at(n).isKing())
//		if (isMoveforOneField(p) && isManLegalMove(m_pieces[n], p))
//			return true;
//
//	return false;
//}


Board::~Board()
{
	//delete m_sprite;
	//m_sprite = nullptr;
	//delete m_texture;
	//m_texture = nullptr;
}

// Get all legal moves for string depending on color or king 
std::string Board::getLegalMoves(Piece &piece, sf::Vector2f position)
{
	std::string moves = "";
	if (!piece.isKing())
	{
		if (piece.getColor() == Piece::Color::BLACK)
		{
			moves += toChessNote(position) + toChessNote(position + sf::Vector2f((float)(-m_pieceSize), (float)(m_pieceSize))) + " ";
			moves += toChessNote(position) + toChessNote(position + sf::Vector2f((float)(m_pieceSize), (float)(m_pieceSize))) + " ";
		}
		else // piece is White
		{
			moves += toChessNote(position) + toChessNote(position + sf::Vector2f((float)(-m_pieceSize), (float)(-m_pieceSize))) + " ";
			moves += toChessNote(position) + toChessNote(position + sf::Vector2f((float)(m_pieceSize), (float)(-m_pieceSize))) + " ";

		}
	}
	else
	{
		moves += toChessNote(position) + toChessNote(position + sf::Vector2f((float)(-m_pieceSize), (float)(m_pieceSize))) + " ";
		moves += toChessNote(position) + toChessNote(position + sf::Vector2f((float)(m_pieceSize), (float)(m_pieceSize))) + " ";
		moves += toChessNote(position) + toChessNote(position + sf::Vector2f((float)(-m_pieceSize), (float)(-m_pieceSize))) + " ";
		moves += toChessNote(position) + toChessNote(position + sf::Vector2f((float)(m_pieceSize), (float)(-m_pieceSize))) + " ";
	}

	return moves;
}


//bool Board::isFreePosition(std::string position)
//{
//	for (int i = 0; i < m_pieces.size(); i++)
//	{
//		if (m_pieces[i].getPosition() == toCoord(field[0], field[1]))
//			return false;
//	}
//	return true;
//}


void Board::calculatePossibleMoves(Piece &piece)
{
	std::pair<int, std::string> attackChain;

	std::string legalMoves = getLegalMoves(piece, piece.getPosition()); // get all legal moves for piece

	for (int i = 0; i < legalMoves.length(); i += 5) //iterate over all legal moves
	{
		//std::string legalPosition = legalMoves.substr(i + 2, 2); // get position after move
		sf::Vector2f legalPosition = toCoord(legalMoves[i+2], legalMoves[i+3]);
		if (isInPlayfield(legalPosition)) // if position is is play field
		{
			int k = getPieceIdxOnPosition(legalPosition); // check if there is a piece on that position
			if (k == -1) // if no piece found on that position
				piece.addPossibleMove(std::make_pair(1, legalMoves.substr(i, 4))); // add move to possible moves
			else
			{
				if (m_pieces[k].getColor() != piece.getColor())// if it's opponents piece
				{

					if (isCapturePossible(piece.getPosition(), m_pieces[k])) // if we can attack enemy piece
					{
						
						// get the position of piece after possible attack
						sf::Vector2f position = m_pieces[k].getPosition() + (m_pieces[k].getPosition() - piece.getPosition());

						std::string move = toChessNote(piece.getPosition()) + toChessNote(position) + " ";
						attackChain = std::make_pair(1, move); // create an attack chain
						captureChainRecursiveSearch(piece, position, attackChain); // call recursive search of attack chain
					}

				}
			}
		}
	}
}

void Board::captureChainRecursiveSearch(Piece &piece, sf::Vector2f position, std::pair<int, std::string> attackChain)
{
	piece.addPossibleMove(attackChain); // add simple attack move

	std::string legalMoves = getLegalMoves(piece, position); // get all legal moves for piece
	for (int i = 0; i < legalMoves.length(); i += 5) //iterate over all legal moves
	{
		//std::string legalPosition = legalMoves.substr(i + 2, 2); // get position after move
		sf::Vector2f legalPosition = toCoord(legalMoves[i + 2], legalMoves[i + 3]);
		if (isInPlayfield(legalPosition)) // if position is is play field
		{
			int k = getPieceIdxOnPosition(legalPosition); // check if there is a piece on that position
			// if there is a piece found on that position and it is enemy piece
			if (k != -1)
				if(m_pieces[k].getColor() != piece.getColor())
					if (isCapturePossible(position, m_pieces[k]) && !isInCaptureChain(m_pieces[k].getPosition(), attackChain)) // if we can attack enemy piece
					{						
						// get new position of piece
						sf::Vector2f newPosition = m_pieces[k].getPosition() + (m_pieces[k].getPosition() - position);
						std::string move = toChessNote(position) + toChessNote(newPosition) + " ";
						captureChainRecursiveSearch(piece, newPosition, std::make_pair(attackChain.first + 1, attackChain.second + move)); // call recursive search of attack chain
					}
		}
	}
}

bool Board::isInCaptureChain(sf::Vector2f position, std::pair<int, std::string> attackChain)
{
	std::string chain = attackChain.second;
	for (int i = 0; i < chain.length(); i += 5)
	{
		sf::Vector2f attackPos = sf::Vector2f((toCoord(chain[i], chain[i + 1]).x + toCoord(chain[i + 2], chain[i + 3]).x) / 2,
			(toCoord(chain[i], chain[i + 1]).y + toCoord(chain[i + 2], chain[i + 3]).y) / 2);
		if (attackPos == position)
			return true;
	}

	return false;
}



bool Board::isInPlayfield(sf::Vector2f position)
{
	//return (position.x >= m_offset.x && position.x <= m_sprite->getGlobalBounds().width - m_offset.x - m_pieceSize
		//&& position.y >= m_offset.y && position.y <= m_sprite->getGlobalBounds().height - m_offset.y - m_pieceSize);
	return (position.x >= m_offset.x && position.x <= m_width - m_offset.x - m_pieceSize
		&& position.y >= m_offset.y && position.y <= m_height - m_offset.y - m_pieceSize);
}

int Board::getPieceIdxOnPosition(sf::Vector2f position)
{
	for (int i = 0; i < m_pieces.size(); i++)
	{
		if (m_pieces[i].getPosition() == position)
			return i;
	}
	return -1;
}

//int Board::getPieceIdxBySprite(sf::Vector2i mousePos)
//{
//	for (int i = 0; i < m_pieces.size(); i++)
//	{
//		if (m_pieces.at(i).getSprite().getGlobalBounds().contains(float(mousePos.x), float(mousePos.y)))
//			return i;
//	}
//	return -1;
//}

bool Board::isCapturePossible(sf::Vector2f position, Piece &enemyPiece)
{
	
	// get the position after jumping over enemy piece
	sf::Vector2f newPos = enemyPiece.getPosition() + (enemyPiece.getPosition() - position);


	// return if there is no piece on that position and it is in playfield
	return(getPieceIdxOnPosition(newPos) == -1 && isInPlayfield(newPos)); 
}

bool Board::isMoveforOneField(sf::Vector2f oldPos, sf::Vector2f newPos)
{
	sf::Vector2f move = newPos - oldPos;
	return sqrt((move.x * move.x) + (move.y * move.y)) <= 2 * m_pieceSize;
}

//void Board::removePieceByIdx(int idx)
//{
//	m_pieces.erase(m_pieces.begin() + idx);
//}

void Board::printPositions()
{
	std::cout << "Positions: ";
	std::for_each(m_positions.begin(), m_positions.end(), [](auto move) { std::cout << "<" << move.first << ", " << move.second << ">, ";});
	std::cout << '\n';
}

bool Board::isGameOver(Piece::Color color)
{
	// Game ends if
	// 1) no enemy pieces left on board
	// 2) all enemy pieces are locked

	//std::vector<Piece> leftPieces;
	
	for (int i = 0; i < m_pieces.size(); i++)
	{
		Piece p = m_pieces.at(i);
		if (p.getColor() == color) // if the piece is that color
			if (m_pieces.at(i).getPosition() != sf::Vector2f(-100.0f, -100.0f)) // if it is not outside of the field (taken) 
				if (m_pieces.at(i).hasPossibleMoves()) // if it is not locked
					return false;
	}
	return true;
}

void Board::calculateAllMovesForColor(Piece::Color color)
{
	for (int h = 0; h < m_pieces.size(); h++)
		if (m_pieces.at(h).getColor() == color)
			calculatePossibleMoves(m_pieces.at(h));
}

void Board::clearAllMovesForColor(Piece::Color color)
{
	for (int h = 0; h < m_pieces.size(); h++)
		if (m_pieces.at(h).getColor() == color)
			m_pieces.at(h).clearPossibleMoves();
}