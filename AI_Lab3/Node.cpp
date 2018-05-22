#include "stdafx.h"
#include "Node.h"


Node::Node (Node* parent, Board& board) 
{
	m_parent = parent;
	m_board = new Board(board);
	m_alphaPos = std::make_pair(std::numeric_limits<int>::min(), board.getPositions());
	m_betaPos = std::make_pair(std::numeric_limits<int>::max(), board.getPositions());

}


Node::~Node()
{
	m_parent = nullptr;
	delete m_board;
	m_board = nullptr;
}
