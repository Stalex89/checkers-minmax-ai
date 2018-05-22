#pragma once
#include "stdafx.h"
#include "Agent.h"
#include "Board.h"


Agent::Agent(int depth, Board &board) : m_depth(depth)
{
	// iitialize root node
	m_root = new Node(m_root, board);

}

Agent::~Agent()
{
	delete m_root;
	m_root = nullptr;
}


//std::pair<int, std::vector<std::pair<int, std::string>>> Agent::alphaBeta(Board board,
//	std::vector<std::pair<int, std::string>> positions,
//	Node* parent, int depth, bool isPlayerMaximize,
//	std::pair<int, std::vector<std::pair<int, std::string>>> alphaPos,
//	std::pair<int, std::vector<std::pair<int, std::string>>> betaPos)
//{
//	//create a new node
//	Node *n = new Node();
//
//	//update the state of the board and positions 
//	if (parent != nullptr)
//	{
//		alphaPos = std::make_pair(std::numeric_limits<int>::min(), board.getPositions());
//		betaPos = std::make_pair(std::numeric_limits<int>::max(), board.getPositions());
//		board.setPositions(positions);
//		board.loadPosition();
//	}
//	n->m_parent = parent;
//
//	// if we still can forward track the subsequent nodes
//	if (depth > 0)
//	{
//		// traverse through all pieces on the board
//		for (int idx = 0; idx <board.getPieceSize(); idx++)
//		{
//			Piece p = board.getPieceByIdx(idx);
//
//			// if piece is not captured
//			if (p.getPosition() != sf::Vector2f(-100.0f, -100.0f))
//			{
//				// for maximizer and white piece
//				if (isPlayerMaximize && p.getColor() == Piece::Color::WHITE)
//				{
//					board.calculatePossibleMoves(p);
//
//					// if piece has possible moves, traverse through every possible move of the piece
//					if (!p.getAllPossibleMoves().empty())
//					{
//						for (auto move : p.getAllPossibleMoves())
//						{
//							std::vector<std::pair<int, std::string>> pos = board.getPositions();
//							pos.push_back(move);
//							std::pair<int, std::vector<std::pair<int, std::string>>> val = alphaBeta(board, pos, n, depth - 1, false, alphaPos, betaPos);
//							alphaPos = (alphaPos.first > val.first) ? alphaPos : val;
//
//							// if alpha is greater or equal beta, we can prune
//							if (alphaPos.first >= betaPos.first)
//								break;
//
//
//						}
//
//						return alphaPos;
//					}
//					else
//					{
//						return std::make_pair(evaluateBoard(board, isPlayerMaximize), board.getPositions());
//					}
//
//				}
//				// for minimizer and black piece
//				else if (!isPlayerMaximize && p.getColor() == Piece::Color::BLACK)
//				{
//					board.calculatePossibleMoves(p);
//
//					// if piece has possible moves, traverse through every possible move of the piece
//					if (!p.getAllPossibleMoves().empty())
//					{
//						for (auto move : p.getAllPossibleMoves())
//						{
//							std::vector<std::pair<int, std::string>> pos = board.getPositions();
//							pos.push_back(move);
//							std::pair<int, std::vector<std::pair<int, std::string>>> val = alphaBeta(board, pos, n, depth - 1, true, alphaPos, betaPos);
//							betaPos = (betaPos.first < val.first) ? betaPos : val;
//
//
//
//							// if alpha is greater or equal beta, we can prune
//							if (alphaPos.first >= betaPos.first)
//								break;
//
//
//						}
//
//						return betaPos;
//					}
//					else
//					{
//						return std::make_pair(evaluateBoard(board, isPlayerMaximize), board.getPositions());
//					}
//				}
//			}
//		}
//	}
//	else
//	{
//		return std::make_pair(evaluateBoard(board, isPlayerMaximize), board.getPositions());
//	}
//}


