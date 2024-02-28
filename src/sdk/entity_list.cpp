#include "entity_list.hpp"

EntityList *EntityList::get() { return memory.readv<EntityList *>(g_entity_list); }

void EntityList::update() {

  entities.clear();

  // 1 == C_World
  for (auto i = 1; i < this->max_entities(); i++) {
    const auto entity = this->get<uintptr_t>(i);

    if (!entity)
      continue;

    const auto schema_name = this->get_schema_name(entity);

#if _DEBUG
    SPDLOG_INFO(fmt::format("CLASS_NAME {}, INDEX {}", schema_name, i));
#endif

    if (schema_name == "CCSPlayerController") {
      entities.emplace_back(BaseEntity(entity, i, EntityType::PLAYER));
    } else if (schema_name == "C_HEGrenadeProjectile" || schema_name == "C_FlashbangProjectile" || schema_name == "C_SmokeGrenadeProjectile" || schema_name == "C_DecoyProjectile" ||
               schema_name == "C_MolotovProjectile") {
      entities.emplace_back(BaseEntity(entity, i, EntityType::GRENADE));
    } else if (schema_name == "C_Inferno") {
      entities.emplace_back(BaseEntity(entity, i, EntityType::INFERNO));
    } else if (schema_name == "C_PlantedC4") {
      entities.emplace_back(BaseEntity(entity, i, EntityType::C4));
    } else if (schema_name == "C_Chicken") {
      entities.emplace_back(BaseEntity(entity, i, EntityType::CHICKEN));
    } else if (schema_name == "C_Fish") {
      entities.emplace_back(BaseEntity(entity, i, EntityType::FISH));
    } else if (schema_name.find("C_Weapon") != std::string::npos) {
      entities.emplace_back(BaseEntity(entity, i, EntityType::WEAPON));
    } else
      continue;
  }
}

const std::string EntityList::get_schema_name(const uintptr_t &entity) {

  uintptr_t entity_identity = memory.readv<uintptr_t>(entity + offsets::CEntityInstance::m_pEntity);

  if (!entity_identity)
    return "";

  uintptr_t entity_class_info = memory.readv<uintptr_t>(entity_identity + 0x8);
  uintptr_t schema_class_info_data = memory.readv<uintptr_t>(entity_class_info + 0x28);
  uintptr_t class_name = memory.readv<uintptr_t>(schema_class_info_data + 0x8);

  std::string name = memory.read_str(class_name);

  if (name.empty())
    return "";

  return name;
}
