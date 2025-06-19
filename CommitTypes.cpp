#include "CommitTypes.h"
#include <string>
#include <vector>

static const std::vector<CommitType> dependencies = {
    {"add dependency", ":heavy_plus_sign:", "➕"},
    {"remove dependency", ":heavy_minus_sign:", "➖"},
    {"upgrade dependency", ":arrow_up:", "⬆️"},
    {"downgrade dependency", ":arrow_down:", "⬇️"},
    {"packages", ":package:", "📦"},
};

static const std::vector<CommitType> features = {
    {"feat", ":sparkles:", "✨"},
    {"feature flag", ":triangular_flag_on_post:", "🚩"},
};

static const std::vector<CommitType> fixes = {
    {"fix", ":hammer:", "🔨"},
    {"bug", ":bug:", "🐛"},
    {"hotfix", ":ambulance:", "🚑️"},
};

static const std::vector<CommitType> maintenance = {
    {"cleanup", ":soap:", "🧼"},
    {"refactor", ":recycle:", "♻️"},
    {"remove logging", ":mute:", "🔇"},
    {"add logging", ":loud_sound:", "🔊"},
    {"move files", ":truck:", "🚚"},
    {"removed", ":coffin:", "⚰️"},
    {"revert", ":rewind:", "⏪"},
};

static const std::vector<CommitType> documentation = {
    {"docs", ":memo:", "📝"},
};

static const std::vector<CommitType> configuration = {
    {"config", ":wrench:", "🔧"},
    {"ci", ":green_heart:", "💚"},
    {"docker", ":whale:", "🐳"},
    {"infra", ":bricks:", "🧱"},
};

static const std::vector<CommitType> style = {
    {"style", ":art:", "🎨"},
    {"types", ":label:", "🏷️"},
    {"lint", ":shirt:", "👕"},
};

static const std::vector<CommitType> testing = {
    {"test", ":test_tube:", "🧪"},
};

static const std::vector<CommitType> deployment = {
    {"deploy", ":rocket:", "🚀"},
};

const std::vector<CommitTypeCategory> &getCommitTypeCategories()
{
    static const std::vector<CommitTypeCategory> categories = {
        {"features", features},
        {"fixes", fixes},
        {"maintenance", maintenance},
        {"documentation", documentation},
        {"configuration", configuration},
        {"style", style},
        {"testing", testing},
        {"deployment", deployment},
        {"dependencies", dependencies},
    };
    return categories;
}

const std::vector<CommitType> &getCommitStatuses()
{
    static const std::vector<CommitType> statuses = {
        {"wip", ":construction:", "🚧"},
    };
    return statuses;
}