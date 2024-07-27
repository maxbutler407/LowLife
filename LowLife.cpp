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

#include "Player.h"
#include "Enemy.h"
#include "Utility.h"

#pragma comment(lib, "irrKlang.lib")

//using namespace cv;
using namespace irrklang;
using MapInventory = std::map<std::string, int>;

int delay1 = 30;
int delay2 = 100;
std::string playerName = "\033[33mMax\033[0m";
std::string hermitsPlayerName;
std::string GAMEOVER = "\n\n\n\033[31m                                                GAME OVER.\033[0m\n\n\n";

// ----------Classes----------
class Wizard : public Player {
public:
    // Attributes.
    Wizard(std::string playerName) : Player(playerName, 100, 10, 50, 40, 0, 60) {};

    // Abilities.
    void MindTrick(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {
        std::string mindTrick1 = "\n" + playerName + " used a \033[34mmind trick\033[0m...\n\n... \033[31m-";
        Stagger(mindTrick1, delay1);
        int mindTrick2 = magic;
        StaggerInt(mindTrick2, delay1);
        std::string mindTrick3 = " enemy damage\033[0m!";
        Stagger(mindTrick3, delay1);
        enemy.DecreaseDamage(magic);
    }
    void SinisterSpell(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {
        std::string spell1 = "\n" + playerName + " used a \033[34mpowerful spell\033[0m...\n\n... \033[31m-";
        Stagger(spell1, delay1);
        int spell2 = magic;
        StaggerInt(spell2, delay1);
        std::string spell3 = " enemy health\033[0m!";
        Stagger(spell3, delay1);
        enemy.DecreaseHealth(magic);
    }
    void SelfEnchant(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {
        std::string spell1 = "\n" + playerName + " \033[34menchanted\033[0m themselves...\n\n... \033[34m";
        Stagger(spell1, delay1);
        magic += 10;
        std::string spell3 = "+10 player damage\033[0m!";
        Stagger(spell3, delay1);
        player.IncreaseStrength(magic);
    }
    void DarkForces(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {
        std::string spell1 = "\n" + playerName + " summoned \033[34mpowers from an evil realm\033[0m onto the " + enemyName + "...\n\n... \033[31m-";
        Stagger(spell1, delay1);
        int spell2 = magic;
        StaggerInt(spell2, delay1);
        std::string spell3 = " enemy health\033[0m!";
        Stagger(spell3, delay1);
        enemy.DecreaseHealth(magic);

        // Increases player's darkness stat.
        int darknessCalculation = enemy.darkness * 0.8;
        std::string spell4 = "\n\n" + playerName + "'s darkness has increased...";
        Stagger(spell4, delay1);
        player.IncreaseDarkness(darknessCalculation);
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
    // strength == 70 when ability is active.
    Beast(std::string playerName) : Player(playerName, 100, 70, 10, 20, 0, 0) {};
    // Attributes.

    // Abilities.
    void Transform(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {
        std::string transform = "\n" + playerName + " \033[34mtransformed\033[0m into a creature of mythical and powerful origin...";
        Stagger(transform, delay1);

        // Increases player's darkness stat.
        int darknessCalculation = enemy.darkness * 0.8;
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
        std::string roar1 = "\n" + playerName + " opened their jaws to bellow a terrifying \033[34mroar\033[0m...\n\n... \033[31m-";
        Stagger(roar1, delay1);
        int roar2 = magic;
        StaggerInt(roar2, delay1);
        std::string roar3 = " enemy damage\033[0m!";
        Stagger(roar3, delay1);
        enemy.DecreaseDamage(magic);
    }
    void BeatDown(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {
        std::string beat1 = "\n" + playerName + " lept onto the " + enemyName + ", \033[34mbeating\033[0m it ferociously...\n\n... \033[31m-";
        Stagger(beat1, delay1);
        int boostedStrength = 70;
        StaggerInt(boostedStrength, delay1);
        std::string beat2 = " enemy health\033[0m!";
        Stagger(beat2, delay1);
        enemy.DecreaseHealth(boostedStrength);
    }
    void ClawStab(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {
        std::string spell1 = "\n" + playerName + " pierced their serrated \033[34mclaw\033[0m into the " + enemyName + "...\n\n... \033[31m-";
        Stagger(spell1, delay1);
        int boostedStrength = 70;
        StaggerInt(boostedStrength, delay1);
        std::string spell2 = " enemy health\033[0m!";
        Stagger(spell2, delay1);
        enemy.DecreaseHealth(boostedStrength);
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
    Astronomer(std::string playerName) : Player(playerName, 100, 20, 10, 60, 0, 20) {};

    // Abilities.
    void Examine(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {
        std::string examine1 = "\n" + playerName + "\033[34midentified\033[0m the " + enemyName + "'s weaknesses...\n\n... \033[31m-";
        Stagger(examine1, delay1);
        int examine2 = intelligence;
        StaggerInt(examine2, delay1);
        std::string examine3 = " enemy damage\033[0m!";
        Stagger(examine3, delay1);
        enemy.DecreaseDamage(intelligence);
    }
    void OptimiseMoves(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {
        std::string calculate1 = "\n" + playerName + " \033[34mcalculated\033[0m their advantages...\n\n... \033[34m";
        Stagger(calculate1, delay1);
        intelligence += 10;
        std::string calculate3 = "+10 player damage\033[0m!";
        Stagger(calculate3, delay1);
        player.IncreaseStrength(intelligence);
    }
    void CallTheStars(int delay1, const std::string& playerName, const std::string& enemyName, Player& player, Enemy& enemy) override {
        std::string call1 = "\n" + playerName + " brought down the \033[34mlight\033[0m from the sky...\n\n... \033[31m-";
        Stagger(call1, delay1);
        int call2 = magic;
        StaggerInt(call2, delay1);
        std::string call3 = " enemy health\033[0m!";
        Stagger(call3, delay1);
        enemy.DecreaseHealth(magic);

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
class NPC {
public:
    // Parent constructors.
    std::string name;
    std::string dialogue;
    std::string itemRequest;
    std::string abilities;
    std::string health;

    // Parent methods.
    NPC(const std::string& name, const std::string& dialogue)
        : name(name), dialogue(dialogue) {}
};
class Hermit : public NPC {
public:
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

    void addPerson(const Hermit& hermit) {
        // Adds NPC objects to npcs vector.
        npcs.push_back(hermit);
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
void IntroductionP1(int delay1, std::string name, Player& player) {
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
}
void IntroductionP2(int delay1, std::string name, Player& player) {
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
    Region A1("\033[33mFungisle\033[0m", "\n\n" + playerName + " arrived to find a lagoon flourishing with various species of funghi.\nOne mushroom seemed to glow with a precious aura.");
    A1.addItem(Item("\nMera's Glowth", "Glowed with a precious aura."));
    A1.addPerson(NPC("\nUnfortunately, there's no one to ask...", "..."));
    map.setArea(0, 0, A1);

    Region A2("", "\n\nAfter days of travelling, " + playerName + " discovered a derelict temple surrounded by no sign of life.\nIf " + playerName + " listened carefully, they could hear the faint sound of industrial work emitting from the temple.");
    A2.addItem(Item("\nUnfortunately, there's no item here...", "..."));
    A2.addPerson(NPC("\nUnfortunately, there's no one to ask...", "..."));
    map.setArea(0, 1, A2);

    Region A3("A3", "\n\n" + playerName + " looked North across the horizon and saw many places which they hoped to visit someday.");
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

    Region C3("C3", "\n\n" + playerName + " peered South across the horizon and saw many places which they hoped to visit someday.");
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
void InitialiseBattle(int delay1, Player& player, const std::string& playerName, std::string character) {
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
        if (character == "wizard" || character == "Wizard") {
            std::string battleChoice;
            std::string battle2 = "\n\nWhat would you like to do?";
            Stagger(battle2, delay1);
            std::cout << "\n|        MindTrick        ||     SinisterSpell       |";
            std::cout << "\n|       SelfEnchant       ||       DarkForces        |";
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
            else {
                std::cout << "Please select an action silly boy.";
            }
            if (enemy.health > 0) {
                enemy.EnemyAttack(delay1, player);
            }
        }


        else if (character == "beast" || character == "Beast") {
            if (!transformed) {
                std::string battleChoice;
                std::string battle2 = "\n\nWhat would you like to do?";
                Stagger(battle2, delay1);
                std::cout << "\n|        Transform        ||       ThrowStone        |";
                std::cout << "\n> ";
                std::getline(std::cin, battleChoice);

                if (battleChoice == "Transform" || battleChoice == "transform") {
                    transformed = true;
                    player.Transform(delay1, playerName, enemy.enemyName, player, enemy);
                }
                else if (battleChoice == "ThrowStone" || battleChoice == "Throwstone" || battleChoice == "throwstone") {
                    player.ThrowStone(delay1, playerName, enemy.enemyName, player, enemy);
                }
                else {
                    std::cout << "Please select an action silly boy.";
                }
                if (enemy.health > 0) {
                    enemy.EnemyAttack(delay1, player);
                }
            }
            else {
                std::string transformChoice;
                std::string transform = "\n\nWhat would you like to do?";
                Stagger(transform, delay1);
                std::cout << "\n|        Transform        ||       FearfulRoar       |";
                std::cout << "\n|        BeatDown         ||        ClawStab         |";
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
                else {
                    std::cout << "Please select an action silly boy.";
                }
                if (enemy.health > 0) {
                    enemy.EnemyAttack(delay1, player);
                }
            }
        }
    




        else if (character == "astronomer" || character == "Astronomer") {
            std::string battleChoice;
            std::string battle2 = "\n\nWhat would you like to do?";
            Stagger(battle2, delay1);
            std::cout << "\n|        Examine          ||      OptimiseMoves      |";
            std::cout << "\n|      CallTheStars       ||  UseTelescopeAsWeapon   |";
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
            else {
                std::cout << "Please select an action silly boy.";
            }
            if (enemy.health > 0) {
                enemy.EnemyAttack(delay1, player);
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
            player.magic = 50;
        }
        else if (character == "beast" || character == "Beast") {
        }
        else if (character == "astronomer" || character == "Astronomer") {
            player.intelligence = 60;
        }
        player.DisplayPlayerStats();
    }
    else if (player.darkness >= 100) {
        std::string darknessDeath1 = "\n" + playerName + " was now fully consumed by the darkness inside them...";
        Stagger(darknessDeath1, delay1);
        std::string darknessDeath2 = "\n" + playerName + " collapsed to the floor as the black goo streamed out of their eyes and mouth...";
        Stagger(darknessDeath2, delay1);
        std::string darknessDeath3 = "\nOur hero died in agony as the darkness took another LowLife.";
        Stagger(darknessDeath3, delay1);
        Stagger(GAMEOVER, delay2);
        // Ends the game.
        exit(0);
    }
    else {
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
    }
}

// ----------Main Function----------
int main()
{
    // Variables.
    int delay2 = 100;
    //int musicDelay = 30;
    //int input;
    bool bold = false;
    std::string character;

    // Allows players stats to be kept up to date?
    

    // ----------Runs Game Chronology----------
    //std::string audioFilePath = "C:\\Programming\\C++ Games\\LowLife\\LowLifeMusic\\main_theme.wav";
    //playAudio(audioFilePath, bold, delay1);
    //IntroductionP1(delay1, playerName, player);
    Player* player = nullptr; // Creates a null pointer.
    
    // Player is asked their character selection.
    /*
    std::string character1 = "\nWhat are you LowLife?...A wizard? A beast? Perhaps an astronomer??";
    Stagger(character1, delay1);
    while (true) {
        std::cout << "\n> ";
        std::getline(std::cin, character);
        if (character == "wizard" || character == "Wizard") {
            player = new Wizard(playerName);
            std::string wizard1 = "\nHmm, wizards have dwindled in numbers since the Darkness befell the land.";
            Stagger(wizard1, delay1);
            break;
        }
        else if (character == "beast" || character == "Beast") {
            player = new Beast(playerName);
            std::string beast1 = "\nHmm, a beast you say? You're not going to transform on me are you haha?";
            Stagger(beast1, delay1);
            break;
        }
        else if (character == "astronomer" || character == "Astronomer") {
            player = new Astronomer(playerName);
            std::string astronomer1 = "\nHmm, an astronomer? Fascinating. I always wished to be one of you. Ah well.";
            Stagger(astronomer1, delay1);
            break;
        }
        else {
            std::string retry = "\nWhat are you?...A wizard? A beast? Perhaps an astronomer??";
            Stagger(retry, delay1);
        }
    }
    */
    //IntroductionP2(delay1, playerName, player);
    
    // Creates game map.
    InitialiseGameMap(playerName, *player);
    //player->DisplayPlayerStats();
    //InitialiseBattle(delay1, *player, playerName, character);



    // Clean up dynamically allocated memory created by "Player* player = nullptr;".
    delete player;

    return 0;
}