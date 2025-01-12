#include <iostream>
#include <vector>
#include <sstream>
#include <filesystem>
#include <cstdlib>

std::vector<std::string>
    commands = {"exit", "echo", "type"};

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

void echo(const std::vector<std::string> &tokens)
{
  std::string temp = "";
  for (int i = 1; i < tokens.size(); ++i)
  {
    temp += tokens[i] + " ";
  }
  std::cout << temp << std::endl;
}

void splitString(std::vector<std::string> &outTokens, const std::string &str, const char &delimiter = ':')
{
  std::string temp = "";
  for (int i = 0; i < str.size(); ++i)
  {
    if (str[i] != delimiter)
    {
      temp += str[i];
    }
    if (i == str.size() - 1 || str[i] == delimiter)
    {
      outTokens.push_back(temp);
      temp = "";
    }
  }
}

std::pair<bool, std::string> searchPath(const std::string &cmd)
{
  std::vector<std::string> pathTokens;
  std::string pathEnv = getenv("PATH");
  splitString(pathTokens, pathEnv);

  for (int i = 0; i < pathTokens.size(); ++i)
  {
    for (const auto &dir : std::filesystem::directory_iterator(pathTokens[i]))
    {
      std::string t = dir.path().c_str();
      size_t i = t.find_last_of("/");
      t = t.substr(i + 1, t.size());
      if (t == cmd)
      {
        return std::pair(true, dir.path().c_str());
      }
    }
  }
  return std::pair(false, "");
}

void processCommand(const std::vector<std::string> &tokens)
{
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
      else if (searchPath(tokens[1]).first)
      {
        // TODO: Implement
        std::cout << tokens[1] << " found on path" << std::endl;
      }
      else
      {
        std::cout << tokens[1] << ": not found" << std::endl;
      }
    }
  }
  else
  {
    std::cout << tokens[0] << ": command not found" << std::endl;
  }
}

int main(int argc, char *argv[])
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
    processCommand(tokens);

  } while (input != "");
}
