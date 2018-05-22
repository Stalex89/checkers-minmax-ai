#pragma once
#include "stdafx.h"
#include "Board.h"
#include "Piece.h"
#include "Node.h"



class Agent
{
	int m_depth;
	Node *m_root;

public:

	Agent(int depth, Board &board);
	~Agent();

	Node* getRootNode() const { return m_root; }
	int getTreeDepth() const { return m_depth; }


	std::pair<int, std::vector<std::pair<int, std::string>>> alphaBeta(Node *node, int depth, bool isPlayerMaximize);

	int evaluateBoard(Board &board, bool isPlayerMaximize);


};
