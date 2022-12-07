#include "GameEngine.h"

GameEngine::GameEngine()
{
	screenResolution.x = VideoMode::getDesktopMode().width;
	screenResolution.y = VideoMode::getDesktopMode().height;

	window.create(VideoMode(screenResolution.x, screenResolution.y),
		"Space Shooter", Style::Default);

	 mainView.reset(FloatRect(0, 0, screenResolution.x, screenResolution.y));
	 UI_View.reset(FloatRect(0, 0, screenResolution.x, screenResolution.y));

     LoadUI();

    CreateBackground();

	player.Create(Vector2f(screenResolution.x / 2, screenResolution.y - 100));

    SpawnEnemies();

    InstantiateExplosionVFXsObjects();

    initialPlayerHealthAmount = player.GetHealthAmount();

    explosionSFXBuffer.loadFromFile("sound/explosion.wav");
    explosionSFX.setBuffer(explosionSFXBuffer);
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
    Vector2f spawningStartPoint(screenResolution.x * 0.2, (-200 * sqrtOfEnemiesCount));
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
        if (enemies[i]->IsAlive())
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

void GameEngine::InstantiateExplosionVFXsObjects()
{
    explosionTexture.loadFromFile("graphics/explosion_sp.png");
    for (int i = 0; i < explosionVFXsPoolCount; i++)
    {
        Spritesheet* sp = new Spritesheet;
        sp->Create(explosionTexture, 4, 5);
        sp->SetScale(Vector2f(2, 2));
        sp->SetAnimationRate(0.05);
        sp->SetIsLooping(false);
        sp->SetIsPlaying(false);

        explosionVFXs.push_back(sp);
    }
}

void GameEngine::PlayExplosions()
{
    for (int i = 0; i < allControllers.size(); i++)
    {
        if (allControllers[i]->ShouldDestroy())
        {
            explosionSFX.play();
            score += 75;

            explosionVFXs[availableExplosionVFXsIndex]->SetPosition(allControllers[i]->GetExplosionPosition());
            explosionVFXs[availableExplosionVFXsIndex]->SetIsPlaying(true);

            availableExplosionVFXsIndex++;
        }
    }

    if (availableExplosionVFXsIndex >= explosionVFXsPoolCount)
    {
        availableExplosionVFXsIndex = 0;
    }

    for (int i = 0; i < availableExplosionVFXsIndex; i++)
    {
        explosionVFXs[i]->PlayAnimation(dt);
    }
}

void GameEngine::LoadUI()
{
    font.loadFromFile("fonts/Audiowide-Regular.ttf");

    titleText.setFont(font);
    titleText.setCharacterSize(200);
    titleText.setFillColor(Color::Red);
    titleText.setPosition(screenResolution.x / 2, 300);
    titleText.setString("Space Shooter");

    startGameText.setFont(font);
    startGameText.setCharacterSize(75);
    startGameText.setFillColor(Color::White);
    startGameText.setPosition(screenResolution.x / 2, screenResolution.y / 2);
    startGameText.setString("Press Enter to Start");

    hudText.setFont(font);
    hudText.setCharacterSize(50);
    hudText.setFillColor(Color::White);
    hudText.setPosition(20, 20);

    instructionsText.setFont(font);
    instructionsText.setCharacterSize(50);
    instructionsText.setFillColor(Color::White);
    instructionsText.setPosition(screenResolution.x / 2, screenResolution.y - 300);

    stringstream ss;
    ss << "How to play:" << endl << "1. Press arrow keys to move around" << endl << "2. Press spacebar key to shoot" << endl
        << "3. Press 1 or 2 to change weapon" << endl;
    instructionsText.setString(ss.str());

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(150);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setPosition(screenResolution.x / 2, screenResolution.y / 2);
    gameOverText.setString("Game Over");

    levelCompletedText.setFont(font);
    levelCompletedText.setCharacterSize(150);
    levelCompletedText.setFillColor(Color::Green);
    levelCompletedText.setPosition(screenResolution.x / 2, screenResolution.y / 2);
    levelCompletedText.setString("Level Completed");

    allTexts.push_back(&titleText);
    allTexts.push_back(&startGameText);
    allTexts.push_back(&instructionsText);
    allTexts.push_back(&gameOverText);
    allTexts.push_back(&levelCompletedText);

    CenterTheOriginForTexts();
}

void GameEngine::CenterTheOriginForTexts()
{
    for (Text* txt : allTexts)
    {
        FloatRect textRect = txt->getLocalBounds();
        txt->setOrigin(textRect.left +
            textRect.width / 2.0f,
            textRect.top +
            textRect.height / 2.0f);
    }
}

void GameEngine::UpdateHud()
{
    stringstream stringStream;

    stringStream << "Score:" << score
        << setw(30) << "Health: " << (player.GetHealthAmount() / (float)initialPlayerHealthAmount) * 100.0 << "%";

    hudText.setString(stringStream.str());
}

void GameEngine::DrawUI()
{
    if (!isGameStarted && !isGameOver)
    {
        window.draw(titleText);
        window.draw(startGameText);
        window.draw(instructionsText);
    }

    if (isGameStarted && !isGameOver && !isLevelCompleted)
    {
        window.draw(hudText);
    }

    if (isGameStarted && isGameOver && !isLevelCompleted)
    {
        window.draw(gameOverText);
    }

    if (isGameStarted && isLevelCompleted && !isGameOver)
    {
        window.draw(levelCompletedText);
    }
}

void GameEngine::CheckIfLevelIsCompleted()
{
    if (aliveEnemies.size() == 0)
    {
        isLevelCompleted = true;
    }
}

void GameEngine::Run()
{
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
        if (Keyboard::isKeyPressed(Keyboard::Enter))
        {
            isGameStarted = true;
        }

        UpdateBackground(player.GetMovingDirection().y);
        
        if (isGameStarted && !isGameOver && !isLevelCompleted)
        {
            GetAllObjectsAndCheckForCollisions();

            player.Move();
            player.CheckIfShouldChangeWeapon();
            player.CheckIfShouldFire(dt);
            player.UpdateController(dt, screenResolution);

            UpdateEnemiesAIBehaviour();

            PlayExplosions();

            UpdateHud();

            CheckIfLevelIsCompleted();

            if (!player.IsAlive())
            {
                isGameOver = true;
            }
        }

        Draw();
    }
}

void GameEngine::Draw()
{
    window.clear();

    window.setView(mainView);

    window.draw(Sprite(finalBackgroundRenderTexture.getTexture()));

    if (isGameStarted && !isGameOver && !isLevelCompleted)
    {
        if (player.IsAlive())
        {
            window.draw(player.GetSprite());
        }
        for (Sprite& projectileSprite : player.GetProjectileSprites())
        {
            window.draw(projectileSprite);
        }
        for (int i = 0; i < aliveEnemies.size(); i++)
        {
            window.draw(aliveEnemies[i]->GetSprite());

            for (Sprite& projectileSprite : aliveEnemies[i]->GetProjectileSprites())
            {
                window.draw(projectileSprite);
            }
        }
        for (Spritesheet* explosionSS : explosionVFXs)
        {
            if (explosionSS->IsStillPlaying())
                window.draw(explosionSS->GetSprite());
        }
    }

    window.setView(UI_View);
    
    DrawUI();

    window.display();
}
