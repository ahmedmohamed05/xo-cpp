#pragma once
#include <iostream>
#include <limits>
#include <vector>

class Input {

public:
  static int readInt(std::string msg, std::string errMsg = "Invalid number\n") {
    int n;
    std::cout << msg;
    std::cin >> n;

    while (std::cin.fail()) {
      std::cout << errMsg;

      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      std::cout << msg;
      std::cin >> n;
    }

    return n;
  }

  static short readShort(std::string msg,
                         std::string errMsg = "Invalid number\n") {
    short n;
    std::cout << msg;
    std::cin >> n;

    while (std::cin.fail()) {
      std::cout << errMsg;

      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      std::cout << msg;
      std::cin >> n;
    }

    return n;
  }

  static int readIntInRange(std::string msg, int min, int max,
                            std::string errMsg = "Invalid number\n") {
    int n = readInt(msg, errMsg);

    while (!isNumberBetween(n, min, max)) {
      std::cout << errMsg;
      n = readInt(msg, errMsg);
    }

    return n;
  }

  static short readShortInRange(std::string msg, short min, short max,
                                std::string errMsg = "Invalid number\n") {
    short n = readShort(msg, errMsg);

    while (!isNumberBetween(n, min, max)) {
      std::cout << errMsg;
      n = readShort(msg, errMsg);
    }

    return n;
  }

  static unsigned int readUnsignedInt(std::string msg) {
    unsigned n;
    std::cout << msg;
    std::cin >> n;

    while (std::cin.fail()) {
      std::cout << "Invalid number\n";

      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      std::cout << msg;
      std::cin >> n;
    }

    return n;
  }

  static unsigned short
  readUnsignedShort(std::string msg, std::string errMsg = "Invalid number\n") {
    unsigned short n;
    std::cout << msg;
    std::cin >> n;

    while (std::cin.fail()) {
      std::cout << errMsg;

      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      std::cout << msg;
      std::cin >> n;
    }

    return n;
  }

  static double readDouble(std::string msg,
                           std::string errMsg = "Invalid number\n") {
    double n;

    std::cout << msg;
    std::cin >> n;

    while (std::cin.fail()) {
      std::cout << errMsg;

      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      std::cout << msg;
      std::cin >> n;
    }

    return n;
  }

  static std::string readString(std::string msg) {
    std::string answer = "";

    std::cout << msg;
    std::getline(std::cin >> std::ws, answer);

    return answer;
  }

  static bool readBool(std::string msg,
                       std::string errMsg = "Invalid number\n") {
    bool answer;
    std::cout << msg;
    std::cin >> answer;

    while (std::cin.fail()) {
      std::cout << errMsg;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << msg;
      std::cin >> answer;
    }

    return answer;
  }

  static char readCharacter(std::string msg,
                            std::string errMsg = "Invalid number\n") {
    std::cin.clear();
    char answer;

    std::cout << msg;
    std::cin >> answer;

    while (std::cin.fail()) {
      std::cout << errMsg;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << msg;
      std::cin >> answer;
    }

    return answer;
  }

  static void readVectorItem(std::vector<int> &vctr, std::string msg,
                             std::string errMsg = "Invalid number\n") {
    vctr.push_back(readInt(msg, errMsg));
  }

  static void readVectorItem(std::vector<std::string> &vctr, std::string msg,
                             bool clearWhiteSpaces = true) {
    vctr.push_back(readString(msg));
  }

  static void fillVector(std::vector<int> &v, std::string msg,
                         std::string errMsg = "Invalid number\n") {
    char addMore = 'y';

    while (addMore == 'y' || addMore == 'Y') {
      readVectorItem(v, msg, errMsg);
      addMore = readCharacter("Do you want to add more: [n, y]: ");
    }
  }

  static void fillVector(std::vector<std::string> &v, std::string msg,
                         bool clearWhiteSpaces = true) {
    char addMore = 'y';

    while (addMore == 'y' || addMore == 'Y') {
      readVectorItem(v, msg, clearWhiteSpaces);
      addMore = readCharacter("Do you want to add more: [n, y]: ");
    }
  }

  template <typename T> static bool isNumberBetween(T n, T min, T max) {
    return (min <= n && n <= max);
  }
};
