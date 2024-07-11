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
#include <irrKlang.h>
#include <filesystem>
#include <limits>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

#pragma comment(lib, "irrKlang.lib")

//using namespace cv;
using namespace irrklang;
using MapInventory = std::map<std::string, int>;

int delay1 = 30;
std::string playerName = "\033[33mMax\033[0m";
std::string hermitsPlayerName;

// ----------Stylistic Functions----------
// Stagger function's bool value is set to false.
void Stagger(const std::string& string, int delay_ms);

// Function staggers text that appears in the game.
void Stagger(const std::string& string, int delay_ms) {
    // For loop iterates over each character in the string.
    for (char c : string) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
        std::cout << "";
    }


}

void StaggerInt(const int& integer, int delay_ms) {
    // Converts int input to string.
    std::string intStr = std::to_string(integer);
    for (char c : intStr) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
        std::cout << "";
    }
}

// Sleep_xs() methods delays the execution of the programme when called.
void Sleep_1s() {
    using namespace std::this_thread;
    using namespace std::chrono;

    sleep_until(system_clock::now() + seconds(1));
}

void Sleep_5s() {
    using namespace std::this_thread;
    using namespace std::chrono;

    sleep_until(system_clock::now() + seconds(5));
}

void DisplayASCIIArtFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "\nCould not open the file!" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    file.close();
}

// ----------Classes----------
class Player {
public:
    // ----------Player Variables----------
        // Player stats - can be altered (ie. increased/decreased) depending on the paths the player takes.
    std::string playerName;
    int health; // Not set a value until object is called.
    int strength;
    int magic;
    int intelligence;
    int wealth;
    int darkness;

    Player() : playerName(""), health(0), strength(0), magic(0), intelligence(0), wealth(0), darkness(0) {}
    
    // This constructor initialises the private member variables (using an 'initiliser list').
    Player(std::string n, int h, int s, int m, int i, int w, int d) : playerName(n), health(h), strength(s), magic (m), intelligence (i), wealth (w), darkness (d) {}

    // Methods are used to modify INITIALISED member variables for better encapsulation.
    void IncreaseHealth(int amount) {
        health += amount;
    }

    void DecreaseHealth(int amount) {
        health -= amount;
    }

    void IncreaseStrength(int amount) {
        strength += amount;
    }

    void DecreaseStrength(int amount) {
        strength -= amount;
    }

    void IncreaseMagic(int amount) {
        magic += amount;
    }

    void DecreaseMagic(int amount) {
        magic -= amount;
    }

    void IncreaseIntelligence(int amount) {
        intelligence += amount;
    }

    void DecreaseIntelligence(int amount) {
        intelligence -= amount;
    }

    void IncreaseWealth(int amount) {
        wealth += amount;
    }

    void DecreaseWealth(int amount) {
        wealth -= amount;
    }

    void IncreaseDarkness(int amount) {
        wealth += amount;
    }

    void DecreaseDarkness(int amount) {
        wealth -= amount;
    }

    void DisplayPlayerStats() const {
        std::cout << "\nCurrent Stats:";
        std::cout << "\n   - Health         |  " << health;
        std::cout << "\n   - Strength       |  " << strength;
        std::cout << "\n   - Magic          |  " << magic;
        std::cout << "\n   - Intelligence   |  " << intelligence;
        std::cout << "\n   - Wealth         |  " << wealth;
        std::cout << "\n   - Darkness       |  " << darkness;
    }

    // ----------Player Inventory----------
    int spaceSuitCount = 0;
    int testItemCount = 12;

    // Each item is a string which can have its own quantity (using int vector).
    MapInventory inventory;

    void InitialiseInventory() {

        inventory["Inter-realm Spacesuit"] = spaceSuitCount;
        inventory["test item"] = testItemCount;
    }

    // Doesn't show items in inventory when quantity = 0;
    void HideEmptySlots() {
        for (auto item = inventory.begin(); item != inventory.end(); ) {
            if (item->second == 0) {
                item = inventory.erase(item);  // Erase the item and update the iterator
            }
            else {
                ++item;  // Move to the next item
            }
        }
    }

