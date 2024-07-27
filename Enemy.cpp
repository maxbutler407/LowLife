#include "Enemy.h"
#include "Utility.h"

Enemy::Enemy() : enemyName(""), attackName(""), buffName(""), potionName(""), inflictDarkness(""), health(0), damage(0), buff(0), darkness(0) {}

Enemy::Enemy(std::string eN, std::string aN, std::string bN, std::string pN, std::string iD, int h, int dam, int b, int dar)
    : enemyName(eN), attackName(aN), buffName(bN), potionName(pN), inflictDarkness(iD), health(h), damage(dam), buff(b), darkness(dar) {}

// Generates a random enemy.
void Enemy::GenerateEnemy(const std::string& playerName) {
    srand(static_cast<unsigned int>(time(nullptr)));
    int randNum = rand() % 2 + 1;
    if (randNum == 1) {
        enemyName = "\033[31mPossessed Astronaut\033[0m";
        attackName = " used its raygun on " + playerName;
        buffName = " activated its stim injection";
        health = 80;
        damage = 15;
        buff = 10;
        darkness = 5;
    }
    else if (randNum == 2) {
        enemyName = "\033[31mCentimane\033[0m";
        attackName = " used a number of his arms to bombard " + playerName;
        buffName = "brought out more arms to attack the LowLife";
        health = 100;
        damage = 30;
        buff = 5;
        darkness = 10;
    }
}

// Methods are used to modify INITIALISED member variables for better encapsulation.
void Enemy::IncreaseHealth(int amount) { health += amount; }
void Enemy::DecreaseHealth(int amount) { health -= amount; }
void Enemy::IncreaseDamage(int amount) { damage += amount; }
void Enemy::DecreaseDamage(int amount) { damage -= amount; }

void Enemy::EnemyAttack(int delay1, Player& player) {
    std::string attack1 = "\n\nThe " + enemyName + attackName + "..." + "\n\n...\033[31m";
    Stagger(attack1, delay1);
    int attack2 = damage;
    StaggerInt(attack2, delay1);
    std::string attack3 = " damage\033[0m!";
    Stagger(attack3, delay1);
    player.DecreaseHealth(damage);
}

void Enemy::EnemyDefence(Player& player, Enemy& enemy) {
    std::cout << "\nThe " + enemyName + buffName + "..." + "\n\n\033[31m...+" << buff << " damage\033[0m";
    enemy.IncreaseDamage(buff);
}

void Enemy::DisplayEnemyStats() const {
    int strength = damage;
    std::cout << "\n" + enemyName + "'s Current Stats : ";
    std::cout << "\n   - Health         |  " << health;
    std::cout << "\n   - Strength       |  " << strength;
    std::cout << "\n   - Darkness       |  " << darkness;
}