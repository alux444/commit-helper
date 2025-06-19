#include "CommitTypes.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

// Terminal helpers
void clearTerminal()
{
  std::cout << "\033[2J\033[H";
}

void enterAltScreen()
{
  std::cout << "\033[?1049h";
}

void exitAltScreen()
{
  std::cout << "\033[?1049l";
}

// Commit preview builder
std::string buildCommitPreview(
    const CommitType *type,
    const std::string &wip,
    const std::string &scope,
    const std::string &desc,
    const std::vector<CommitType> &statuses)
{
  std::string preview;
  if (type && !type->emoji.empty())
    preview += type->emoji;
  if (wip == "y" && !statuses.empty())
    preview += statuses[0].emoji;
  if (type && !type->id.empty())
  {
    preview += " " + type->id;
    if (!scope.empty())
      preview += "(" + scope + ")";
    preview += ": ";
  }
  if (!desc.empty())
    preview += desc;
  return preview;
}

// Category selector
int selectCategory(const std::vector<CommitTypeCategory> &categories, const std::string &preview)
{
  clearTerminal();
  std::cout << "Current commit: " << preview << "\n\n";
  std::cout << "Select a commit category:\n";
  for (size_t i = 0; i < categories.size(); ++i)
  {
    std::cout << i + 1 << ") " << categories[i].first << "\n";
  }
  std::cout << "0) Go back\n";

  int catChoice = -1;
  while (catChoice < 0 || catChoice > static_cast<int>(categories.size()))
  {
    std::cout << "Enter choice [0-" << categories.size() << "]: ";
    std::cin >> catChoice;
    std::cin.ignore();
  }
  return (catChoice == 0) ? -1 : catChoice;
}

// Commit type selector
const CommitType &selectCommit(
    const std::vector<CommitType> &options,
    const std::string &promptText,
    bool allowBack,
    const std::string &preview)
{
  clearTerminal();
  std::cout << "Current commit: " << preview << "\n\n";
  std::cout << promptText << "\n";
  for (size_t i = 0; i < options.size(); ++i)
  {
    std::cout << i + 1 << ") " << options[i].emoji << "  " << options[i].id << "\n";
  }
  if (allowBack)
    std::cout << "0) Go back\n";

  int choice = -1;
  while (choice < (allowBack ? 0 : 1) || choice > static_cast<int>(options.size()))
  {
    std::cout << "Enter choice [";
    if (allowBack)
      std::cout << "0-";
    std::cout << options.size() << "]: ";
    std::cin >> choice;
    std::cin.ignore();
  }

  static CommitType empty = {"", "", ""};
  return (choice == 0 && allowBack) ? empty : options[choice - 1];
}

// Prompt with preview
std::string prompt(const std::string &label, bool allowBack, const std::string &preview)
{
  clearTerminal();
  std::cout << "Current commit: " << preview << "\n\n";
  std::cout << label;
  if (allowBack)
    std::cout << " (type '0' to go back)";
  std::cout << ": ";

  std::string input;
  std::getline(std::cin, input);
  return input;
}

void resetCommitState(std::string &wip, std::string &scope, std::string &desc, const CommitType *&type)
{
  wip.clear();
  scope.clear();
  desc.clear();
  type = nullptr;
}

bool handleCommitFlow(
    const std::vector<CommitType> &subtypes,
    const std::vector<CommitType> &statuses,
    std::string &wip,
    std::string &scope,
    std::string &desc,
    const CommitType *&type)
{
  while (true)
  {
    const CommitType selected = selectCommit(subtypes, "Select a commit type:", true, buildCommitPreview(type, wip, scope, desc, statuses));
    if (selected.id.empty())
    {
      return false;
    }
    type = &selected;

    wip = prompt("Is this commit WIP? (y/n)", true, buildCommitPreview(type, wip, scope, desc, statuses));
    if (wip == "0")
      continue;

    scope = prompt("Enter scope (press Enter to skip)", true, buildCommitPreview(type, wip, scope, desc, statuses));
    if (scope == "0")
      continue;

    while (true)
    {
      desc = prompt("Enter short description", true, buildCommitPreview(type, wip, scope, desc, statuses));
      if (desc == "0")
      {
        scope.clear();
        desc.clear();
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
    if (desc.empty())
      continue;

    std::string message = buildCommitPreview(type, wip, scope, desc, statuses);

    std::string confirm = prompt("Confirm?", true, message);
    if (confirm == "0")
      continue;
    if (!confirm.empty())
      return true;

    std::string command = "git commit -m \"" + message + "\"";

    exitAltScreen();

    std::cout << "Running: " << command << "\n";
    std::exit(system(command.c_str()));
  }
  return false;
}

int main()
{
  enterAltScreen();

  const auto &categories = getCommitTypeCategories();
  const auto &statuses = getCommitStatuses();

  std::string wip, scope, desc;
  const CommitType *type = nullptr;

  while (true)
  {
    int catChoice = selectCategory(categories, buildCommitPreview(type, wip, scope, desc, statuses));
    if (catChoice == -1)
    {
      resetCommitState(wip, scope, desc, type);
      continue;
    }
    const auto &subtypes = categories[catChoice - 1].second;

    bool cancelled = !handleCommitFlow(subtypes, statuses, wip, scope, desc, type);
    if (cancelled)
    {
      resetCommitState(wip, scope, desc, type);
      continue;
    }
    // If handleCommitFlow returns, user cancelled or completed
    break;
  }
}