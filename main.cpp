#include "./classes/game.h"
#include "./libs/input.h"
#include <iostream>

void printPlayer(XOPlayer *p);
int readRounds();
void printFinalResult(XOGame::results result);
XOPlayer *getWinner(std::pair<XOPlayer, XOPlayer> *players);
void printBoard(char **board);
void playRound(XOGame *game, int currentRound, int totalRounds);
void playLocally(int rounds);
int getComputerMove(char **board);
void playAgainstComputer(int rounds);
enum PlayingOptions { locally = 1, computer = 2 };
PlayingOptions readPlayingOption();
void play(PlayingOptions option, int rounds);

int main() {
  char playAgain = 'y';

  while (tolower(playAgain) == 'y') {
    system("clear");
    PlayingOptions playingOption = readPlayingOption();
    int rounds = readRounds();
    play(playingOption, rounds);

    playAgain = Input::readCharacter("Do you want ot play again [y, n]: ");
  }

  return 0;
}

PlayingOptions readPlayingOption() {
  std::cout << "Playing Options: \n";
  std::cout << "[1] You Can play locally.\n";
  std::cout << "[2] Play with the computer.\n";

  int choice = Input::readIntInRange("Enter 1 or 2: ", 1, 2);
  return PlayingOptions(choice);
}

int readRounds() {
  int rounds = Input::readInt("Enter number of rounds: ");
  while (rounds < 0) {
    std::cerr << "Number of rounds must be a  positive number\n";
    rounds = Input::readInt("Enter number of rounds: ");
  }

  return rounds;
}

void play(PlayingOptions option, int rounds) {
  if (option == locally)
    playLocally(rounds);
  else
    playAgainstComputer(rounds);
}

void playLocally(int rounds) {
  XOGame game(10);
  for (int i = 1; i <= rounds; i++) {
    playRound(&game, i, rounds);
    system("clear");

    printFinalResult(game.state());
    game.reset();

    std::pair<XOPlayer, XOPlayer> players = game.getPlayers();
    std::cout << "Players results: \n";
    std::cout << "-------------------------------------\n";
    printPlayer(&players.first);
    std::cout << "-------------------------------------\n";
    printPlayer(&players.second);

    std::cout << "Press Enter to continue\n";
    std::cin.clear();
    std::cin.get();
    std::cin.get();
  }
  system("clear");
  std::pair<XOPlayer, XOPlayer> players = game.getPlayers();
  XOPlayer *winner = getWinner(&players);

  if (winner == nullptr) {
    std::cout << "It's a tie: \n";
  } else {
    std::cout << "Winner: \n";
    printPlayer(winner);
  }
}

void playAgainstComputer(int rounds) {
  XOGame game(10);
  for (int i = 1; i <= rounds; i++) {

    while (game.state() == XOGame::NotDoneYet) {
      system("clear");
      std::cout << "Round " << i << " of " << rounds << '\n';

      printBoard(game.getBoard());

      // Computer turn
      if (game.howsTurn() == 'O') {
        int computerMove = getComputerMove(game.getBoard());

        if (computerMove == -1) {
          std::cerr << "Something went wrong\n";
          exit(EXIT_FAILURE);
        }

        if (!game.play(computerMove)) {
          std::cerr << "Something went wrong\n";
          exit(EXIT_FAILURE);
        }
        continue;
      }

      int playingPosition =
          Input::readIntInRange("Enter Playing Position [1, 9]: ", 1, 9);

      bool success = game.play(playingPosition);
      while (!success) {
        std::cerr << "This box already played, Choice another one\n";
        playingPosition =
            Input::readIntInRange("Enter Playing Position [1, 9]: ", 1, 9);
        success = game.play(playingPosition);
      }
    }

    system("clear");

    printFinalResult(game.state());
    game.reset();

    std::pair<XOPlayer, XOPlayer> players = game.getPlayers();
    std::cout << "Players results: \n";
    std::cout << "-------------------------------------\n";
    printPlayer(&players.first);
    std::cout << "-------------------------------------\n";
    printPlayer(&players.second);

    std::cout << "Press Enter to continue\n";
    std::cin.clear();
    std::cin.get();
    std::cin.get();
  }

  system("clear");
  std::pair<XOPlayer, XOPlayer> players = game.getPlayers();
  XOPlayer *winner = getWinner(&players);

  if (winner == nullptr) {
    std::cout << "It's a tie: \n";
  } else {
    std::cout << "Winner: \n";
    printPlayer(winner);
  }
}

void printPlayer(XOPlayer *p) {
  std::cout << "Item  : " << p->getLetter() << '\n';
  std::cout << "Score : " << p->getScore() << '\n';
  std::cout << "Wins  : " << p->getWins() << '\n';
  std::cout << "Losses: " << p->getLosses() << '\n';
}

