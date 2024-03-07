/*
 *   Copyright (c) 2024 vsantos1
 *   All rights reserved.
 */
#ifndef FEATURES_CONFIG_CONFIG_SYSTEM_H_
#define FEATURES_CONFIG_CONFIG_SYSTEM_H_


#include "../globals.h"
#include <fstream>
#include <nlohmann/json.hpp>

#define FOLDER "C:/Documents/infestation-cfg/"

class ConfigSystem {

public:

bool create(const char* file_name);

private:

nlohmann::json to_json();

};

#endif // FEATURES_CONFIG_CONFIG_SYSTEM_H_
