//
// Created by victor on 17/05/2023.
//

#ifndef A89_VICTORS3136_1_HTMLREPOSITORY_H
#define A89_VICTORS3136_1_HTMLREPOSITORY_H

#include <fstream>
#include "FileRepository.h"

class HTMLRepository: public FileRepository
{
protected:;
	void writeSpecialFile(std::vector<Tutorial> toWrite)override{
		std::ofstream fout(specialisedFilePath);
		if (!fout.is_open()){
		}
		fout<<"<!DOCTYPE html>\n <html>\n <head>\n";
		fout<<"<title> My Playlist </title>\n";
		fout<<"</head>\n <body>\n";
		fout<<"<table border=\"1\">\n";
		fout<<"<tr>\n <td> Title </td> <td> Presenter </td> <td> Duration </td> <td> Likes </td> <td> Link </td> </tr>";
		for(const auto& tutorial: toWrite){
			fout<<tutorial.strung_html_format()+"\n";
		}
		fout<<"</table> </body> </html>";
        fout.close();
	};
public:
    explicit HTMLRepository(const std::string& initFile,const std::string &IOFileName, const std::string
	&HTMLFileName) :
	FileRepository(initFile, IOFileName){
        specialisedFilePath = HTMLFileName;
    }
};


#endif //A89_VICTORS3136_1_HTMLREPOSITORY_H
