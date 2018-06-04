#pragma once
#include "stdafx.h"
#include "Piece.h"

class Board
{
	//sf::Texture *m_texture;
	//sf::Sprite *m_sprite;

	std::vector<std::pair<int, std::string>> m_positions;
	std::vector<Piece> m_pieces;

	int m_pieceSize = 56;
	int m_width = 504;
	int m_height = 504;
	sf::Vector2f m_offset = sf::Vector2f(28,28);

public:
	Board();
	Board(Board &board);

	// Loads the board with starting positions of pieces. 
	// If there were moves, loads the state of the board with all moves performed  
	void loadPosition();

	// Converts position of piece in Vector2f to chess notation in string
	std::string toChessNote(sf::Vector2f position);

	// Converts chess notation in two chars to Vector2f 
	sf::Vector2f toCoord(char a, char b);

	std::vector<Piece>& getPieces() { return m_pieces; }

	// Returns the number of pieces instantiated 
	int getPiecesNum() { return (int)(m_pieces.size()); }

	// Finds the piece in the array of pieces by index, returns reference to the piece
	Piece& getPieceByIdx(int idx) { return m_pieces.at(idx); }

	// Finds the the piece by its coordinates on the board, returns the index of piece in the array
	int getPieceIdxOnPosition(sf::Vector2f position);

	// Finds the the piece by its coordinates on the board, returns the index of piece in the array
	//int getPieceIdxBySprite(sf::Vector2i mousePos);

	// Appends move to the list of all performed moves
	void addPosition(std::pair<int, std::string> position) { m_positions.push_back(position); }
	
	// Pops up the move from the list of all performed moves
	void deleteLastPosition() { m_positions.pop_back(); }

	// Gets the number of all performed moves
	int getPositionsSize() { return (int)(m_positions.size()); }

	std::vector<std::pair<int, std::string>>& getPositions() { return m_positions; }
	void setPositions(std::vector<std::pair<int, std::string>> positions) { m_positions = positions; }
	
	// Prints all performed moves
	void printPositions();

	// Calculates all possible moves for piece
	void calculatePossibleMoves(Piece &piece);

	// Checks if the move is for one field (simple move), or it is capture
	bool isMoveforOneField(sf::Vector2f oldPos, sf::Vector2f newPos);

	// Checks of the move is performed within the borders of playing field
	bool isInPlayfield(sf::Vector2f position);

	// Checks if the capture is possible
	bool isCapturePossible(sf::Vector2f position, Piece &enemyPiece);

	// Checks if the position is already in the capture chain
	bool isInCaptureChain(sf::Vector2f position, std::pair<int, std::string> captureChain);

	// Depth first traversal search for constucting capture leap chain
	void captureChainRecursiveSearch(Piece &piece, sf::Vector2f position, std::pair<int, std::string> attackChain);

	// Get all legal moves for piece
	std::string getLegalMoves(Piece &piece, sf::Vector2f position);

	//int getXBound() { return m_sprite->getGlobalBounds().width; }
	//int getYBound() { return m_sprite->getGlobalBounds().height; }

	void calculateAllMovesForColor(Piece::Color color);
	void clearAllMovesForColor(Piece::Color color);

	//sf::Sprite& getSprite() { return *m_sprite; };
	int getPieceSize() { return m_pieceSize; }
	sf::Vector2f getOffset() { return m_offset; }
	
	bool isGameOver(Piece::Color color);

	~Board();
};

