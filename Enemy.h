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
    std::string pAttackName;
    std::string sAttackName;
    std::string buffName;
    std::string healName;
    int health;
    int damage;
    int buff;
    int darkness;

    Enemy();
    Enemy(std::string eN, std::string pAN, std::string sAN, std::string bN, std::string hN, int h, int dam, int b, int dar);

    void GenerateEnemy(const std::string& playerName);
    void GenerateAvis(const std::string& playerName);
    void GeneratePigman(const std::string& playerName);
    void GenerateBali(const std::string& playerName);
    void GenerateTonobros(const std::string& playerName);
    void IncreaseHealth(int amount);
    void DecreaseHealth(int amount);
    void IncreaseDamage(int amount);
    void DecreaseDamage(int amount);
    void DisplayEnemyStats() const;
    void EnemyAttack(int delay1, Player& player);
    void EnemySAttack(int delay1, Player& player);
    void EnemyBuff(int delay1, Player& player, Enemy& enemy);
    void EnemyHealthRegen(int delay1, Player& player, Enemy& enemy);
};

#endif // ENEMY_H