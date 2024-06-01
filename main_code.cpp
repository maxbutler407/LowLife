#include <iostream>
#include <string.h>
#include <string>
#include <thread>
#include <chrono>  

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

// ##Classes##
class GameWorld {
public:
    int map;
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

// ##GameChronology##
// Start-up text.
void Prologue(int delay1, int delay2, bool bold) 
{
    // Highlighted red words.
    std::string marosia = "\033[31mMarosia\033[0m";
    std::string darkness = "\033[31mDarkness\033[0m";
    std::string lowlives = "\033[31mLowLives\033[0m";

    std::string prologue1 = "There was once a land of many mythical beings...";
    Stagger(prologue1, delay1);
    Sleep_1s();
    std::string prologue2 = "\n...this realm of fantasy and science came to be known as " + marosia + "...";
    Stagger(prologue2, delay1);
    Sleep_1s();
    std::string prologue3 = "\n...however, as the centuries went on, these mythical beings began to fall in numbers; as the " + darkness + " possessed their mind and will...";
    Stagger(prologue3, delay1);
    Sleep_1s();
    std::string prologue4 = "\n...those that remained came to be known as " + lowlives + "; once beings with awesome power and influence, now mere mortals amongst a diverging world";
    Stagger(prologue4, delay1);
    Sleep_5s();
}

void Introduction(int delay1, std::string name)
{
    // Player is asked their name
    std::string name1 = "\nTell me your name LowLife...";
    Stagger(name1, delay1);
    Sleep_1s();
    std::string name2 = "\n...TELL ME!";
    Stagger(name2, delay1);
    std::cout << "\n>";
    std::getline(std::cin, name);
    std::string name3 = "\nIt's a pleasure to meet you " + name + ".";
    Stagger(name3, delay1);
    Sleep_1s();
    std::string character1 = "\nWhat are you?...A wizard? A beast? Perhaps an astronomer??";
    Stagger(character1, delay1);

    // Player is asked their character selection.
    while (true) {

        std::string character;
        std::cout << "\n>";
        std::getline(std::cin, character);

        if (character == "wizard" || "Wizard") {
            std::cout << "Wizard test";
            Wizard wizard;
            wizard.MindTrick(delay1, name);
        }
        else if (character == "beast" || "Beast") {
            std::cout << "Beast test";
            Beast beast;
        }
        else if (character == "astronomer" || "Astronomer") {
            std::cout << "Astronomer test";
            Astronomer astronomer;
        }
        else {
            std::string character1 = "\nWhat are you?...A wizard? A beast? Perhaps an astronomer??";
            Stagger(character1, delay1);
            std::getline(std::cin, character);
            continue;
        }
    }
}







// ##Main Function##
int main()
{
    // Section sets the variables.
    int delay1 = 50;
    int delay2 = 200;
    int input;
    bool bold = false;
    std::string name;

    // Section calls the GameChronology Functions
    //Prologue(delay1, delay2, bold);
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
