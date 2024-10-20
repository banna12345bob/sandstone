#pragma once
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <fstream>
#include <iostream>

#include "Log.h"

namespace Sandstone {

	class JSON {
	public:
		static json Read (std::string file) {
			std::string fileExtension = file.substr(file.find_last_of(".") + 1);
			SS_CORE_ASSERT(fileExtension == "json", "File is not json");
			std::ifstream f(file);
			if (!(f)) {
				return false;
			}
			json data = json::parse(f);
			return data;
		}

		static bool Write(std::string file, json data) {
			std::string fileDir = file.substr(0, file.find_last_of("/"));
			if (!std::filesystem::is_directory(fileDir) || !std::filesystem::exists(fileDir)) {
				std::filesystem::create_directory(fileDir);
			}
			std::string dataStr = data.dump();
			std::ofstream out(file);
			out << dataStr;
			out.close();
			return true;
		}
	};

	class debugger {
	public:
        debugger() { 
            if (JSON().Read("../data/options.json") != false) 
            {
                m_Enable = JSON().Read("../data/options.json")["debuggerEnabled"];
                if (m_Enable)
                    ignoreLocks = JSON().Read("../data/options.json")["ignoreLocks"];
            }
        }
		bool m_Enable = false;
		bool ignoreLocks = false;
	};

}
