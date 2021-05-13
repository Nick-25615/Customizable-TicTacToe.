/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Includes
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Custom Data Types
//NOTE: I'm using -1 as an invalid value
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct spaceInfo { char X = -1, Y = -1, occupant = ' '; };//This is used for the board array //Making occupant a enum or enum class might be a good idea but right now I don't know enough to

struct posCode { //This is used for storing x and y position
	char X = -1, Y = -1;
	posCode() {}
	posCode(char x, char y) :X(x), Y(y) {}
};

struct sizeCode { //This is used for storing x and y size
	char X = -1, Y = -1;
	sizeCode() {}
	sizeCode(char x, char y) :X(x), Y(y) {}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function Decarations
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
sizeCode WelcomePlayerAndGetSize();
char GetAndCheckPlayerInputForSize();//This is a support function for WelcomePlayerAndGetSize() and is not ment to be use by it's self

spaceInfo* GenerateStartboard(sizeCode size);

char ExplainHowToPlayAndGetWinCondition(char maxWinCondition);
char GetAndCheckPlayerInputForWinCondition(char maxWinCondition);//This is a support function for ExplainHowToPlayAndGetWinCondition(char maxWinCondition) and is not ment to be use by it's self

void Printboard(spaceInfo* board, sizeCode size);

posCode MakeMove(spaceInfo* board, sizeCode size, char player);
posCode GetAndCheckPlayerInputForMove(spaceInfo* board, sizeCode size);//This is a support function for MakeMove(spaceInfo* board, sizeCode size, char player) and is not ment to be use by it's self

bool CheckIfPlayerWins(spaceInfo* board, sizeCode size, posCode pos, char winCondition);
char CheckDirForWin(spaceInfo* board, sizeCode size, posCode pos, posCode dirToCheck);//This is a support function for CheckIfPlayerWins(spaceInfo* board, sizeCode size, posCode pos, char winCondition) and is not ment to be use by it's self

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Main And Other Functures
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
	sizeCode size = WelcomePlayerAndGetSize();
	char winCondition = ExplainHowToPlayAndGetWinCondition(size.X > size.Y ? size.X : size.Y);

	spaceInfo* board = GenerateStartboard(size);

	Printboard(board, size);

	for (char i = 0; i < size.X * size.Y; i++) {
		posCode move;
		move = MakeMove(board, size, 'X');

		std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

		Printboard(board, size);

		if (CheckIfPlayerWins(board, size, move, winCondition)) {
			std::cout << "\n\n\n\n\n";
			std::cout << "Well Done Player X You Have Just Won";
			std::cout << "\n\n\n\n\n";
			break;
		}

		move = MakeMove(board, size, 'O');

		std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

		Printboard(board, size);

		if (CheckIfPlayerWins(board, size, move, winCondition)) {
			std::cout << "\n\n\n\n\n";
			std::cout << "Well Done Player Y You Have Just Won";
			std::cout << "\n\n\n\n\n";
			break;
		}
	}

	std::cout << "\n\n\n\n\n";
	std::cout << "It Was A Tie";
	std::cout << "\n\n\n\n\n";

	std::cin.get();

	delete[] board;
}
//delete board when done.

sizeCode WelcomePlayerAndGetSize() {
	sizeCode size;

	std::cout << "Welcome To TicTacToe Where You Can Choose The Size Of The board Up To 26 By 26\n";
	std::cout << "\nPlease Type In How Wide You Want The board To Be ";

	do {
		size.X = GetAndCheckPlayerInputForSize();
	} while (size.X == -1);

	std::cout << "\nResize The Window So That This Line Is On One Line\n\n";

	for (unsigned char i = 0; i < size.X * 6 + size.X - 1; i++) {
		std::cout << '-';
	}

	std::cout << '\n';

	std::cout << "\nWhen Your Done That Please Type In How Tall You Want The board To Be ";

	do {
		size.Y = GetAndCheckPlayerInputForSize();
	} while (size.Y == -1);

	return size;
}

char GetAndCheckPlayerInputForSize() {
	char size = -1;
	std::string line;

	std::getline(std::cin, line);

	if (line.size() == 2) {
		if (line[0] < 49 || line[0] > 50 || line[1] < 48 || line[1] > 57 || (line[0] == 50 && line[1] > 54)) {
			std::cout << "\nOne Or Two Digit Numbers Under 26 Only Please ";
			return -1;
		}
		else {
			size = (line[0] - 48) * 10 + line[1] - 48;
		}
	}
	else if (line.size() != 1 || line[0] < 48 || line[0] > 57) {
		std::cout << "\nOne Or Two Digit Numbers Under 26 Only Please ";
		return -1;
	}
	else {
		size = line[0] - 48;
	}
	return size;
}

spaceInfo* GenerateStartboard(sizeCode size) {
	spaceInfo* board = new spaceInfo[size.X * size.Y];
	for (short j = 0; j < size.Y; j++) {
		for (short i = 0; i < size.X; i++) {
			board[j * size.X + i].X = 97 + i;
			board[j * size.X + i].Y = 65 + j;
		}
	}
	return board;
}

