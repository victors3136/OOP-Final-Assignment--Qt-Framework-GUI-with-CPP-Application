//
// Created by victor on 17/05/2023.
//

#ifndef A89_VICTORS3136_1_BASEREPOSITORY_H
#define A89_VICTORS3136_1_BASEREPOSITORY_H


#include "../Tutorial.h"

class BaseRepository
{
protected:

public:
	BaseRepository()=default;
	~BaseRepository()=default;
	virtual void add(const Tutorial& newElem)=0;
	virtual void remove(const Tutorial& toRemove)=0;
	virtual void modifyMember(int indexOfElemToModify, int fieldToModify, const std::string& newValue)=0;
	[[nodiscard]]  virtual int size()const=0;
	virtual Tutorial operator[] (int index)const=0;
};


#endif //A89_VICTORS3136_1_BASEREPOSITORY_H
