#include "CommitTypes.h"
#include <iostream>
#include <string>
#include <cstdlib>

const CommitType &selectCommit(const std::vector<CommitType> &options, const std::string &promptText, bool allowSkip = false)
{
  std::cout << promptText << "\n";
  for (size_t i = 0; i < options.size(); ++i)
  {
    std::cout << i + 1 << ") " << options[i].emoji << "  " << options[i].id << "\n";
  }
  if (allowSkip)
  {
    std::cout << "0) Skip\n";
  }

  int choice = -1;
  while (choice < (allowSkip ? 0 : 1) || choice > (int)options.size())
  {
    std::cout << "Enter choice [";
    if (allowSkip)
      std::cout << "0-";
    std::cout << options.size() << "]: ";
    std::cin >> choice;
    std::cin.ignore(); // clear newline
  }

  static CommitType empty = {"", "", ""};
  return (choice == 0 && allowSkip) ? empty : options[choice - 1];
}

std::string prompt(const std::string &label)
{
  std::cout << label;
  std::string input;
  std::getline(std::cin, input);
  return input;
}

int main()
{
  const auto &types = getCommitTypes();
  const auto &statuses = getCommitStatuses();

  // Choose commit type (required)
  CommitType type = selectCommit(types, "Select a commit type:");

  // Choose commit status (optional)
  CommitType status = selectCommit(statuses, "Select a commit status (optional):", true);

  std::string scope = prompt("Enter scope (optional, press Enter to skip): ");
  std::string desc = prompt("Enter short description: ");

  if (desc.empty())
  {
    std::cerr << "❌ Description cannot be empty.\n";
    return 1;
  }

  std::string prefix;
  if (!status.emoji.empty())
  {
    prefix += status.emoji + " ";
  }
  prefix += type.id;

  std::string message;
  if (!scope.empty())
  {
    message = prefix + "(" + scope + "): " + desc;
  }
  else
  {
    message = prefix + ": " + desc;
  }

  std::string command = "git commit -m \"" + message + "\"";
  std::cout << "Running: " << command << "\n";

  return system(command.c_str());
}
