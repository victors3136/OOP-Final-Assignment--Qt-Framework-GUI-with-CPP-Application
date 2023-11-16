//
// Created by victor on 17/05/2023.
//

#include "../Headers/Manager.h"
#include <utility>

void Manager::addTutorial(std::string title, std::string presenter, int duration, int likes,
										std::string link) {
    Tutorial t{std::move(title), std::move(presenter), duration, likes, std::move(link)};
    repo->add(t);
}

void Manager::addTutorial(const Tutorial& t){
    repo->add(t);
}

void Manager::removeTutorial(const std::string& link) {
    Tutorial t;
    t.setLink(link);
    repo->remove(t);
}

void Manager::modifyField(int index, const std::string& field, const std::string& newValue) {
    if(field == "title"){
	    repo->modifyMember(index, 1, newValue);
		return;
    }
    if(field == "presenter"){
	    repo->modifyMember(index, 2, newValue);
		return;
    }
    if(field == "duration"){
	    repo->modifyMember(index, 3, newValue);
		return;
    }
    if(field == "likes"){
	    repo->modifyMember(index, 4, newValue);
		return;
    }
    if(field == "link") {
		if(linkIndex(newValue) == -1){
			repo->modifyMember(index, 5, newValue);
			return;
		}else{
			throw RepositoryError("Error: This change would result in overlapping links\n");
		}
    }
    throw RepositoryError("Error: No field by that name\n");
}
