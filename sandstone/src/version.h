#pragma once
#include "consoleApplication/json.h"

namespace Sandstone {

	bool checkForVersionFile() {
		auto ver = JSON().Read("../sandstone/version.json");
		if (ver != false) {
			return true;
		}
		else {
			SS_CORE_ASSERT(false, "version.json not found");
		}
		return false;
	}

	int getMajorVersion() {
		if (checkForVersionFile()) {
			auto ver = JSON().Read("../sandstone/version.json");
			if (ver != false) {
				return ver["version"]["major"];
			}
		}
		return false;
	}

	int getMinorVersion() {
		if (checkForVersionFile()) {
			auto ver = JSON().Read("../sandstone/version.json");
			if (ver != false) {
				return ver["version"]["minor"];
			}
		}
		return false;
	}

	int getPatchVersion() {
		if (checkForVersionFile()) {
			auto ver = JSON().Read("../sandstone/version.json");
			if (ver != false) {
				return ver["version"]["patch"];
			}
		}
		return false;
	}

	bool checkVersionForFile(std::string file) {
		int fileMajor = 0;
		int fileMinor = 0;
		int filePatch = 0;
		auto readFile = JSON().Read(file);
		if (readFile != false) {
			fileMajor = readFile["version"]["major"];
			fileMinor = readFile["version"]["minor"];
			filePatch = readFile["version"]["patch"];
		} else {
			SS_CORE_ASSERT(false, "file not found");
		}
		SS_CORE_ASSERT(fileMajor == Sandstone::getMajorVersion(), "Major version mismatch");
		if (fileMinor < getMinorVersion() || filePatch < getPatchVersion()) {
			SS_ERROR("{0}: {1}.{2}.{3}", file, fileMajor, fileMinor, filePatch);
			return false;
		} else if (fileMinor > getMinorVersion() || filePatch > getPatchVersion()) {
			SS_WARN("{0}: {1}.{2}.{3}", file, fileMajor, fileMinor, filePatch);
			return false;
		} else {
			SS_INFO("{0}: {1}.{2}.{3}", file, fileMajor, fileMinor, filePatch);
			return true;
		}
	}
}
