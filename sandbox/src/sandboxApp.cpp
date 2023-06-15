#include <sandstone.h>

class Sandbox : public Sandstone::Application
{
public:
	Sandbox()
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