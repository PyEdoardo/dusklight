#include "translation.hpp"

#include <fstream>

namespace dusk::ui {

bool Translation::load(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return false;
    }

    try {
        file >> data;
    } catch (const nlohmann::json::exception&) {
        data = nlohmann::json::object();
        return false;
    }

    return data.is_object();
}

std::string Translation::get(const std::string& key) const {
    auto it = data.find(key);
    if (it != data.end() && it->is_string()) {
        return it->get<std::string>();
    }

    return key;
}

}