std::pair<int, std::vector<std::pair<int, std::string>>> Agent::alphaBeta(Node *node, int depth, bool isPlayerMaximize)
{
	Piece::Color currColor; 

	if (isPlayerMaximize)
	{
		node->getNodeBoard().clearAllMovesForColor(Piece::Color::BLACK);
		currColor = Piece::Color::WHITE;
	}
	else
	{
		node->getNodeBoard().clearAllMovesForColor(Piece::Color::WHITE);
		currColor = Piece::Color::BLACK;
	}

	node->getNodeBoard().clearAllMovesForColor(currColor);
	node->getNodeBoard().calculateAllMovesForColor(currColor);

	// terminal condition
	if (depth == 0 || node->getNodeBoard().isGameOver(currColor))
	{
		std::vector<std::pair<int, std::string>> po = node->getNodeBoard().getPositions();
		int eb = evaluateBoard(node->getNodeBoard(), isPlayerMaximize);
		std::pair<int, std::vector<std::pair<int, std::string>>> pair = std::make_pair(eb, po);
		return pair;
	}
	// traverse through all pieces on the board
	for (int idx = 0; idx < node->getNodeBoard().getPieceSize(); idx++)
	{
		Piece p = node->getNodeBoard().getPieceByIdx(idx);
		
			//for maximizer and white piece
			if (isPlayerMaximize && p.getColor() == Piece::Color::WHITE && p.hasPossibleMoves())
			{
				for (auto move : p.getAllPossibleMoves())
				{
					//create a child node
					Node *child = new Node(node, node->getNodeBoard());
					
						
					//update the positions of the child node with new move and update the state of the board
					std::vector<std::pair<int, std::string>> pos = node->getNodeBoard().getPositions();
					pos.push_back(move);
					child->getNodeBoard().setPositions(pos);

					std::pair<int, std::vector<std::pair<int, std::string>>> val = alphaBeta(child, depth - 1, false);
						
					// delete child after evaluation of child node
					delete child;
					child = nullptr;

					// replase aplha if the value of child node is bigger than parent node
					node->setAlphaPos((node->getAlphaPos().first > val.first) ? node->getAlphaPos() : val);
				
					// if alpha is greater or equal beta, we can prune
					if (node->getAlphaPos().first >= node->getBetaPos().first)
						break;
				
				
				}
				
				return node->getAlphaPos();
			}

			else if (!isPlayerMaximize && p.getColor() == Piece::Color::BLACK && p.hasPossibleMoves())
			{

				for (auto move : p.getAllPossibleMoves())
				{
					//create a child node
					Node *child = new Node(node, node->getNodeBoard());

					//update the positions of the child node with new move and update the state of the board
					std::vector<std::pair<int, std::string>> pos = node->getNodeBoard().getPositions();
					pos.push_back(move);
					child->getNodeBoard().setPositions(pos);

					std::pair<int, std::vector<std::pair<int, std::string>>> val = alphaBeta(child, depth - 1, false);

					// delete child after evaluation of child node
					delete child;
					child = nullptr;

					// replase beta if the value of child node is lesser than parent node
					node->setBetaPos((node->getBetaPos().first < val.first) ? node->getBetaPos() : val);

					// if alpha is greater or equal beta, we can prune
					if (node->getAlphaPos().first >= node->getBetaPos().first)
						break;


				}

					return node->getBetaPos();

			}
		

	}

}




int Agent::evaluateBoard(Board &board, bool isPlayerMaximize)
{
	int value = 0;
	for (int idx = 0; idx < board.getPiecesNum(); idx++)
	{
		Piece p = board.getPieceByIdx(idx);
		if (p.getPosition() != sf::Vector2f(-100.0f, -100.0f))
			if (p.getColor() == Piece::Color::WHITE)
			{
				if (p.isKing())
					value += (isPlayerMaximize) ? 2 : -2;
				else
					value += (isPlayerMaximize) ? 1 : -1;
			}
			else if (p.getColor() == Piece::Color::BLACK)
			{
				if (p.isKing())
					value += (isPlayerMaximize) ? -2 : 2;
				else
					value += (isPlayerMaximize) ? -1 : 1;
			}

	}

	return value;
}






















#pragma region unused

