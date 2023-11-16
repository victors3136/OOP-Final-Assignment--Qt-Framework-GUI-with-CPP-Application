//
// Created by victor on 17/05/2023.
//

#ifndef A89_VICTORS3136_1_FILEREPOSITORY_H
#define A89_VICTORS3136_1_FILEREPOSITORY_H
#include "MemoryRepository.h"

class FileRepository: public MemoryRepository
{
private:
	std::string IOFilePath;
	void updateFile();
	static std::vector<std::string> splitLine(const std::string& line, char delimiter);

protected:
	std::string specialisedFilePath;
    virtual void writeSpecialFile(std::vector <Tutorial> toWrite)=0;
	virtual void writeSpecialisedFile();

public:
	bool changed;
	explicit FileRepository(const std::string& initialFilePath, const std::string& IOFileName);
	virtual ~FileRepository()=default;
	void add(const Tutorial& newElem)override;
	void remove(const Tutorial& toRemove)override;
	void modifyMember(int indexOfElemToModify, int fieldToModify, const std::string& newValue) override;
	virtual void run();
    virtual void writeAndOpen(std::vector<Tutorial> toWrite);
};


#endif //A89_VICTORS3136_1_FILEREPOSITORY_H
