#pragma once
#include "stdafx.h"
#include "Board.h"
#include "Piece.h"
#include "Node.h"



class Agent
{
	int m_depth;
	Node *m_root;
	Piece::Color m_agentColor;

public:

	Agent(int depth, Board &board, Piece::Color agentColor);
	~Agent();

	Node* getRootNode() const { return m_root; }
	int getTreeDepth() const { return m_depth; }
	Piece::Color getAgentColor() const { return m_agentColor; }


	std::pair<int, std::vector<std::pair<int, std::string>>> alphaBeta(Node *node, int depth, bool isPlayerMaximize);
	//std::pair<int, std::pair<int, std::string>> alphaBeta(Node *node, int depth, bool isPlayerMaximize);

	int evaluateBoard(Board &board, bool isPlayerMaximize, Piece::Color agentColor);


};
