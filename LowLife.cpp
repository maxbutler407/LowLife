#define NOMINMAX

#include <iostream>
#include <string.h>
#include <string>
#include <thread>
#include <chrono>  
#include <map>
#include <vector>
#include <functional>
#include <fstream>
#include <windows.h>
#include <filesystem>
#include <limits>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/logger.hpp>
#include <iomanip>

#include "Player.h"
#include "Enemy.h"
#include "Utility.h"

using MapInventory = std::map<std::string, int>;

// Global variables.
int delay1 = 30;
int delay2 = 90;
int delay3 = 5;
std::string playerName;
std::string GAMEOVER = "\n\n\n                                                \033[31mGAME OVER.\033[0m\n\n\n";
bool spokenToHermit = false;
bool spokenToFilia = false;
bool spokenToGorkan = false;
bool spokenToBali = false;
bool spokenToCowboy = false;
bool spokenToPilot = false;
bool spokenToTonobros = false;
bool hando = false;
bool bold = false;
std::string character;
bool randomEnemy = false;
bool avis = false;
bool pigman = false;
bool bali = false;
bool tonobros = false;

// ----------Classes----------
class Wizard : public Player {
public:
    // Attributes.
    Wizard(std::string playerName) : Player(playerName, 100, 10, 30, 20, 0) {};

