#pragma once

#include "player.h"
#include "room.h"
#include "scriptingEngine.h"

namespace Sandstone {
	class command {
	public:
		command() = default;
		virtual std::string run(std::string lCommand[]) = 0;
		rooms* m_roomPtr;
		objects* m_objectsPtr;
		player* m_playerPtr;
        scriptingEngine* m_scripingEngine;
		bool m_DebugOnly = false;
		std::string m_Description;
	};

	class look : public command {
	public:
		look(rooms* roomPtr, objects* objectsPtr, player* playerPtr);
		virtual std::string run(std::string lCommand[]) override;
	};

	class save : public command {
	public:
		save(rooms* roomPtr, objects* objectsPtr, player* playerPtr, std::string baseRoomFile);
		virtual std::string run(std::string lCommand[]) override;
	private:
		std::string m_BaseRoomFile;
	};

	class inv : public command {
	public:
		inv(rooms* roomPtr, objects* objectsPtr, player* playerPtr);
		virtual std::string run(std::string lCommand[]) override;
	};

	class use : public command {
	public:
		use(rooms* roomPtr, objects* objectsPtr, player* playerPtr);
		virtual std::string run(std::string lCommand[]) override;
	};

	class dir : public command {
	public:
		dir(rooms* roomPtr, objects* objectsPtr, player* playerPtr);
		virtual std::string run(std::string lCommand[]) override;
	};

	class pickup : public command {
	public:
		pickup(rooms* roomPtr, objects* objectsPtr, player* playerPtr);
		virtual std::string run(std::string lCommand[]) override;
	};

	class drop : public command {
	public:
		drop(rooms* roomPtr, objects* objectsPtr, player* playerPtr);
		virtual std::string run(std::string lCommand[]) override;
	};

	class talk : public command {
	public:
		talk(rooms* roomPtr, objects* objectsPtr, player* playerPtr, scriptingEngine* scripingEngine);
		virtual std::string run(std::string lCommand[]) override;
	};

	// ----------- Debug Commands ----------- //

	class open : public command {
	public:
		open(rooms* roomPtr, objects* objectsPtr, player* playerPtr);
		virtual std::string run(std::string lCommand[]) override;
	};

	class give : public command {
	public:
		give(rooms* roomPtr, objects* objectsPtr, player* playerPtr);
		virtual std::string run(std::string lCommand[]) override;
	};

	class go_to : public command {
	public:
		go_to(rooms* roomPtr, objects* objectsPtr, player* playerPtr);
		virtual std::string run(std::string lCommand[]) override;
	};

	class log : public command {
	public:
		log(rooms* roomPtr, objects* objectsPtr, player* playerPtr);
		virtual std::string run(std::string lCommand[]) override;
	};
}
