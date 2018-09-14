#include <iostream>
#include "lexer/lexer.h"

using std::string;
using std::vector;
using std::unique_ptr;
using std::cout;
using std::cin;
using std::endl;

int main(int argc, char **argv) {
  string command;
  std::getline(cin, command);
  vector<unique_ptr<const Token>> tokes;
  cout << "Lexical analysis:" << endl;
  tokenize_command(command, tokes);
  for (auto it = tokes.begin(); it != tokes.end(); ++it) {
    cout << **it << " ";
  }
  cout << endl;
  cout << "Parsing analysis:" << endl;
  
}
