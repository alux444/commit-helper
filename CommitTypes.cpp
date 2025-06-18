#include "CommitTypes.h"

const std::vector<CommitType> &getCommitTypes()
{
  static const std::vector<CommitType> types = {
      {"feat", ":sparkles:", "✨"},
      {"fix", ":hammer:", "🔨"},
      {"config", ":wrench:", "🔧"},
      {"docs", ":memo:", "📝"},
      {"style", ":art:", "🎨"},
      {"refactor", ":recycle:", "♻️"},
      {"test", ":test_tube:", "🧪"},
      {"removed", ":coffin:", "⚰️"},
      {"bug", ":bug:", "🐛"},
      {"hotfix", ":ambulance:", "🚑️"},
      {"infrastructure", ":bricks:", "🧱"},
      {"feature flags", ":triangular_flag_on_post:", "🚩"},
      {"types", ":label:", "🏷️"},
      {"remove logging", ":mute:", "🔇"},
      {"add logging", ":loud_sound:", "🔊"},
      {"move files", ":truck:", "🚚"},
      {"revert", ":rewind:", "⏪"},
      {"deploy", ":rocket:", "🚀"},
      {"add dependency", ":heavy_plus_sign:", "➕"},
      {"remove dependency", ":heavy_minus_sign:", "➖"},
      {"upgrade dependency", ":arrow_up:", "⬆️"},
      {"downgrade dependency", ":arrow_down:", "⬇️"},
      {"packages", ":package:", "📦"},
      {"deploy", ":rocket:", "🚀"},
      {"ci", ":green_heart:", "💚"},
      {"docker", ":whale:", "🐳"},
  };
  return types;
}

const std::vector<CommitType> &getCommitStatuses()
{
  static const std::vector<CommitType> statuses = {
      {"wip", ":construction:", "🚧"},
      {"completed", ":heavy_check_mark:", "✔️"},
  };
  return statuses;
}