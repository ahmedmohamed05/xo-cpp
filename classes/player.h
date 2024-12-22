#pragma once
#include <iostream>

// Player comes with default letter x, to change it call change letter method
class XOPlayer {
private:
  bool _myTurn;
  unsigned _score, _wins, _losses;
  char _letter;

public:
  XOPlayer() {
    _letter = 'X';
    _myTurn = false;
    _score = 0;
    _wins = 0;
    _losses = 0;
  }

  XOPlayer(bool turn) {
    _letter = 'X';
    _myTurn = turn;
    _score = 0;
    _wins = 0;
    _losses = 0;
  }

  void changeTurn() { _myTurn = !_myTurn; }
  bool isItMyTurn() { return _myTurn; }

  void increaseScore(unsigned quantity) {
    if (quantity < 0)
      return;

    _score += quantity;
  }
  void decreaseScore(unsigned quantity) {
    if (quantity < 0)
      return;

    _score -= quantity;
  }

  unsigned getScore() { return _score; }

  // make the player wins
  void won() { _wins++; }
  unsigned getWins() { return _wins; }

  // make the player lose
  void lost() { _losses++; }
  unsigned getLosses() { return _losses; }

  // Changes player letter X <-> O
  void changeLetter() {
    if (_letter == 'X')
      _letter = 'O';
    else
      _letter = 'X';
  }
  char getLetter() { return _letter; }
};