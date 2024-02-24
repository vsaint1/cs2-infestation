#include "entity_list.hpp"

EntityList *EntityList::get() { return memory.readv<EntityList *>(entity_list); }