    // Method prints out the description when a region has been entered.
    void ShowInventory() const {
        std::cout << "\nCurrent Inventory:";
        for (const auto& item : inventory) {
            std::cout << "\n" << item.first << " quantity: " << item.second << std::endl;
        }
    }

    void UpdateInventory() {

    }

    // ----------Player Combat----------
    virtual void MindTrick(int delay1, const std::string &playerName, const std::string &enemyName, Player& player) = 0;
    virtual void SinisterSpell(int delay1, const std::string& playerName, const std::string& enemyName, Player& player) = 0;
};

class Wizard : public Player {
public:

    // Attributes.
    Wizard(std::string playerName) : Player(playerName, 100, 10, 50, 40, 0, 60) {};

    // Abilities.
    void MindTrick(int delay1, const std::string &playerName, Enemy& enemy, Player& player) override {
        std::string mindTrick1 = "\n" + playerName + " used a \033[34mMindTrick\033[0m...\n\n...\033[34m";
        Stagger(mindTrick1, delay1);
        int mindTrick2 = magic;
        StaggerInt(mindTrick2, delay1);
        std::string mindTrick3 = " magical damage\033[0m!";
        Stagger(mindTrick3, delay1);
        enemy.DecreaseHealth(magic);
    }

    void SinisterSpell(int delay1, const std::string& playerName, const std::string& enemyName, Player& player) override {
        std::string mindTrick1 = "\n" + playerName + " used a \033[34mSinisterSpell\033[0m...\n\n...\033[34m";
        Stagger(mindTrick1, delay1);
        int mindTrick2 = magic;
        StaggerInt(mindTrick2, delay1);
        std::string mindTrick3 = " magical damage\033[0m!";
        Stagger(mindTrick3, delay1);
        player.DecreaseHealth(magic);
    }
};

class Beast {
public:

    // Attributes.
    //int level;
    int strength = 70; // When ability is active.
    int magic = 10;
    int intelligence = 20;
    int wealth = 0;
    int darkness = 50;

    // Abilities.
    void Transform(int delay1, std::string name) {
        std::string transform = "\n" + name + "transformed into a creature of mythical and powerful origin...";
        Stagger(transform, delay1);
    }
};

class Astronomer {
public:

    // Attributes.
    //int level;
    int strength = 20;
    int magic = 10;
    int intelligence = 60;
    int wealth = 0;
    int darkness = 20;

    // Abilities.
    void Examine(int delay1, std::string name) {
        std::string examine = "\n" + name + "examined the item with great detail...";
        Stagger(examine, delay1);
    }
};

class NPC {
public:

    // Constructors.
    std::string name;
    std::string dialogue;
    std::string itemRequest;
    std::string abilities;
    std::string health;

    // Methods.
    NPC(const std::string& name, const std::string& dialogue)
        : name(name), dialogue(dialogue) {}

    void HermitDialogue(std::string playerName) const {
        //std::cout << name << " says: " << dialogue << std::endl;

        std::cout << "\n" + playerName + " asked the hermit about the mountain...";

        std::string hermitFilePath = "C:\\Programming\\C++ Games\\LowLife\\ASCIIFiles\\hermit.txt";
        DisplayASCIIArtFromFile(hermitFilePath);

        std::cout << "\nOh hello! I didn't see your wee-self over on those rocks.";
        std::cout << "\nI should really introduce myself; I'm being quite rude...I am Kroka of House Kruuka!";
        std::cout << "\nAnd you are..?";
        std::cout << "\n> ";
        std::getline(std::cin, hermitsPlayerName);
        std::cout << "\nHow excellent to meet you " + hermitsPlayerName + "! I was just on my way to fish for the day...";
        std::cout << "\nBut I don't want to bore you. I noticed you were staring at the great Boruna - the portal between two vastly different worlds.";
        std::cout << "\nIf you were considering to enter that portal you require a spacesuit if you want to survive in there.";

    }
};

class Item {
public:
    std::string name;
    std::string description;

    Item(const std::string& name, const std::string& description)
        : name(name), description(description) {}

    void examine() const {
        std::cout << "You see a " << name << ". " << description << std::endl;
    }
};

class Region {
public:
    // Variables.
    std::string name;
    std::string description;
    std::vector<Item> items;
    std::vector<NPC> npcs;

