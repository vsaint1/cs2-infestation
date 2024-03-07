#include "config_system.h"
bool ConfigSystem::create(const char *file_name) {

  if (!std::filesystem::exists(FOLDER))
    std::filesystem::create_directory(FOLDER);

  if (!std::filesystem::exists(FOLDER + std::string(file_name))) {
    std::ofstream file(FOLDER + std::string(file_name) + ".json");
    file << this->to_json();
    file.close();
    return true;
  }

  return false;
}

nlohmann::json ConfigSystem::to_json() {

  auto j = nlohmann::json::object();
  j["aimbot"] = {{"enabled", settings::aimbot::aimbot},
                 {"visible_check", settings::aimbot::visible_check},
                 {"fov", settings::aimbot::fov},
                 {"smooth", settings::aimbot::smooth},
                 {"hitbox", settings::aimbot::hitbox}

  };

  j["visuals"] = {
      {"player_esp", settings::visuals::player_esp},
      {"player_name", settings::visuals::player_name},
      {"player_distance", settings::visuals::player_distance},
      {"player_snaplines", settings::visuals::player_snaplines},
      {"player_skeleton", settings::visuals::player_skeleton},
      {"player_health", settings::visuals::player_health},

      {"chicken_esp", settings::world::chicken_esp},

      {"grenade_esp", settings::world::grenade_esp},
      {"greande_name", settings::world::grenade_name},
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
