#include "Player.h"

Player::Player() : playerName(""), health(0), strength(0), magic(0), intelligence(0), darkness(0), spaceSuitCount(0), merasGlowthCount(0), coinCount(0), ectoplasmCount(0), headCount(0) {}

// This constructor initialises the private member variables (using an 'initiliser list').
Player::Player(std::string n, int h, int s, int m, int i, int d)
    : playerName(n), health(h), strength(s), magic(m), intelligence(i), darkness(d), spaceSuitCount(0), merasGlowthCount(0), coinCount(0), ectoplasmCount(0), headCount(0) {}

// Methods are used to modify INITIALISED member variables for better encapsulation.
void Player::IncreaseHealth(int amount) {
    health += amount;
}

void Player::DecreaseHealth(int amount) {
    health -= amount;
}

void Player::IncreaseStrength(int amount) {
    strength += amount;
}

void Player::DecreaseStrength(int amount) {
    strength -= amount;
}

void Player::IncreaseMagic(int amount) {
    magic += amount;
}

void Player::DecreaseMagic(int amount) {
    magic -= amount;
}

void Player::IncreaseIntelligence(int amount) {
    intelligence += amount;
}

void Player::DecreaseIntelligence(int amount) {
    intelligence -= amount;
}

void Player::IncreaseDarkness(int amount) {
    darkness += amount;
}

void Player::DecreaseDarkness(int amount) {
    darkness -= amount;
}

void Player::DisplayPlayerStats() const {
    std::cout << "\n\n" + playerName + "'s Current Stats: ";
    std::cout << "\n   - Health         |  " << health;
    std::cout << "\n   - Strength       |  " << strength;
    std::cout << "\n   - Magic          |  " << magic;
    std::cout << "\n   - Intelligence   |  " << intelligence;
    std::cout << "\n   - \033[31mDarkness\033[0m       |  " << darkness << "\n\n";
}

// ----------Player Inventory----------
void Player::InitialiseInventory() {
    inventory["\033[33mInter-realm Spacesuit\033[0m"] = spaceSuitCount;
    inventory["\033[33mMera's Glowth\033[0m"] = merasGlowthCount;
    inventory["\033[33mKaltornan Coin\033[0m"] = coinCount;
    inventory["\033[33mAncient Ghost's Ectoplasm\033[0m"] = ectoplasmCount;
    inventory["\033[33mLord Bali's Head\033[0m"] = headCount;
}

// Doesn't show items in inventory when quantity = 0;
void Player::HideEmptySlots() {
    for (auto item = inventory.begin(); item != inventory.end(); ) {
        if (item->second == 0) {
            item = inventory.erase(item);  // Erases the item and updates the iterator.
        }
        else {
            ++item; // Moves to the next item.
        }
    }
}

void Player::ShowInventory() const {
    std::cout << "\nCurrent Inventory:";
    for (const auto& item : inventory) {
        std::cout << "\n" << item.first << " quantity: " << item.second;
    }
}

void Player::AddSpaceSuitToInventory() {
    spaceSuitCount = 1;
    std::cout << "\n\nAdded \033[33mInter-realm Spacesuit\033[0m to inventory!";
}

void Player::AddMerasGlowthToInventory() {
    merasGlowthCount = 1;
    std::cout << "\n\nAdded \033[33mMera's Glowth\033[0m to inventory!";
}

void Player::AddCoinToInventory() {
    coinCount = 1;
    std::cout << "\n\nAdded \033[33mKaltornan Coin\033[0m to inventory!";
}

void Player::AddEctoplasmToInventory() {
    ectoplasmCount = 1;
    std::cout << "\n\nAdded \033[33mAncient Ghost's Ectoplasm\033[0m to inventory!";
}

void Player::AddBalisHeadToInventory() {
    headCount = 1;
    std::cout << "\n\nAdded \033[33mLord Bali's Head\033[0m to inventory!";
}