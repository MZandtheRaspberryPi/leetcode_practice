/*
othello. each piece is white one side, black on other.

piece surrounded by opponents on left and right side,
or on top and bottom, it is said captured and its color flipped

on your turn, msut capture at least 1 piece
game ends when no valid moves.

win to person w/ most pieces.

implement object orientated design for othello

game is an 8 x 8 board, and starts with middle 4 populated, top left white, bottom right white, others black.

black goes first.

ambiguity
is this for professionals where we need to do ranking and competitions and all?

do we need to match players to each other? or do we already have 2 players signing up.

lets assume we are desiging a game for 2 people to play, that are already tehre and have found each other. its a casual game, no rankings.

core objects:
GamePieceLocation
GamePieceState
GamePiece
Player
Board
Game

relationships
a player has a game piece color
a board has 0 or more game pieces
A game has 2 players, one board, and many game pieces, as well as one game piece representing last piece played

actions
a game can be started, clearing the board, putting the opening pieces down, and assiging next player to black. it can also count the score.
a player can play a piece at a certain point
a piece can be flipped if this is applicable


feedback from solution:
we are adding more layers to the program. a function may call game and then directly board gets called. but nice to seperate logic out too.

could have made game singleton, as then anyone can call. but then can only have one game at a time. should have discussed that logic.

didnt go through how you might flip multiple pieces. should have clarified that part of the rules.
*/

#include <string>
#include <vector>

class Game;
class Player;

enum GamePieceColor
{
	Black,
	White
};

struct GamePieceLocation
{
	int x;
	int y;
};

class GamePiece
{
	public:
	  GamePiece(GamePieceColor current_state)
		{
			current_state_ = current_state;
		}
	  GamePieceColor getCurrentState();
		void setCurrentState(GamePieceColor state);
	
	private:
	  GamePieceColor current_state_;
};

class Player
{
	public:
	  Player(std::string player_name);
		
		// checks if it is our turn and if it is will play and return true, if not return false
		bool playPiece(const Game& game, const GamePiece& piece, const GamePieceLocation& location);
	
	private:
	  std::string player_name_;
		GamePieceColor color_;
};

class Board
{
	public:
	  Board(int x_size, int y_size);
		// replaces all the game pieces on the game_board_ with nullptr
		void clearBoard();
		
		// checks if a piece is already in the location, and if it is returns false, if it isnt, adds it
		bool addPiece(GamePiece* piece, const GamePieceLocation& location);
		bool removePiece(GamePiece* piece, const GamePieceLocation& location);
		
		std::vector<std::vector<GamePiece*>> getBoard();
	
	private:
	  int x_size_;
		int y_size_;
		std::vector<std::vector<GamePiece*>> game_board_;
};

enum GameTypes
{
	Othello
};

class Game
{
	public:
	  // sets up the board
	  Game(std::vector<Player*> players);
		virtual bool playPiece(GamePiece piece, GamePieceLocation location) = 0;
		virtual bool isGameFinished() = 0;
		virtual Player* whoWon() = 0;

	protected:
	  // looks at the board and updates the scores of the game
		virtual updateScores() = 0;
	
		std::vector<GamePiece> pieces_played_;
	  std::vector<Player*> players_;
		std::vector<int> scores_;
		Board board_;
};

class OthelloGame : public Game
{
	public:
	  // clears the board, puts the initial 4 pieces down, sets the next player to black
	  OthelloGame(std::vector<Player*> players);
		// tries to play this piece, returns false if cant. if can, after playing check neighbors and flip color.
		//		if dont flip, remove piece and return false.
		// update scores
		// set player to next player
		bool playPiece(GamePiece piece, GamePieceLocation location);
		// checks if the next player has an open move
		bool isGameFinished();
		// checks whose score is higher, assuming the game is finished
		Player* whoWon();
	private:
	  Player* next_player_;
};

int main()
{
	
}