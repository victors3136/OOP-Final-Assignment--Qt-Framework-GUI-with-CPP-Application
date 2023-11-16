//
// Created by victor on 17/05/2023.
//

#ifndef A89_VICTORS3136_1_VALIDATOR_H
#define A89_VICTORS3136_1_VALIDATOR_H


#include <string>
#include <exception>
#include <regex>
#include "Errors.h"

class Validator
{
public:
	static void validateTitle(__attribute__((unused)) const std::string& input) { }
	static void validatePresenter(__attribute__((unused)) const std::string& input) { }
	static void validateDuration(const std::string& input){
		std::regex rgx { R"(\b[1-9][0-9]*\b)" };
		if(!std::regex_match(input, rgx)){
			throw ValidatorError("Duration does not represent a positive integer :-(\n");
		}
	}
	static void validateLikes(const std::string& input)
	{
		std::regex rgx{R"(\b[0-9]*\b)"};
		if (!std::regex_match(input, rgx)) {
			throw ValidatorError("Likes does not represent a positive integer :-(\n");
		}
	}
	static void validateLink(const std::string& input){
		std::regex rgx { R"(\bhttps:\/\/(w{3}\.)?[a-z0-9A-Z]+\.[a-z]{2,3}(\/.*)?\b)" };
		if(!std::regex_match(input, rgx)){
			throw ValidatorError("Link is not valid :-(\n");
		}
	}
    static void validateStandardTimeFormat(const std::string& input){
        std::regex rgx{ R"(\b[0-9]+\:[0-5][0-9]\b)"};
        if(!std::regex_match(input, rgx)){
            throw ValidatorError("Invalid duration format\n");
        }
    }
};


#endif //A89_VICTORS3136_1_VALIDATOR_H
