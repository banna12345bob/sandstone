#pragma once
#include "interpreter.h"

namespace Sandstone {
	class command {
	public:
		command() = default;
		virtual std::string run(std::string lCommand[]) = 0;
		int m_Area;
		int m_Room;
		std::string m_roomFile;
		std::string m_objectFile;
		std::string m_saveFile;
		std::string m_player;
	};

	class look : public command {
	public:
		look(int area, int room, std::string roomFile, std::string objectFile, std::string saveFile, std::string player);
		virtual std::string run(std::string lCommand[]) override;
	};
}