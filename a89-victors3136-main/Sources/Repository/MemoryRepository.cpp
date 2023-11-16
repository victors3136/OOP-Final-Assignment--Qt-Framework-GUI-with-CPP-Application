//
// Created by victor on 17/05/2023.
//

#include "../../Headers/Repository/MemoryRepository.h"

void MemoryRepository::modifyMember(int indexOfElemToModify, int fieldToModify, const std::string& newValue)
{

	if(indexOfElemToModify < 0)
		throw RepositoryError { "Error: Index does not represent a valid position inside the repository\n" };
	if(indexOfElemToModify >= data.size())
		throw RepositoryError { "Error: Index does not represent a valid position inside the repository\n" };
	switch(fieldToModify)
	{
		case 1:
		{
			data[indexOfElemToModify].setTitle(newValue);
			return;
		}

		case 2:
		{
			data[indexOfElemToModify].setPresenter(newValue);
			return;
		}

		case 3:
		{
			int duration = stoi(newValue);
			data[indexOfElemToModify].setDuration(duration);
			return;
		}
		case 4:
		{
			int likes = stoi(newValue);
			data[indexOfElemToModify].setLikes(likes);
			return;
		}
		case 5:
		{
			data[indexOfElemToModify].setLink(newValue);
			return;
		}
		default:
			throw RepositoryError { "Error: No field by that name \n" };
	}
}