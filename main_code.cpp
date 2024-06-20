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

#pragma comment(lib, "irrKlang.lib")

// ##Namespaces##
//using namespace cv;
using namespace irrklang;

// ##Functions##
// Stagger function's bool value is set to false.
void Stagger(const std::string& string, int delay_ms, bool bold = false);

// Function staggers text that appears in the game.
void Stagger(const std::string& string, int delay_ms, bool bold)
{
    // ANSI escape codes initiate bold letters (using the "1" and "0")
    const std::string boldStart = "\033[1m";
    const std::string boldEnd = "\033[0m";

    if (bold) {
        std::cout << boldStart;
    }

    // For loop iterates over each character in the string.
    for (char c : string) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
        std::cout << "";
        if (bold == true) {

        }
    }

    if (bold) {
        std::cout << boldEnd;
    }

    std::cout << std::endl;
}

// Sleep_xs() methods delays the execution of the programme when called.
void Sleep_1s()
{
    using namespace std::this_thread;
    using namespace std::chrono;

    sleep_until(system_clock::now() + seconds(1));
}

void Sleep_5s()
{
    using namespace std::this_thread;
    using namespace std::chrono;

    sleep_until(system_clock::now() + seconds(5));
}

void TitleScreen(bool bold, int delay1, int musicDelay) {

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
    Stagger(title9, musicDelay);
    std::cout << "";
    std::getline(std::cin, title9);
}

void DisplayASCIIArtFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Could not open the file!" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    file.close();
}

using MapInventory = std::map<std::string, int>;
// ##Classes##
class Hermit {
public:

    // Inherited constructors.
    std::string name = "hermit";
    int dialogue = 0;

    //GameWorld test;

    /*
        void initiateregions() {
        test.InitialiseRegions(MultiValueMap & region, const std::string & description, const std::string & examination, const std::string & ask);
    }
    */
    // Methods.
    void StartingDialogue(std::string name) {

        std::string hermitFilePath = "C:\\C++ Games\\LowLife\\ASCIIFiles\\hermit.txt";
        DisplayASCIIArtFromFile(hermitFilePath);
        
        std::cout << "\nOh hello! I didn't see your wee-self over on those rocks.";
        std::cout << "\nI should really introduce myself; I'm being quite rude...I am Kroka of House Kruuka!";
        std::cout << "\nAnd you are..?";
        std::cout << "\nHow excellent to meet you " + name + "! I was just on my way to fish for the day...";
        std::cout << "\nBut I don't want to bore you. I noticed you were staring at the great Boruna - the portal between two vastly different worlds.";
        std::cout << "\nIf you were considering to enter that portal you require a spacesuit if you want to survive that realm...";
    }

    //if 

    /*
    void InitiateInfoDialogue() {
        if (region& B3 && )
    }
    */
};
class Player {
public:

    // Constructors.
    std::string location = "B2";
    int spaceSuitCount = 0;

    // ###Player Inventory### 
    // Each item is a string which can have its own quantity (using int vector).


    void InitialiseInventory(MapInventory& inventory) {

        inventory["Inter-realm Spacesuit"] = spaceSuitCount;
    }

    // Method prints out the description when a region has been entered.
    void ShowInventory(const MapInventory& inventory) const {
        for (const auto& item : inventory) {
            std::cout << item.first << " quantity: " << item.second << std::endl;
        }
    }

    void UpdateInventory() {

    }
};

class GameWorld : public Player {
public:

    // Creates a map that contains a single key but, multiple values (using a vector taking in strings).
    using MultiValueMapRegions = std::map<std::string, std::vector<std::string>>;

    // Instantiates objects of MultiValueMaps for each region (used when player enters an area).
    MultiValueMapRegions A1;
    MultiValueMapRegions A2;
    MultiValueMapRegions B1;
    MultiValueMapRegions B2;
    MultiValueMapRegions B4;
    MultiValueMapRegions C1;
    MultiValueMapRegions C2;

    MultiValueMapRegions A3;
    MultiValueMapRegions B3;
    MultiValueMapRegions C3;

    // Creates a player object.
    Player player;

