#include "entity_list.hpp"

EntityList *EntityList::get() { return memory.readv<EntityList *>(g_entity_list); }

void EntityList::update() {

    entities.clear();

    // 1 == C_World
    for (auto i = 1; i <= this->max_entities(); i++) {
        const auto entity = this->get<uintptr_t>(i);

        if (!entity)
            continue;

        const auto schema_name = this->get_schema_name(entity);

        if (schema_name.empty())
            continue;

#if _DEBUG
       SPDLOG_INFO(fmt::format("CLASS_NAME {}, INDEX {}", schema_name, i));
#endif

        switch (hash_const_enhanced(schema_name.c_str())) {
            case hash_const("CCSPlayerController"):
                entities.emplace_back(BaseEntity(entity, i, EntityType::PLAYER));
                break;
            case hash_const("C_HEGrenadeProjectile"):
            case hash_const("C_FlashbangProjectile"):
            case hash_const("C_SmokeGrenadeProjectile"):
            case hash_const("C_DecoyProjectile"):
            case hash_const("C_MolotovProjectile"):
                entities.emplace_back(BaseEntity(entity, i, EntityType::GRENADE));
                break;

            case hash_const("C_Inferno"):
                entities.emplace_back(BaseEntity(entity, i, EntityType::INFERNO));
                break;

            case hash_const("C_PlantedC4"):
                entities.emplace_back(BaseEntity(entity, i, EntityType::C4));
                break;

            case hash_const("C_Chicken"):
                entities.emplace_back(BaseEntity(entity, i, EntityType::CHICKEN));
                break;

            case hash_const("C_Fish"):
                entities.emplace_back(BaseEntity(entity, i, EntityType::FISH));
                break;

            case 0x1234ABCD: // TODO: comparing C_Weapons
                entities.emplace_back(BaseEntity(entity, i, EntityType::WEAPON));
                break;

            default:
                entities.emplace_back(BaseEntity(entity, i, EntityType::INVALID));
                break;
        }

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
