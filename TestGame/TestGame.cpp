#include "CardboardCore.h"

class TestGameApp : public Cardboard::App
{
public:
	TestGameApp() : Cardboard::App()
	{

	}
};

Cardboard::App* Cardboard::App::createApp()
{
	return new Cardboard::App();
}