    // Abilities.
    void MindTrick(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {
        std::string mindTrick1 = "\n" + playerName + " used a \033[34mmind trick\033[0m...\n\n... \033[31m";
        Stagger(mindTrick1, delay1);
        std::string mindTrick3 = "-15 enemy damage\033[0m!";
        Stagger(mindTrick3, delay1);
        enemy.DecreaseDamage(15);
    }
    void SinisterSpell(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {
        std::string spell1 = "\n" + playerName + " used a \033[34mpowerful spell\033[0m...\n\n... \033[31m-";
        Stagger(spell1, delay1);
        int spell2 = magic + strength;
        StaggerInt(spell2, delay1);
        std::string spell3 = " enemy health\033[0m!";
        Stagger(spell3, delay1);
        enemy.DecreaseHealth(magic + strength);
    }
    void SelfEnchant(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {
        std::string spell1 = "\n" + playerName + " \033[34menchanted\033[0m themselves...\n\n... \033[34m";
        Stagger(spell1, delay1);
        std::string spell3 = "+10 player health\033[0m!";
        Stagger(spell3, delay1);
        player.IncreaseHealth(10);
    }
    void DarkForces(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {
        std::string spell1 = "\n" + playerName + " summoned \033[34mcruel powers from another realm\033[0m onto the " + enemyName + "...\n\n... \033[31m-";
        Stagger(spell1, delay1);
        int spell2 = magic * 2;
        StaggerInt(spell2, delay1);
        std::string spell3 = " enemy health\033[0m!";
        Stagger(spell3, delay1);
        enemy.DecreaseHealth(magic * 2);

        // Increases player's darkness stat.
        int darknessCalculation = enemy.darkness * 0.8;
        std::string spell4 = "\n\n" + playerName + "'s darkness has increased...";
        Stagger(spell4, delay1);
        player.IncreaseDarkness(darknessCalculation);
    }
    void LightningWrath(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {
        std::string spell1 = "\nThe eyes of \033[34mBali's head\033[0m suddenly glowed red...\n\n... \033[31m-";
        Stagger(spell1, delay1);
        int spell2 = magic + darkness;
        StaggerInt(spell2, delay1);
        std::string spell3 = " enemy health\033[0m!";
        Stagger(spell3, delay1);
        enemy.DecreaseHealth(magic + darkness);
    }
    void LatherEctoplasm(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {
        std::string spell1 = "\n" + playerName + " poured some of the \033[34mectoplasm\033[0m onto themself - becoming invisible for a while...\n\n... \033[34m+";
        Stagger(spell1, delay1);
        int spell2 = magic + darkness;
        StaggerInt(spell2, delay1);
        std::string spell3 = " player damage\033[0m!";
        Stagger(spell3, delay1);
        player.IncreaseMagic(magic + darkness);
    }

    void Transform(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {}
    void ThrowStone(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {}
    void TransformBack(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {}
    void FearfulRoar(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {}
    void BeatDown(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {}
    void ClawStab(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {}
    void Examine(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {}
    void OptimiseMoves(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {}
    void CallTheStars(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {}
    void UseTelescopeAsWeapon(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {}
};
class Beast : public Player {
public:

    // Attributes.
    Beast(std::string playerName) : Player(playerName, 100, 20, 20, 10, 0) {}; // strength == 70 when ability is active.
    int boostedStrength = 40;

    // Abilities.
    void Transform(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {
        std::string transform = "\n" + playerName + " \033[34mtransformed\033[0m into a creature of mythical and powerful origin...";
        Stagger(transform, delay1);

        // Increases player's darkness stat.
        int darknessCalculation = enemy.darkness * 0.2;
        std::string spell4 = "\n\n" + playerName + "'s darkness has increased...";
        Stagger(spell4, delay1);
        player.IncreaseDarkness(darknessCalculation);
    }
    void ThrowStone(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {
        std::string throw1 = "\n" + playerName + " threw a \033[34mstone\033[0m at the " + enemyName + "...\n\n... \033[31m-";
        Stagger(throw1, delay1);
        int throw2 = 10;
        StaggerInt(throw2, delay1);
        std::string throw3 = " enemy health\033[0m!";
        Stagger(throw3, delay1);
        enemy.DecreaseHealth(throw2);
    }
    void TransformBack(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {
        std::string transform1 = "\n" + playerName + " \033[34mtransformed\033[0m back into their basic form...";
        Stagger(transform1, delay1);
    }
    void FearfulRoar(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {
        std::string roar1 = "\n" + playerName + " bellowed a terrifying \033[34mroar\033[0m...\n\n... \033[31m";
        Stagger(roar1, delay1);
        std::string roar2 = "-15 enemy damage\033[0m!";
        Stagger(roar2, delay1);
        enemy.DecreaseDamage(15);
    }
    void BeatDown(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {
        std::string beat1 = "\n" + playerName + " lept onto the " + enemyName + ", \033[34mbeating\033[0m it ferociously...\n\n... \033[31m-";
        Stagger(beat1, delay1);
        int beat2 = boostedStrength + strength;
        StaggerInt(beat2, delay1);
        std::string beat3 = " enemy health\033[0m!";
        Stagger(beat3, delay1);
        enemy.DecreaseHealth(boostedStrength + strength);
    }
    void ClawStab(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {
        std::string spell1 = "\n" + playerName + " pierced their serrated \033[34mclaw\033[0m into the " + enemyName + "...\n\n... \033[31m-";
        Stagger(spell1, delay1);
        int spell2 = boostedStrength + intelligence;
        StaggerInt(spell2, delay1);
        std::string spell3 = " enemy health\033[0m!";
        Stagger(spell3, delay1);
        enemy.DecreaseHealth(boostedStrength + intelligence);
    }
    void LightningWrath(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {
        std::string spell1 = "\nThe eyes of \033[34mBali's head\033[0m suddenly glowed red...\n\n... \033[31m-";
        Stagger(spell1, delay1);
        int spell2 = boostedStrength + darkness;
        StaggerInt(spell2, delay1);
        std::string spell3 = " enemy health\033[0m!";
        Stagger(spell3, delay1);
        enemy.DecreaseHealth(boostedStrength + darkness);
    }
    void LatherEctoplasm(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {
        std::string spell1 = "\n" + playerName + " poured some of the \033[34mectoplasm\033[0m onto themself - becoming invisible for a while...\n\n... \033[34m+";
        Stagger(spell1, delay1);
        int spell2 = boostedStrength + darkness;
        StaggerInt(spell2, delay1);
        std::string spell3 = " player damage\033[0m!";
        Stagger(spell3, delay1);
        player.IncreaseMagic(boostedStrength + darkness);
    }

    // Provide default implementations for non-Beast abilities
    void MindTrick(int, const std::string&, const std::string&, Player&, Enemy&) override {}
    void SinisterSpell(int, const std::string&, const std::string&, Player&, Enemy&) override {}
    void SelfEnchant(int, const std::string&, const std::string&, Player&, Enemy&) override {}
    void DarkForces(int, const std::string&, const std::string&, Player&, Enemy&) override {}
    void Examine(int, const std::string&, const std::string&, Player&, Enemy&) override {}
    void OptimiseMoves(int, const std::string&, const std::string&, Player&, Enemy&) override {}
    void CallTheStars(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {}
    void UseTelescopeAsWeapon(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {}
};
class Astronomer : public Player {
public:
    // Attributes.
    Astronomer(std::string playerName) : Player(playerName, 100, 10, 5, 30, 0) {};

    // Abilities.
    void Examine(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {
        std::string examine1 = "\n" + playerName + " \033[34midentified\033[0m the " + enemyName + "'s weaknesses...\n\n... \033[31m-";
        Stagger(examine1, delay1);
        int examine2 = intelligence * 1.3;
        StaggerInt(examine2, delay1);
        std::string examine3 = " enemy damage\033[0m!";
        Stagger(examine3, delay1);
        enemy.DecreaseDamage(intelligence * 1.3);
    }
    void OptimiseMoves(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {
        std::string calculate1 = "\n" + playerName + " \033[34mcalculated\033[0m their advantages...\n\n... \033[34m";
        Stagger(calculate1, delay1);
        std::string calculate3 = "+20 player damage\033[0m!";
        Stagger(calculate3, delay1);
        player.IncreaseStrength(20);
    }
    void CallTheStars(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {
        std::string call1 = "\n" + playerName + " brought down the \033[34mlight\033[0m from the sky...\n\n... \033[31m-";
        Stagger(call1, delay1);
        int call2 = intelligence + magic;
        StaggerInt(call2, delay1);
        std::string call3 = " enemy health\033[0m!";
        Stagger(call3, delay1);
        enemy.DecreaseHealth(intelligence + magic);

        // Increases player's darkness stat.
        int darknessCalculation = enemy.darkness * 0.8;
        std::string spell4 = "\n\n" + playerName + "'s darkness has increased...";
        Stagger(spell4, delay1);
        player.IncreaseDarkness(darknessCalculation);
    }
    void UseTelescopeAsWeapon(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {
        std::string telescope1 = "\n" + playerName + " hit the " + enemyName + " with their \033[34mtelescope\033[0m...\n\n... \033[31m-";
        Stagger(telescope1, delay1);
        int telescope2 = strength;
        StaggerInt(telescope2, delay1);
        std::string telescope3 = " enemy health\033[0m!";
        Stagger(telescope3, delay1);
        enemy.DecreaseHealth(strength);
    }
    void LightningWrath(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {
        std::string spell1 = "\nThe eyes of \033[34mBali's head\033[0m suddenly glowed red...\n\n... \033[31m-";
        Stagger(spell1, delay1);
        int spell2 = intelligence + darkness;
        StaggerInt(spell2, delay1);
        std::string spell3 = " enemy health\033[0m!";
        Stagger(spell3, delay1);
        enemy.DecreaseHealth(intelligence + darkness);
    }
    void LatherEctoplasm(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {
        std::string spell1 = "\n" + playerName + " poured some of the \033[34mectoplasm\033[0m onto themself - becoming invisible for a while...\n\n... \033[34m+";
        Stagger(spell1, delay1);
        int spell2 = intelligence + darkness;
        StaggerInt(spell2, delay1);
        std::string spell3 = " player damage\033[0m!";
        Stagger(spell3, delay1);
        player.IncreaseMagic(intelligence + darkness);
    }

    // Provide default implementations for non-Astronomer abilities
    void MindTrick(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {}
    void SinisterSpell(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {}
    void SelfEnchant(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {}
    void DarkForces(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {}
    void Transform(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {}
    void ThrowStone(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {}
    void TransformBack(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {}
    void FearfulRoar(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {}
    void BeatDown(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {}
    void ClawStab(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {}
};
void Credits(int delay2) {
    std::string credits1 = "\n\n\n                                                Thanks for playing LowLife! - Max.";
    Stagger(credits1, delay2);
    Sleep_5s();
    Sleep_5s();
    Sleep_5s();
    exit(0);
}
void StartBattle(int delay1, Player& player, Enemy& enemy, const std::string& playerName, std::string character, bool transformed, bool hando) {
    while (player.health > 0 && enemy.health > 0) {
        if (character == "wizard" || character == "Wizard") {
            std::string battleChoice;
            std::string battle2 = "\n\nWhat would you like to do?";
            Stagger(battle2, delay1);
            std::cout << "\n|        MindTrick        ||     SinisterSpell       |";
            std::cout << "\n|       SelfEnchant       ||       \033[31mDarkForces\033[0m        |";
            if (player.headCount >= 1) {
                std::cout << "\n          |        LightningWrath         |";
            }
            else if (player.ectoplasmCount >= 1) {
                std::cout << "\n          |        LatherEctoplasm        |";
            }
            std::cout << "\n> ";
            std::getline(std::cin, battleChoice);

            if (battleChoice == "MindTrick" || battleChoice == "Mindtrick" || battleChoice == "mindtrick") {
                player.MindTrick(delay1, playerName, enemy.enemyName, player, enemy);
            }
            else if (battleChoice == "SinisterSpell" || battleChoice == "Sinisterspell" || battleChoice == "sinisterspell") {
                player.SinisterSpell(delay1, playerName, enemy.enemyName, player, enemy);
            }
            else if (battleChoice == "SelfEnchant" || battleChoice == "Selfenchant" || battleChoice == "selfenchant") {
                player.SelfEnchant(delay1, playerName, enemy.enemyName, player, enemy);
            }
            else if (battleChoice == "DarkForces" || battleChoice == "Darkforces" || battleChoice == "darkforces") {
                player.DarkForces(delay1, playerName, enemy.enemyName, player, enemy);
            }
            else if (battleChoice == "LightningWrath" || battleChoice == "Lightningwrath" || battleChoice == "lightningwrath") {
                player.LightningWrath(delay1, playerName, enemy.enemyName, player, enemy);
            }
            else if (battleChoice == "LatherEctoplasm" || battleChoice == "Latherectoplasm" || battleChoice == "latherectoplasm") {
                player.LatherEctoplasm(delay1, playerName, enemy.enemyName, player, enemy);
            }
            else {
                std::cout << "\n\033[90mPlease select an action silly boy\033[0m\n";
            }
            // Pseudo-randomly generates hando and enemy moves.
            if (enemy.health > 0 && hando == false) {
                srand(time(NULL));
                int randNum = rand() % 4 + 1;
                if (randNum == 1 || randNum == 2) {
                    enemy.EnemyAttack(delay1, player);
                }
                else if (randNum == 3) {
                    enemy.EnemyBuff(delay1, player, enemy);
                }
                else if (randNum == 4) {
                    enemy.EnemyHealthRegen(delay1, player, enemy);
                }
            }
            else if (enemy.health > 0) {
                srand(time(NULL));
                int randNum = rand() % 3 + 1;
                if (randNum == 1) {
                    enemy.EnemyAttack(delay1, player);
                    std::string handoAttack1 = "\n\nHando brought out his plasma rifle and fired it at the " + enemy.enemyName + " - some of its feathers caught fire!..\n\n...\033[31m-";
                    Stagger(handoAttack1, delay1);
                    StaggerInt(player.magic * 1.2, delay1);
                    std::string handoAttack2 = " enemy health\033[0m!";
                    Stagger(handoAttack2, delay1);
                    enemy.DecreaseHealth(player.magic * 0.5);
                }
                else if (randNum == 2) {
                    enemy.EnemyBuff(delay1, player, enemy);
                    std::string handoAttack1 = "\n\nThe creature Hando rode roared, biting and scratching the flesh off the " + enemy.enemyName + "...\n\n...\033[31m-";
                    Stagger(handoAttack1, delay1);
                    StaggerInt(player.magic * 1.2, delay1);
                    std::string handoAttack2 = " enemy health\033[0m!";
                    Stagger(handoAttack2, delay1);
                    enemy.DecreaseHealth(player.strength * 0.5);
                }
                else if (randNum == 3) {
                    enemy.EnemyHealthRegen(delay1, player, enemy);
                    std::string handoAttack1 = "\n\nA lasso was thrown round the " + enemy.enemyName + "'s neck - it struggled to move...\n\n...\033[31m-";
                    Stagger(handoAttack1, delay1);
                    StaggerInt(player.magic * 1.2, delay1);
                    std::string handoAttack2 = " enemy damage\033[0m!";
                    Stagger(handoAttack2, delay1);
                    enemy.DecreaseDamage(player.intelligence * 0.5);
                }
            } 
        }

        else if (character == "beast" || character == "Beast") {
            if (!transformed) {
                std::string battleChoice;
                std::string battle2 = "\n\nWhat would you like to do?";
                Stagger(battle2, delay1);
                std::cout << "\n|        \033[31mTransform\033[0m        ||       ThrowStone        |";
                if (player.headCount >= 1) {
                    std::cout << "\n          |        LightningWrath         |";
                }
                else if (player.ectoplasmCount >= 1) {
                    std::cout << "\n          |        LatherEctoplasm        |";
                }
                std::cout << "\n> ";
                std::getline(std::cin, battleChoice);

                if (battleChoice == "Transform" || battleChoice == "transform") {
                    transformed = true;
                    player.Transform(delay1, playerName, enemy.enemyName, player, enemy);
                }
                else if (battleChoice == "ThrowStone" || battleChoice == "Throwstone" || battleChoice == "throwstone") {
                    player.ThrowStone(delay1, playerName, enemy.enemyName, player, enemy);
                }
                else if (battleChoice == "LightningWrath" || battleChoice == "Lightningwrath" || battleChoice == "lightningwrath") {
                    player.LightningWrath(delay1, playerName, enemy.enemyName, player, enemy);
                }
                else if (battleChoice == "LatherEctoplasm" || battleChoice == "Latherectoplasm" || battleChoice == "latherectoplasm") {
                    player.LatherEctoplasm(delay1, playerName, enemy.enemyName, player, enemy);
                }
                else {
                    std::cout << "\n\033[90mPlease select an action silly boy\033[0m\n";
                }
                // Pseudo-randomly generates hando and enemy moves.
                if (enemy.health > 0 && hando == false) {
                    srand(time(NULL));
                    int randNum = rand() % 4 + 1;
                    if (randNum == 1 || randNum == 2) {
                        enemy.EnemyAttack(delay1, player);
                    }
                    else if (randNum == 3) {
                        enemy.EnemyBuff(delay1, player, enemy);
                    }
                    else if (randNum == 4) {
                        enemy.EnemyHealthRegen(delay1, player, enemy);
                    }
                }
                else if (enemy.health > 0) {
                    srand(time(NULL));
                    int randNum = rand() % 3 + 1;
                    if (randNum == 1) {
                        enemy.EnemyAttack(delay1, player);
                        std::string handoAttack1 = "\n\nHando brought out his plasma rifle and fired it at the " + enemy.enemyName + " - some of its feathers caught fire!..\n\n...\033[31m-";
                        Stagger(handoAttack1, delay1);
                        StaggerInt(player.magic * 1.2, delay1);
                        std::string handoAttack2 = " enemy health\033[0m!";
                        Stagger(handoAttack2, delay1);
                        enemy.DecreaseHealth(player.magic * 0.5);
                    }
                    else if (randNum == 2) {
                        enemy.EnemyBuff(delay1, player, enemy);
                        std::string handoAttack1 = "\n\nThe creature Hando rode roared, biting and scratching the flesh off the " + enemy.enemyName + "...\n\n...\033[31m-";
                        Stagger(handoAttack1, delay1);
                        StaggerInt(player.magic * 1.2, delay1);
                        std::string handoAttack2 = " enemy health\033[0m!";
                        Stagger(handoAttack2, delay1);
                        enemy.DecreaseHealth(player.strength * 0.5);
                    }
                    else if (randNum == 3) {
                        enemy.EnemyHealthRegen(delay1, player, enemy);
                        std::string handoAttack1 = "\n\nA lasso was thrown round the " + enemy.enemyName + "'s neck - it struggled to move...\n\n...\033[31m-";
                        Stagger(handoAttack1, delay1);
                        StaggerInt(player.magic * 1.2, delay1);
                        std::string handoAttack2 = " enemy damage\033[0m!";
                        Stagger(handoAttack2, delay1);
                        enemy.DecreaseDamage(player.intelligence * 0.5);
                    }
                }
            }
            else {
                std::string transformChoice;
                std::string transform = "\n\nWhat would you like to do?";
                Stagger(transform, delay1);
                std::cout << "\n|        Transform        ||       FearfulRoar       |";
                std::cout << "\n|        BeatDown         ||        ClawStab         |";
                if (player.headCount >= 1) {
                    std::cout << "\n          |        LightningWrath         |";
                }
                else if (player.ectoplasmCount >= 1) {
                    std::cout << "\n          |        LatherEctoplasm        |";
                }
                std::cout << "\n> ";
                std::getline(std::cin, transformChoice);

                if (transformChoice == "Transform" || transformChoice == "transform") {
                    transformed = false;
                    player.TransformBack(delay1, playerName, enemy.enemyName, player, enemy);
                }
                else if (transformChoice == "FearfulRoar" || transformChoice == "Fearfulroar" || transformChoice == "fearfulroar") {
                    player.FearfulRoar(delay1, playerName, enemy.enemyName, player, enemy);
                }
                else if (transformChoice == "BeatDown" || transformChoice == "Beatdown" || transformChoice == "beatdown") {
                    player.BeatDown(delay1, playerName, enemy.enemyName, player, enemy);
                }
                else if (transformChoice == "ClawStab" || transformChoice == "Clawstab" || transformChoice == "clawstab") {
                    player.ClawStab(delay1, playerName, enemy.enemyName, player, enemy);
                }
                else if (transformChoice == "LightningWrath" || transformChoice == "Lightningwrath" || transformChoice == "lightningwrath") {
                    player.LightningWrath(delay1, playerName, enemy.enemyName, player, enemy);
                }
                else if (transformChoice == "LatherEctoplasm" || transformChoice == "Latherectoplasm" || transformChoice == "latherectoplasm") {
                    player.LatherEctoplasm(delay1, playerName, enemy.enemyName, player, enemy);
                }
                else {
                    std::cout << "\n\033[90mPlease select an action silly boy\033[0m\n";
                }
                // Pseudo-randomly generates hando and enemy moves.
                if (enemy.health > 0 && hando == false) {
                    srand(time(NULL));
                    int randNum = rand() % 4 + 1;
                    if (randNum == 1 || randNum == 2) {
                        enemy.EnemyAttack(delay1, player);
                    }
                    else if (randNum == 3) {
                        enemy.EnemyBuff(delay1, player, enemy);
                    }
                    else if (randNum == 4) {
                        enemy.EnemyHealthRegen(delay1, player, enemy);
                    }
                }
                else if (enemy.health > 0) {
                    srand(time(NULL));
                    int randNum = rand() % 3 + 1;
                    if (randNum == 1) {
                        enemy.EnemyAttack(delay1, player);
                        std::string handoAttack1 = "\n\nHando brought out his plasma rifle and fired it at the " + enemy.enemyName + " - some of its feathers caught fire!..\n\n...\033[31m-";
                        Stagger(handoAttack1, delay1);
                        StaggerInt(player.magic * 1.2, delay1);
                        std::string handoAttack2 = " enemy health\033[0m!";
                        Stagger(handoAttack2, delay1);
                        enemy.DecreaseHealth(player.magic * 0.5);
                    }
                    else if (randNum == 2) {
                        enemy.EnemyBuff(delay1, player, enemy);
                        std::string handoAttack1 = "\n\nThe creature Hando rode roared, biting and scratching the flesh off the " + enemy.enemyName + "...\n\n...\033[31m-";
                        Stagger(handoAttack1, delay1);
                        StaggerInt(player.magic * 1.2, delay1);
                        std::string handoAttack2 = " enemy health\033[0m!";
                        Stagger(handoAttack2, delay1);
                        enemy.DecreaseHealth(player.strength * 0.5);
                    }
                    else if (randNum == 3) {
                        enemy.EnemyHealthRegen(delay1, player, enemy);
                        std::string handoAttack1 = "\n\nA lasso was thrown round the " + enemy.enemyName + "'s neck - it struggled to move...\n\n...\033[31m-";
                        Stagger(handoAttack1, delay1);
                        StaggerInt(player.magic * 1.2, delay1);
                        std::string handoAttack2 = " enemy damage\033[0m!";
                        Stagger(handoAttack2, delay1);
                        enemy.DecreaseDamage(player.intelligence * 0.5);
                    }
                }
            }
        }
        else if (character == "astronomer" || character == "Astronomer") {
            std::string battleChoice;
            std::string battle2 = "\n\nWhat would you like to do?";
            Stagger(battle2, delay1);
            std::cout << "\n|        Examine          ||      OptimiseMoves      |";
            std::cout << "\n|      \033[31mCallTheStars\033[0m       ||  UseTelescopeAsWeapon   |";
            if (player.headCount >= 1) {
                std::cout << "\n          |        LightningWrath         |";
            }
            else if (player.ectoplasmCount >= 1) {
                std::cout << "\n          |        LatherEctoplasm        |";
            }
            std::cout << "\n> ";
            std::getline(std::cin, battleChoice);

            if (battleChoice == "Examine" || battleChoice == "examine") {
                player.Examine(delay1, playerName, enemy.enemyName, player, enemy);
            }
            else if (battleChoice == "OptimiseMoves" || battleChoice == "Optimisemoves" || battleChoice == "optimisemoves") {
                player.OptimiseMoves(delay1, playerName, enemy.enemyName, player, enemy);
            }
            else if (battleChoice == "CallTheStars" || battleChoice == "Callthestars" || battleChoice == "callthestars") {
                player.CallTheStars(delay1, playerName, enemy.enemyName, player, enemy);
            }
            else if (battleChoice == "UseTelescopeAsWeapon" || battleChoice == "Usetelescopeasweapon" || battleChoice == "usetelescopeasweapon") {
                player.UseTelescopeAsWeapon(delay1, playerName, enemy.enemyName, player, enemy);
            }
            else if (battleChoice == "LightningWrath" || battleChoice == "Lightningwrath" || battleChoice == "lightningwrath") {
                player.LightningWrath(delay1, playerName, enemy.enemyName, player, enemy);
            }
            else if (battleChoice == "LatherEctoplasm" || battleChoice == "Latherectoplasm" || battleChoice == "latherectoplasm") {
                player.LatherEctoplasm(delay1, playerName, enemy.enemyName, player, enemy);
            }
            else {
                std::cout << "\n\033[90mPlease select an action silly boy.\033[0m\n";
            }
            // Pseudo-randomly generates hando and enemy moves.
            if (enemy.health > 0 && hando == false) {
                srand(time(NULL));
                int randNum = rand() % 4 + 1;
                if (randNum == 1 || randNum == 2) {
                    enemy.EnemyAttack(delay1, player);
                }
                else if (randNum == 3) {
                    enemy.EnemyBuff(delay1, player, enemy);
                }
                else if (randNum == 4) {
                    enemy.EnemyHealthRegen(delay1, player, enemy);
                }
            }
            else if (enemy.health > 0) {
                srand(time(NULL));
                int randNum = rand() % 3 + 1;
                if (randNum == 1) {
                    enemy.EnemyAttack(delay1, player);
                    std::string handoAttack1 = "\n\nHando brought out his plasma rifle and fired it at the " + enemy.enemyName + " - some of its feathers caught fire!..\n\n...\033[31m-";
                    Stagger(handoAttack1, delay1);
                    StaggerInt(player.magic * 1.2, delay1);
                    std::string handoAttack2 = " enemy health\033[0m!";
                    Stagger(handoAttack2, delay1);
                    enemy.DecreaseHealth(player.magic * 0.5);
                }
                else if (randNum == 2) {
                    enemy.EnemyBuff(delay1, player, enemy);
                    std::string handoAttack1 = "\n\nThe creature Hando rode roared, biting and scratching the flesh off the " + enemy.enemyName + "...\n\n...\033[31m-";
                    Stagger(handoAttack1, delay1);
                    StaggerInt(player.magic * 1.2, delay1);
                    std::string handoAttack2 = " enemy health\033[0m!";
                    Stagger(handoAttack2, delay1);
                    enemy.DecreaseHealth(player.strength * 0.5);
                }
                else if (randNum == 3) {
                    enemy.EnemyHealthRegen(delay1, player, enemy);
                    std::string handoAttack1 = "\n\nA lasso was thrown round the " + enemy.enemyName + "'s neck - it struggled to move...\n\n...\033[31m-";
                    Stagger(handoAttack1, delay1);
                    StaggerInt(player.magic * 1.2, delay1);
                    std::string handoAttack2 = " enemy damage\033[0m!";
                    Stagger(handoAttack2, delay1);
                    enemy.DecreaseDamage(player.intelligence * 0.5);
                }
            }
        }
    }

    // Decides various outcomes of battle.
    if (player.health > 0) {
        std::cout << "\n" + playerName + " defeated the " + enemy.enemyName + "!";
        std::cout << "\n" + playerName + "'s stats has been fully restored.";
        // Restores player's stats.
        player.health = 100;
        if (character == "wizard" || character == "Wizard") {
            player.strength = 10;
            player.intelligence = 20;
            player.magic = 30;
        }
        else if (character == "beast" || character == "Beast") {
            player.strength = 20;
            player.intelligence = 10;
            player.magic = 20;
        }
        else if (character == "astronomer" || character == "Astronomer") {
            player.strength = 10;
            player.intelligence = 40;
            player.magic = 10;
        }
        player.DisplayPlayerStats();
        stopMusic();
        startMusic("C:\\Programming\\C++ Games\\LowLife\\LowLifeMusic\\travel.wav");
    }
    else if (player.darkness >= 100) {
        std::string darknessDeath1 = "\n" + playerName + " was now fully consumed by the darkness inside them...";
        Stagger(darknessDeath1, delay1);
        std::string darknessDeath2 = "\n" + playerName + " collapsed to the floor as black goo streamed out of their eyes and mouth...";
        Stagger(darknessDeath2, delay1);
        std::string darknessDeath3 = "\nOur hero died in agony as the darkness consumed another LowLife.";
        Stagger(darknessDeath3, delay1);
        Stagger(GAMEOVER, delay2);
        // Ends the game.
        exit(0);
    }
}
void InitialiseBattle(int delay1, Player& player, const std::string& playerName, std::string character, bool randomEnemy, bool avis, bool pigman, bool bali, bool tonobros) {
    if (pigman == true) {
        stopMusic();
        startMusic("C:\\Programming\\C++ Games\\LowLife\\LowLifeMusic\\miniBoss.wav");
        Enemy enemy;
        enemy.GeneratePigman(playerName);

        // Commences battle events.
        std::string battle1 = "\n\n" + playerName + " was ambushed by " + enemy.enemyName + "!";
        Stagger(battle1, delay1);
        // Displays both player and enemy stats at the start of battle.
        player.DisplayPlayerStats();
        enemy.DisplayEnemyStats();

        bool transformed = false;
        while (player.health > 0 && enemy.health > 0) {
            StartBattle(delay1, player, enemy, playerName, character, transformed, hando);

            if (player.health <= 0) {
            std::string gorkanKill1 = "\n\nGorkan threw " + playerName + " into the mud, allowing all his rotten features to fall and squirm on them as they lay helpless.";
            Stagger(gorkanKill1, delay1);
            std::string gorkanKill2 = "\nGorkan then began to tear our hero apart; eating what remained";
            Stagger(gorkanKill2, delay1);
            Stagger(GAMEOVER, delay2);
            // Ends the game.
            exit(0);
            }
        }
        stopMusic();
    }
    if (avis == true) {
        stopMusic();
        startMusic("C:\\Programming\\C++ Games\\LowLife\\LowLifeMusic\\miniBoss.wav");
        Enemy enemy;
        enemy.GenerateAvis(playerName);

        // Commences battle events.
        std::string battle1 = "\n\nA gigantic bird suddenly landed with a boom onto the desert floor.";
        Stagger(battle1, delay1);
        // Displays both player and enemy stats at the start of battle.
        player.DisplayPlayerStats();
        enemy.DisplayEnemyStats();

        bool transformed = false;
        bool hando = true;
        while (player.health > 0 && enemy.health > 0) {
            StartBattle(delay1, player, enemy, playerName, character, transformed, hando);

            if (player.health <= 0) {
                std::string avisKill1 = "\n\n" + playerName + " fell to the desert floor, Hando had already been torn apart by the magnificent beast...";
                Stagger(avisKill1, delay1);
                std::string avisKill2 = "\n" + enemy.enemyName + " placed a giant claw onto " + playerName + " trapping them, allowing it to launch its beak at " + playerName + "...leaving nothing but a pile of remains";
                Stagger(avisKill2, delay1);
                Stagger(GAMEOVER, delay2);
                // Ends the game.
                exit(0);
            }
        }
    }
    if (randomEnemy) {
        stopMusic();
        startMusic("C:\\Programming\\C++ Games\\LowLife\\LowLifeMusic\\battle_music1.wav");
        Enemy enemy;
        enemy.GenerateEnemy(playerName);

        // Commences battle events.
        std::string battle1 = "\n\n" + playerName + " was ambushed by a " + enemy.enemyName + "!";
        Stagger(battle1, delay1);
        // Displays both player and enemy stats at the start of battle.
        player.DisplayPlayerStats();
        enemy.DisplayEnemyStats();

        bool transformed = false;
        while (player.health > 0 && enemy.health > 0) {

            StartBattle(delay1, player, enemy, playerName, character, transformed, hando);

            if (player.health <= 0) {
                if (enemy.enemyName == "\033[31mPossessed Astronaut\033[0m") {
                    std::string astronautKill = "\n\nThe " + enemy.enemyName + "'s helmet twisted off, revealing a ghoulish, rotting face which opened its mouth wide, biting off " + playerName + "'s face.";
                    Stagger(astronautKill, delay1);
                    Stagger(GAMEOVER, delay2);
                    // Ends the game.
                    exit(0);
                }
                else if (enemy.enemyName == "\033[31mCentimane\033[0m") {
                    std::string centimaneKill = "\n\nThe " + enemy.enemyName + " grabbed hold of our hero's limbs; twisting and popping them until " + playerName + " was no more.";
                    Stagger(centimaneKill, delay1);
                    Stagger(GAMEOVER, delay2);
                    // Ends the game.
                    exit(0);
                }
                else if (enemy.enemyName == "\033[31mFeral Ape\033[0m") {
                    std::string apeKill1 = "\n\nThe " + enemy.enemyName + " jumped onto " + playerName + ", only to then separate each limb one by one.";
                    Stagger(apeKill1, delay1);
                    Stagger(GAMEOVER, delay2);
                    // Ends the game.
                    exit(0);
                }
            }
        }
    }
    if (bali == true) {
        stopMusic();
        startMusic("C:\\Programming\\C++ Games\\LowLife\\LowLifeMusic\\miniBoss.wav");
        Enemy enemy;
        enemy.GenerateBali(playerName);

        // Commences battle events.
        std::string battle1 = "\n\n" + playerName + " now faced " + enemy.enemyName + "!";
        Stagger(battle1, delay1);
        // Displays both player and enemy stats at the start of battle.
        player.DisplayPlayerStats();
        enemy.DisplayEnemyStats();

        bool transformed = false;
        while (player.health > 0 && enemy.health > 0) {
            StartBattle(delay1, player, enemy, playerName, character, transformed, hando);

            if (player.health <= 0) {
                std::string baliKill1 = "\n\nBali soon gained the upper hand, catching " + playerName + " off-guard, disintegrating them with a final blast of lightning";
                Stagger(baliKill1, delay1);
                Stagger(GAMEOVER, delay2);
                // Ends the game.
                exit(0);
            }
        }
    }
    if (tonobros == true) {
        stopMusic();
        startMusic("C:\\Programming\\C++ Games\\LowLife\\LowLifeMusic\\battle_music3.wav");
        Enemy enemy;
        enemy.GenerateTonobros(playerName);

        // Commences battle events.
        std::string battle1 = "\n\n" + playerName + " was now face to face with the manifestation of darkness itself, " + enemy.enemyName + "!";
        Stagger(battle1, delay1);
        // Displays both player and enemy stats at the start of battle.
        player.DisplayPlayerStats();
        enemy.DisplayEnemyStats();

        bool transformed = false;
        while (player.health > 0 && enemy.health > 0) {
            // initialises a battle for player with Bali's head moves.
            if (player.headCount >= 1) {
                StartBattle(delay1, player, enemy, playerName, character, transformed, hando);
            }
            else if (player.ectoplasmCount >= 1) {
                StartBattle(delay1, player, enemy, playerName, character, transformed, hando);
            }
            if (player.health <= 0) {
                std::string tonobrosKill1 = "\n\n" + playerName + " was seen as a simple meatsack in " + enemy.enemyName + "'s souless eyes...";
                Stagger(tonobrosKill1, delay1);
                std::string tonobrosKill2 = "\n\nWith a final stretch of its arms, the god grabbed hold of and crushed " + playerName + ", causing their eyes to pop out of their head and their limbs to severe...";
                Stagger(tonobrosKill2, delay1);
                std::string tonobrosKill3 = "\n\nAll that was left of " + playerName + " was a red stain on the floor.";
                Stagger(tonobrosKill3, delay1);
                Stagger(GAMEOVER, delay2);
                // Ends the game.
                exit(0);
            }
        }
    }
}
class NPC {
public:
    // Parent constructors.
    std::string name;
    std::string dialogue;

    // Parent methods.
    NPC(const std::string& name, const std::string& dialogue)
        : name(name), dialogue(dialogue) {}

    void HermitDialogue(std::string &playerName, bool &spokenToHermit, bool tonobros) const {
        if (spokenToHermit == false) {
            std::string hermitsPlayerName;
            std::string hermit1 = "\n" + playerName + " asked the hermit about the mountain...";
            std::string hermit2 = "\nOh hello! I didn't see yer wee-self over on those rocks.";
            std::string hermit3 = "\nI should really introduce miself...I am \033[33mKroka\033[0m of House Kruuka!";
            std::string hermit4 = "\nAnd yer go by..?";
            std::string hermit5 = "\nHow excellent to meet yer " + hermitsPlayerName + "! I was just on mi way to fish for the day...";
            std::string hermit6 = "\nBut I dun't wanna bore yer. I noticed yer were staring at the \033[33mGreat Boruna\033[0m - the portal between worlds!";
            std::string hermit7 = "\nIf yer were considering to enter that portal yer'd need an \033[33mInter-realm Spacesuit\033[0m to survive in there...";
            Stagger(hermit1, delay1);
            DisplayPhotoInNewWindow("C:\\Programming\\C++ Games\\LowLife\\LowLifePhotos\\Hermit.jpeg", "Kroka, The Content Dwarf");
            Stagger(hermit2, delay1);
            Stagger(hermit3, delay1);
            Stagger(hermit4, delay1);
            std::cout << "\n> ";
            std::getline(std::cin, hermitsPlayerName);
            Stagger(hermit5, delay1);
            Stagger(hermit6, delay1);
            Stagger(hermit7, delay1);
            spokenToHermit = true;
        }
        else {
            std::string error1 = "\nThe hermit must've gone fishing...";
            Stagger(error1, delay1);
        }
    }
    void GhostBoyDialogue(std::string& playerName, bool &spokenToFilia, bool tonobros) const {
        if (spokenToFilia == false) {
            std::string boy1 = "\n" + playerName + " asked the \033[33mboy-ghost\033[0m about the castle...";
            std::string boy2 = "\nAre you here to steal from us again?";
            std::string boy3 = "\nEver since that portal was opened, lowlives like you come to our house to take what you think is yours.";
            std::string boy4 = "\nPlease just leave us alone!";
            Stagger(boy1, delay1);
            DisplayPhotoInNewWindow("C:\\Programming\\C++ Games\\LowLife\\LowLifePhotos\\GhostBoy.jpeg", "Filia, The Ghost-Child");
            Stagger(boy2, delay1);
            Stagger(boy3, delay1);
            Stagger(boy4, delay1);
            spokenToFilia = true;
        }
        else {
            DisplayPhotoInNewWindow("C:\\Programming\\C++ Games\\LowLife\\LowLifePhotos\\GhostBoy.jpeg", "Filia, The Ghost-Child");
            std::string boy5 = "\n\033[33mFilia\033[0m stood, crying.";
            Stagger(boy5, delay1);
        }
    }
    void RottenPigmanDialogue(std::string& playerName, int delay1, Player& player, std::string character, bool randomEnemy, bool avis, bool pigman, bool bali, bool &spokenToGorkan, bool tonobros) const {
        if (spokenToGorkan == false) {
            std::string gorkan1 = "\n" + playerName + " drew their weapon as the pigman charged towards them!";
            Stagger(gorkan1, delay1);
            DisplayPhotoInNewWindow("C:\\Programming\\C++ Games\\LowLife\\LowLifePhotos\\Pigman.jpeg", "Gorkan, The Rotten Pigman");

            // Initialises special battle against Gorkan.
            pigman = true;
            InitialiseBattle(delay1, player, playerName, character, randomEnemy = false, avis = false, pigman = true, bali = false, tonobros = false);
            stopMusic();
            startMusic("C:\\Programming\\C++ Games\\LowLife\\LowLifeMusic\\travel.wav");

            std::string gorkan2 = "\nAfter all these years of waiting, My old fighting spirit is no more.";
            Stagger(gorkan2, delay1);
            std::string gorkan3 = "\nIt would not be wise to say you are a LowLife, " + character + ". You have a higher purpose in this ruined land...";
            Stagger(gorkan3, delay1);
            std::string gorkan4 = "\nAlthough the stories of heros are long dead, I believe you could be significant in re-establishing the \033[33mMoranthian Order\033[0m in this land and that wretched other.";
            Stagger(gorkan4, delay1);
            while (true) {
                std::string gorkan5 = "\nWhat do you say fearless one?";
                Stagger(gorkan5, delay1);
                std::string choice;
                std::cout << "\nAgree | Disagree";
                std::cout << "\n> ";
                std::getline(std::cin, choice);

                if (choice == "Agree" || choice == "agree") {
                    std::string gorkan6 = "\nWell chosen.";
                    Stagger(gorkan6, delay1);
                    std::string gorkan7 = "\nNorth-East of here, you'll find the \033[31mGreat Boruna\033[0m - a portal between worlds. It'll take you to a land of stars and wonder...";
                    Stagger(gorkan7, delay1);
                    std::string gorkan8 = "\nBut do not be fooled, monsters exist there to make you their slave.";
                    Stagger(gorkan8, delay1);
                    std::string gorkan9 = "\nTake this inter-realm spacesuit. You deserve it more than I do.\nYou may need more than just a spacesuit to get around that place...";
                    Stagger(gorkan9, delay1);
                    std::string gorkan10 = "\nFarewell, fearless one!";
                    Stagger(gorkan10, delay1);
                    player.AddSpaceSuitToInventory();
                    break;
                }
                else {
                    std::string gorkan11 = "\nI think you should rethink your choice...";
                    Stagger(gorkan11, delay1);
                }
            }
        }
        else {
            std::string gorkan12 = "\nWhen you cross \033[33mBoruna\033[0m, beware of the \033[31mKhan\033[0m and \033[31mTonobros\033[0m, the creature that dwells in the land of woe.";
            Stagger(gorkan12, delay1);
        }
    }
    void LordBaliDialogue(std::string& playerName, int delay1, Player& player, std::string character, bool randomEnemy, bool avis, bool pigman, bool bali, bool &spokenToBali, bool tonobros) const {
        if (spokenToBali == false) {
            std::string bali1 = "\nAs the blue lady started to speak, An android voice boomed over the palace room...";
            Stagger(bali1, delay1);
            std::string bali2 = "\nThe thousands of worshippers fell to their feet; their heads shaking violently.";
            Stagger(bali2, delay1);
            DisplayPhotoInNewWindow("C:\\Programming\\C++ Games\\LowLife\\LowLifePhotos\\LordBali.jpeg", "Lord Bali, Khan of the Kaltorna Galaxy");
            while (true) {
                std::string bali3 = "\nWhy does this LowLife come to me?";
                Stagger(bali3, delay1);
                std::string choice1;
                std::cout << "\nToFight | ToSubmit | ToBargain";
                std::cout << "\n> ";
                std::getline(std::cin, choice1);

                if (choice1 == "ToFight" || choice1 == "Tofight" || choice1 == "tofight") {
                    std::string bali4 = "\nIf that is your choice LowLife - so be it.";
                    Stagger(bali4, delay1);
                    std::string bali5 = "\nThe floor dropped beneath " + playerName + ", dropping them onto a platform; shrouded in red mist and lava...\n\n";
                    Stagger(bali5, delay1);

                    DisplayPhotoInNewWindow("C:\\Programming\\C++ Games\\LowLife\\LowLifePhotos\\LordBali3.jpeg", "Lord Bali, Khan of the Kaltorna Galaxy");

                    // Initialises special battle against Lord Bali.
                    bali = true;
                    InitialiseBattle(delay1, player, playerName, character, randomEnemy = false, avis = false, pigman = false, bali = true, tonobros = false);
                    stopMusic();
                    startMusic("C:\\Programming\\C++ Games\\LowLife\\LowLifeMusic\\travel.wav");

                    // Gives Bali's head to the player (for use in final battle).
                    player.AddBalisHeadToInventory();

                    std::string bali6 = "\nUsing \033[31mLord Bali\033[0m's head as a symbol of fear, " + playerName + " marched out of the palace to complete their quest and destroy \033[31mTonobros\033[0m, the manifestation of the Darkness itelf...";
                    Stagger(bali6, delay1);
                    break;
                }
                else if (choice1 == "ToSubmit" || choice1 == "Tosubmit" || choice1 == "tosubmit") {
                    std::string bali7 = "\nHow noble of you LowLife. You are smarter than most who come knocking at my door...";
                    Stagger(bali7, delay1);
                    std::string bali8 = "\nFrom now on you are mine...";
                    Stagger(bali8, delay1);
                    std::string bali9 = "\nYou will soon be blinded, bounding your life to worshipping me as a god...";
                    Stagger(bali9, delay1);
                    Sleep_1s();
                    std::string bali10 = "\nLet us begin.";
                    Stagger(bali10, delay1);
                    Stagger(GAMEOVER, delay2);
                    exit(0);
                }
                else if (choice1 == "ToBargain" || choice1 == "Tobargain" || choice1 == "tobargain") {
                    std::string bali11 = "\nThere is only one thing I want from Moranthia...\033[33mMera's Glowth\033[0m!";
                    Stagger(bali11, delay1);
                    while (true) {
                        std::string bali12 = "\nDo you have it LowLife?";
                        Stagger(bali12, delay1);
                        std::string choice2;
                        std::cout << "\nYes | No";
                        std::cout << "\n> ";
                        std::getline(std::cin, choice2);
                        if (choice2 == "Yes" || choice2 == "yes") {
                            std::string bali13 = "\nYou are brave, LowLife. Perhaps you are brave enough to fight \033[31mTonobros\033[0m haha?";
                            Stagger(bali13, delay1);
                            std::string bali14 = "\nIf you travel to the planet of \033[33mValdestrone\033[0m, you will find a great pyramid, shrouded in darkness.";
                            Stagger(bali14, delay1);
                            std::string bali15 = "\nhere, take this fresh ectoplasm - absorbed from a Boy-ghost - and good luck LowLife...You will need it.";
                            Stagger(bali15, delay1);
                            player.AddEctoplasmToInventory();
                            return;
                        }
                        else if (choice2 == "No" || choice2 == "no") {
                            std::string bali16 = "\nReturn to me when you have the goddess' prized possession.";
                            Stagger(bali16, delay1);
                            return;
                        }
                        else {
                            std::string bali17 = "\nLet me ask you again...and be honest this time.";
                            Stagger(bali17, delay1);
                        }
                    }
                }
            }
        }
        else {
            std::string bali18 = "The blue lady repeated to " + playerName + " where \033[31mTonobros\033[0m resided.";
            Stagger(bali18, delay1);
        }
    }
    void CowboyDialogue(std::string& playerName, int delay1, Player& player, std::string character, bool randomEnemy, bool avis, bool pigman, bool bali, bool& spokenToCowboy, bool tonobros) const {
        if (spokenToCowboy == false) {
            std::string hando1 = "\nA battle-damaged stranger, riding some kind of reptile, bound towards " + playerName;
            Stagger(hando1, delay1);
            DisplayPhotoInNewWindow("C:\\Programming\\C++ Games\\LowLife\\LowLifePhotos\\ManOnDino.jpeg", "Hando, The Lone Explorer");

            std::string hando2 = "\nHow you doin' son?";
            Stagger(hando2, delay1);
            std::string reply;
            std::cout << "\n> ";
            std::getline(std::cin, reply);
            std::string hando3 = "\nHaha sounds like you're doing well...";
            Stagger(hando3, delay1);
            std::string hando4 = "\nLook son, I'm being chased...I stole the \033[31mAvis\033[0m' eggs, so we better run...NOW.";
            Stagger(hando4, delay1);
            std::string hando5 = "\nOh hell, its too late...its found us!";
            Stagger(hando5, delay1);
            DisplayPhotoInNewWindow("C:\\Programming\\C++ Games\\LowLife\\LowLifePhotos\\DesertBird.jpeg", "The Great Vermilion Avis");

            // Initialises special battle against the Avis.
            avis = true;
            InitialiseBattle(delay1, player, playerName, character, randomEnemy = false, avis = true, pigman = false, bali = false, tonobros = false);
            stopMusic();
            startMusic("C:\\Programming\\C++ Games\\LowLife\\LowLifeMusic\\travel.wav");

            std::string hando6 = "\nThanks son for the assist...";
            Stagger(hando6, delay1);
            std::string hando7 = "\nYou deserve some pennys from that robbery I did - here. Take these, it can only be used in the \033[33mKaltorna System\033[0m, its the least I owe you.";
            Stagger(hando7, delay1);
            player.AddCoinToInventory();
            std::string hando8 = "\nTake care son...";
            Stagger(hando8, delay1);
            std::string hando9 = "\nThe stranger then proceeded to bound into the sunset.";
            Stagger(hando9, delay1);
            spokenToCowboy = true;
        }
        else {
            std::string hando10 = "\nAll " + playerName + " saw in the clearing was the carcass of the \033[31mGreat Vermilion Avis\033[0m.\nA group of goblins were looting the body";
            Stagger(hando10, delay1);
        }
    }
    void TonobrosDialogue(std::string& playerName, int delay1, Player& player, std::string character, bool randomEnemy, bool avis, bool pigman, bool bali, bool& spokenToTonobros, bool tonobros) const {
        if (spokenToTonobros == false) {
            if (player.headCount > 0 || player.ectoplasmCount > 0) {
                std::string tonobros1 = "\nThe black, simmering figure let " + playerName + " past...";
                std::string tonobros2 = "\nThe so-called LowLife had gotten further than most knights, wizards or creatures had in destroying the Darkness once and for all...";
                std::string tonobros3 = "\nBy the time " + playerName + " had reached the foot of the pyramid, the Darkness was thicker than any fog they had experienced...";
                std::string tonobros4 = "\nBut this did not stop them from entering the foreboding structure...";
                std::string tonobros5 = "\nThe sliding doors quickly shut behind " + playerName + ", leaving them in pure, unbounded darkness.";
                Stagger(tonobros1, delay1);
                Stagger(tonobros2, delay1);
                Stagger(tonobros3, delay1);
                Stagger(tonobros4, delay1);
                Stagger(tonobros5, delay1);
                Sleep_1s();
                std::string tonobros6 = "\nHow was your adventure LowLife?";
                std::string tonobros7 = "\nWas every miserable, rotten creature in this land as terrible as i said?";
                std::string tonobros8 = "\n" + playerName + " instantly recognised the voice...it belonged to whatever creature dropped them into this place!";
                std::string tonobros9 = "\nThey drew their weapon in the hopes to rid Moranthia and Kaltorna of the evil before them.";
                std::string tonobros10 = "\nVery well LowLife, you will join the rest of the so-called heros...";
                std::string tonobros11 = "\nThe darkness in the air shifted and accumulated into a horrific sight...\033[31mTonobros\033[0m! The Destroyer of Worlds!!!\n\n";
                Stagger(tonobros6, delay1);
                Stagger(tonobros7, delay1);
                Stagger(tonobros8, delay1);
                Stagger(tonobros9, delay1);
                Stagger(tonobros10, delay1);
                Stagger(tonobros11, delay1);
                DisplayPhotoInNewWindow("C:\\Programming\\C++ Games\\LowLife\\LowLifePhotos\\Boss.jpeg", "Tonobros, The Devourer of Worlds");
                InitialiseBattle(delay1, player, playerName, character, randomEnemy = false, avis = false, pigman = false, bali = false, tonobros = true);
                spokenToTonobros = true;

                // Instantiates the end of the game.
                if (player.headCount > 0 && player.darkness >= 60) {
                    startMusic("C:\\Programming\\C++ Games\\LowLife\\LowLifeMusic\\Finale.wav");
                    std::string tonobros12 = "\n" + playerName + ", left exhausted, bitter and disgusted by their experience in these worlds, grew into a fit of rage...";
                    Stagger(tonobros12, delay1);
                    std::string tonobros13 = "\n" + playerName + " kicked the now diminished \033[31mTonobros\033[0m onto the cold, crystal floor...ready to rid the world of the darkness...";
                    Stagger(tonobros13, delay1);
                    std::string tonobros14 = "\nThey brutally grabbed hold of \033[31mTonobros\033[0m' heart - the centre of his power - and pulled it out...";
                    Stagger(tonobros14, delay1);
                    Sleep_1s();
                    std::string tonobros15 = "\nThe great room was suddenly dazzling with colours. But at what cost?";
                    Stagger(tonobros15, delay1);
                    DisplayPhotoInNewWindow("C:\\Programming\\C++ Games\\LowLife\\LowLifePhotos\\End3.jpeg", " ");
                    DisplayPhotoInNewWindow("C:\\Programming\\C++ Games\\LowLife\\LowLifePhotos\\End2.jpeg", " ");
                    std::string tonobros16 = "\nBy stealing the heart of \033[31mTonobros\033[0m, " + playerName + " had passed on the power to themselves thus, destroying it, but disinegrating themselves in the process...";
                    Stagger(tonobros16, delay1);
                    std::string tonobros17 = "\nAlthough the creature was gone, " + playerName + " had made the ultimate sacrifice to save the realm.";
                    Stagger(tonobros17, delay1);
                    std::string tonobros18 = "\nAnd that is how the stories will portay them...a fearless, unforgiving...LowLife.";
                    Stagger(tonobros18, delay1);
                    // Ends the game.
                    Credits(delay2);
                }
                else {
                    startMusic("C:\\Programming\\C++ Games\\LowLife\\LowLifeMusic\\Finale.wav");
                    std::string tonobros19 = "\nWith a sudden hesitation from \033[31mTonobros\033[0m, " + playerName + " was able to gain the upper hand and strike a final blow against the heart of the beings power...his blue heart!";
                    Stagger(tonobros19, delay1);
                    std::string tonobros20 = "\n\033[31mTonobros\033[0m howled in surprise as the darkness that formed him crumbled onto the cold, crystal floor.";
                    Stagger(tonobros20, delay1);
                    std::string tonobros21 = "\n" + playerName + "'s journey was complete. The hero gleamed in delight as the darkness around them turned to dazzling light.";
                    Stagger(tonobros21, delay1);
                    Sleep_1s();
                    std::string tonobros22 = "\nOne month later...";
                    Stagger(tonobros22, delay1);
                    Sleep_1s();
                    DisplayPhotoInNewWindow("C:\\Programming\\C++ Games\\LowLife\\LowLifePhotos\\End6.jpeg", " ");
                    std::string tonobros23 = "\n" + playerName + " was proclaimed into the \033[31mMoranthian Order\033[0m - which dedicated itself to form a union between the Moranthians and Kaltornans.";
                    Stagger(tonobros23, delay1);
                    DisplayPhotoInNewWindow("C:\\Programming\\C++ Games\\LowLife\\LowLifePhotos\\End5.jpeg", " ");
                    std::string tonobros24 = "\nWithout the Darkness in the realm, the two worlds saw a new age ahead of them.";
                    Stagger(tonobros24, delay1);
                    Credits(delay1);
                }
            }
            else {
                std::string tonobros25 = "\nThe black, simmering figure rejected " + playerName + "'s request to enter...";
                Stagger(tonobros25, delay1);
            }
        }
        else {
            std::string tonobros26 = "\nThe great pyramid shone bright under the galaxy's nearby stars.";
            Stagger(tonobros26, delay1);
        }
    }
};
void PilotDialogue(std::string& playerName, int delay1, Player& player, std::string character, bool randomEnemy, bool avis, bool pigman, bool bali, bool& spokenToPilot, bool tonobros) {
    if (spokenToPilot == false) {
        std::string pilot1 = "\nBefore " + playerName + " could make a move, an armoured soldier yelled: HALT LOWLIFE!";
        Stagger(pilot1, delay1);
        DisplayPhotoInNewWindow("C:\\Programming\\C++ Games\\LowLife\\LowLifePhotos\\pilot.jpeg", "Hank, Some Border Control Officer");
        if (player.coinCount > 0) {
            std::string pilot2 = "\nThe pilot quickly realised " + playerName + " was no monster - he was relieved. The LowLife showed their coins...";
            Stagger(pilot2, delay1);
            std::string pilot3 = "\nYou haven't got enough to reach the closest city of Medrina, but I'll get Brank to drop you off at either Bali's Plateau if you'd like? \033[33mOr\033[0m, you could simply offer your life in \033[33mValdestrone\033[0m.";
            Stagger(pilot3, delay1);
            std::string pilot4 = "\nHope I see you again, LowLife...";
            Stagger(pilot4, delay1);
            spokenToPilot = true;
        }
        else {
            std::string pilot5 = "\nThe pilot quickly realised " + playerName + " was no monster - he was relieved.";
            Stagger(pilot5, delay1);
            std::string pilot6 = "\n Looks like you got no coins on you...";
            Stagger(pilot6, delay1);
            std::string pilot7 = "\nYou better turn round NOW, before you're executed LowLife...";
            Stagger(pilot7, delay1);
        }
    }
    else {
        std::string pilot8 = "\nYou're back! Knew I'd see you again!";
        Stagger(pilot8, delay1);
    }
}
class Item {
public:
    std::string name;
    std::string description;

    Item(const std::string& name, const std::string& description)
        : name(name), description(description) {}
};
class Region {
public:
    // Variables.
    std::string name;
    std::string description;
    std::vector<Item> items;
    std::vector<NPC> npcs;

    // Initialises the name and description string variables.
    Region(const std::string& name, const std::string& description)
        : name(name), description(description) {}

    // Describes what items and people are in this area.
    void describe() const {
        std::cout << "\n\nYou are in " << name << ". " << description << "\n";
        if (!items.empty()) {
            for (const auto& item : items) {
                std::cout << item.name << " ";
            }
            std::cout << "\n";
        }
        if (!npcs.empty()) {
            for (const auto& person : npcs) {
                std::cout << person.name << " ";
            }
            std::cout << "\n";
        }
    }

    void addItem(const Item& item) {
        // Adds Item objects to items vector.
        items.push_back(item);
    }

    void addPerson(const NPC& npc) {
        // Adds NPC objects to npcs vector.
        npcs.push_back(npc);
    }

    void examineItem(const std::string& itemName, Player &player) const {
        for (const auto& item : items) {
            if (item.name == itemName) {
                if (item.name == "Mera's Glowth") {
                    player.AddMerasGlowthToInventory();
                }
                return;
            }
        }
        std::cout << "\nThere is no " << itemName << " here.\n";
    }

    void talkToPerson(const std::string& personName, Player &player, std::string character, bool randomEnemy, bool avis, bool pigman, bool bali, bool tonobros) const {
        for (const auto& person : npcs) {
            if (person.name == person.name) {
                if (person.name == "Boy-ghost") {
                    person.GhostBoyDialogue(playerName, spokenToFilia, tonobros);
                }
                else if (person.name == "Hermit") {
                    person.HermitDialogue(playerName, spokenToHermit, tonobros);
                }
                else if (person.name == "Rotten Pigman") {
                    person.RottenPigmanDialogue(playerName, delay1, player, character, randomEnemy, avis, pigman, bali, spokenToGorkan, tonobros);
                }
                else if (person.name == "Rider") {
                    person.CowboyDialogue(playerName, delay1, player, character, randomEnemy, avis, pigman, bali, spokenToCowboy, tonobros);
                }
                else if (person.name == "Starship pilot") {
                    PilotDialogue(playerName, delay1, player, character, randomEnemy, avis, pigman, bali, spokenToPilot, tonobros);
                }
                else if (person.name == "Blue Lady") {
                    person.LordBaliDialogue(playerName, delay1, player, character, randomEnemy, avis, pigman, bali, spokenToBali, tonobros);
                }
                else if (person.name == "Black figure") {
                    person.TonobrosDialogue(playerName, delay1, player, character, randomEnemy, avis, pigman, bali, spokenToBali, tonobros);
                }
            }
            else {
                std::cout << "\n\033[90mInvalid name. Please enter a real dude.\033[0m\n";
            }
        }
    }
};
class Map {
private:
    // Vector (named areas) takes in a vector of objects of class Area (2D Vector)
    std::vector<std::vector<Region>> regions;
public:
    // Sets variables for class.
    int currentRow;
    int currentCol;

    Map(int rows, int cols)
        // For each row, a vector of Area objects is created with cols number (of elements). Each Area object is then initialised with a generic name and description ('Unknown').
        : regions(rows, std::vector<Region>(cols, Region("Unknown", "An unknown area."))),
        // Sets the current rows and col elements to 0.
        currentRow(1), currentCol(1) {}

    void setArea(int row, int col, const Region& area) {
        // Initialises an Area object for each position in the 2D vector.
        if (row >= 0 && row < regions.size() && col >= 0 && col < regions[row].size()) {
            regions[row][col] = area;
        }
    }

    void AddNPCToArea(int row, int col, const NPC& npc) {
        if (row >= 0 && row < regions.size() && col >= 0 && col < regions[row].size()) {
            regions[row][col].addPerson(npc);
        }
    }

    // rowOffset and colOffset are automatically defined in this parameter as int values (so can be used to increase/decrease currentRow/currentCol.
    void move(Player& player, int rowOffset, int colOffset) {
        int newRow = currentRow + rowOffset;
        int newCol = currentCol + colOffset;

        if (PreventRegionEntry(player, currentRow, currentCol, newRow, newCol)) {
            return;
        }

        // Updates the newRow as the currentRow (so long as they are within the Map size).
        if (newRow >= 0 && newRow < regions.size() && newCol >= 0 && newCol < regions[newRow].size()) {
            currentRow = newRow;
            currentCol = newCol;
        }
        if (PrintImageWhenEnteringRegion(newRow, newCol)) {
        }
        else {
            std::cout << "\n\033[90mYou cannot move in that direction.\033[0m\n";
        }
    }

    void describeCurrentArea() const {
        regions[currentRow][currentCol].describe();
    }

    void displayOptions() const {
        std::cout << "\n\033[97mYour Choice:\033[0m";
        std::cout << "\n\033[97m - North\033[0m";
        std::cout << "\n\033[97m - East\033[0m";
        std::cout << "\n\033[97m - South\033[0m";
        std::cout << "\n\033[97m - West\033[0m";
        std::cout << "\n\033[97m - Examine (Item)\033[0m";
        std::cout << "\n\033[97m - Talk (to Person)\033[0m";
        std::cout << "\n\033[97m - (View) Inventory\033[0m";
        std::cout << "\n\033[97m - Quit\033[0m";
    }

    void examineItem(const std::string& itemName, Player& player) const {
        regions[currentRow][currentCol].examineItem(itemName, player);
    }

    void talkToPerson(const std::string& personName, Player& player, std::string character, bool randomEnemy, bool avis, bool pigman, bool bali, bool tonobros) const {
        regions[currentRow][currentCol].talkToPerson(personName, player, character, randomEnemy, avis, pigman, bali, tonobros);
    }

    void CallRandomBattle(Player &player) {
        srand(time(NULL));
        int random = rand() % 6 + 1;
        if (random == 1) {
            randomEnemy = true;
            InitialiseBattle(delay1, player, playerName, character, randomEnemy, avis, pigman, bali, tonobros);
        }
    }

    bool PrintImageWhenEnteringRegion(int newRow, int newCol) {
        if (newRow == 0 && newCol == 0) {
            DisplayPhotoInNewWindow("C:\\Programming\\C++ Games\\LowLife\\LowLifePhotos\\Mushrooms.jpeg", " ");
            return true;
        }
        if (newRow == 0 && newCol == 1) {
            DisplayPhotoInNewWindow("C:\\Programming\\C++ Games\\LowLife\\LowLifePhotos\\Desert2.jpeg", " ");
            return true;
        }
        if (newRow == 0 && newCol == 3) {
            DisplayPhotoInNewWindow("C:\\Programming\\C++ Games\\LowLife\\LowLifePhotos\\Palace.jpeg", " ");
            return true;
        }
        if (newRow == 1 && newCol == 0) {
            DisplayPhotoInNewWindow("C:\\Programming\\C++ Games\\LowLife\\LowLifePhotos\\BlueForest.jpeg", " ");
            return true;
        }
        if (newRow == 1 && newCol == 1) {
            DisplayPhotoInNewWindow("C:\\Programming\\C++ Games\\LowLife\\LowLifePhotos\\Ravine.jpeg", " ");
            return true;
        }
        if (newRow == 1 && newCol == 2) {
            DisplayPhotoInNewWindow("C:\\Programming\\C++ Games\\LowLife\\LowLifePhotos\\Portal2.jpeg", " ");
            return true;
        }
        if (newRow == 1 && newCol == 3) {
            DisplayPhotoInNewWindow("C:\\Programming\\C++ Games\\LowLife\\LowLifePhotos\\Station2.jpeg", " ");
            return true;
        }
        if (newRow == 2 && newCol == 0) {
            DisplayPhotoInNewWindow("C:\\Programming\\C++ Games\\LowLife\\LowLifePhotos\\ForestRuins.jpeg", " ");
            return true;
        }
        if (newRow == 2 && newCol == 1) {
            DisplayPhotoInNewWindow("C:\\Programming\\C++ Games\\LowLife\\LowLifePhotos\\Forest.jpeg", " ");
            return true;
        }
        if (newRow == 2 && newCol == 3) {
            DisplayPhotoInNewWindow("C:\\Programming\\C++ Games\\LowLife\\LowLifePhotos\\Pyramid.jpeg", " ");
            return true;
        }
    }

    bool PreventRegionEntry(Player& player, int currentRow, int currentCol, int newRow, int newCol) const {
        if (player.spaceSuitCount == 0 && newRow == 1 && newCol == 3) {
            std::cout << "\n\n\033[90mYou need an inter-realm spacesuit to enter the portal...";
            return true;// Exits the function, effectively preventing entry to the region.
        }
        // When the player passes through Boruna, they're immediately questioned by Hank.
        else if (newRow == 1 && newCol == 3) {
            PilotDialogue(playerName, delay1, player, character, randomEnemy, avis, pigman, bali, spokenToPilot, tonobros);
            return false; // Allows player to stay in this region.
        }
        else if (player.coinCount == 0 && newRow == 0 && newCol == 3) {
            std::cout << "\n\033[90mYou cannot afford to go this way.\033[0m";
            return true;
        }
        else if (player.coinCount == 0 && newRow == 2 && newCol == 3) {
            std::cout << "\n\033[90mYou cannot afford to go this way.\033[0m";
            return true;
        }
        else if (newRow == 0 && newCol == 2 || newRow == 2 && newCol == 2) {
            std::cout << "\n\033[90mYou cannot go this way.\033[0m";
            return true;
        }
        else if (currentRow == 1 && currentCol == 1 && newRow == 0 && newCol == 1) {
            std::cout << "\n\033[90mYou cannot go this way.\033[0m";
            return true;
        }
        else if (currentRow == 0 && currentCol == 1 && newRow == 0 && newCol == 2) {
            std::cout << "\n\033[90mYou cannot go this way.\033[0m";
            return true;
        }
        else if (currentRow == 0 && currentCol == 1 && newRow == 1 && newCol == 1) {
            std::cout << "\n\033[90mYou cannot go this way.\033[0m";
            return true;
        }
        else if (currentRow == 1 && currentCol == 2 && newRow == 0 && newCol == 2) {
            std::cout << "\n\033[90mYou cannot go this way.\033[0m";
            return true;
        }
        else if (currentRow == 1 && currentCol == 2 && newRow == 2 && newCol == 2) {
            std::cout << "\n\033[90mYou cannot go this way.\033[0m";
            return true;
        }
        else if (currentRow == 1 && currentCol == 1 && newRow == 2 && newCol == 1) {
            std::cout << "\n\033[90mYou cannot go this way.\033[0m";
            return true;
        }
        else if (currentRow == 2 && currentCol == 1 && newRow == 1 && newCol == 1) {
            std::cout << "\n\033[90mYou cannot go this way.\033[0m";
            return true;
        }
        else {
            std::string enter1 = "\n\033[90mEntering the region...";
            Stagger(enter1, delay1);
            return false;
        }
    }
};

// ----------GameChronology----------
void PreText(bool bold, int delay3) {
    std::cout << "\033[90m --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\033[0m\n\n";
    std::string preText1 = "\033[90m   Some info before you play...\033[0m\n\n";
    std::string preText2 = "\033[90m - LowLife is a dark fantasy and science-fiction text-based RPG.\033[0m\n\n";
    std::string preText3 = "\033[90m - The game is set in a realm of both fantasy and science-fiction, the result of a portal being opened sometime during Moranthia's Third Age.\033[0m\n\n";
    std::string preText4 = "\033[90m - The aim of the game is for you to defeat Tonobros - the manifestation of the Darkness that has polluted the realm since the portal was opened.\033[0m\n\n";
    std::string preText5 = "\033[90m - From the start, you can choose to be either a wizard, astronomer or beast - generating unique moves when in battle.\033[0m\n\n";
    std::string preText6 = "\033[90m - You can navigate through the world (dependant on the items you have in your inventory) by typing the direction you'd like to travel in.\033[0m\n\n";
    std::string preText7 = "\033[90m - There's a chance you will be ambushed as you make your way through the realm. There are 4 bosses to overcome.\033[0m\n\n";
    std::string preText8 = "\033[90m - During the battles, you have a powerful move however, using it will increase your darkness stat (depending on how much darkness the enemy has). Once you reach 100 darkness, you will be consumed by it.\033[0m\n\n";
    std::string preText9 = "\033[90m - There are 2 endings in the game - which are dependant on your darkness when fighting Tonobros and what choice you make with Lord Bali.\033[0m\n\n";

    Stagger(preText1, delay3);
    Stagger(preText2, delay3);
    Stagger(preText3, delay3);
    Stagger(preText4, delay3);
    Stagger(preText5, delay3);
    Stagger(preText6, delay3);
    Stagger(preText7, delay3);
    Stagger(preText8, delay3);
    Stagger(preText9, delay3);
    std::cout << "\033[90m  ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\033[0m\n\n";
}
void TitleScreen(bool bold, int delay1) {
    std::string title1 = "\n\033[31m                                           .___     ._______           ___ .___    .___ ._______._______\033[0m";
    std::string title2 = "\n\033[31m                                           |   |    : .___  \\ .___    |   ||   |   : __|:_ ____/: .____/\033[0m";
    std::string title3 = "\n\033[31m                                           |   |    | :   |  |:   | /\\|   ||   |   | : ||   _/  | : _/\\ \033[0m";
    std::string title4 = "\n\033[31m                                           |   |/\\  |     :  ||   |/  :   ||   |/\\ |   ||   |   |   /  \\ \033[0m";
    std::string title5 = "\n\033[31m                                           |   /  \\  \\_. ___/ |   /       ||   /  \\|   ||_. |   |_.: __/\033[0m";
    std::string title6 = "\n\033[31m                                           |______/    :/     |______/|___||______/|___|  :/       :/   \033[0m";
    std::string title7 = "\n\033[31m                                                       :              :                   :            \033[0m";
    std::string title8 = "\n\033[31m                                                                      :                                \033[0m";

    // Prints out the ASCII title in red text.
    Stagger(title1, bold);
    Stagger(title2, bold);
    Stagger(title3, bold);
    Stagger(title4, bold);
    Stagger(title5, bold);
    Stagger(title6, bold);
    Stagger(title7, bold);
    Stagger(title8, bold);

    // Prints out player prompt.
    std::string title9 = "\n\n                                                           Press any button to play...";
    Stagger(title9, delay1);
    
    // Waits for any user input.
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
void Prologue(bool bold, int delay1, int delay2)
{
    // Highlighted red words.
    std::string moranthia = "\033[31mMoranthia\033[0m";
    std::string darkness = "\033[31mDarkness\033[0m";
    std::string lowlives = "\033[31mLowLives\033[0m";
    std::string kaltorna = "\033[31mKaltorna Galaxy\033[0m";

    std::string prologue1 = "\n\nThere was once a land of many mythical beings which resided in the realm of " + moranthia + "...";
    Stagger(prologue1, delay1);
    Sleep_1s();
    std::string prologue2 = "\n\n...eventually however, a portal suddenly appeared, which led to a completely different land of science...";
    Stagger(prologue2, delay1);
    Sleep_1s();
    std::string prologue3 = "\n\n...the realm of " + moranthia + " and the " + kaltorna + " were suddenly bound together for the worse...";
    Stagger(prologue3, delay1);
    Sleep_1s();
    std::string prologue4 = "\n\n...the knowledge and technological advancement of the Kaltornans let them easily rule over the 'inferior' " + moranthia + "...";
    Stagger(prologue4, delay1);
    Sleep_1s();
    std::string prologue5 = "\n\n...these " + lowlives + " were robbed of their wealth and peace, forcing them to submit to the Kaltornans or live off the scraps of their once beautiful realm...";
    Stagger(prologue5, delay1);
    Sleep_1s();
    std::string prologue6 = "\n\n...and those that withered away fed the feared lifeforce known as the " + darkness + "...";
    Stagger(prologue6, delay1);
    Sleep_1s();
    std::string prologue7 = "\n\n...this " + darkness + " began to spread across both worlds, slowly turning them both into ruin";
    Stagger(prologue7, delay1);
    std::string prologue8 = "...";
    Stagger(prologue8, delay2);
    // Prints out player prompt.
    std::string title9 = "\n\n\n                                                           Press any button to continue...";
    Stagger(title9, delay1);

    // Waits for any user input.
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
void IntroductionP1(int delay1, std::string &playerName) {
    
    // Player is asked their name
    std::string name1 = "\n\nTell me your name LowLife...";
    Stagger(name1, delay1);
    Sleep_1s();
    std::string name2 = "\n...TELL ME!";
    Stagger(name2, delay1);
    std::cout << "\n> ";
    std::getline(std::cin, playerName);
    std::string name3 = "\nIt's a pleasure to meet you " + playerName + ".";
    Stagger(name3, delay1);
    Sleep_1s();
}
void IntroductionP2(int delay1, std::string playerName, Player& player) {

    std::string lore1 = "\nAnyhow, I should warn you LowLife; the realm of Moranthia is not a place of sunshine and happiness...";
    Stagger(lore1, delay1);
    std::string lore2 = "\nThe creatures that live in this land must NEVER be trusted. No matter how genuine they may seem...";
    Stagger(lore2, delay1);
    std::string lore3 = "\nYou'll never meet anyone as kind and fair as me.";
    Stagger(lore3, delay1);
    std::string lore4 = "\nI would not recommend travelling to see Lord Bali and his order of slaves and worshippers either; however, he does enjoy his trades...";
    Stagger(lore4, delay1);
    std::string lore5 = "\nI wish you plenty of luck LowLife on your whatever-it-is mission. Goodbye for now " + playerName + "...";
    Stagger(lore5, delay1);
    std::string lore6 = "\n" + playerName + " suddenly found themselves free-falling into a new world...";
    Stagger(lore6, delay1);

    // Prints image of falling man.
    DisplayPhotoInNewWindow("C:\\Programming\\C++ Games\\LowLife\\LowLifePhotos\\Falling.jpeg", "Welcome to Moranthia");

    // Transitions the player into the actual game.
    std::string beginning1 = "\n" + playerName + " landed into the torrent of a river, surrounded by crumbling cliffs and ancient ruins...";
    Stagger(beginning1, delay1);
    std::string beginning2 = "\nThey managed to grab onto a piece of debris lodged between two rocks...";
    Stagger(beginning2, delay1);
    std::string beginning3 = "\n" + playerName + " was then able to pull themself up onto a slab of stone and onto the river bank...";
    Stagger(beginning3, delay1);

    // Prints image of a ravine.
    DisplayPhotoInNewWindow("C:\\Programming\\C++ Games\\LowLife\\LowLifePhotos\\Ravine.jpeg", " ");
}
void InitialiseGameMap(std::string playerName, Player& player, std::string character, bool randomEnemy, bool avis, bool pigman, bool bali, bool tonobros) {
    // Sets the map size.
    Map map(3, 4);
    // CHEATS
    //player.AddSpaceSuitToInventory();
    //player.AddBalisHeadToInventory();
    //player.AddEctoplasmToInventory();
    //player.AddCoinToInventory();

    // Set the descriptions for each area and add items and people
    Region A1("\033[33mFungisle\033[0m", "\n\n" + playerName + " arrived to find a lagoon flourishing with various species of funghi.\nOne mushroom seemed to glow with a precious aura...\n");
    A1.addItem(Item("Mera's Glowth", "Glowed with a precious aura.\n"));
    A1.addPerson(NPC("Unfortunately, there's no one to ask...", "..."));
    map.setArea(0, 0, A1);

    Region A2("\033[33mThe Scorched Plains\033[0m", "\n\nAfter days of travelling, " + playerName + " came across a desolate wasteland, as far as the eye could see.\nIn the distance a rider charged towards " + playerName + "!\n");
    A2.addItem(Item("Unfortunately, there's no item here...\n", "..."));
    A2.addPerson(NPC("Rider", "..."));
    map.setArea(0, 1, A2);

    Region A4("\033[33mBali's Plateau\033[0m", "\n\nThe shuttle dropped " + playerName + " outside the palace's walls.\nThe place shone bright against the foreboding night sky.\n" + playerName + " was greeted and taken into the palace hall by a young man without the back of his skull...\nA blue lady waited for them.\n");
    A4.addItem(Item("Unfortunately, there's no item here...\n", "..."));
    A4.addPerson(NPC("Blue Lady", "She seemed unusually happy."));
    map.setArea(0, 3, A4);

    Region B1("\033[33mThe Hollow Castle\033[0m", "\n\nA mysterious castle loomed at the back of the ancient ravine.\nBlue, ghostly characters wandered about the tower's rooms.\n");
    B1.addItem(Item("Unfortunately, there's no item here...\n", "..."));
    B1.addPerson(NPC("Boy-ghost", "\nAlone in the clearing nearby, a small, ghostly figure cried."));
    map.setArea(1, 0, B1);

    Region B2("\033[33mDavven's Ravine\033[0m", "\n\n" + playerName + " found themself inside a collosal ravine, a powerful rapids ran through it.\nWhen " + playerName + " examined the landscape, they saw ancient towers and statues carved into the overgrown landscape.\n" + playerName + " could only travel East or West...\n");
    B2.addItem(Item("Unfortunately, there's no item here...\n", "..."));
    B2.addPerson(NPC("Unfortunately, there's no one to ask...", "..."));
    map.setArea(1, 1, B2);

    Region B3("\033[33mThe Great Boruna\033[0m", "\n\nAfter a day of travelling, the ravine finally opened up to reveal a gorgeous mountain range however, there was one thing off about it...\n" + playerName + " wondered whether it was magic or science that had caused this...\n");
    B3.addItem(Item("Unfortunately, there's no item here...\n", "..."));
    B3.addPerson(NPC("Hermit", "\nA hermit was poorly hiding from " + playerName + "."));
    map.setArea(1, 2, B3);

    Region B4("\033[33mThe Kaltorna System\033[0m", "\n\nThe teleporter threw " + playerName + " into a luminescent expanse.\nAn enormous ship hovered in the distance.\n");
    B4.addItem(Item("Unfortunately, there's no item here...\n", "..."));
    B4.addPerson(NPC("Starship pilot", playerName + " could only afford a trip to the Khan's palace or the The Pyramid of Valdestrone..."));
    map.setArea(1, 3, B4);

    Region C1("\033[33mThe Nivilian Forest\033[0m", "\n\nAfter a long sail, " + playerName + " reached a vast tropical island.\nAs they made their way up the mountain, a long-forgotten fortress could be seen. To the East, an overgrown path led deeper into the jungle.\n");
    C1.addItem(Item("Unfortunately, there's no item here...\n", "..."));
    C1.addPerson(NPC("Unfortunately, there's no one to ask...", "..."));
    map.setArea(2, 0, C1);

    Region C2("\033[33mNidrow's Forest\033[0m", "\n\nThe trail took " + playerName + " into an ancient forest.\nSome of the trees had faces which seemed to groan as " + playerName + " walked past.\nAt the end of the trail stood pig-like figure.\nThe rotten creature strode towards " + playerName + ".\n");
    C2.addItem(Item("Unfortunately, there's no item here...\n", "..."));
    C2.addPerson(NPC("Rotten Pigman", "He bellowed out ""FIGHT ME!"""));
    map.setArea(2, 1, C2);

    Region C4("\033[33mThe Pyramid of Valdestrone\033[0m", "\n\nThe shuttle left " + playerName + " in a landscape shrouded by darkness.\nAn immense green pyramid rose into the clouds.\nAn unmoving black figure stood nearby...\n");
    C4.addItem(Item("Unfortunately, there's no item here...\n", "..."));
    C4.addPerson(NPC("Black figure", "..."));
    map.setArea(2, 3, C4);

    // Handles user choice/movement.
    bool running = true;
    while (running) {
        map.describeCurrentArea();
        map.CallRandomBattle(player);
        map.displayOptions();
        std::string choice;
        std::cout << "\n\n\033[97mPlease enter a direction or command:\033[0m";
        std::cout << "\n\033[97m> \033[0m";
        std::cin >> choice;

        // Convert input to lowercase to make case insensitive comparison easier.
        std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);

        if (choice == "north") {
            map.move(player, -1, 0);
        }
        else if (choice == "east") {
            map.move(player, 0, 1);
        }
        else if (choice == "south") {
            map.move(player, 1, 0);
        }
        else if (choice == "west") {
            map.move(player, 0, -1);
        }
        else if (choice == "examine") { // Examine item
            std::string itemName;
            std::cout << "\nEnter the name of the item to examine: ";
            std::cin.ignore(); // Ignore leftover newline character from previous input.
            std::getline(std::cin, itemName);
            map.examineItem(itemName, player);
        }
        else if (choice == "talk") { // Talk to person
            std::string personName;
            std::cout << "\nEnter the name of the person to talk to: ";
            std::cin.ignore(); // Ignore leftover newline character from previous input.
            std::getline(std::cin, personName);
            map.talkToPerson(personName, player, character, randomEnemy, avis, pigman, bali, tonobros);
        }
        else if (choice == "inventory") { // Show inventory
            player.InitialiseInventory();
            player.HideEmptySlots();
            player.ShowInventory();
        }
        else if (choice == "quit") { // Quit
            std::cout << "\n" + playerName + " suddenly collapsed...his story was over.";
            Stagger(GAMEOVER, delay1);
            exit(0); // Terminates the program.
        }
        else { // Invalid input
            std::cout << "\n\033[90mInvalid input. Please enter a valid direction or command.\033[0m";
        }
    }
}

// ----------Main Function----------
int main()
{
    Player* player = nullptr; // Creates a null pointer.

    // ----------Runs Game Chronology----------
    PreText(bold, delay3);
    startMusic("C:\\Programming\\C++ Games\\LowLife\\LowLifeMusic\\main_theme.wav");
    TitleScreen(bold, delay1);
    Prologue(bold, delay1, delay2);
    stopMusic();
    IntroductionP1(delay1, playerName);

    // Player is asked their character selection.
    std::string character1 = "\nWhat are you then?...A wizard? A beast? Perhaps an astronomer?";
    Stagger(character1, delay1);
    while (true) {
        std::cout << "\n> ";
        std::getline(std::cin, character);
        if (character == "wizard" || character == "Wizard") {
            player = new Wizard(playerName);
            std::string wizard1 = "\nHmm, wizards are virtually extinct ever since the great battle at \033[33mValdestrone\033[0m...\n\n";
            Stagger(wizard1, delay1);
            break;
        }
        else if (character == "beast" || character == "Beast") {
            player = new Beast(playerName);
            std::string beast1 = "\nHmm, a beast you say? You're not going to transform on me are you haha?..\n\n";
            Stagger(beast1, delay1);
            break;
        }
        else if (character == "astronomer" || character == "Astronomer") {
            player = new Astronomer(playerName);
            std::string astronomer1 = "\nHmm, an astronomer? Your kind betrayed \033[33mMoranthia\033[0m to search for the stars...\n\n";
            Stagger(astronomer1, delay1);
            break;
        }
        else {
            std::string retry = "\nLet me ask you again. What are you LowLife?...A wizard? A beast? Or an astronomer?";
            Stagger(retry, delay1);
        }
    }
    IntroductionP2(delay1, playerName, *player);
    
    // Creates game map.
    startMusic("C:\\Programming\\C++ Games\\LowLife\\LowLifeMusic\\travel.wav");
    InitialiseGameMap(playerName, *player, character, randomEnemy, avis, pigman, bali, tonobros);
    player->DisplayPlayerStats();
    
    // Clean up dynamically allocated memory created by "Player* player = nullptr;".
    delete player;
    return 0;
}
