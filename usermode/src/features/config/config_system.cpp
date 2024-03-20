#include "config_system.h"
bool ConfigSystem::create() {

  std::string file_name = this->generate_file_name(16);

  if (file_name.empty())
    return false;

  std::filesystem::path documents_path = std::filesystem::path(USERNAME) / "Documents";

  std::filesystem::path PATH = documents_path / "infestation-cfg/";

  if (!std::filesystem::exists(PATH))
    std::filesystem::create_directory(PATH);

  std::string file_json = PATH.string() + file_name;

  if (!std::filesystem::exists(file_json)) {
    std::ofstream file(file_json);
    file << this->to_json();
    file.close();
    return true;
  }

  return false;
}

std::vector<std::string> ConfigSystem::get_files() {

  std::filesystem::path PATH = std::filesystem::path(USERNAME) / "Documents" / "infestation-cfg/";

  if (!std::filesystem::exists(PATH))
    return std::vector<std::string>();

  std::vector<std::string> files;

  for (const auto &entry : std::filesystem::directory_iterator(PATH)) {
    files.push_back(entry.path().filename().string());
  }

  return files;
}

nlohmann::json ConfigSystem::to_json() {

  // 28
  auto j = nlohmann::json::object();
  j["aimbot"] = {{"enabled", settings::aimbot::aimbot},
                 {"visible_check", settings::aimbot::visible_check},
                 {"fov", settings::aimbot::fov},
                 {"smooth", settings::aimbot::smooth},
                 {"hitbox", settings::aimbot::selectedhitbox}

  };

  j["visuals"] = {
      {"player_esp", settings::visuals::player_esp},
      {"player_name", settings::visuals::player_name},
      {"player_distance", settings::visuals::player_distance},
      {"player_snaplines", settings::visuals::player_snaplines},
      {"player_skeleton", settings::visuals::player_skeleton},
      {"player_health", settings::visuals::player_health},
      {"player_box", settings::visuals::player_box},

      {"world", settings::world::esp},

      {"chicken_esp", settings::world::chicken_esp},

      {"grenade_esp", settings::world::grenade_esp},
      {"grenade_name", settings::world::grenade_name},
      {"grenade_warning", settings::world::grenade_warning},
      {"grenade_distance", settings::world::grenade_distance},
      {"grenade_trajectory", settings::world::grenade_trajectory},
      {"grenade_inferno", settings::world::grenade_inferno_esp},
      {"grenade_warning", settings::world::grenade_warning},

      {"weapon_esp", settings::world::weapon_esp},
      {"weapon_name", settings::world::weapon_name},
      {"weapon_distance", settings::world::weapon_distance},
      {"weapon_icon", settings::world::weapon_icon},

  };

  j["misc"] = {
      {"experimental_features", settings::misc::experimental_features},
      {"bomb_timer", settings::misc::bomb_timer},
      {"team_check", settings::misc::team_check},
      {"performance_metrics", settings::misc::performance},

  };

  return j;
}

std::string ConfigSystem::generate_file_name(int len) {

  std::random_device rd;
  std::mt19937 generator(rd());

  const std::string allowed_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789._-";

  std::string filename;
  std::uniform_int_distribution<int> distribution(0, allowed_chars.size() - 1);
  for (int i = 0; i < len; ++i) {
    filename += allowed_chars[distribution(generator)];
  }

  filename += ".json";

  return filename;
}

void ConfigSystem::load(const std::string file_name) {
  std::filesystem::path PATH = std::filesystem::path(USERNAME) / "Documents" / "infestation-cfg" / file_name;

  std::string file_path = PATH.string();

  std::ifstream file(file_path);
  auto j = nlohmann::json::parse(file);

  settings::aimbot::aimbot = j["aimbot"]["enabled"];
  settings::aimbot::visible_check = j["aimbot"]["visible_check"];
  settings::aimbot::fov = j["aimbot"]["fov"];
  settings::aimbot::smooth = j["aimbot"]["smooth"];
  settings::aimbot::selectedhitbox = j["aimbot"]["hitbox"];

  settings::visuals::player_esp = j["visuals"]["player_esp"];
  settings::visuals::player_health = j["visuals"]["player_health"];
  settings::visuals::player_name = j["visuals"]["player_name"];
  settings::visuals::player_distance = j["visuals"]["player_distance"];
  settings::visuals::player_snaplines = j["visuals"]["player_snaplines"];
  settings::visuals::player_skeleton = j["visuals"]["player_skeleton"];
  settings::visuals::player_box = j["visuals"]["player_box"];

  settings::world::esp = j["visuals"]["world"];
  settings::world::chicken_esp = j["visuals"]["chicken_esp"];

  settings::world::grenade_esp = j["visuals"]["grenade_esp"];
  settings::world::grenade_name = j["visuals"]["grenade_name"];
  settings::world::grenade_warning = j["visuals"]["grenade_warning"];
  settings::world::grenade_distance = j["visuals"]["grenade_distance"];
  settings::world::grenade_trajectory = j["visuals"]["grenade_trajectory"];
  settings::world::grenade_inferno_esp = j["visuals"]["grenade_inferno"];

  settings::world::weapon_esp = j["visuals"]["weapon_esp"];
  settings::world::weapon_name = j["visuals"]["weapon_name"];
  settings::world::weapon_distance = j["visuals"]["weapon_distance"];
  settings::world::weapon_icon = j["visuals"]["weapon_icon"];

  settings::misc::experimental_features = j["misc"]["experimental_features"];
  settings::misc::performance = j["misc"]["performance_metrics"];
  settings::misc::bomb_timer = j["misc"]["bomb_timer"];
  settings::misc::team_check = j["misc"]["team_check"];

  file.close();
}

void ConfigSystem::override(const std::string file_name) {
  std::filesystem::path PATH = std::filesystem::path(USERNAME) / "Documents" / "infestation-cfg" / file_name;

  std::string file_path = PATH.string();

  std::ofstream file(file_path);

  file.clear();
  file << this->to_json();
  file.close();
}

void ConfigSystem::remove(const std::string file_name) {
  std::filesystem::path PATH = std::filesystem::path(USERNAME) / "Documents" / "infestation-cfg" / file_name;

  if (std::filesystem::exists(PATH))
    std::filesystem::remove(PATH);
    
}
