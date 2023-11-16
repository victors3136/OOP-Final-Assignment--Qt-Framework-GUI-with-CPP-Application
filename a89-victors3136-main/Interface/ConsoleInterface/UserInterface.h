//
// Created by victor on 17/05/2023.
//

#ifndef A89_VICTORS3136_1_USERINTERFACE_H
#define A89_VICTORS3136_1_USERINTERFACE_H

#include "../../Headers/Manager.h"
#include <iostream>
#include <regex>

class UserInterface {

private:
    Manager man;
    std::string input;

    [[nodiscard]] std::string getInput()const {return input;};
    void readInput(const std::string& prompt) {
        std::cout<<prompt;
        std::getline(std::cin, input);
    };
    void runUserMode();
    void runAdminMode();
    void chooseMode()
    {
        if(input == "user") {
            runUserMode();
            printMainMenu();
            return;
        }
        if(input == "admin") {
            runAdminMode();
            printMainMenu();
            return;
        }
        std::cout << "This is not an accepted mode..." << std::endl;
    };
    static void printMainMenu()
    {
        std::cout<<"Choose mode: "<<std::endl;
        std::cout<<"\tadmin"<<std::endl;
        std::cout<<"\tuser"<<std::endl;
        std::cout<<"\texit"<<std::endl;

    };
    static void printAdminMenu()
    {
        std::cout<<"Write the key word for the command you want to use:"<<std::endl;
        std::cout<<"\tadd -> input a new tutorial and add it to the database"<<std::endl;
        std::cout<<"\tremove -> remove an existing tutorial from the database"<<std::endl;
        std::cout<<"\tmodify -> modify the field of an existing tutorial"<<std::endl;
        std::cout<<"\tlist -> show all entries currently in the database"<<std::endl;
        std::cout<<"\texit -> exit the program"<<std::endl;
    };
    static void printUserMenu()
    {
        std::cout<<"Write the key word for the command you want to use:"<<std::endl;
        std::cout<<"\tnext -> fetch the next tutorial "<<std::endl;
        std::cout<<"\tlike -> add the current tutorial to the favourites playlist"<<std::endl;
        std::cout<<"\tremove -> who knows what this does?"<<std::endl;
        std::cout<<"\twatchlist -> display all the videos in the watchlist list"<<std::endl;
        std::cout<<"\tliked -> show all liked videos"<<std::endl;
        std::cout<<"\topen -> open the specialised file in an external app"<<std::endl;
        std::cout<<"\texit -> exit the program"<<std::endl;
    };
    bool correctPassword(){
        return input == "password";
    }
    static void openLink(const Tutorial& toOpen);

public:
    UserInterface()=default;
    virtual ~UserInterface()=default;
    void run()
    {
	    readInput("Type of file to generate (html/csv): ");
	    while(true){
		    try{
			    man.setRepoType("initload.txt", input, "data.txt");
			    break;
		    }catch(const RepositoryError& err){
			    std::cout<<err.what()<<std::endl;
			    readInput("Type of file to generate (html/csv): ");
		    }
	    }
        printMainMenu();
        while(true)
        {
            readInput("> ");
            if(input == "exit")
                return;
            else chooseMode();
        }
    }
};


#endif //A89_VICTORS3136_1_USERINTERFACE_H
