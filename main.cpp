//warning happens in rlutil, so I disable it
#ifdef _MSC_VER
    #pragma warning( disable : 4267 )
#endif

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <deque>
#include <fstream>
#include <cmath>
#include <filesystem>
#include <cstdlib>
#include "ext/random.hpp"
#include "boost.h"
#include "autoFarmer.h"
#include "normalProfile.h"
#include "wordlist.h"
#include "errors.h"
#include "ext/rlutil/rlutil.h"
#include "profileMinimal.h"
#include "hardcoreProfile.h"
#include "application.h"
#include "randomWords.h"


using Random = effolkronium::random_static;
namespace fs = std::filesystem;

template <typename T>
std::string collectionToString(T col)
{
    std::stringstream ss;
    for(auto i : col)
    {
        ss << i << " ";
    }
    return ss.str();
}


void mainMenu()
{
    std::cout << "\np to play\ns for shop\nc to create a copy of current profile\nq to save and quit\n";
}
void getReady()
{
    std::string temp1;
    std::cout << "q to quit\n";
    rlutil::msleep(600);
    std::cout << "GET READY TO TYPE.\n";
    rlutil::msleep(600);
    std::cout << "3.\n";
    rlutil::msleep(600);
    std::cout << "2.\n";
    rlutil::msleep(600);
    std::cout << "1.\n";
    rlutil::msleep(400);
    std::cout << "GO!\n";
    rlutil::msleep(400);
    getline(std::cin, temp1);
    rlutil::cls();
}
void tutorial(){
    rlutil::cls();
    std::cout << "NEW PROFILE DETECTED. TIME FOR TUTORIAL.\n\n";
    rlutil::msleep(1000);
    std::cout << "Your job is to type the words on the screen.\n\n";
    rlutil::msleep(1000);
    std::cout << "If you do a good job you will be awarded points.\n\n";
    rlutil::msleep(1000);
    std::cout << "If you do a bad job you will either recieve 0 points or an invalid length warning.\n\n";
    rlutil::msleep(1000);
    std::cout << "Here's some examples:\n\n";
    randomWords<12,12> rw;
    std::cout << collectionToString(rw.getRandomWords()) << "\n\n";
    std::cout << "^ You're supposed to type all that in, ideally with no mistakes. ^\n\n\n";
    rlutil::msleep(1000);
    std::cout << "That's all for the tutorial. It's time for you to play.\n\nPress any key to continue...";
    rlutil::anykey();
}


int main()
{
    auto& app = application::get_app();
    auto& wl = wordlist::get_wordlist();
    wl.init();

    app.init();


    std::string userInput;
    bool logged = false;
    int failcount = 0;
    fs::create_directories("userdata");
    while(true)
    {
        if(!logged) // login, but there is no logout feature yet
        {
            while(true) // profile selection loop
            {
                if(logged) break;
                getline(std::cin, userInput);
                if(userInput == "q" || userInput == "Q") return 0;
                else if(userInput == "new") {
                    int tries = 0;
                    while (true) {
                        tries ++;
                        try {
                            std::cout << "Name your profile: ";
                            std::cin >> userInput;
                            //bool nameused = false;
                            if(userInput.length() < 2)
                                throw naming_error{"This name is too short. Give me antoher one.\n"};
                            for (auto i: app.getProfileList()) {
                                if (i->getName() == userInput) {
                                    throw naming_error{"This name is already on the list. Give me antoher one.\n"};
//                                nameused = true;
                                    break;
                                }
                            }
                            normalProfile aup{userInput};
                            app.setCurrentProfile(aup.clone());
                            app.addToProfileList(aup.clone());
                            tutorial();
                            logged = true;


                            break;
                        }
                        catch (app_error &err) {
                            if (tries > 5) {std::cout << "You're obviously not here to create a new profile so I'm going. Bye!"; return 0;}

                            std::cout << err.what();

                        }
                    }
                }
                else if(userInput == "new hardcore") {
                    int tries = 0;
                    while (true) {
                        tries ++;
                        try {
                            std::cout << "Name your profile: ";
                            std::cin >> userInput;
                            //bool nameused = false;
                            if(userInput.length() < 2)
                                throw naming_error{"This name is too short. Give me antoher one.\n"};
                            for (auto i: app.getProfileList()) {
                                if (i->getName() == userInput) {
                                    throw naming_error{"This name is already on the list. Give me antoher one.\n"};
//                                nameused = true;
                                    break;
                                }
                            }
//                        if (nameused) throw naming_error{"This name is already on the list. Give me antoher one."};
//                        if (!nameused)
//                        {
                            hardcoreProfile aup{userInput};
                            app.setCurrentProfile(aup.clone());
                            app.addToProfileList(aup.clone());
                            logged = true;
                            tutorial();
                            break;
//                        }
                        }
                        catch (app_error &err) {
                            if (tries > 5) {std::cout << "You're obviously not here to create a new profile so I'm going. Bye!"; return 0;}

                            std::cout << err.what();

                        }
                    }
                }
                else
                {
                    bool matching = false;
                    for(auto i : app.getProfileList())
                    {
                        if(userInput == i->getName())
                        {
                            matching = true;
                            app.setCurrentProfile(i);
                            std::cout << "profile selected: " << userInput << "\n";
                            break;
                        }
                    }
                    if(matching)
                    {
                        logged = true;
                        break;
                    }
                    else
                    {
                        std::cout << "profile not found\n";
                        failcount ++;
                    }
                    if(failcount >= 5) break;
                }
            }
        }
        while(true) // most user interaction happens here
        {
            rlutil::cls();
            std::cout << "Yo. Choose an option. Playing on profile "<< app.getCurrentProfile()->getName() << "\n";
            mainMenu();
            std::cin >> userInput;
            if(userInput[0] == 'q' || userInput[0] == 'Q')
            {
                if(!logged) rlutil::msleep(2); // just to pass cppcheck on clang 11
                app.quitGame();
                return 0;
            }
            else if(userInput[0] == 'c' || userInput[0] == 'C')
            {
                auto aup = app.getCurrentProfile()->clone();
                aup->setName("copy of " + app.getCurrentProfile()->getName());
                app.addToProfileList(aup);
            }
            else if(userInput[0] == 'p' || userInput[0] == 'P') // play cycle
            {
                getReady();
                app.playCycle();
            }
            else if(userInput[0] == 's' || userInput[0] == 'S')
            {
                try{
                    app.buyCycle();
                }
                catch(shop_error& err)
                {
                    std::cout << "\n" << err.what() << "\n";
                    rlutil::msleep(1000);
                }
            }
            else {std::cout << "No clue what you're trying to do."; return 0;}
        }
        break;
    }

    return 0;
}

