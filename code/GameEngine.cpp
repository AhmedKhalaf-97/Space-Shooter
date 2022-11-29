#include "GameEngine.h"

GameEngine::GameEngine()
{
	screenResolution.x = VideoMode::getDesktopMode().width;
	screenResolution.y = VideoMode::getDesktopMode().height;

	window.create(VideoMode(screenResolution.x, screenResolution.y),
		"Space Shooter", Style::Fullscreen);

	 mainView.reset(FloatRect(0, 0, screenResolution.x, screenResolution.y));
	 hudView.reset(FloatRect(0, 0, screenResolution.x, screenResolution.y));

	 font.loadFromFile("fonts/Audiowide-Regular.ttf");
	 hud.setFont(font);
	 hud.setCharacterSize(75);
	 hud.setFillColor(Color::White);
	 hud.setPosition(20, 20);

    CreateBackground();

	player.Create(Vector2f(screenResolution.x / 2, screenResolution.y / 2));
}

void GameEngine::Run()
{
    Texture explosionTexture;
    explosionTexture.loadFromFile("graphics/explosion_sp.png");
    Spritesheet sp;
    sp.Create(explosionTexture, 4, 5);
    sp.SetPosition(Vector2f(500, 500));
    sp.SetScale(Vector2f(2,2));
    sp.SetAnimationRate(0.05);
    sp.SetIsLooping(true);

    while (window.isOpen())
    {
        Event event;
        Time dt = clock.restart();
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        stringstream ss;
        ss << "Score:" << 100 << " Lives:" << 3;
        hud.setString(ss.str());

        player.Move();
        player.UpdatePosition(dt, screenResolution);

        UpdateBackground(dt, player.GetMovingDirection().y);

        sp.PlayAnimation(dt);

        window.clear();

        window.setView(mainView);

        for (Sprite& backgroundSprite : backgroundSprites)
        {
            window.draw(backgroundSprite);
        }

        window.draw(player.GetSprite());

        window.draw(sp.GetSprite());

        window.setView(hudView);
        window.draw(hud);

        window.display();
    }
}