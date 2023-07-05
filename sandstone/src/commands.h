#pragma once
#include "inventory.h"

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
		bool m_DebugOnly = false;
	};

	class look : public command {
	public:
		look(int area, int room, std::string roomFile, std::string objectFile, std::string saveFile, std::string player);
		virtual std::string run(std::string lCommand[]) override;
	};

	class save : public command {
	public:
		save(int area, int room, std::string roomFile, std::string objectFile, std::string saveFile, std::string player);
		virtual std::string run(std::string lCommand[]) override;
	};

	class inv : public command {
	public:
		inv(int area, int room, std::string roomFile, std::string objectFile, std::string saveFile, std::string player);
		virtual std::string run(std::string lCommand[]) override;
	};

	class use : public command {
	public:
		use(int area, int room, std::string roomFile, std::string objectFile, std::string saveFile, std::string player);
		virtual std::string run(std::string lCommand[]) override;
	};

	class open : public command {
	public:
		open(int area, int room, std::string roomFile, std::string objectFile, std::string saveFile, std::string player);
		virtual std::string run(std::string lCommand[]) override;
	};

	class give : public command {
	public:
		give(int area, int room, std::string roomFile, std::string objectFile, std::string saveFile, std::string player);
		virtual std::string run(std::string lCommand[]) override;
	};
}