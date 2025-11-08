#include "CardboardCore.h"


class TestGameApp : public Cardboard::App
{
public:
	TestGameApp() : Cardboard::App(),
		spriteRenderer(),
		texture( "../CardboardCore/DiamondPlate009_1K-PNG_Color.bmp", "diffuse", logger ),
		sprite(
			{ 0, 0 },
			{ 1, 1 },
			& texture
		)
	{
		GL::clearColor( 0.5f, 0.3f, 0.4f, 1.0f );
	}

	void customOnDrawStuff() override
	{
		spriteRenderer.drawSprite ( sprite );
	}

	Cardboard::SpriteRenderer spriteRenderer;
	Cardboard::Texture texture;
	Cardboard::Sprite sprite;
};

Cardboard::App* Cardboard::App::createApp()
{
	return new TestGameApp();
}