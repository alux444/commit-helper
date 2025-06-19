#include "CommitTypes.h"
#include <iostream>
#include <string>
#include <vector>
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
  const auto &categories = getCommitTypeCategories();
  const auto &statuses = getCommitStatuses();

  // Present categories to user
  std::cout << "Select a commit category:\n";
  for (size_t i = 0; i < categories.size(); ++i)
  {
    std::cout << i + 1 << ") " << categories[i].first << "\n";
  }
  int catChoice = -1;
  while (catChoice < 1 || catChoice > (int)categories.size())
  {
    std::cout << "Enter choice [1-" << categories.size() << "]: ";
    std::cin >> catChoice;
    std::cin.ignore();
  }
  const auto &subtypes = categories[catChoice - 1].second;

  // Now select the actual type within the chosen category
  CommitType type = selectCommit(subtypes, "Select a commit type:");

  std::cout << '\n';

  std::string wip = prompt("Is this commit WIP? (y): ");
  std::cout << '\n';

  std::string scope = prompt("Enter scope (optional, press Enter to skip): ");
  std::cout << '\n';

  std::string desc = prompt("Enter short description: ");
  std::cout << '\n';

  if (desc.empty())
  {
    std::cerr << "❌ Description cannot be empty.\n";
    return 1;
  }

  std::string prefix;

  if (!type.emoji.empty())
  {
    prefix += type.emoji;
  }

  if (wip == "y")
  {
    prefix += statuses[0].emoji;
  }

  prefix += " ";
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

  std::cout << "Final git commit message: \n"
            << message << '\n';

  std::string confirm = prompt("Confirm? (y): ");
  if (confirm != "y")
    return 0;
  std::cout << '\n';

  std::string command = "git commit -m \"" + message + "\"";
  std::cout << "Running: " << command << "\n";

  // return system(command.c_str());
}