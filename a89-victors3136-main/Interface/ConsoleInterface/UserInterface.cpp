//
// Created by victor on 17/04/2023.
//

#include "UserInterface.h"
#include "../../ErrorsAndValidators/Validator.h"

void UserInterface::runUserMode()
{
    std::cout<<"Entering user mode..."<<std::endl;
	readInput("Enter a presenter name: ");
	std::vector<Tutorial> likesPlaylist;
	std::vector<Tutorial> playlist = man.getByPresenter(input);
	if(!playlist.empty()) {
		int index = 0;
		printUserMenu();
		Tutorial currentTutorial = playlist[index];
		UserInterface::openLink(currentTutorial);
		while (!playlist.empty()) {
			readInput("> ");
			if (input == "exit")
				break;
			if (input == "next") {
				index++;
				if (index >= playlist.size())
					index = 0;
				currentTutorial = playlist[index];
				UserInterface::openLink(currentTutorial);
				goto end;
			}
			if (input == "like") {
                if(std::find(likesPlaylist.begin(), likesPlaylist.end(), currentTutorial) != likesPlaylist.end())
				    likesPlaylist.push_back(currentTutorial);
				playlist[index].setLikes(currentTutorial.getLikes() + 1);
				goto end;
			}
			if (input == "remove") {
				playlist.erase(playlist.begin() + index);
				if (index >= playlist.size())
					index = 0;
				if(!playlist.empty()){
					currentTutorial = playlist[index];
					UserInterface::openLink(currentTutorial);
				}
				else{std::cout<<"No more videos to show; you will now be taken back to the main menu"<<std::endl; break;}
				goto end;
			}
			if (input == "watchlist") {
				for (const auto & i : playlist)
					std::cout << i.strung() << std::endl;
				goto end;
			}
			if (input == "liked") {
				for (const auto & tutorial : likesPlaylist)
					std::cout << tutorial.strung() << std::endl;
				goto end;
			}
            if (input == "open") {
                man.openExternal();
				goto end;
            }
			std::cout << "That is not a valid option :(" << std::endl;
			end:
			printUserMenu();
		}
	}else{
		std::cout<<"No presenter by that name :("<<std::endl;
	}
}

void UserInterface::runAdminMode()
{
    std::cout<<"Entering admin mode..."<<std::endl;
	readInput("Enter password: ");
	if(!correctPassword()){
		std::cout<<"Incorrect password :("<<std::endl;
		return;
	}
	printAdminMenu();
	while(true){
		readInput("> ");
		if(input == "exit")
			break;
		if(input == "add")
		{
			Tutorial t;
			readInput("title: ");
            while(true){
                try{
                    Validator::validateTitle(input);
                    break;
                }catch(const ValidatorError& err){
                    std::cout<<err.what()<<std::endl;
                    readInput("title: ");
                }
            }
			t.setTitle(input);
			readInput("presenter: ");
            while(true){
                try{
                    Validator::validatePresenter(input);
                    break;
                }catch(const ValidatorError& err){
                    std::cout<<err.what()<<std::endl;
                    readInput("presenter: ");
                }
            }
			t.setPresenter(input);
			readInput("duration: ");
            while(true){
                try{
                    Validator::validateDuration(input);
                    break;
                }catch(const ValidatorError& err){
                    std::cout<<err.what()<<std::endl;
                    readInput("duration: ");
                }
            }
			t.setDuration(std::stoi(input));
			readInput("likes: ");
			while(true){
				try{
					Validator::validateLikes(input);
					break;
				}catch(const ValidatorError& err){
					std::cout<<err.what()<<std::endl;
					readInput("likes: ");
				}
			}
			t.setLikes(std::stoi(input));
			readInput("link: ");
			while(true){
				try{
					Validator::validateLink(input);
					break;
				}catch(const ValidatorError& err){
					std::cout<<err.what()<<std::endl;
					readInput("link: ");
				}
			}
			t.setLink(input);
			try{
				man.addTutorial(t);
			}catch(const RepositoryError& err){
				std::cout<<err.what()<<std::endl;
			}
			goto end;
		}
		if(input == "remove")
		{
			readInput("link: ");
			try{
				Validator::validateLink(input);
			}catch(const ValidatorError& err){
				std::cout<<err.what()<<std::endl;
				goto end;
			}
			try{
				man.removeTutorial(input);
				std::cout<<"Removing successful"<<std::endl;
			}catch(const RepositoryError& err){
				std::cout<<err.what()<<std::endl;
			}
			goto end;
		}
		if(input == "modify")
		{
			readInput("link of tutorial to modify: ");
			try{
				Validator::validateLink(input);
			}catch(const ValidatorError& err){
				std::cout<<err.what()<<std::endl;
				goto end;
			}
			std::string link = input;
			int index = man.linkIndex(link);
			if(index == -1){
				std::cout<<"No tutorial by that name..."<<std::endl;
				goto end;
			}
			readInput("field to modify: ");
			std::string field = input;
			readInput("new value: ");
			std::string newValue = input;
			if(field == "title"){
				try {
					Validator::validateTitle(newValue);
				}catch(const ValidatorError& err){
					std::cout<<err.what()<<std::endl;
					goto end;
				}
			}
			if(field == "presenter"){
				try {
					Validator::validatePresenter(newValue);
				}catch(const ValidatorError& err){
					std::cout<<err.what()<<std::endl;
					goto end;
				}
			}
			if(field == "duration"){
				try {
					Validator::validateDuration(newValue);
				}catch(const ValidatorError& err){
					std::cout<<err.what()<<std::endl;
					goto end;
				}
			}
			if(field == "likes"){
				try {
					Validator::validateLikes(newValue);
				}catch(const ValidatorError& err){
					std::cout<<err.what()<<std::endl;
					goto end;
				}
			}
			if(field == "link"){
				try {
					Validator::validateLink(newValue);
				}catch(const ValidatorError& err){
					std::cout<<err.what()<<std::endl;
					goto end;
				}
			}
			try{
				man.modifyField(index, field, newValue);
			}catch(const RepositoryError& err){
				std::cout<<err.what()<<std::endl;
			}
		}
		if(input == "list")
		{
			for(const auto& tutorial: man.list()){
				std::cout<<tutorial.strung()<<std::endl;
			}
			goto end;
		}
		std::cout<< "That is not a valid option :(" << std::endl;
		end:
		printAdminMenu();
	}
}

void UserInterface::openLink(const Tutorial& toOpen) {
	const std::string& url = toOpen.getLink();
	std::string op = std::string("start ").append(url);
	system(op.c_str());
}
