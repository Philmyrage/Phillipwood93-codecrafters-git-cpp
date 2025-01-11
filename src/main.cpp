#include <iostream>
#include <vector>
#include <sstream>

std::vector<std::string> commands = {"exit", "echo", "type"};

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

void tokenizeString(std::vector<std::string> &outTokens, const std::string &str)
{
  std::stringstream inputStream(str);
  std::string temp;
  while (inputStream >> temp)
  {
    outTokens.push_back(temp);
  }
}

void echo(std::vector<std::string> &tokens)
{
  std::string temp = "";
  for (int i = 1; i < tokens.size(); ++i)
  {
    temp += tokens[i] + " ";
  }
  std::cout << temp << std::endl;
}

int main()
{
  std::string input;
  do
  {
    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    std::cout << "$ ";

    std::getline(std::cin, input);

    std::vector<std::string> tokens;
    tokenizeString(tokens, input);

    if (validCommand(tokens[0]))
    {
      if (tokens[0] == "exit")
      {
        exit(std::stoi(tokens[1]));
      }
      else if (tokens[0] == "echo")
      {
        echo(tokens);
      }
      else if (tokens[0] == "type")
      {
        if (validCommand(tokens[1]))
        {
          std::cout << tokens[1] << " is a shell builtin" << std::endl;
        }
        else
        {
          std::cout << tokens[1] << ": not found" << std::endl;
        }
      }
    }
    else
    {
      std::cout << input << ": command not found" << std::endl;
    }

  } while (input != "");
}
