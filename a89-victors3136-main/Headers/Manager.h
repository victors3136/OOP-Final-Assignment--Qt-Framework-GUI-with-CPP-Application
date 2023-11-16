//
// Created by victor on 17/05/2023.
//

#ifndef A89_VICTORS3136_1_MANAGER_H
#define A89_VICTORS3136_1_MANAGER_H


#include <utility>

#include "Repository/FileRepository.h"
#include "Repository/HTMLRepository.h"
#include "Repository/CSVRepository.h"

class Manager {
private:
    FileRepository* repo{};

public:
    void setRepoType(const std::string &initFile, const std::string &repoType, const std::string &filePath)
    {
        if(repoType == "html"){
            repo = new HTMLRepository{initFile, filePath, "html_file.html"};
        }
        else{if(repoType == "csv"){
                repo = new CSVRepository{initFile, filePath, "csv_file.csv"};
        }else{
                throw RepositoryError("Error: Invalid repository type\n");
        }}
    }
    [[nodiscard]] int linkIndex(const std::string& link) const{
        for(int i = 0; i < repo->size(); i ++)
            if((*repo)[i].getLink() == link)
                return i;
        return -1;
    }
    std::vector<Tutorial> list(){
        std::vector<Tutorial> tutorials;
        tutorials.reserve(repo->size());
		for(int i = 0; i < repo->size(); i ++)
            tutorials.push_back((*repo)[i]);
        return tutorials;
    }

    Manager()= default;
    virtual ~Manager() {
        if(repo!=nullptr)
            delete repo;
    };
    [[nodiscard]] std::vector<Tutorial> getByPresenter(const std::string& presenterName) const
    {
        std::vector<Tutorial> returnRepo;
        if(presenterName.empty()){
			returnRepo.reserve(repo->size());
            for(int i = 0; i < repo->size(); i ++)
                returnRepo.push_back((*repo)[i]);
        }
        else{
            for(int i = 0; i < repo->size(); i ++)
                if((*repo)[i].getPresenter() == presenterName)
                    returnRepo.push_back((*repo)[i]);
        }
	    return returnRepo;};

    void addTutorial(std::string title,std::string presenter, int duration, int likes, std::string link);
    void addTutorial(const Tutorial& t);
    void removeTutorial(const std::string& link);
    void modifyField(int index, const std::string& field, const std::string& newValue);
    void openExternal(){
      repo->run();
    };
    void openVectorExternally(std::vector<Tutorial> toOpen){
        repo->writeAndOpen(std::move(toOpen));
    }
};


#endif //A89_VICTORS3136_1_MANAGER_H
