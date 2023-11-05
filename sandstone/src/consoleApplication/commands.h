#pragma once
#include "inventory.h"

namespace Sandstone {
	class command {
	public:
		command() = default;
		virtual std::string run(std::string lCommand[]) = 0;
		room* m_roomPtr;
		objects* m_objectsPtr;
		inventory* m_invPtr;
		bool m_DebugOnly = false;
		std::string m_Description;
	};

	class look : public command {
	public:
		look(room* roomPtr, objects* objectsPtr, inventory* invPtr);
		virtual std::string run(std::string lCommand[]) override;
	};

	class save : public command {
	public:
		save(room* roomPtr, objects* objectsPtr, inventory* invPtr, std::string baseRoomFile);
		virtual std::string run(std::string lCommand[]) override;
	private:
		std::string m_BaseRoomFile;
	};

	class inv : public command {
	public:
		inv(room* roomPtr, objects* objectsPtr, inventory* invPtr);
		virtual std::string run(std::string lCommand[]) override;
	};

	class use : public command {
	public:
		use(room* roomPtr, objects* objectsPtr, inventory* invPtr);
		virtual std::string run(std::string lCommand[]) override;
	};

	class dir : public command {
	public:
		dir(room* roomPtr, objects* objectsPtr, inventory* invPtr);
		virtual std::string run(std::string lCommand[]) override;
	};

	class pickup : public command {
	public:
		pickup(room* roomPtr, objects* objectsPtr, inventory* invPtr);
		virtual std::string run(std::string lCommand[]) override;
	};

	class drop : public command {
	public:
		drop(room* roomPtr, objects* objectsPtr, inventory* invPtr);
		virtual std::string run(std::string lCommand[]) override;
	};

	class talk : public command {
	public:
		talk(room* roomPtr, objects* objectsPtr, inventory* invPtr);
		virtual std::string run(std::string lCommand[]) override;
	};

	// ----------- Debug Commands ----------- //

	class open : public command {
	public:
		open(room* roomPtr, objects* objectsPtr, inventory* invPtr);
		virtual std::string run(std::string lCommand[]) override;
	};

	class give : public command {
	public:
		give(room* roomPtr, objects* objectsPtr, inventory* invPtr);
		virtual std::string run(std::string lCommand[]) override;
	};

	class go_to : public command {
	public:
		go_to(room* roomPtr, objects* objectsPtr, inventory* invPtr);
		virtual std::string run(std::string lCommand[]) override;
	};

	class log : public command {
	public:
		log(room* roomPtr, objects* objectsPtr, inventory* invPtr);
		virtual std::string run(std::string lCommand[]) override;
	};
}