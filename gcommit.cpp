#include "CommitTypes.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

const CommitType &selectCommit(const std::vector<CommitType> &options, const std::string &promptText, bool allowBack = false)
{
  std::cout << promptText << "\n";
  for (size_t i = 0; i < options.size(); ++i)
  {
    std::cout << i + 1 << ") " << options[i].emoji << "  " << options[i].id << "\n";
  }
  if (allowBack)
  {
    std::cout << "0) Go back\n";
  }

  int choice = -1;
  while (choice < (allowBack ? 0 : 1) || choice > (int)options.size())
  {
    std::cout << "Enter choice [";
    if (allowBack)
      std::cout << "0-";
    std::cout << options.size() << "]: ";
    std::cin >> choice;
    std::cin.ignore(); // clear newline
  }

  static CommitType empty = {"", "", ""};
  return (choice == 0 && allowBack) ? empty : options[choice - 1];
}

int selectCategory(const std::vector<CommitTypeCategory> &categories)
{
  std::cout << "Select a commit category:\n";
  for (size_t i = 0; i < categories.size(); ++i)
  {
    std::cout << i + 1 << ") " << categories[i].first << "\n";
  }
  std::cout << "0) Go back\n";
  int catChoice = -1;
  while (catChoice < 0 || catChoice > (int)categories.size())
  {
    std::cout << "Enter choice [0-" << categories.size() << "]: ";
    std::cin >> catChoice;
    std::cin.ignore();
  }
  return catChoice;
}

std::string prompt(const std::string &label, bool allowBack = false)
{
  std::cout << label;
  if (allowBack)
    std::cout << " (type 'back' to go back)";
  std::cout << ": ";
  std::string input;
  std::getline(std::cin, input);
  return input;
}

int main()
{
  const auto &categories = getCommitTypeCategories();
  const auto &statuses = getCommitStatuses();

  while (true)
  {
    // Category selection
    int catChoice = selectCategory(categories);
    if (catChoice == 0)
    {
      std::cout << "Cancelled.\n";
      return 0;
    }
    const auto &subtypes = categories[catChoice - 1].second;

    // Commit type selection
    CommitType type;
    while (true)
    {
      type = selectCommit(subtypes, "Select a commit type:", true);
      if (type.id.empty())
      {
        // Go back to category selection
        break;
      }

      // WIP prompt
      std::string wip = prompt("Is this commit WIP? (y)", true);
      if (wip == "back")
        continue;

      // Scope prompt
      std::string scope = prompt("Enter scope (optional, press Enter to skip)", true);
      if (scope == "back")
        continue;

      // Description prompt
      std::string desc;
      while (true)
      {
        desc = prompt("Enter short description", true);
        if (desc == "back")
        {
          scope = "back";
          break;
        }
        if (desc.empty())
        {
          std::cerr << "❌ Description cannot be empty.\n";
        }
        else
        {
          break;
        }
      }
      if (scope == "back")
        continue;

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

      std::string confirm = prompt("Confirm? (y)", true);
      if (confirm == "back")
        continue;
      if (confirm != "y")
        return 0;
      std::cout << '\n';

      std::string command = "git commit -m \"" + message + "\"";
      std::cout << "Running: " << command << "\n";

      return system(command.c_str());
    }
  }
}