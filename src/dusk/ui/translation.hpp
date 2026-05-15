#pragma once

#include <nlohmann/json.hpp>

#include <string>

namespace dusk::ui {
class Translation {
public:
	Translation() = default;
	~Translation() = default;

	bool load(const std::string& path);
	std::string get(const std::string& key) const;

private:
	nlohmann::json data;
};
}