    // Constructors for GameWorld Class.
    std::string description;
    std::string examination;
    std::string ask;
    std::string north = "north" "North";
    std::string east = "east" "East";
    std::string south = "south" "South";
    std::string west = "west" "West";
    //bool solved = false; ???

    // Creates a map that has a bool value for the map value.
    std::map<std::string, bool>solvedRegion;
    void SolvedRegions() {

        solvedRegion["A1"] = false, solvedRegion["A2"] = false, solvedRegion["A3"] = false,
        solvedRegion["B1"] = false, solvedRegion["B2"] = false, solvedRegion["B3"] = false,
        solvedRegion["C1"] = false, solvedRegion["C2"] = false, solvedRegion["C3"] = false;
    }

    // Update area accordingly??

        // Method initialises regions by giving each map an alias: 'region' etc.
    void InitialiseRegions(MultiValueMapRegions& region, const std::string& description, const std::string& examination, const std::string& ask) {

        // Instantiates objects of MultiValueMaps for each region (used when player enters an area).
        if (!description.empty()) {
            region["Description"].push_back(description);
        }
        else if (!examination.empty()) {
            region["Examination"].push_back(examination);
        }
        else if (!ask.empty()) {
            region["Ask"].push_back(ask);
        }
    }

    // Method prints out player's choices.
    void PlayerChoice() {
        std::cout << "\nWhat would you like to do?";
        std::cout << "\n";
        std::cout << "\nDescribe --- Examine --- Ask --- Travel --- Inventory";
        std::cout << "\n";
    }

    void PlayerTravel() {
        std::cout << "\nWhere would you like to venture to?";
        std::cout << "\n";
        std::cout << "\nNorth --- South --- East --- West";
        std::cout << "\n";
    }

    // Method prints out the description when a region has been entered.
    void PrintDescriptions(const std::vector<std::string>& descriptions) {
        for (const auto& text : descriptions) {
            std::cout << text << std::endl;
        }
    }

    // Handles player choice.
    void PlayerChoiceHandler(MultiValueMapRegions*& region, std::string name) {
        while (true) {
            PlayerChoice();
            std::string choice;
            std::cout << "\n> ";
            std::getline(std::cin, choice);

            if (choice == "describe" || choice == "Describe") {
                PrintDescriptions(region->at("Description"));
            }
            else if (choice == "examine" || choice == "Examine") {
                PrintDescriptions(region->at("Examination"));
            }
            else if (choice == "ask" || choice == "Ask") {
                PrintDescriptions(region->at("Ask"));
                // Creates a Hermit object and calls its starting dialogue.
                Hermit hermit;
                hermit.StartingDialogue(name);
            }
            else if (choice == "travel" || choice == "Travel") {
                PlayerTravel();
                std::string newRegion;
                std::cout << "\n> ";
                std::getline(std::cin, newRegion);

                MultiValueMapRegions* playerPosition = nullptr;

                if (newRegion == "A1") playerPosition = &A1;
                else if (newRegion == "A2") playerPosition = &A2;
                else if (newRegion == "A3") playerPosition = &A3;
                else if (newRegion == "B1") playerPosition = &B1;
                else if (newRegion == "B2") playerPosition = &B2;
                else if (newRegion == "B3") playerPosition = &B3;
                else if (newRegion == "B4") playerPosition = &B4;
                else if (newRegion == "C1") playerPosition = &C1;
                else if (newRegion == "C2") playerPosition = &C2;
                else if (newRegion == "C3") playerPosition = &C3;
                else {
                    std::cout << "Please enter a valid direction or region...\n";
                    continue;
                }

                region = playerPosition;
                PrintDescriptions(playerPosition->at("Description"));
                PlayerChoiceHandler(playerPosition, name);

            }
            else if (choice == "inventory" || choice == "Inventory") {
                //Player player;
                MapInventory inventory;

                player.InitialiseInventory(inventory);
                player.ShowInventory(inventory);
            }
            else {
                std::cout << "Please enter a real word silly...";
                continue;
                
            }
        }
    }

