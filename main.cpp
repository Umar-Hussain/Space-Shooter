#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
#include"Player.h"
#include"GameScreen.h"
#include"FighterJet.h"
#include"Asteroids.h"
#include"Menu.h"
#include"Enemy.h"
#include"gameOver.h"

int main() {
Label1:
    RenderWindow window(sf::VideoMode(1200, 900), "SpaceShooter Game");
    int score = 0;
    string current = "Menu";
    Fighter P1;
    Font scoreFont;
    Font healthFont;
    healthFont.loadFromFile("assets/scoreFont.ttf");
    Text healthText;
    healthText.setFont(healthFont);
    healthText.setCharacterSize(24);
    healthText.setFillColor(Color::White);
    healthText.setPosition(1000, 10);
    scoreFont.loadFromFile("assets/scoreFont.ttf");
    Text scoreText;
    scoreText.setFont(scoreFont);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(10, 10);
    Enemy E1;
    bool enemyAppeared = false;
    gameScreen G;
    Menu m;
    gameOver g;
    vector<Enemy> enemies;
    vector<Asteroid> asteroids;
    std::srand(static_cast<unsigned>(time(0)));
    Clock clock;
    float spawnTimer = 0;
    float enemySpawnInterval = 5.0f;
    bool enemySpawningStarted = false;
    float littleEnemiesSpawnTimer = 0;
    float littleEnemySpawnInterval = 30.0f;
    bool littleEnemySpawnStarted = false;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        if (current == "Menu")
        {
            m.drawMenu(window);
            if (Keyboard::isKeyPressed(Keyboard::S))
                current = "Game";
        }

        else if (current == "gameOver")
        {


            g.drawgameover(window);
            if (Keyboard::isKeyPressed(Keyboard::R))
                goto Label1;


        }
        else   if (current == "Game") {
            if (Keyboard::isKeyPressed) {
                P1.handleMovements();
                P1.updateBullets();
            }
            if (P1.getHealth() <= 0) {
                current = "gameOver";


            }
            float deltaTime = clock.restart().asSeconds();
            spawnTimer += deltaTime;

            littleEnemiesSpawnTimer += deltaTime;
            if (littleEnemiesSpawnTimer >= littleEnemySpawnInterval) {
                float randomX = static_cast<float>(std::rand() % 1200);  // Random X position
                enemies.push_back(Enemy(randomX, 0));  // Spawn little enemies
                littleEnemiesSpawnTimer = 0;
            }
            if (spawnTimer >= 4.0f) {
                float randomX = static_cast<float>(std::rand() % globalBoundsX);
                asteroids.push_back(Asteroid(randomX, 0));
                spawnTimer = 0;
            }
            if (score >= 50 && !enemyAppeared) {
                enemyAppeared = true;
            }
            if (score >= 100 && !littleEnemySpawnStarted) {
                littleEnemySpawnStarted = true;
                spawnTimer = 0;
            }

            // Add the spawning of little enemies separately
            littleEnemiesSpawnTimer += deltaTime;
            if (littleEnemiesSpawnTimer >= littleEnemySpawnInterval&&littleEnemySpawnStarted) {
                float randomX = static_cast<float>(std::rand() % 1200);
                enemies.push_back(Enemy(randomX, 0));  // Adjust attributes for little enemies
                littleEnemiesSpawnTimer = 0;
            }


            // Update enemies
            for (size_t i = 0; i < enemies.size(); ++i) {
                enemies[i].move(deltaTime);
                enemies[i].shoot(deltaTime);
               
                // Check for bullet collisions
                Bullet* playerBullets = P1.getBullets();
                for (int j = 0; j < P1.bulletsSize(); ++j) {
                    Bullet& currentBullet = playerBullets[j];

                    if (currentBullet.getCoordinate().x < enemies[i].getGlobalBounds().left + enemies[i].getGlobalBounds().width &&
                        currentBullet.getCoordinate().x + currentBullet.getWidth() > enemies[i].getGlobalBounds().left &&
                        currentBullet.getCoordinate().y < enemies[i].getGlobalBounds().top + enemies[i].getGlobalBounds().height &&
                        currentBullet.getCoordinate().y + currentBullet.getHeight() > enemies[i].getGlobalBounds().top) {

                        enemies[i].takeDamage(1);

                        // Remove the bullet
                        playerBullets[j] = playerBullets[P1.bulletsSize() - 1];
                        P1.decBullet();
                        --j;
                    }
                }

                // Check if enemy is dead
                if (enemies[i].getHealth() <= 0) {
                    enemies.erase(enemies.begin() + i);  // Remove dead enemy
                    --i;  // Adjust index after removal
                }
            }



            if (enemyAppeared) {
                E1.move(deltaTime);
                E1.shoot(deltaTime);


                const vector<Sprite>& enemyBullets = E1.getBullets();
                for (size_t i = 0; i < enemyBullets.size(); ++i) {
                    if (enemyBullets[i].getGlobalBounds().intersects(P1.getGlobalBounds())) {

                        P1.takeDamage(30);


                        E1.getBullets().erase(E1.getBullets().begin() + i);
                        --i;
                    }
                    Bullet* playerBullets = P1.getBullets();
                    for (int j = 0; j < P1.bulletsSize(); ++j) {

                        Bullet& currentBullet = playerBullets[j];


                        if (currentBullet.getCoordinate().x < E1.getGlobalBounds().left + E1.getGlobalBounds().width &&
                            currentBullet.getCoordinate().x + currentBullet.getWidth() > E1.getGlobalBounds().left &&
                            currentBullet.getCoordinate().y < E1.getGlobalBounds().top + E1.getGlobalBounds().height &&
                            currentBullet.getCoordinate().y + currentBullet.getHeight() > E1.getGlobalBounds().top) {


                            E1.takeDamage(1);
                            score += 100;

                            playerBullets[j] = playerBullets[P1.bulletsSize() - 1];
                            P1.decBullet();
                            --j;
                        }
                    }


                    if (E1.getHealth() <= 0) {
                        enemyAppeared = false;
                        current = "gameOver";
                    }
                }
            }



            for (size_t i = 0; i < asteroids.size(); ++i) {
                bool asteroidDestroyed = false;


                asteroids[i].fall(0.5f);

                if (P1.checkCollision(asteroids[i].getCoordinates()) && !asteroids[i].isExplodingg()) {
                    P1.takeDamage(50);
                    asteroids[i].explode(window);
                }


                for (int j = 0; j < P1.bulletsSize(); ++j) {
                    if (asteroids[i].checkBulletCollision(P1.getBullets()[j]) && !asteroids[i].isExplodingg()) {
                        score += 50;
                        asteroids[i].explode(window);
                        P1.getBullets()[j] = P1.getBullets()[P1.bulletsSize() - 1];
                        P1.decBullet();
                        break;
                    }
                }

                if (asteroids[i].isOutOfBounds(globalBoundsY) || (asteroids[i].isExplodingg() == false && asteroids[i].getCurrentFrame() >= 20)) {
                    asteroids.erase(asteroids.begin() + i);
                    --i;
                }
            }


            window.clear();
            G.draw(window);
            P1.drawPlayer(window);
            if (enemyAppeared)
                E1.draw(window);
            for (auto& enemy : enemies) {
                if(littleEnemySpawnStarted)
                enemy.draw(window,true);
            }
            scoreText.setString("Score: " + std::to_string(score));
            window.draw(scoreText);
            healthText.setString("Health: " + std::to_string(P1.getHealth()));
            window.draw(healthText);

            for (auto& asteroid : asteroids) {
                if (asteroid.isExplodingg()) {
                    asteroid.animate(window);

                }
                else {
                    window.draw(asteroid.getSprite());
                }
            }
        }
        window.display();
    }
    return 0;
}