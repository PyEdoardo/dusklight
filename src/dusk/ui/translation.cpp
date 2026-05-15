#include "translation.hpp"

#include <fstream>

namespace dusk::ui {

namespace {
bool load_json_file(const std::string& path, nlohmann::json& out) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return false;
    }

    try {
        file >> out;
    } catch (const nlohmann::json::exception&) {
        out = nlohmann::json::object();
        return false;
    }

    return out.is_object();
}
}

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

bool Translation::load(const std::string& path, const std::string& fallbackPath) {
    const bool fallbackLoaded = load_json_file(fallbackPath, fallbackData);
    const bool primaryLoaded = load_json_file(path, data);
    if (!primaryLoaded && fallbackLoaded) {
        data = fallbackData;
    }
    return primaryLoaded || fallbackLoaded;
}

std::string Translation::get(const std::string& key) const {
    auto it = data.find(key);
    if (it != data.end() && it->is_string()) {
        return it->get<std::string>();
    }
    auto fallback = fallbackData.find(key);
    if (fallback != fallbackData.end() && fallback->is_string()) {
        return fallback->get<std::string>();
    }

    return key;
}

}
