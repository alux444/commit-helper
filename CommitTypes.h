#pragma once
#include <string>
#include <vector>

struct CommitType
{
    std::string id;
    std::string emojiAlias;
    std::string emoji;
};

using CommitTypeCategory = std::pair<std::string, std::vector<CommitType>>;

const std::vector<CommitTypeCategory> &getCommitTypeCategories();
const std::vector<CommitType> &getCommitStatuses();