    void RegionNavigation(const std::string& name) {

        // Descriptors for each area.
        InitialiseRegions(A1, "\n" + name + " arrived to find a lagoon flourishing with various species of funghi.", "\nOne mushroom seemed to glow with a preciosu aura.", "\nUnfortunately, there's no one to ask...");
        InitialiseRegions(A2, "\nAfter days of travelling, " + name + " discovered a derelict temple surrounded by no sign of life.", "\nIf " + name + " listened carefully, they could hear the faint sound of industrial work emitting from the temple.", "\nUnfortunately, there's no one to ask...");
        InitialiseRegions(A3, "\nA great plateau of moon rock spread to as far as " + name + "'s eyes could see.", "\nA distant palace consisting of gems and moon rock could be seen.", "\nUnfortunately, there's no one to ask...");
        InitialiseRegions(B1, "\nA mysterious tower loomed at the back of the ancient ravine " + name + " found themselves in.", "\nB;ue, ghostly characters seemed to wander about the tower's rooms.", "\nUnfortunately, there's no one to ask...");
        InitialiseRegions(B2, "\n" + name + " found thmselves inside a collosal ravine, with a powerful rapids running through it.", "\nWhen " + name + " examined the landscape, they saw ancient statues carved into the stone walls.", "\nUnfortunately, there's no one to ask...");
        InitialiseRegions(B3, "\nAfter a day of travelling, the ravine finally opened up to reveal a gorgeous mountain range however, there was one thing off about it...\nA hermit is poorly hiding from you.", "\n" + name + " wondered whether it was magic or potentially technology causing this.", "\n" + name + " asked the hermit about the mountain...");
        InitialiseRegions(B4, "\nThe teleporter threw " + name + " into a luminescent expanse.\nA massive spaceport stood a couple miles away.", "A blue spaceship was offering rides across this planet.", "\nUnfortunately, there's no one to ask nearby...");
        InitialiseRegions(C1, "\nAfter a long sail, " + name + " reached a vast tropical island.\nA dangerous storm hung above the island.", "A long-abandoned route led into the deep jungle.", "\nUnfortunately, there's no one to ask...");
        InitialiseRegions(C2, "\nThe trail led into a long-forgotten wood.\nEach tree had its own skeletal face which seemed to groan and move to follow " + name + " as they explored through.", "\nAt the end of the trail stood a possessed pig.", "\nThe rotten creature strode towards " + name + ".");
        InitialiseRegions(C3, "\nA week later, " + name + " found themselves in a land encapsulated by darkness.\nAn immense green pyramid rose into the clouds.\nA gleaming light protruded from its peak.", "\nA section of the pyramid looked like it could be opened up by placing some type of object onto a pedestal nearby.", "\nUnfortunately, there's no one to ask...");

        // Sets player's starting location and prints it out.
        MultiValueMapRegions* playerPosition = &B2;
        PrintDescriptions(playerPosition->at("Description"));

        PlayerChoiceHandler(playerPosition, name);

        /* Prints out automatic description of newly - entered region.
        std::vector<std::string> keys = { "Description", "Examination", "Ask" };
        for (const std::string& key : keys) {
            for (const std::string value : B2[key]) {
                std::cout << value << " ";
            }
            std::cout << std::endl;
        }
        */
    }
};

class Wizard {
public:

    // Attributes.
    //int level;
    int strength = 10;
    int magic = 50;
    int intelligence = 40;
    int wealth = 0;
    int darkness = 60;

    // Abilities.
    void MindTrick(int delay1, std::string name) {
        std::string mindTrick = "\n" + name + "used MindTrick...";
        Stagger(mindTrick, delay1);
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
    std::string speech;
    std::string itemRequest;
    std::string abilities;
    std::string health;

    // Methods.
};



class B3Class {
public:

    // Constructors.
    Hermit hermit;
    GameWorld b3Gameworld;

    // Methods.
    void ActionHandler(GameWorld::MultiValueMapRegions*& region) {
        //b3Gameworld.PlayerChoiceHandler(region, name);
    }

