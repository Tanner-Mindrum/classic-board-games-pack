#include "OthelloBoard.h"
#include "OthelloView.h"
#include "OthelloMove.h"
#include "GameBoard.h"
#include "GameMove.h"
#include "GameView.h"
#include "ConnectFourBoard.h"
#include "ConnectFourMove.h"
#include "ConnectFourView.h"
#include "TicTacToeBoard.h"
#include "TicTacToeMove.h"
#include "TicTacToeView.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

using namespace std;

int main() {
	// Initialization
	shared_ptr<GameBoard> board;
	unique_ptr<GameView> v;
	string userCommand;
	int playerCount = 0;

	while (true) {
		cout << "Select a game to play!\n----------------------\n1) Othello\n2) Tic Tac Toe" << endl <<
			"3) Connect Four\n4) How to play: Game commands\n5) Exit" << endl;
		getline(cin, userCommand);

		if (userCommand == "1") {
			auto oBoard = make_shared<OthelloBoard>();
			v = make_unique<OthelloView>(oBoard);
			board = oBoard;
		}
		else if (userCommand == "2") {
			auto tBoard = make_shared<TicTacToeBoard>();
			v = make_unique<TicTacToeView>(tBoard);
			board = tBoard;
		}
		else if (userCommand == "3") {
			auto cBoard = make_shared<ConnectFourBoard>();
			v = make_unique<ConnectFourView>(cBoard);
			board = cBoard;
		}
		else if (userCommand == "4") {
			cout <<
				"\nCommand: you type this\n"
				"-----------------\n"
				"Apply move: move (row, column)\n"
				"Undo move: undo n\n"
				"Show current value of board: showValue\n"
				"Show history of applied moves: showHistory\n"
				"Quit game: quit\n"
				<< endl;
			continue;
		}
		else if (userCommand == "5") {
			cout << endl << "Thanks for playing!" << endl;
			break;
		}
		else {
			cout << endl << "That option does not exist." << endl << endl;
			continue;
		}

		bool isMoveOrUndo = true;
		//Runs until user decides to quit
		while (true) {
			const vector<std::unique_ptr<GameMove>> &moveHistory = board->GetMoveHistory();
			vector<std::unique_ptr<GameMove>> possibleMoves = board->GetPossibleMoves();
			playerCount++;

			//Print board
			if (isMoveOrUndo) {
				cout << *v << endl;
				cout << v->GetPlayerString(playerCount % 2) << "'s move" << endl;


				//Print possible moves
				cout << "Possible moves: " << endl;
				for (vector<unique_ptr<GameMove>>::iterator itr = possibleMoves.begin(); itr != possibleMoves.end(); itr++) {
					cout << static_cast<string> (*(*itr)) << " ";
				}
			}

			//Get a command
			bool valid = false;

			cout << endl << "Enter a command: " << endl;
			getline(cin, userCommand);

			//Read in move and apply it accordingly or give user error message
			if (userCommand.substr(0, 4) == "move") {
				int notValidMoveCount = 0;
				while (!valid) {
					auto userMove = v->ParseMove(userCommand.substr(5));
					for (vector<unique_ptr<GameMove>>::iterator itr = possibleMoves.begin(); itr != possibleMoves.end(); itr++) {
						if (static_cast<string> (*userMove) == static_cast<string> (*(*itr))) {
							board->ApplyMove(std::move(userMove));
							valid = true;
							isMoveOrUndo = true;
							break;

						}
					}
					if (!valid) {
						cout << endl << "Not a valid move" << endl;
						cout << endl << "Enter a command: " << endl;
						getline(cin, userCommand);
					}
				}
			}

			//Undo n amounts of moves
			else if (userCommand.substr(0, 4) == "undo") {
				istringstream undoInput{ userCommand };
				int undoAmount;
				string theCommand;
				undoInput >> theCommand >> undoAmount;
				while (undoAmount > 0) {
					board->UndoLastMove();
					undoAmount--;
				}
			}

			//Display value of the board
			else if (userCommand.substr(0, 9) == "showValue") {
				cout << endl << "Board value: " << board->GetValue() << endl;
				isMoveOrUndo = false;
			}

			//Display move history
			else if (userCommand.substr(0, 11) == "showHistory") {
				string stringToPrint;
				int playerToPrint = moveHistory.size();
				cout << endl;
				for (vector<unique_ptr<GameMove>>::const_reverse_iterator itr = moveHistory.rbegin();
					itr != moveHistory.rend(); itr++) {
						stringToPrint = (playerToPrint % 2) != 0 ? v->GetPlayerString(1) + ": " + 
							static_cast<string> (*(*itr)) : v->GetPlayerString(2) + ": " +
							static_cast<string> (*(*itr));
						cout << stringToPrint << endl;
					playerToPrint--;
				}
				isMoveOrUndo = false;
			}

			else if (userCommand.substr(0, 4) == "quit") {
				cout << endl;
				break;
			}

			//User did not enter a valid command
			else {
				cout << endl << "Invalid input." << endl;
				isMoveOrUndo = false;
				continue;
			}

			//Quit the game and display who won
			if (board->IsFinished()) {
				string stringToPrint;
				stringToPrint = board->GetValue() > 0 ? v->GetPlayerString(1) + " wins!" : v->GetPlayerString(2) + " wins!";
				if (board->GetValue() == 0) {
					stringToPrint = "Cat's game!";
				}
				cout << endl << "Final board:\n" << *v << endl;
				cout << stringToPrint << endl << endl;
				playerCount = 0;
				break;
			}
		}
	}
	return 0;
}