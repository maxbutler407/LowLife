#include "Enemy.h"
#include "Utility.h"

Enemy::Enemy() : enemyName(""), pAttackName(""), sAttackName(""), buffName(""), healName(""), health(0), damage(0), buff(0), darkness(0) {}

Enemy::Enemy(std::string eN, std::string pAN, std::string sAN, std::string bN, std::string hN, int h, int dam, int b, int dar)
    : enemyName(eN), pAttackName(pAN), sAttackName(sAN), buffName(bN), healName(hN), health(h), damage(dam), buff(b), darkness(dar) {}

// Generates a random enemy.
void Enemy::GenerateEnemy(const std::string& playerName) {
    srand(static_cast<unsigned int>(time(nullptr)));
    int randEnemy = rand() % 3 + 1;
    if (randEnemy == 1) {
        enemyName = "\033[31mPossessed Astronaut\033[0m";
        pAttackName = " fired its raygun at " + playerName + " causing searing pain";
        buffName = " called the evil spirits inside";
        healName = " activated its stim injection";
        health = 80;
        damage = 20;
        buff = 10;
        darkness = 15;
    }
    else if (randEnemy == 2) {
        enemyName = "\033[31mCentimane\033[0m";
        pAttackName = " used a number of its arms to bombard " + playerName;
        buffName = " brought out more arms to attack the LowLife";
        healName = " wrapped its arms tightly around its wounds";
        health = 90;
        damage = 30;
        buff = 10;
        darkness = 5;
    }
    else if (randEnemy == 3) {
        enemyName = "\033[31mFeral Ape\033[0m";
        pAttackName = " opened its mouth wide, biting a chunk of flesh out of " + playerName;
        buffName = " beat its chest aggressively";
        healName = " spat on its wounds in an attempt to heal itself";
        health = 70;
        damage = 40;
        buff = 15;
        darkness = 10;
    }
}

void Enemy::GenerateAvis(const std::string& playerName) {
    enemyName = "\033[31mThe Vermilion Avis\033[0m";
    pAttackName = " landed a great peck on " + playerName + " - the ground shook violently";
    buffName = " magically set its whole body aflame";
    healName = " spread its massive wings, absorbing the hot sunlight";
    health = 190;
    damage = 20;
    buff = 15;
    darkness = 25;
}

void Enemy::GeneratePigman(const std::string& playerName) {
    enemyName = "\033[31mThe Rotten Pigman\033[0m";
    pAttackName = " swung his greatsword at " + playerName;
    buffName = " ate a clump of a past victim's flesh";
    healName = " shook off his wounds";
    health = 110;
    damage = 20;
    buff = 15;
    darkness = 25;
}

void Enemy::GenerateBali(const std::string& playerName) {
    enemyName = "\033[31mLord Bali\033[0m";
    pAttackName = "'s eyes glowed intensely, causing flashes of red lightning to strike " + playerName;
    buffName = " grabbed hold of a nearby worshipper, consuming his brain";
    healName = " called down a robotic arm, which surgically attached metal plating to his damaged areas";
    health = 150;
    damage = 30;
    buff = 15;
    darkness = 30;
}

void Enemy::GenerateTonobros(const std::string& playerName) {
    enemyName = "\033[31mTonobros\033[0m";
    pAttackName = "' great claws glistened as he slashed them on " + playerName;
    sAttackName = "' glowing chest beat, accelerated - projecting beams of white light all around the chamber";
    buffName = " laughed maniacally, realising how easily he could destroy " + playerName;
    healName = " seemingly consumed all the darkness around the two of them";
    health = 200;
    damage = 35;
    buff = 20;
    darkness = 100;
}

// Methods are used to modify INITIALISED member variables for better encapsulation.
void Enemy::IncreaseHealth(int amount) { health += amount; }
void Enemy::DecreaseHealth(int amount) { health -= amount; }
void Enemy::IncreaseDamage(int amount) { damage += amount; }
void Enemy::DecreaseDamage(int amount) { damage -= amount; }

void Enemy::EnemyAttack(int delay1, Player& player) {
    std::string attack1 = "\n\n" + enemyName + pAttackName + "..." + "\n\n...\033[31m-";
    Stagger(attack1, delay1);
    StaggerInt(damage, delay1);
    std::string attack2 = " player health\033[0m!";
    Stagger(attack2, delay1);
    player.DecreaseHealth(damage);
}

void Enemy::EnemySAttack(int delay1, Player& player) {
    std::string attack1 = "\n\n" + enemyName + sAttackName + "..." + "\n\n...\033[31m-";
    Stagger(attack1, delay1);
    StaggerInt(damage * 1.1, delay1);
    std::string attack2 = " player health\033[0m!";
    Stagger(attack2, delay1);
    player.DecreaseHealth(damage * 1.1);
}

void Enemy::EnemyBuff(int delay1, Player& player, Enemy& enemy) {
    std::string buff1 = "\n\n" + enemyName + buffName + "..." + "\n\n...\033[31m+";
    Stagger(buff1, delay1);
    StaggerInt(buff, delay1);
    std::string buff2 = " enemy damage\033[0m!";
    Stagger(buff2, delay1);
    enemy.IncreaseDamage(buff);
}

void Enemy::EnemyHealthRegen(int delay1, Player& player, Enemy& enemy) {
    std::string heal1 = "\n\n" + enemyName + healName + "..." + "\n\n...\033[31m+";
    Stagger(heal1, delay1);
    StaggerInt(health * 0.4, delay1);
    std::string heal2 = " enemy health\033[0m!";
    Stagger(heal2, delay1);
    enemy.IncreaseHealth(health * 0.2);
}

void Enemy::DisplayEnemyStats() const {
    std::cout << "\n" + enemyName + "'s Current Stats : ";
    std::cout << "\n   - Health         |  " << health;
    std::cout << "\n   - Damage         |  " << damage;
    std::cout << "\n   - Buff           |  " << buff;
    std::cout << "\n   - \033[31mDarkness\033[0m       |  " << darkness;
}