void printFinalResult(XOGame::results result) {
  switch (result) {
  case XOGame::Draw:
    std::cout << "It's a DRAW!!!\n";
    break;
  case XOGame::X:
    std::cout << "Congratulation X player won, !!\n";
    break;
  case XOGame::O:
    std::cout << "Congratulation O player won, !!\n";
    break;
  }
}

XOPlayer *getWinner(std::pair<XOPlayer, XOPlayer> *players) {
  if (players->first.getScore() > players->second.getScore())
    return &players->first;

  if (players->first.getScore() < players->second.getScore())
    return &players->second;

  // it's a tie
  return nullptr;
}

void printBoard(char **board) {
  short indicator = 1;
  for (int i = 0; i < 3; i++) {
    // Print horizontal line
    std::cout << '-';
    for (int j = 0; j < 3; j++) {
      std::cout << "--";
    }

    std::cout << '\n';
    std::cout << '|';

    // print game
    for (int j = 0; j < 3; j++) {
      // Print box item or box number if the box empty
      if (board[i][j] == '-') {
        std::cout << indicator << '|';
      } else {
        std::cout << board[i][j] << '|';
      }
      indicator++;
    }

    std::cout << '\n';
  }
  // print the bottom line
  std::cout << "-------\n";
}

void playRound(XOGame *game, int currentRound, int totalRounds) {
  while (game->state() == XOGame::NotDoneYet) {
    system("clear");
    std::cout << "Round " << currentRound << " of " << totalRounds << '\n';

    printBoard(game->getBoard());

    std::cout << game->howsTurn() << " to play\n";

    int playingPosition =
        Input::readIntInRange("Enter Playing Position [1, 9]: ", 1, 9);

    bool success = game->play(playingPosition);
    while (!success) {
      std::cerr << "This box already played on, Choice another one\n";
      playingPosition =
          Input::readIntInRange("Enter Playing Position [1, 9]: ", 1, 9);
      success = game->play(playingPosition);
    }
  }
}

int getComputerMove(char **board) {
  { // Check Rows
    int position = 0;
    for (int i = 0; i < 3; i++) {
      int userMarks = 0, emptyBoxes = 0, computerMarks = 0;
      bool updatePosition = true;
      for (int j = 0; j < 3; j++) {
        if (updatePosition)
          position++;

        if (board[i][j] == 'X')
          userMarks++;

        if (board[i][j] == 'O')
          computerMarks++;

        if (board[i][j] == '-') {
          emptyBoxes++;
          position = j + (i * 3 + 1); // to correct the position
          updatePosition = false;
        }
      }

      if ((userMarks == 2 || computerMarks == 2) && emptyBoxes == 1)
        return position;
    }
  }

  { // Check columns
    int position = 0;
    for (int i = 0; i < 3; i++) {
      int userMarks = 0, emptyBoxes = 0, computerMarks = 0;
      bool updatePosition = true;
      for (int j = 0; j < 3; j++) {
        if (updatePosition)
          position++;

        if (board[j][i] == 'X')
          userMarks++;

        if (board[j][i] == 'O')
          computerMarks++;

        if (board[j][i] == '-') {
          emptyBoxes++;
          position = j * 3 + i + 1; // to correct the position
          updatePosition = false;
        }
      }

      if ((userMarks == 2 || computerMarks == 2) && emptyBoxes == 1)
        return position;
    }
  }

  // Check main diagonal
  {
    int position = 0, userMarks = 0, emptyBoxes = 0, computerMarks = 0;
    bool updatePosition = true;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (updatePosition)
          position++;
        if (i == j) {
          if (board[i][j] == 'X')
            userMarks++;
          if (board[i][j] == 'O')
            computerMarks++;

          if (board[i][j] == '-') {
            emptyBoxes++;
            updatePosition = false;
          }
        }
      }

      if ((userMarks == 2 || computerMarks == 2) && emptyBoxes == 1)
        return position;
    }
  }

  // Anti-Diagonal
  {
    int position = 0, userMarks = 0, emptyBoxes = 0, computerMarks = 0;
    bool updatePosition = true;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (updatePosition)
          position++;
        if (i + j == 2) {
          if (board[i][j] == 'X')
            userMarks++;

          if (board[i][j] == 'O')
            computerMarks++;

          if (board[i][j] == '-') {
            emptyBoxes++;
            updatePosition = false;
          }
        }
      }

      if ((userMarks == 2 || computerMarks == 2) && emptyBoxes == 1)
        return position;
    }
  }

  int position = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      position++;
      if (board[i][j] == '-') {
        return position;
      }
    }
  }

  return -1;
}
