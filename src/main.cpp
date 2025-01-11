#include <iostream>
#include <vector>

std::vector<std::string> commands = {};

bool validCommand(const std::string &cmd)
{
  bool valid = false;
  for (int i = 0; i < commands.size(); ++i)
  {
    if (cmd == commands[i])
    {
      return true;
    }
  }
  std::cout << cmd << ": command not found" << std::endl;
  return valid;
}

int main()
{
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::cout << "$ ";

  std::string input;
  std::getline(std::cin, input);
  validCommand(input);
}
