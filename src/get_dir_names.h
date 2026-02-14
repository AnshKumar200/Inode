#pragma once

#include <filesystem>
#include <string>
#include <vector>

std::vector<std::filesystem::directory_entry> get_names(const std::string &path);
