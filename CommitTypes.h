#pragma once
#include <string>
#include <vector>

struct CommitType {
    std::string id;
    std::string emojiAlias; 
    std::string emoji;
};

const std::vector<CommitType>& getCommitTypes();
const std::vector<CommitType>& getCommitStatuses();
