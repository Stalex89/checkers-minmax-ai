#pragma once
#include "stdafx.h"
#include "Agent.h"
#include "Board.h"


Agent::Agent(int depth, Board &board, Piece::Color agentColor) : m_depth(depth), m_agentColor(agentColor)
{
	// iitialize root node
	m_root = new Node(m_root, board);

}

Agent::~Agent()
{
	delete m_root;
	m_root = nullptr;
}


std::pair<int, std::vector<std::pair<int, std::string>>> Agent::alphaBeta(Node *node, int depth, bool isPlayerMaximize)
{
	Piece::Color currColor; 

	if (isPlayerMaximize && m_agentColor == Piece::Color::WHITE)
	{
		node->getNodeBoard().clearAllMovesForColor(Piece::Color::BLACK);
		currColor = Piece::Color::WHITE;
	}
	else if (isPlayerMaximize && m_agentColor == Piece::Color::BLACK)
	{
		node->getNodeBoard().clearAllMovesForColor(Piece::Color::WHITE);
		currColor = Piece::Color::BLACK;
	}
	else if (!isPlayerMaximize && m_agentColor == Piece::Color::WHITE)
	{
		node->getNodeBoard().clearAllMovesForColor(Piece::Color::WHITE);
		currColor = Piece::Color::BLACK;
	}
	else if (!isPlayerMaximize && m_agentColor == Piece::Color::BLACK)
	{
		node->getNodeBoard().clearAllMovesForColor(Piece::Color::BLACK);
		currColor = Piece::Color::WHITE;
	}


	node->getNodeBoard().clearAllMovesForColor(currColor);
	node->getNodeBoard().calculateAllMovesForColor(currColor);


//	// terminal condition
//	if (depth == 0 || node->getNodeBoard().isGameOver(currColor))
//	{
//		std::vector<std::pair<int, std::string>> po = node->getNodeBoard().getPositions();
//		int eb = evaluateBoard(node->getNodeBoard(), isPlayerMaximize);
//		std::pair<int, std::vector<std::pair<int, std::string>>> pair = std::make_pair(eb, po);
//		return pair;
//	}
//	// traverse through all pieces on the board
//	for (int idx = 0; idx < node->getNodeBoard().getPieceSize(); idx++)
//	{
//		Piece p = node->getNodeBoard().getPieceByIdx(idx);
//		
//			//for maximizer and white piece
//			if (isPlayerMaximize && p.getColor() == Piece::Color::WHITE && p.hasPossibleMoves())
//			{
//				for (auto move : p.getAllPossibleMoves())
//				{
//					//create a child node
//					Node *child = new Node(node, node->getNodeBoard());
//					
//						
//					//update the positions of the child node with new move and update the state of the board
//					std::vector<std::pair<int, std::string>> pos = node->getNodeBoard().getPositions();
//					pos.push_back(move);
//					child->getNodeBoard().setPositions(pos);
//
//					std::pair<int, std::vector<std::pair<int, std::string>>> val = alphaBeta(child, depth - 1, false);
//						
//					// delete child after evaluation of child node
//					delete child;
//					child = nullptr;
//
//					// replase aplha if the value of child node is bigger than parent node
//					node->setAlphaPos((node->getAlphaPos().first > val.first) ? node->getAlphaPos() : val);
//				
//					// if alpha is greater or equal beta, we can prune
//					if (node->getAlphaPos().first >= node->getBetaPos().first)
//						break;
//				
//				
//				}
//				
//				return node->getAlphaPos();
//			}
//
//			else if (!isPlayerMaximize && p.getColor() == Piece::Color::BLACK && p.hasPossibleMoves())
//			{
//
//				for (auto move : p.getAllPossibleMoves())
//				{
//					//create a child node
//					Node *child = new Node(node, node->getNodeBoard());
//
//					//update the positions of the child node with new move and update the state of the board
//					std::vector<std::pair<int, std::string>> pos = node->getNodeBoard().getPositions();
//					pos.push_back(move);
//					child->getNodeBoard().setPositions(pos);
//
//					std::pair<int, std::vector<std::pair<int, std::string>>> val = alphaBeta(child, depth - 1, true);
//
//					// delete child after evaluation of child node
//					delete child;
//					child = nullptr;
//
//					// replase beta if the value of child node is lesser than parent node
//					node->setBetaPos((node->getBetaPos().first < val.first) ? node->getBetaPos() : val);
//
//					// if alpha is greater or equal beta, we can prune
//					if (node->getAlphaPos().first >= node->getBetaPos().first)
//						break;
//
//
//				}
//
//					return node->getBetaPos();
//
//			}
//		
//
//	}
//
//}

	// terminal condition
	if (depth == 0 || node->getNodeBoard().isGameOver(currColor))
	{
		std::vector<std::pair<int, std::string>> po = node->getNodeBoard().getPositions();
		int eb = evaluateBoard(node->getNodeBoard(), isPlayerMaximize, m_agentColor);
		std::pair<int, std::vector<std::pair<int, std::string>>> pair = std::make_pair(eb, po);
		return pair;
	}
	// traverse through all pieces on the board
	for (int idx = 0; idx < node->getNodeBoard().getPieceSize(); idx++)
	{
		Piece p = node->getNodeBoard().getPieceByIdx(idx);

		//for maximizer and white piece
		if (isPlayerMaximize && p.getColor() == m_agentColor && p.hasPossibleMoves())
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

		else if (!isPlayerMaximize && p.getColor() != m_agentColor && p.hasPossibleMoves())
		{

			for (auto move : p.getAllPossibleMoves())
			{
				//create a child node
				Node *child = new Node(node, node->getNodeBoard());

				//update the positions of the child node with new move and update the state of the board
				std::vector<std::pair<int, std::string>> pos = node->getNodeBoard().getPositions();
				pos.push_back(move);
				child->getNodeBoard().setPositions(pos);

				std::pair<int, std::vector<std::pair<int, std::string>>> val = alphaBeta(child, depth - 1, true);

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




int Agent::evaluateBoard(Board &board, bool isPlayerMaximize, Piece::Color agentColor)
{
	int value = 0;
	for (int idx = 0; idx < board.getPiecesNum(); idx++)
	{
		Piece p = board.getPieceByIdx(idx);
		if (p.getPosition() != sf::Vector2f(-100.0f, -100.0f))
			if (p.getColor() == agentColor)
			{
				if (p.isKing())
					value += (isPlayerMaximize) ? 2 : -2;
				else
					value += (isPlayerMaximize) ? 1 : -1;
			}
			else if (p.getColor() != agentColor)
			{
				if (p.isKing())
					value += (isPlayerMaximize) ? -2 : 2;
				else
					value += (isPlayerMaximize) ? -1 : 1;
			}

	}

	return value;
}



//int Agent::evaluateBoard(Board &board, bool isPlayerMaximize)
//{
//	int value = 0;
//	for (int idx = 0; idx < board.getPiecesNum(); idx++)
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