    void HermitDialogue() {
        //hermit.InitiateInfoDialogue();
    }
};

// ##GameChronology##
void Prologue(int delay1, int delay2, bool bold, int musicDelay) 
{
    // Highlighted red words.
    std::string moranthia = "\033[31mMoranthia\033[0m";
    std::string darkness = "\033[31mDarkness\033[0m";
    std::string lowlives = "\033[31mLowLives\033[0m";

    std::string prologue1 = "\nThere was once a land of many mythical beings...";
    Stagger(prologue1, musicDelay);
    Sleep_1s();
    std::string prologue2 = "\n...this realm of fantasy and science came to be known as " + moranthia + "...";
    Stagger(prologue2, musicDelay);
    Sleep_1s();
    std::string prologue3 = "\n...however, as the centuries went on, these mythical beings began to fall in numbers; as the " + darkness + " possessed their mind and will...";
    Stagger(prologue3, musicDelay);
    Sleep_1s();
    std::string prologue4 = "\n...those that remained came to be known as " + lowlives + "; once beings with awesome power and influence, now mere mortals amongst a diverging world.";
    Stagger(prologue4, musicDelay);
    Sleep_5s();
}

void Introduction(int delay1, std::string name)
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
    std::string character1 = "\nWhat are you?...A wizard? A beast? Perhaps an astronomer??";
    Stagger(character1, delay1);

    // Player is asked their character selection.
    while (true) {

        std::string character;
        std::cout << "\n> ";
        std::getline(std::cin, character);

        if (character == "wizard" || character == "Wizard") {
            // Creates a Wizard object.
            Wizard wizard;

            std::string wizard1 = "Hmm, wizards have dwindled in numbers since the Darkness befell the land.";
            Stagger(wizard1, delay1);
            break;
        }
        else if (character == "beast" || character == "Beast") {
            //Creates a Beast object.
            Beast beast;

            std::string beast1 = "Hmm, a beast you say? You're not going to transform on me are you haha?";
            Stagger(beast1, delay1);
            break;
        }
        else if (character == "astronomer" || character == "Astronomer") {
            // Creates an Astronomer object.
            Astronomer astronomer;

            std::string astronomer1 = "Hmm, an astronomer? Fascinating. I was discouraged to become one of those as a child.";
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

    std::string lore1 = "\nAnyhow, I should warn you LowLife; the realm of Moranthia is not a place of sunshine and happiness...";
    Stagger(lore1, delay1);
    std::string lore2 = "\nThe creatures that live in this land must NEVER be trusted. No matter how genuine they may seem...";
    Stagger(lore2, delay1);
    std::string lore3 = "\nYou'll never meet anyone as kind and fair as me.";
    Stagger(lore3, delay1);
    std::string lore4 = "\nI don't recommend travelling to see Lord Bali and his order of slaves and worshippers either; however, he does enjoy his trades...";
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

    // Creates a GameWorld object and calls its methods.
    GameWorld gameWorld;
    gameWorld.SolvedRegions();
    gameWorld.RegionNavigation(name);
}

void playAudio(const std::string& filePath, bool bold, int delay1, int delay2, int musicDelay) {

    // Create sound engine
    ISoundEngine* engine = createIrrKlangDevice();

    if (!engine) {
        std::cerr << "Could not initialise sound engine" << std::endl;
        return;
    }

    // Play the sound file
    ISound* sound = engine->play2D(filePath.c_str(), true);

    TitleScreen(bold, delay1, musicDelay);
    Prologue(delay1, delay2, bold, musicDelay);

    // Wait until user interrupts with a key press
    std::cin.get(); // Wait for user input to stop playback

    // Stop and drop the sound engine
    engine->stopAllSounds();
    engine->drop();
}

// ##Main Function##
int main()
{
    // Section sets the variables.
    int delay1 = 50;
    int delay2 = 200;
    int musicDelay = 30;
    int input;
    bool bold = false;
    std::string name = "Max";

    std::string audioFilePath = "C:\\Programming\\C++ Games\\LowLife\\LowLifeMusic\\main_theme.wav";
    //playAudio(audioFilePath, delay1, delay2, bold, musicDelay);

    Introduction(delay1, name);

    return 0;
}


// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
