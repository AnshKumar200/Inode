#include "get_dir_names.h"

#include <filesystem>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

std::vector<std::filesystem::directory_entry>
get_names(std::stack<std::string> path_stack) {
    std::string path_str = "";
    while (!path_stack.empty()) {
        path_str = path_stack.top() + "/" + path_str;
        path_stack.pop();
    }
    const char *path_char = path_str.c_str();

    std::vector<std::filesystem::directory_entry> dir_list;
    for (const auto &entry : std::filesystem::directory_iterator(path_char)) {
        dir_list.push_back(entry);
    }
    return dir_list;
}
