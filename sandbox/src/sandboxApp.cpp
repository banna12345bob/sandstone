#include <sandstone.h>

class Sandbox : public Sandstone::Application
{
public:
	Sandbox()
	{
		Sandstone::run("sandboxRooms.json", "sandboxObjects.json");
	}
	~Sandbox()
	{

	}
};

Sandstone::Application* Sandstone::CreateApplication()
{
	return new Sandbox();
}