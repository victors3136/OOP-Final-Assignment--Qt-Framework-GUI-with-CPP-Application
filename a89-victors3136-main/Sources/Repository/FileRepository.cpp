//
// Created by victor on 17/05/2023.
//

#include "../../Headers/Repository/FileRepository.h"
#include <fstream>
#include <utility>

void FileRepository::add(const Tutorial &newElem){
	MemoryRepository::add(newElem);
	updateFile();
}

void FileRepository::modifyMember(int indexOfElemToModify, int fieldToModify, const std::string &newValue){
	MemoryRepository::modifyMember(indexOfElemToModify, fieldToModify, newValue);
	updateFile();
}

void FileRepository::remove(const Tutorial &toRemove){
	MemoryRepository::remove(toRemove);
	updateFile();
}

void FileRepository::updateFile()
{
	std::ofstream fout(IOFilePath);
	if(!fout.is_open()){
		throw std::runtime_error("Failed to open file for writing: " + IOFilePath);
	}
	for(const auto& tutorial: data){
		fout << tutorial << std::endl;
	}
	fout.close(); /// not necessary due to RAII principle
}

FileRepository::FileRepository(const std::string& initialFilePath, const std::string& IOFilePath)
{
	std::ifstream fin(initialFilePath);
	if(!fin.is_open()){
		throw std::runtime_error("Error: Failed to open init file for reading");
	}else{
		this->IOFilePath = IOFilePath;
	}
	std::string line;
	while(std::getline(fin, line)){
		if(line.empty())
			break;
		std::vector<std::string> words = FileRepository::splitLine(line,'|');
		std::string name = words[0], presenter = words[1], link = words[4];
		int duration = stoi(words[2]), likes = stoi(words[3]);
		Tutorial t{name, presenter, duration, likes, link};
		data.push_back(t);
	}
	updateFile();
	changed = true;
}

std::vector<std::string> FileRepository::splitLine(const std::string& line, char delimiter){
	std::vector<std::string> result;
	std::string::size_type start = 0, end = line.find(delimiter);
	while(end != std::string::npos /*return value of find when the sought char is not found*/){
		result.push_back(line.substr(start, end-start));
		start = end+1;
		end = line.find(delimiter,start);
	}
	result.push_back(line.substr(start));
	return result;
}

void FileRepository::run() {
        if(changed){
            writeSpecialisedFile();
            changed = false;
        }
        std::string command = "start " + specialisedFilePath;
        system(command.c_str());
}
void FileRepository::writeSpecialisedFile(){
    writeSpecialFile(data);
}

void FileRepository::writeAndOpen(std::vector<Tutorial> toWrite) {
    writeSpecialFile(std::move(toWrite));
    std::string command = "start " + specialisedFilePath;
    system(command.c_str());
}
