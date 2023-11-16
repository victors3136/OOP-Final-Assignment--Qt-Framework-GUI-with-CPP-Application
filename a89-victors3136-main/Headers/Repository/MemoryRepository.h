//
// Created by victor on 17/05/2023.
//

#ifndef A89_VICTORS3136_1_REPOSITORY_H
#define A89_VICTORS3136_1_REPOSITORY_H


#include "../Tutorial.h"
#include "BaseRepository.h"
#include "../../ErrorsAndValidators/Errors.h"
#include <algorithm>
#include <vector>

class MemoryRepository: public BaseRepository
{
protected:
	std::vector<Tutorial> data;
public:
	MemoryRepository()=default;
	~MemoryRepository()=default;
	void add (const Tutorial& newElem) override {
		if(std::count(data.begin(), data.end(), newElem))
			throw RepositoryError("Error: Tutorial already in repo\n");
		data.push_back(newElem);
	};
	void remove(const Tutorial& toRemove) override {
		for(auto tutorialPtr = data.begin(); tutorialPtr < data.end(); tutorialPtr ++)
			if(*tutorialPtr == toRemove){
				data.erase(tutorialPtr);
				return;
			}
		throw RepositoryError {"Error: Tutorial does not exist\n"};
	};
	int size() const override { return (int)data.size(); } /// this vector does not need a ull size...
	Tutorial operator[] (int index) const override { return data[index]; }
	void modifyMember (int indexOfElemToModify, int fieldToModify, const std::string& newValue) override;
};


#endif //A89_VICTORS3136_1_REPOSITORY_H
