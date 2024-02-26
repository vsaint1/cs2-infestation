#include "entity_list.hpp"

EntityList *EntityList::get() { return memory.readv<EntityList *>(g_entity_list); }