char ExplainHowToPlayAndGetWinCondition(char maxWinCondition) {
	char winCondition;

	std::cout << "\nPlease Type In How Many In A Row Should Count As A Win ";
	do {
		winCondition = GetAndCheckPlayerInputForWinCondition(maxWinCondition);
	} while (winCondition == -1);

	std::cout << "\nTo Play Just Type In The Code Of The Space You Want To Go\n";

	return winCondition;
}

char GetAndCheckPlayerInputForWinCondition(char maxWinCondition) {
	char winCondition = '\0';
	std::string line;

	std::getline(std::cin, line);

	if (line.size() == 2 && maxWinCondition / 10) {
		if (line[0] < 49 || line[0] > maxWinCondition / 10 + 48 || line[1] < 48 || line[1] > maxWinCondition % 10 + 48) {
			std::cout << "\nOne Or Two Digit Numbers Under " << (int)maxWinCondition << " Only Please ";
			return -1;
		}
		else {
			winCondition = (line[0] - 48) * 10 + line[1] - 48;
		}
	}
	else if (line.size() != 1 || line[0] < 48 || line[0] > maxWinCondition + 48) {
		std::cout << "\nOne Or Two Digit Numbers Under " << (int)maxWinCondition << " Only Please ";
		return -1;
	}
	else {
		winCondition = line[0] - 48;
	}
	return winCondition;
}

void Printboard(spaceInfo* board, sizeCode size) {

	for (short j = 0; j < size.Y; j++) {

		std::cout << "\n ";

		for (short i = 0; i < size.X; i++) {
			std::cout << board[j * size.X + i].occupant << board[j * size.X + i].occupant << board[j * size.X + i].occupant << board[j * size.X + i].occupant;

			std::cout << (i < size.X - 1 ? " | " : " ");
		}

		std::cout << "\n ";

		for (short i = 0; i < size.X; i++) {
			std::cout << board[j * size.X + i].occupant << board[j * size.X + i].Y << board[j * size.X + i].X << board[j * size.X + i].occupant;

			std::cout << (i < size.X - 1 ? " | " : " ");
		}

		std::cout << "\n ";

		for (short i = 0; i < size.X; i++) {
			std::cout << board[j * size.X + i].occupant << board[j * size.X + i].occupant << board[j * size.X + i].occupant << board[j * size.X + i].occupant;

			std::cout << (i < size.X - 1 ? " | " : " ");
		}

		std::cout << '\n' << (j < (size.Y - 1) ? "-" : "");

		for (short i = 0; i < size.X; i++) {
			if (j < (size.Y - 1)) {
				std::cout << "----" << (i < (size.X - 1) ? "-|-" : "-");
			}
		}
	}
}

posCode MakeMove(spaceInfo* board, sizeCode size, char player) {
	posCode pos;
	do {
		pos = GetAndCheckPlayerInputForMove(board, size);
	} while (pos.X == -1);
	board[pos.Y * size.X + pos.X].occupant = player;
	return pos;
}

posCode GetAndCheckPlayerInputForMove(spaceInfo* board, sizeCode size) {
	std::string line;
	posCode posOfPlayerMove;

	std::getline(std::cin, line);

	if (line[0] < 65 || line[0] > 65 + size.Y - 1 || line[1] < 97 || line[1] > 97 + size.X - 1) {
		std::cout << "Valid Space Codes Only Please\n";
		return posOfPlayerMove;
	}
	else if (board[(line[0] - 65) * size.X + (line[1] - 97)].occupant != ' ') {
		std::cout << "Empty Spaces Only Please\n";
		return posOfPlayerMove;
	}
	else {
		posOfPlayerMove.X = line[1] - 97;
		posOfPlayerMove.Y = line[0] - 65;
	}
	return posOfPlayerMove;
}

bool CheckIfPlayerWins(spaceInfo* board, sizeCode size, posCode pos, char winCondition) {
	if (CheckDirForWin(board, size, pos, posCode(0, 1)) > winCondition - 1) {
		return 1;
	}
	else if (CheckDirForWin(board, size, pos, posCode(1, 0)) > winCondition - 1) {
		return 1;
	}
	else if (CheckDirForWin(board, size, pos, posCode(1, 1)) > winCondition - 1) {
		return 1;
	}
	else if (CheckDirForWin(board, size, pos, posCode(-1, 1)) > winCondition - 1) {
		return 1;
	}
	return 0;
}

char CheckDirForWin(spaceInfo* board, sizeCode size, posCode pos, posCode dirToCheck) {
	char total = -1;
	char player = board[pos.Y * size.X + pos.X].occupant;

	for (char i = pos.X, j = pos.Y; i < size.X && j < size.Y && i > -1 && j > -1; i += dirToCheck.X, j += dirToCheck.Y) {
		if (board[j * size.X + i].occupant == player) {
			total++;
		}
		else {
			break;
		}
	}

	for (char i = pos.X, j = pos.Y; i < size.X && j < size.Y && i > -1 && j > -1; i -= dirToCheck.X, j -= dirToCheck.Y) {
		if (board[j * size.X + i].occupant == player) {
			total++;
		}
		else {
			break;
		}
	}
	return total;
}
