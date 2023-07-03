#include <sandstone.h>

class Sandbox : public Sandstone::Application
{
public:
	Sandbox()
		: Sandstone::Application("sandboxRooms.json", "sandboxObjects.json")
	{

	}
	~Sandbox()
	{

	}
};

Sandstone::Application* Sandstone::CreateApplication()
{
	return new Sandbox();
}