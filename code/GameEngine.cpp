#include "GameEngine.h"

GameEngine::GameEngine()
{
	screenResolution.x = VideoMode::getDesktopMode().width;
	screenResolution.y = VideoMode::getDesktopMode().height;

	window.create(VideoMode(screenResolution.x, screenResolution.y),
		"Space Shooter", Style::Default);

	 mainView.reset(FloatRect(0, 0, screenResolution.x, screenResolution.y));
	 hudView.reset(FloatRect(0, 0, screenResolution.x, screenResolution.y));

	 font.loadFromFile("fonts/Audiowide-Regular.ttf");
	 hud.setFont(font);
	 hud.setCharacterSize(75);
	 hud.setFillColor(Color::White);
	 hud.setPosition(20, 20);

    CreateBackground();

	player.Create(Vector2f(screenResolution.x / 2, screenResolution.y - 100));

    SpawnEnemies();
}

void GameEngine::SpawnEnemies()
{
    for (int i = 0; i < enemiesCount; i++)
    {
        EnemyAIController* enemy = new EnemyAIController();
        enemy->Create(Vector2f(250, 250));
        enemies.push_back(enemy);
    }

    //Design the level.
    int sqrtOfEnemiesCount = sqrt(enemiesCount);
    Vector2f spawningStartPoint(screenResolution.x * 0.3, (-200 * sqrtOfEnemiesCount));
    int gapSize = 200;
    int x = 0;

    for (int r = 0; r < sqrtOfEnemiesCount; r++)
    {
        for (int c = 0; c < sqrtOfEnemiesCount; c++)
        {
            enemies[x]->SetPosition(Vector2f(spawningStartPoint.x + (r * gapSize), spawningStartPoint.y + (c * gapSize)));
            x++;
        }
    }
}

void GameEngine::UpdateEnemiesAIBehaviour()
{
    aliveEnemies.clear();
    for (int i = 0; i < enemies.size(); i++)
    {
        if (enemies[i]->IsEnabled())
        {
            aliveEnemies.push_back(enemies[i]);
        }
    }

    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i]->Move();
        enemies[i]->SetMovingSpeed(speed);
        enemies[i]->UpdateController(dt, screenResolution);
        enemies[i]->UpdateSurrondings(&player, &aliveEnemies);
        enemies[i]->CheckIfShouldFire(dt);
    }
}

void GameEngine::GetAllObjectsAndCheckForCollisions()
{
    allControllers.clear();
    allProjectiles.clear();

    allControllers.push_back(&player);
    allControllers.insert(allControllers.end(), aliveEnemies.begin(), aliveEnemies.end());

    allProjectiles = player.GetProjectiles();

    for (int i = 0; i < aliveEnemies.size(); i++)
    {
        for (Projectile* projectile : aliveEnemies[i]->GetProjectiles())
        {
            allProjectiles.push_back(projectile);
        }
    }

    collisionDetection.CheckForCollisions(allProjectiles, allControllers);
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
        dt = clock.restart();
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

        GetAllObjectsAndCheckForCollisions();

        player.Move();
        player.CheckIfShouldChangeWeapon();
        player.CheckIfShouldFire(dt);
        player.UpdateController(dt, screenResolution);

        UpdateEnemiesAIBehaviour();

        UpdateBackground(player.GetMovingDirection().y);

        sp.PlayAnimation(dt);

        Draw();
    }
}

void GameEngine::Draw()
{
    window.clear();

    window.setView(mainView);

    window.draw(Sprite(finalBackgroundRenderTexture.getTexture()));

    window.draw(player.GetSprite());

    for (Sprite& projectileSprite : player.GetProjectileSprites())
    {
        window.draw(projectileSprite);
    }

    for (int i = 0; i < aliveEnemies.size(); i++)
    {
        window.draw(aliveEnemies[i]->GetSprite());

        for (Sprite& projectileSprite : enemies[i]->GetProjectileSprites())
        {
            window.draw(projectileSprite);
        }
    }

    //window.draw(sp.GetSprite());

    window.setView(hudView);
    window.draw(hud);

    window.display();
}
