#pragma once
#include "stdafx.h"
#include "Board.h"
#include "Piece.h"
#include "Node.h"

//class Agent
//{
//
//	struct Sausage
//	{
//		// for backtracking along the tree
//		Sausage *parent;
//
//
//		// for forward tracking the subsequent nodes
//		//std::vector<Node*> children;
//
//		// for preserving the state of the board
//		Board *board;
//
//		// alpha and beta 
//		std::pair<int, std::vector<std::pair<int, std::string>>> alphaPos;
//		std::pair<int, std::vector<std::pair<int, std::string>>> betaPos;
//
//	};
//
//	int m_depth;
//	Sausage *m_root;
//
//public:
//
//	Agent(int depth, Board &board);
//	~Agent();
//
//	Sausage* getRootNode() const { return m_root; }
//	int getTreeDepth() const { return m_depth; }
//
//	//std::pair<int, std::vector<std::pair<int, std::string>>> alphaBeta(Board board, 
//	//	std::vector<std::pair<int, std::string>> positions, 
//	//	Node* parent, int depth, bool isPlayerMaximize,
//	//	std::pair<int, std::vector<std::pair<int, std::string>>> alphaPos,
//	//	std::pair<int, std::vector<std::pair<int, std::string>>> betaPos);
//
//	std::pair<int, std::vector<std::pair<int, std::string>>> alphaBeta(Sausage *node, int depth, bool isPlayerMaximize);
//	
//	int evaluateBoard(Board &board, bool isPlayerMaximize);
//
//
//
//
//
//
//};

class Agent
{
	int m_depth;
	Node *m_root;

public:

	Agent(int depth, Board &board);
	~Agent();

	Node* getRootNode() const { return m_root; }
	int getTreeDepth() const { return m_depth; }

	//std::pair<int, std::vector<std::pair<int, std::string>>> alphaBeta(Board board, 
	//	std::vector<std::pair<int, std::string>> positions, 
	//	Node* parent, int depth, bool isPlayerMaximize,
	//	std::pair<int, std::vector<std::pair<int, std::string>>> alphaPos,
	//	std::pair<int, std::vector<std::pair<int, std::string>>> betaPos);

	std::pair<int, std::vector<std::pair<int, std::string>>> alphaBeta(Node *node, int depth, bool isPlayerMaximize);

	int evaluateBoard(Board &board, bool isPlayerMaximize);






};

#pragma region unused

//void initNodeTree(Board &board, bool isPlayerMaximize);
//Node* initNode(Board board, Node* parent, int depth, bool isPlayerMaximize);
//void deleteNode(Node &node);
//void deleteAllNodes(Node &root);
//int alphaBeta(Node &node, int depth, int alpha, int beta, bool isPlayerMaximize);
//int evaluateBoard(Board &board, bool isPlayerMaximize);
//std::pair<int, std::string> findBestMove(bool isPlayerMaximize);

#pragma endregion
