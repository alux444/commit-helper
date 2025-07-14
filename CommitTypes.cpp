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
    {"rename", ":pencil2", "✏️"},
    {"removed", ":coffin:", "⚰️"},
    {"revert", ":rewind:", "⏪"},
};

static const std::vector<CommitType> documentation = {
    {"docs", ":memo:", "📝"},
    {"comments", ":speech_balloon:", "💬"},
    {"changelog", ":ledger:", "📒"},
    {"spelling", ":pencil2:", "✏️"},
};

static const std::vector<CommitType> configuration = {
    {"config", ":wrench:", "🔧"},
    {"ci", ":green_heart:", "💚"},
    {"docker", ":whale:", "🐳"},
    {"infra", ":bricks:", "🧱"},
    {"analytics", ":bar_chart:", "📊"},
};

static const std::vector<CommitType> style = {
    {"style", ":art:", "🎨"},
    {"types", ":label:", "🏷️"},
    {"lint", ":shirt:", "👕"},
};

static const std::vector<CommitType> testing = {
    {"test", ":test_tube:", "🧪"},
    {"unit test", ":microscope:", "🔬"},
    {"integration test", ":dna:", "🧬"},
    {"mocks", ":clown_face", "🤡"},
};

const std::vector<CommitTypeCategory> &getCommitTypeCategories()
{
    static const std::vector<CommitTypeCategory> categories = {
        {"features", features},
        {"fixes", fixes},
        {"maintenance", maintenance},
        {"documentation", documentation},
        {"devops / infra / config", configuration},
        {"style", style},
        {"testing", testing},
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