#pragma once
#include "stdafx.h"
#include "Board.h"
#include "Piece.h"

class Node
{
	Node *m_parent;

	// for preserving the state of the board
	Board *m_board;

	// alpha and beta 
	std::pair<int, std::vector<std::pair<int, std::string>>> m_alphaPos;
	std::pair<int, std::vector<std::pair<int, std::string>>> m_betaPos;


public:
	Node(Node* parent, Board &board);

	Board& getNodeBoard() { return *m_board; }
	void setNodeBoard(Board &board) 
	{
		delete m_board; 
		m_board = new Board(board);
	}

	std::pair<int, std::vector<std::pair<int, std::string>>> getAlphaPos() { return m_alphaPos; }
	std::pair<int, std::vector<std::pair<int, std::string>>> getBetaPos() { return m_betaPos; }
	void setAlphaPos(const std::pair<int, std::vector<std::pair<int, std::string>>> alphaPos) { m_alphaPos = alphaPos; }
	void setBetaPos(const std::pair<int, std::vector<std::pair<int, std::string>>> betaPos) { m_betaPos = betaPos; }

	~Node();
};

