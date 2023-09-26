#include <sandstone.h>

// Little demo of application commands
class sand : public Sandstone::command {
public:
	sand() {
		command::m_DebugOnly = true;
	}
	virtual std::string run(std::string lCommand[]) override {
		return "I hate sand it's rough it's coarse and it gets everywhere";
	}
};

class Sandbox : public Sandstone::ConsoleApplication
{
public:
	Sandbox()
		: Sandstone::ConsoleApplication("sandboxRooms.json", "sandboxObjects.json")
	{
		this->m_Commands["sand"] = new sand();
	}
	~Sandbox()
	{

	}
};

Sandstone::Application* Sandstone::CreateApplication()
{
	return new Sandbox();
}
