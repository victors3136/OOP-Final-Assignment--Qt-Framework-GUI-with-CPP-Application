//
// Created by victor on 17/05/2023.
//

#ifndef A89_VICTORS3136_1_CSVREPOSITORY_H
#define A89_VICTORS3136_1_CSVREPOSITORY_H


#include <fstream>
#include "FileRepository.h"

class CSVRepository: public FileRepository
{
protected:
	void writeSpecialFile(std::vector<Tutorial> toWrite)override{
		std::ofstream fout(specialisedFilePath);
		if (!fout.is_open()){
            throw std::runtime_error("Failed to open file for writing: " + specialisedFilePath);
		}
		for(const auto& tutorial: toWrite){
			fout<<tutorial.strung_csv_format()+"\n";
		}
        fout.close();
	};
public:
    explicit CSVRepository(const std::string& initFile, const std::string& IOFileName, const std::string& CSVFileName) :
		    FileRepository(initFile, IOFileName){
        specialisedFilePath = CSVFileName;
    }
};


#endif //A89_VICTORS3136_1_CSVREPOSITORY_H
