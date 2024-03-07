/*
 *   Copyright (c) 2024 vsantos1
 *   All rights reserved.
 */
#ifndef FEATURES_CONFIG_CONFIG_SYSTEM_H_
#define FEATURES_CONFIG_CONFIG_SYSTEM_H_


#include "../globals.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <random>
#include <string>

#if _WIN32
#define USERNAME getenv("USERPROFILE")
#else
#define USERNAME getenv("HOME")
#endif

class ConfigSystem {

public:

bool create();

std::vector<std::string> get_files();

void load(const std::string file_name);

private:

nlohmann::json to_json();


std::string generate_file_name(int len);

};

#endif // FEATURES_CONFIG_CONFIG_SYSTEM_H_
