#pragma once
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "Log.h"

namespace Sandstone {
	class JSON {
	public:
		static json Read (std::string file) {
			std::string fileExtension = file.substr(file.find_last_of(".") + 1);
			SS_CORE_ASSERT(fileExtension == "json", "File is not json");
			std::ifstream f(file);
			SS_CORE_ASSERT(f, "File doesn't exist");
			json data = json::parse(f);
			return data;
		}
	};
}