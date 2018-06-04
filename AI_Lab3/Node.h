#pragma once
#include "stdafx.h"
#include "Board.h"
#include "Piece.h"

class Node
{
	Node *m_parent;

	// for preserving the state of the board
	Board *m_board;

	std::vector<std::pair<int, std::string>> m_moves;
	// alpha and beta 
	std::pair<int, std::vector<std::pair<int, std::string>>> m_alphaPos;
	//std::pair<int, std::pair<int, std::string>> m_alphaPos;
	std::pair<int, std::vector<std::pair<int, std::string>>> m_betaPos;
	//std::pair<int, std::pair<int, std::string>> m_betaPos;


public:
	Node(Node* parent, Board &board);

	Board& getNodeBoard() { return *m_board; }
	void setNodeBoard(Board &board) 
	{
		delete m_board; 
		m_board = new Board(board);
	}

	std::pair<int, std::vector<std::pair<int, std::string>>> getAlphaPos() { return m_alphaPos; }
	
	//std::pair<int, std::pair<int, std::string>> getAlphaPos() { return m_alphaPos; }
	
	std::pair<int, std::vector<std::pair<int, std::string>>> getBetaPos() { return m_betaPos; }
	
	//std::pair<int, std::pair<int, std::string>> getBetaPos() { return m_betaPos; }
	
	void setAlphaPos(const std::pair<int, std::vector<std::pair<int, std::string>>> alphaPos) { m_alphaPos = alphaPos; }
	
	//void setAlphaPos(const std::pair<int, std::pair<int, std::string>> alphaPos) { m_alphaPos = alphaPos; }
	
	void setBetaPos(const std::pair<int, std::vector<std::pair<int, std::string>>> betaPos) { m_betaPos = betaPos; }
	
	//void setBetaPos(const std::pair<int, std::pair<int, std::string>> betaPos) { m_betaPos = betaPos; }

	void addMove(std::pair<int, std::string> move) { m_moves.push_back(move); }

	std::vector<std::pair<int, std::string>> getMoves() { return m_moves; }
	void setMoves(std::vector<std::pair<int, std::string>> moves) { m_moves = moves; }

	~Node();
};

