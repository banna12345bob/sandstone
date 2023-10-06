#pragma once
#include "consoleApplication/json.h"

namespace Sandstone {

	class version {
	public:
		version() {
			auto ver = JSON().Read("../sandstone/version.json");
			if (ver != false) {
				major = ver["version"]["major"];
				minor = ver["version"]["minor"];
				patch = ver["version"]["patch"];
			}
			else {
				SS_CORE_ASSERT(false, "version.json not found");
			}
		}
		bool checkVersion(std::string file) {
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
			SS_CORE_ASSERT(fileMajor == major, "Major version mismatch");
			if (fileMinor < minor || filePatch < patch) {
				SS_ERROR("{0}: {1}.{2}.{3}", file, fileMajor, fileMinor, filePatch);
				return false;
			} else if (fileMinor > minor || filePatch > patch) {
				SS_WARN("{0}: {1}.{2}.{3}", file, fileMajor, fileMinor, filePatch);
				return false;
			} else {
				SS_INFO("{0}: {1}.{2}.{3}", file, fileMajor, fileMinor, filePatch);
				return true;
			}
		}

		int major;
		int minor;
		int patch;
	};

}