    // Methods.
    Region(const std::string& name, const std::string& description)
        // Initialises the name and description string variables.
        : name(name), description(description) {}

    void describe() const {
        std::cout << "\n\nYou are in " << name << ". " << description << std::endl;
        if (!items.empty()) {
            //std::cout << "Items here: ";
            for (const auto& item : items) {
                std::cout << item.name << " ";
            }
            std::cout << std::endl;
        }
        if (!npcs.empty()) {
            //std::cout << "People here: ";
            for (const auto& person : npcs) {
                std::cout << person.name << " ";
            }
            std::cout << std::endl;
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

    void examineItem(const std::string& itemName) const {
        for (const auto& item : items) {
            if (item.name == itemName) {
                item.examine();
                return;
            }
        }
        std::cout << "There is no " << itemName << " here." << std::endl;
    }

    void talkToPerson(const std::string& personName) const {
        for (const auto& person : npcs) {
            if (person.name == personName) {
                person.HermitDialogue(playerName);
                return;
            }
        }
        std::cout << "\nThere is no one named " << personName << " here.";
    }
};

// Map class manages multiple regions.
class Map {
private:
    
    // Vector (named areas) takes in a vector of objects of class Area (2D Vector)
    std::vector<std::vector<Region>> regions;

    // Sets variables for class.
    int currentRow;
    int currentCol;

public:

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

    // rowOffset and colOffset are automatically defined in this parameter as int values (so can be used to increase/decrease currentRow/currentCol.
    void move(int rowOffset, int colOffset) {
        int newRow = currentRow + rowOffset;
        int newCol = currentCol + colOffset;
        // Updates the newRow as the currentRow (so long as they are within the Map size).
        if (newRow >= 0 && newRow < regions.size() && newCol >= 0 && newCol < regions[newRow].size()) {
            currentRow = newRow;
            currentCol = newCol;
            //describeCurrentArea();
        }
        else {
            std::cout << "You can't move in that direction." << std::endl;
        }
    }

    void describeCurrentArea() const {
        regions[currentRow][currentCol].describe();
    }

    void displayOptions() const {
        std::cout << "\n\033[97mOptions:\033[0m";
        std::cout << "\n\033[97m1. Move North\033[0m";
        std::cout << "\n\033[97m2. Move East\033[0m";
        std::cout << "\n\033[97m3. Move South\033[0m";
        std::cout << "\n\033[97m4. Move West\033[0m";
        std::cout << "\n\033[97m5. Examine Item\033[0m";
        std::cout << "\n\033[97m6. Talk to Person\033[0m";
        std::cout << "\n\033[97m7. View Inventory\033[0m";
        std::cout << "\n\033[97m8. Quit\033[0m";
    }

    void examineItem(const std::string& itemName) const {
        regions[currentRow][currentCol].examineItem(itemName);
    }

    void talkToPerson(const std::string& personName) const {
        regions[currentRow][currentCol].talkToPerson(personName);
    }
};

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

    Enemy() : enemyName(""), attackName(""), buffName(""), potionName(""), inflictDarkness(""), health(0), damage(0), buff(0), darkness(0) {}

    Enemy(std::string eN, std::string aN, std::string bN, std::string pN, std::string iD, int h, int dam, int b, int dar) : enemyName(eN), attackName(aN), buffName(bN), potionName(pN), inflictDarkness(iD), health(h), damage(dam), buff (b), darkness(dar) {}

    // Generates a random enemy.
    void GenerateEnemy() {
        srand(time(NULL));
        int randNum = rand() % 2 + 1;
        std::cout << randNum;
        if (randNum == 1) {
            enemyName = "\033[31mGoblin\033[0m";
            attackName = "his rusty shank on " + playerName;
            buffName = "a mouldy potion on itself";
            health = 20;
            damage = 25;
            buff = 10;
        }
        else if (randNum == 2) {
            enemyName = "\033[31mCentimane\033[0m";
            attackName = "a number of his arms to bombard " + playerName;
            buffName = "more arms for attacking the LowLife";
            health = 40;
            damage = 40;
            buff = 5;
        }
    }

    // Methods are used to modify INITIALISED member variables for better encapsulation.
    void IncreaseHealth(int amount) {
        health += amount;
    }

    void DecreaseHealth(int amount) {
        health -= amount;
    }

    void IncreaseDamage(int amount) {
        damage += amount;
    }

    void DecreaseDamage(int amount) {
        damage -= amount;
    }

    void DisplayEnemyStats() const {
        std::cout << "\nCurrent Stats:";
        std::cout << "\n   - Health         |  " << health;
        std::cout << "\n   - Strength       |  " << damage;
        std::cout << "\n   - Darkness       |  " << darkness;
    }

    void EnemyAttack(int delay1, Player& player) {
        std::string attack1 = "\n\nThe " + enemyName + " used " + attackName + "..." + "\n\n...\033[31m";
        Stagger(attack1, delay1);
        int attack2 = damage;
        StaggerInt(attack2, delay1);
        std::string attack3 = " damage\033[0m!";
        Stagger(attack3, delay1);
        player.DecreaseHealth(damage);
    }

    void EnemyDefence(Player& player, Enemy &enemy) {
        std::cout << "\nThe " + enemyName + " used " + buffName + "..." + "\n\n\033[31m...+" << buff << " damage\033[0m";
        enemy.IncreaseDamage(buff);
    }
};

// ----------GameChronology----------
void TitleScreen(bool bold, int delay1) {
    
    std::string title1 = "\033[31m                           .___     ._______           ___ .___    .___ ._______._______\033[0m";
    std::string title2 = "\033[31m                           |   |    : .___  \\ .___    |   ||   |   : __|:_ ____/: .____/\033[0m";
    std::string title3 = "\033[31m                           |   |    | :   |  |:   | /\\|   ||   |   | : ||   _/  | : _/\\ \033[0m";
    std::string title4 = "\033[31m                           |   |/\\  |     :  ||   |/  :   ||   |/\\ |   ||   |   |   /  \\ \033[0m";
    std::string title5 = "\033[31m                           |   /  \\  \\_. ___/ |   /       ||   /  \\|   ||_. |   |_.: __/\033[0m";
    std::string title6 = "\033[31m                           |______/    :/     |______/|___||______/|___|  :/       :/   \033[0m";
    std::string title7 = "\033[31m                                       :              :                   :            \033[0m";
    std::string title8 = "\033[31m                                                      :                                \033[0m";

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
    std::string title9 = "                                             Press any button to play...";
    Stagger(title9, delay1);
    std::cout << "";
    std::getline(std::cin, title9);
}

void Prologue(bool bold, int delay1)
{
    // Highlighted red words.
    std::string moranthia = "\033[31mMoranthia\033[0m";
    std::string darkness = "\033[31mDarkness\033[0m";
    std::string lowlives = "\033[31mLowLives\033[0m";

    std::string prologue1 = "\nThere was once a land of many mythical beings...";
    Stagger(prologue1, delay1);
    Sleep_1s();
    std::string prologue2 = "\n...this realm of fantasy and science came to be known as " + moranthia + "...";
    Stagger(prologue2, delay1);
    Sleep_1s();
    std::string prologue3 = "\n...however, as the centuries went on, these mythical beings began to fall in numbers; as the " + darkness + " possessed their mind and will...";
    Stagger(prologue3, delay1);
    Sleep_1s();
    std::string prologue4 = "\n...those that remained came to be known as " + lowlives + "; once beings with awesome power and influence, now mere mortals amongst a diverging world.";
    Stagger(prologue4, delay1);
    Sleep_5s();
}

void playAudio(const std::string& filePath, bool bold, int delay1) {

    // Create sound engine
    ISoundEngine* engine = createIrrKlangDevice();

    if (!engine) {
        std::cerr << "Could not initialise sound engine" << std::endl;
        return;
    }

    // Play the sound file
    ISound* sound = engine->play2D(filePath.c_str(), true);

    TitleScreen(bold, delay1);
    Prologue(bold, delay1);

    // Wait until user interrupts with a key press
    std::cin.get(); // Wait for user input to stop playback

    // Stop and drop the sound engine
    engine->stopAllSounds();
    engine->drop();
}

void Introduction(int delay1, std::string name, Player& player)
{
    /*
    // Player is asked their name
    std::string name1 = "\nTell me your name LowLife...";
    Stagger(name1, delay1);
    Sleep_1s();
    std::string name2 = "\n...TELL ME!";
    Stagger(name2, delay1);
    std::cout << "\n> ";
    std::getline(std::cin, name);
    std::string name3 = "\nIt's a pleasure to meet you " + name + ".";
    Stagger(name3, delay1);
    Sleep_1s();
    */
    std::string character1 = "\nWhat are you LowLife?...A wizard? A beast? Perhaps an astronomer??";
    Stagger(character1, delay1);

    // Player is asked their character selection.
    while (true) {

        std::string character;
        std::cout << "\n> ";
        std::getline(std::cin, character);

        if (character == "wizard" || character == "Wizard") {
            // Creates a Wizard object.
            //Wizard wizard;
            
            // Adds wizard's starting stats to player.
            player.IncreaseStrength(10);
            player.IncreaseMagic(50);
            player.IncreaseIntelligence(40);
            player.IncreaseDarkness(60);

            std::string wizard1 = "\nHmm, wizards have dwindled in numbers since the Darkness befell the land.";
            Stagger(wizard1, delay1);
            break;
        }
        else if (character == "beast" || character == "Beast") {
            //Creates a Beast object.
            Beast beast;

            // Adds beast's starting stats to player.
            player.IncreaseStrength(70);
            player.IncreaseMagic(10);
            player.IncreaseIntelligence(20);
            player.IncreaseDarkness(50);

            std::string beast1 = "\nHmm, a beast you say? You're not going to transform on me are you haha?";
            Stagger(beast1, delay1);
            break;
        }
        else if (character == "astronomer" || character == "Astronomer") {
            // Creates an Astronomer object.
            Astronomer astronomer;

            // Adds astronomer's starting stats to player.
            player.IncreaseStrength(20);
            player.IncreaseMagic(10);
            player.IncreaseIntelligence(60);
            player.IncreaseDarkness(10);

            std::string astronomer1 = "\nHmm, an astronomer? Fascinating. I was discouraged to become one of those as a child.";
            Stagger(astronomer1, delay1);
            break;
        }
        else {
            std::string character1 = "\nWhat are you?...A wizard? A beast? Perhaps an astronomer??";
            Stagger(character1, delay1);
            std::getline(std::cin, character);
            continue;
        }
    }

    /*
    std::string lore1 = "\nAnyhow, I should warn you LowLife; the realm of Moranthia is not a place of sunshine and happiness...";
    Stagger(lore1, delay1);
    std::string lore2 = "\nThe creatures that live in this land must NEVER be trusted. No matter how genuine they may seem...";
    Stagger(lore2, delay1);
    std::string lore3 = "\nYou'll never meet anyone as kind and fair as me.";
    Stagger(lore3, delay1);
    std::string lore4 = "\nI would not recommend travelling to see Lord Bali and his order of slaves and worshippers either; however, he does enjoy his trades...";
    Stagger(lore4, delay1);
    std::string lore5 = "\nI wish you plenty of luck LowLife on your whatever-it-is mission. Goodbye for now " + name + ".";
    Stagger(lore5, delay1);
    std::string lore6 = "\n" + name + " suddenly found themselves free-falling into a new world...";
    Stagger(lore6, delay1);

    // Print image of falling man.
    std::string fallingFilePath = "C:\\C++ Games\\LowLife\\ASCIIFiles\\falling.txt";
    DisplayASCIIArtFromFile(fallingFilePath);

    // Transitions the player into the actual game.
    std::string beginning1 = "\n" + name + " landed into the torrent of a river, surrounded by crumbling cliffs that seemed to reach the sky...";
    Stagger(beginning1, delay1);
    std::string beginning2 = "\nThey managed to grab onto a piece of debris lodged between two rocks...";
    Stagger(beginning2, delay1);
    std::string beginning3 = "\n" + name + " was then able to pull themself up onto the slab of stone and eventually onto the river bank...";
    Stagger(beginning3, delay1);
    */
}

void InitialiseGameMap(std::string playerName, Player& player) {
    Map map(3, 4);

    // Set the descriptions for each area and add items and people
    Region A1("Funghilse", "\n\n" + playerName + " arrived to find a lagoon flourishing with various species of funghi.\nOne mushroom seemed to glow with a precious aura.");
    A1.addItem(Item("\nMera's Glowth", "Glowed with a precious aura."));
    A1.addPerson(NPC("\nUnfortunately, there's no one to ask...", "..."));
    map.setArea(0, 0, A1);

    Region A2("", "\n\nAfter days of travelling, " + playerName + " discovered a derelict temple surrounded by no sign of life.\nIf " + playerName + " listened carefully, they could hear the faint sound of industrial work emitting from the temple.");
    A2.addItem(Item("\nUnfortunately, there's no item here...", "..."));
    A2.addPerson(NPC("\nUnfortunately, there's no one to ask...", "..."));
    map.setArea(0, 1, A2);

    Region A3("A3", "\n\nNothing here...");
    A3.addItem(Item("", ""));
    A3.addPerson(NPC("", ""));
    map.setArea(0, 2, A3);

    Region A4("A4", "\n\nA great plateau of moon rock spread as far as " + playerName + "'s eyes could see.\nA distant palace consisting of gems and moon rock could be seen.");
    A4.addItem(Item("\nUnfortunately, there's no item here...", "..."));
    A4.addPerson(NPC("\nUnfortunately, there's no one to ask...", "..."));
    map.setArea(0, 3, A4);

    Region B1("B1", "\n\nA mysterious tower loomed at the back of the ancient ravine " + playerName + " found themselves in.\nBlue, ghostly characters seemed to wander about the tower's rooms.");
    B1.addItem(Item("\nUnfortunately, there's no item here...", "..."));
    B1.addPerson(NPC("\nUnfortunately, there's no one to ask...", "..."));
    map.setArea(1, 0, B1);

    Region B2("B2", "\n\n" + playerName + " found themself inside a collosal ravine, a powerful rapids ran through it.\nWhen " + playerName + " examined the landscape, they saw ancient statues carved into the stone walls");
    B2.addItem(Item("\nUnfortunately, there's no item here...", "..."));
    B2.addPerson(NPC("\nUnfortunately, there's no one to ask...", "..."));
    map.setArea(1, 1, B2);

    Region B3("B3", "\n\nAfter a day of travelling, the ravine finally opened up to reveal a gorgeous mountain range however, there was one thing off about it...\n" + playerName + " wondered whether it was magic or science causing this.");
    B3.addItem(Item("\nUnfortunately, there's no item here...", "..."));
    B3.addPerson(NPC("Hermit", "\nA hermit was poorly hiding from " + playerName + "."));
    map.setArea(1, 2, B3);

    Region B4("B4", "\n\nThe teleporter threw " + playerName + " into a luminescent expanse.\nA massive spaceport stood in the distance. A blue spaceship was offering rides across this planet.");
    B4.addItem(Item("\nUnfortunately, there's no item here...", "..."));
    B4.addPerson(NPC("\nStarship pilot", "The pilot asked " + playerName + " whether he wanted a trip to the city."));
    map.setArea(1, 3, B4);

    Region C1("C1", "\n\nAfter a long sail, " + playerName + " reached a vast tropical island.\nA dangerous storm hung above the island. A long-abandoned route led into the deep jungle.");
    C1.addItem(Item("\nUnfortunately, there's no item here...", "..."));
    C1.addPerson(NPC("\nUnfortunately, there's no one to ask...", "..."));
    map.setArea(2, 0, C1);

    Region C2("C2", "\n\nThe trail led into a long-forgotten wood.\nEach tree had its own skeletal face which seemed to groan and move to follow " + playerName + " as they explored through.\nAt the end of the trail stood a possessed pig.\nThe rotten creature strode towards " + playerName + ".");
    C2.addItem(Item("\nUnfortunately, there's no item here...", "..."));
    C2.addPerson(NPC("\nGorkan", "He bellowed ""FIGHT ME"""));
    map.setArea(2, 1, C2);

    Region C3("C3", "\n\nNothing here...");
    C3.addItem(Item("", ""));
    C3.addPerson(NPC("", ""));
    map.setArea(2, 2, C3);

    Region C4("C4", "\n\nA week later, " + playerName + " found themselves in a land encapsulated by darkness.\nAn immense green pyramid rose into the clouds.\nA gleaming light protruded from its peak.\nA section of the pyramid looked like it could be opened up by placing some type of object onto a pedestal nearby.");
    C4.addItem(Item("\nUnfortunately, there's no item here...", "..."));
    C4.addPerson(NPC("\nUnfortunately, there's no one to ask...", "..."));
    map.setArea(2, 3, C4);

    // Handles user choice/movement.
    bool running = true;
    while (running) {
        map.describeCurrentArea();
        map.displayOptions();
        int choice;
        std::cout << "\n\n\033[97mPlease enter a number: \033[0m";
        std::cout << "\n\033[97m> \033[0m";
        std::cin >> choice;
        
        if (std::cin.fail()) {
            // Clears the error state if the input isn't an integer.
            std::cin.clear(); // Clears the error state.
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignores the rest of the input until a newline character is found.
            std::cout << "\n\033[90mInvalid input. Please enter a number.\033[0m" << std::endl;
            continue; // Restarts the choice loop.
        }
        
        switch (choice) {
        case 1: // Move North
            map.move(-1, 0);
            break;
        case 2: // Move East
            map.move(0, 1);
            break;
        case 3: // Move South
            map.move(1, 0);
            break;
        case 4: // Move West
            map.move(0, -1);
            break;
        case 5: { // Examine Item
            std::string itemName;
            std::cout << "\nEnter the name of the item to examine: ";
            std::cin.ignore();
            std::getline(std::cin, itemName);
            map.examineItem(itemName);
            break;
        }
        case 6: { // Talk to Person
            std::string personName;
            std::cout << "\nEnter the name of the person to talk to: ";
            std::cin.ignore();
            std::getline(std::cin, personName);
            map.talkToPerson(personName);
            break;
        }
        case 7: { // Show Inventory
            player.InitialiseInventory();
            player.HideEmptySlots();
            player.ShowInventory();
            break;
        }
        case 8: // Quit
            running = false;
            std::cout << "\n" + playerName + " suddenly collapsed...his story was over." << std::endl;
            break;
        default:
            std::cout << "\n\033[90mInvalid input. Please enter a number.\033[0m" << std::endl;
            //std::cin;
            std::cout << "\n\033[90m> \033[0m";
        }
    }
}

void InitialiseBattle(int delay1, Player &player) {
    Enemy enemy;
    enemy.GenerateEnemy();

    // Commences battle events.
    std::string battle1 = "\n" + playerName + " was suddenly ambushed by a " + enemy.enemyName + "!";
    Stagger(battle1, delay1);
    while (player.health > 0 && enemy.health > 0) {
        std::string battleChoice;
        std::string battle2 = "\n\nWhat would you like to do?";
        Stagger(battle2, delay1);
        std::cout << "\n|MindTrick|       |Action2|";
        std::cout << "\n| Action3 |       |Action4|";
        std::cout << "\n\n> ";
        std::getline(std::cin, battleChoice);

        if (battleChoice == "MindTrick" || battleChoice == "Mindtrick" || battleChoice == "mindtrick") {
            player.MindTrick(delay1, playerName, enemy.enemyName, player );
        }
        if (enemy.health > 0) {
            enemy.EnemyAttack(delay1, player);
        }
    }

    if (player.health > 0) {
        std::cout << "\n" + playerName + " wins!";
    }
    else {

        std::cout << "\n" + enemy.enemyName + " wins!";
    }
}

// ----------Main Function----------
int main()
{
    // Section sets the variables.
    int delay2 = 100;
    //int musicDelay = 30;
    //int input;
    bool bold = false;

    // Allows players stats to be kept up to date?
    Wizard player(playerName);
    //player.DisplayPlayerStats();

    // Runs game.
    //std::string audioFilePath = "C:\\Programming\\C++ Games\\LowLife\\LowLifeMusic\\main_theme.wav";
    //playAudio(audioFilePath, bold, delay1);
    //Introduction(delay1, playerName, player);
     
    // Creates game map.
    //InitialiseGameMap(playerName, player);

    //Enemy enemy("enemy", "", "", "", "", 100, 50, 10, 50);
    InitialiseBattle(delay1, player);

    return 0;
}

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file.
