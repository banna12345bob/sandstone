#include <sandstone.h>

class Demo1 : public Sandstone::GameApplication
{
public:
	Demo1()
		: Sandstone::GameApplication("demo1Rooms.json", "demo1Objects.json")
	{
		
	}
	~Demo1()
	{

	}
};

Sandstone::Application* Sandstone::CreateApplication()
{
	return new Demo1();
}
