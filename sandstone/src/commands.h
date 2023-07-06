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
		std::string m_Description;
	};

	class look : public command {
	public:
		look(int area, int room, std::string roomFile, std::string objectFile, std::string saveFile, std::string player);
		virtual std::string run(std::string lCommand[]) override;
	};

	class save : public command {
	public:
		save(int area, int room, std::string roomFile, std::string objectFile, std::string saveFile, std::string player, std::string baseRoomFile);
		virtual std::string run(std::string lCommand[]) override;
	private:
		std::string m_BaseRoomFile;
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

	class dir : public command {
	public:
		dir(int area, int room, std::string roomFile, std::string objectFile, std::string saveFile, std::string player);
		virtual std::string run(std::string lCommand[]) override;
	};

	class pickup : public command {
	public:
		pickup(int area, int room, std::string roomFile, std::string objectFile, std::string saveFile, std::string player);
		virtual std::string run(std::string lCommand[]) override;
	};

	class drop : public command {
	public:
		drop(int area, int room, std::string roomFile, std::string objectFile, std::string saveFile, std::string player);
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