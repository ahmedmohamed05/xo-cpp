#pragma once
#include "./player.h"
#include <iostream>

class XOGame {
public:
  enum results { X = 'X', O = 'O', Draw, NotDoneYet };

private:
  XOPlayer *_p1, *_p2;
  char **_board;

  int _winningScore;

  results _state;

  void _checkGame() {
    // First row case
    if (_board[0][0] == _board[0][1] && _board[0][0] == _board[0][2] &&
        _board[0][0] != '-') {
      _state = results(_board[0][0]);
      return;
    }
    // Second row case
    if (_board[1][0] == _board[1][1] && _board[1][0] == _board[1][2] &&
        _board[1][0] != '-') {
      _state = results(_board[1][0]);
      return;
    }
    // Third row case
    if (_board[2][0] == _board[2][1] && _board[2][0] == _board[2][2] &&
        _board[2][0] != '-') {
      _state = results(_board[2][0]);
      return;
    }
    // First column case
    if (_board[0][0] == _board[1][0] && _board[0][0] == _board[2][0] &&
        _board[0][0] != '-') {
      _state = results(_board[0][0]);
      return;
    }
    // Second column case
    if (_board[0][1] == _board[1][1] && _board[0][1] == _board[2][1] &&
        _board[0][1] != '-') {
      _state = results(_board[0][1]);
      return;
    }
    // Third column case
    if (_board[0][2] == _board[1][2] && _board[0][2] == _board[2][2] &&
        _board[0][2] != '-') {
      _state = results(_board[0][2]);
      return;
    }
    // Main diagonal case
    if (_board[0][0] == _board[1][1] && _board[0][0] == _board[2][2] &&
        _board[0][0] != '-') {
      _state = results(_board[0][0]);
      return;
    }
    // Second diagonal case
    if (_board[0][2] == _board[1][1] && _board[0][2] == _board[2][0] &&
        _board[0][2] != '-') {
      _state = results(_board[0][2]);
      return;
    }

    // game still on
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (_board[i][j] == '-') {
          _state = results::NotDoneYet;
          return;
        }
      }
    }

    // otherwise it is a draw
    _state = results::Draw;
  }

public:
  XOGame(int winningScore = 100) {
    _p1 = new XOPlayer(true);
    _p2 = new XOPlayer;
    _p2->changeLetter();
    setWinningScore(winningScore);
    _state = results::NotDoneYet;
    _board = new char *[3];
    reset();
  }

  ~XOGame() {
    delete _p1, _p2;
    for (int i = 0; i < 3; i++) {
      delete[] _board[i];
    }
    _board = nullptr;
  }

  results state() { return _state; }

  // if new score less than 0 it will reset to 100 point
  void setWinningScore(int score) {
    if (score <= 0) {
      score = 100;
    }
    _winningScore = score;
  }
  int getWinningScore() { return _winningScore; }

  // retuns boolean if action done correctly
  bool play(int position) {
    if (_state != results::NotDoneYet)
      return false;

    char itemToPlay = '-';
    // Select X or O
    itemToPlay = (_p1->isItMyTurn() ? _p1->getLetter() : _p2->getLetter());

    short indicator = 1;

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (indicator++ != position)
          continue;

        // we are at the correct position and it is already played
        if (_board[i][j] != '-')
          return false;

        _board[i][j] = itemToPlay;

        // Change players turns
        _p1->changeTurn();
        _p2->changeTurn();

        _checkGame();

        if (_state == results::X) {
          _p1->increaseScore(_winningScore);
          _p1->won();
          _p2->lost();
        }
        if (_state == results::O) {
          _p2->increaseScore(_winningScore);
          _p2->won();
          _p1->lost();
        }

        return true;
      }
    }

    // in case something went wrong
    return false;
  }

  void reset() {
    for (int i = 0; i < 3; i++) {
      _board[i] = new char[3];
      for (int j = 0; j < 3; j++) {
        _board[i][j] = '-';
      }
    }
    _state = results::NotDoneYet;

    // reset turns
    if (!_p1->isItMyTurn()) {
      _p1->changeTurn();
      _p2->changeTurn();
    }
  }

  std::pair<XOPlayer, XOPlayer> getPlayers() {
    return std::pair<XOPlayer, XOPlayer>{*_p1, *_p2};
  }

  char howsTurn() {
    return (_p1->isItMyTurn() ? _p1->getLetter() : _p2->getLetter());
  }

  // Return pointer to a copy from the board
  char **getBoard() {
    char **board = new char *[3];
    // Copying the original board
    for (int i = 0; i < 3; i++) {
      board[i] = new char[3];
      for (int j = 0; j < 3; j++) {
        board[i][j] = _board[i][j];
      }
    }

    return board;
  }
};