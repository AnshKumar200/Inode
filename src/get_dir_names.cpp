#include "get_dir_names.h"

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

bool sort_files(std::filesystem::directory_entry a,
                  std::filesystem::directory_entry b) {
    if (a.is_directory() && b.is_directory()) {
        return a.path().filename() < b.path().filename();
    } else if (a.is_directory()) {
        return true;
    } else if (b.is_directory()) {
        return false;
    } else {
        return a.path().filename() < b.path().filename();
    }
};

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

    std::sort(dir_list.begin(), dir_list.end(), sort_files);
    return dir_list;
}
