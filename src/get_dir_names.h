#pragma once

#include <filesystem>
#include <stack>
#include <string>
#include <vector>

std::vector<std::filesystem::directory_entry>
    get_names(std::stack<std::string>);