//Agent::Agent(int depth) : m_depth(depth)
//{
//
//	m_root = nullptr;
//}
//
//
//Agent::~Agent()
//{
//	deleteAllNodes(*m_root);
//	delete m_root;
//	m_root = nullptr;
//}
//
//std::pair<int, std::string> Agent::findBestMove(bool isPlayerMaximize)
//{
//	int bestValue = alphaBeta(*m_root, m_depth, std::numeric_limits<int>::infinity(),
//		-std::numeric_limits<int>::infinity(), isPlayerMaximize);
//
//	for (int idx = 0; idx < m_root->m_children.size(); idx++)
//	{
//		if (m_root->m_children.at(idx)->m_value == bestValue)
//			return m_root->m_children.at(idx)->m_move;
//	}
//}
//
//int Agent::alphaBeta(Node &node, int depth, int alpha, int beta, bool isPlayerMaximize)
//{
//	//terminal case
//	if (node.m_children.empty() || depth == 0)
//		return node.m_value;
//
//	if (isPlayerMaximize)
//	{
//		for (auto child : node.m_children)
//		{
//			alpha = std::max(alpha, alphaBeta(*child, depth - 1, alpha, beta, false));
//
//			if (alpha >= beta)
//				break;
//		}
//
//		return alpha;
//	}
//
//	else if (!isPlayerMaximize)
//	{
//		for (auto child : node.m_children)
//		{
//			beta = std::min(beta, alphaBeta(*child, depth - 1, alpha, beta, true));
//
//			if (alpha >= beta)
//				break;
//		}
//
//		return beta;
//	}
//
//	return 0;
//}
//
//void Agent::initNodeTree(Board &board, bool isPlayerMaximize)
//{
//	m_root = initNode(board, m_root, m_depth, isPlayerMaximize);
//}
//
//Agent::Node* Agent::initNode(Board board, Node* parent, int depth, bool isPlayerMaximize)
//{
//	
//
//	Node *n = new Node();
//	
//	if (parent == nullptr)
//	{
//		n->m_pieces = board.getPieces();
//		n->m_positions = board.getPositions();
//	}
//	else
//	{
//		n->m_pieces = parent->m_pieces;
//		n->m_positions = parent->m_positions;
//	}
//
//	n->m_parent = parent;
//
//	if (depth > 0)
//	{
//		for (int idx = 0; idx < n->m_pieces.size(); idx++)
//		{
//			Piece p = n->m_pieces.at(idx);
//			if (p.getPosition() != sf::Vector2f(-100.0f, -100.0f))
//			{
//				if (isPlayerMaximize && p.getColor() == Piece::Color::WHITE)
//				{
//					board.calculatePossibleMoves(p);
//					for (auto move : p.getAllPossibleMoves())
//					{
//						n->m_children.push_back(initNode(board, n, depth - 1, false));
//						n->m_move = move;
//					}
//				}
//				else if (!isPlayerMaximize && p.getColor() == Piece::Color::BLACK)
//				{
//					board.calculatePossibleMoves(p);
//					for (auto move : p.getAllPossibleMoves())
//					{
//						n->m_children.push_back(initNode(board, n, depth, true));
//						n->m_move = move;
//					}
//				}
//			}
//		}
//	}
//	else
//	{
//		n->m_value = evaluateBoard(board, isPlayerMaximize);
//	}
//
//	return n;
//}
//
//void Agent::deleteNode(Node &node)
//{
//	delete node.m_parent;
//	node.m_parent = nullptr;
//	delete &node;
//}
//
//void Agent::deleteAllNodes(Node &node)
//{
//	if (node.m_children.empty())
//	{
//		deleteNode(node);
//		return;
//	}
//	else
//	{
//		for (auto node : node.m_children)
//			deleteAllNodes(*node);
//	}
//}
//
//
//int Agent::evaluateBoard(Board &board, bool isPlayerMaximize)
//{
//	int value = 0;
//	for (int idx = 0; idx < board.getPieceSize(); idx++)
//	{
//		Piece p = board.getPieceByIdx(idx);
//		if (p.getPosition() != sf::Vector2f(-100.0f, -100.0f))
//			if (p.getColor() == Piece::Color::WHITE)
//			{
//				if (p.isKing())
//					value += (isPlayerMaximize) ? 2 : -2;
//				else
//					value += (isPlayerMaximize) ? 1 : -1;
//			}
//			else if (p.getColor() == Piece::Color::BLACK)
//			{
//				if (p.isKing())
//					value += (isPlayerMaximize) ? -2 : 2;
//				else
//					value += (isPlayerMaximize) ? -1 : 1;
//			}
//
//	}
//
//	return value;
//}

#pragma endregion