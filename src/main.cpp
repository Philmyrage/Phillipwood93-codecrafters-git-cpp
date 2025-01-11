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
  return valid;
}

int main()
{
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::cout << "$ ";

  std::string input;
  do
  {
    std::getline(std::cin, input);
    if (validCommand(input))
    {
      // TODO: Handle valid commands...
    }
    else
    {
      std::cout << input << ": command not found" << std::endl;
      std::cout << "$ ";
    }

  } while (input != "");
}
