#include <iostream>
#include <string.h>
#include <thread>
#include <chrono>  

// ##Classes##
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
        void MindTrick(int delay, std::string name) {
            std::string mindTrick = "\n" + name + "used MindTrick...";
            Stagger(mindTrick, delay);
        }
};

// ##Functions##
// Function staggers text that appears in the game.
void Stagger(const std::string& string, int delay_ms)
{
    // For loop iterates over each character in the string.
    for (char c : string) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
        std::cout << "";
    }
    std::cout << std::endl;
}

// Method delays the execution of the programme when called.
void Sleep() 
{
    using namespace std::this_thread;
    using namespace std::chrono;

    sleep_for(milliseconds(10));
    sleep_until(system_clock::now() + seconds(1));
}

// ##Main Function##
int main()
{
    // This section sets the variables.
    int delay = 50;
    int input;
    std::string name;

    // Player is asked their name
    std::string name1 = "Tell me your name LowLife...";
    Stagger(name1, delay);
    Sleep();
    std::string name2 = "\n...TELL ME!";
    Stagger(name2, delay);
    std::getline(std::cin, name);
    std::string name3 = "\nIt's a pleasure to meet you " + name + ".";
    Stagger(name3, delay);
    Sleep();

    // Player is asked their character selection.
    std::string character1 = "What are you?...A wizard? A beast? Perhaps an astronomer??";
    Stagger(character1, delay);
    std::string character;
    std::getline(std::cin, character);

    // If statment for character choice.
    if (character == "wizard") {
        std::string character2 = "\nAhh nowadays, the wizard's power has been muffled recently.";
        Stagger(character2, delay);
    }

    std::string character2 = "\nSo you are a " + character + ".";
    Stagger(character2, delay);





    return 0;
}


// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
