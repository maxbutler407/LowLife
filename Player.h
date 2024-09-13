#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <unordered_map>
#include "Enemy.h"

class Enemy;

class Player {
public:
    // ----------Player Combat and Stats----------
    // Player stats - can be altered (ie. increased/decreased) depending on the paths the player takes.
    std::string playerName;
    int health; // Not set a value until object is called.
    int strength;
    int magic;
    int intelligence;
    int darkness;

    Player();
    Player(std::string n, int h, int s, int m, int i, int d);

    void DisplayPlayerStats() const;

    void IncreaseHealth(int amount);
    void DecreaseHealth(int amount);
    void IncreaseStrength(int amount);
    void DecreaseStrength(int amount);
    void IncreaseMagic(int amount);
    void DecreaseMagic(int amount);
    void IncreaseIntelligence(int amount);
    void DecreaseIntelligence(int amount);
    void IncreaseDarkness(int amount);
    void DecreaseDarkness(int amount);

    // Wizard abilities.
    virtual void MindTrick(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) = 0;
    virtual void SinisterSpell(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) = 0;
    virtual void SelfEnchant(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) = 0;
    virtual void DarkForces(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) = 0;

    // Beast abilities.
    virtual void Transform(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) = 0;
    virtual void ThrowStone(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) = 0;
    virtual void TransformBack(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) = 0;
    virtual void FearfulRoar(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) = 0;
    virtual void BeatDown(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) = 0;
    virtual void ClawStab(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) = 0;

    // Astronomer abilities.
    virtual void Examine(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) = 0;
    virtual void OptimiseMoves(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) = 0;
    virtual void CallTheStars(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) = 0;
    virtual void UseTelescopeAsWeapon(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) = 0;

    // Endgame abilities
    virtual void LightningWrath(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) = 0;
    virtual void LatherEctoplasm(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) = 0;

    // ----------Player Inventory----------
    int spaceSuitCount;
    int merasGlowthCount;
    int coinCount;
    int ectoplasmCount;
    int headCount;

    // Each item is a string which can have its own quantity (using int vector).
    std::unordered_map<std::string, int> inventory;
    void InitialiseInventory();
    void HideEmptySlots();
    void ShowInventory() const;
    void AddSpaceSuitToInventory();
    void AddMerasGlowthToInventory();
    void AddCoinToInventory();
    void AddEctoplasmToInventory();
    void AddBalisHeadToInventory();
};

#endif // PLAYER_H