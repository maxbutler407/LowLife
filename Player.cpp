#include "Player.h"

Player::Player() : playerName(""), health(0), strength(0), magic(0), intelligence(0), wealth(0), darkness(0), spaceSuitCount(0), testItemCount(12) {}

// This constructor initialises the private member variables (using an 'initiliser list').
Player::Player(std::string n, int h, int s, int m, int i, int w, int d)
    : playerName(n), health(h), strength(s), magic(m), intelligence(i), wealth(w), darkness(d), spaceSuitCount(0), testItemCount(12) {}

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

void Player::IncreaseWealth(int amount) {
    wealth += amount;
}

void Player::DecreaseWealth(int amount) {
    wealth -= amount;
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
    std::cout << "\n   - Wealth         |  " << wealth;
    std::cout << "\n   - Darkness       |  " << darkness;
}

// ----------Player Inventory----------
void Player::InitialiseInventory() {
    inventory["Inter-realm Spacesuit"] = spaceSuitCount;
    inventory["test item"] = testItemCount;
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
        std::cout << "\n" << item.first << " quantity: " << item.second << std::endl;
    }
}

void Player::UpdateInventory() {
}