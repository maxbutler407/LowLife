#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Player.h" // Include Player class header

class Player;

class Enemy {
public:
    std::string enemyName;
    std::string attackName;
    std::string buffName;
    std::string potionName;
    std::string inflictDarkness;
    int health;
    int damage;
    int buff;
    int darkness;

    Enemy();
    Enemy(std::string eN, std::string aN, std::string bN, std::string pN, std::string iD, int h, int dam, int b, int dar);

    void GenerateEnemy(const std::string& playerName);
    void GeneratePigman(const std::string& playerName);
    void GenerateBali(const std::string& playerName);
    void IncreaseHealth(int amount);
    void DecreaseHealth(int amount);
    void IncreaseDamage(int amount);
    void DecreaseDamage(int amount);
    void DisplayEnemyStats() const;
    void EnemyAttack(int delay1, Player& player);
    void EnemyDefence(Player& player, Enemy& enemy);
};

#endif // ENEMY_H