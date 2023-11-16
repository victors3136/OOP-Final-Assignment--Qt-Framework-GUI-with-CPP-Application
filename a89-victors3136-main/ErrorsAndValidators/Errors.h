//
// Created by victor on 17/05/2023.
//

#ifndef A89_VICTORS3136_1_REPOSITORYERROR_H
#define A89_VICTORS3136_1_REPOSITORYERROR_H


#include <exception>
#include <string>
#include <utility>

class RepositoryError: public std::exception{
private:
    std::string message;
public:
    explicit RepositoryError(std::string  message) : message(std::move(message)){}
    const char* what() const noexcept override;
};

class ValidatorError: public std::exception{
private:
    std::string message;
public:
    explicit ValidatorError(std::string  message) : message(std::move(message)){}
    const char* what() const noexcept override;
};
#endif //A89_VICTORS3136_1_REPOSITORYERROR_H
