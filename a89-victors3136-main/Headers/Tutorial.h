//
// Created by victor on 16/04/2023.
//

#ifndef A7_VICTORS3136_1_TUTORIAL_H
#define A7_VICTORS3136_1_TUTORIAL_H
#include <string>
#include <iomanip>

class Tutorial{
private:
	std::string title{};
	std::string presenter{};
	int duration{0};
	int likes{0};
	std::string link{"https://www.youtube.com/watch?v=dQw4w9WgXcQ"};
public:
	[[nodiscard]] const std::string &getTitle() const{
        return title;
    };

	void setTitle(const std::string &newTitle){
        title = newTitle;
    };

	[[nodiscard]] const std::string &getPresenter() const{
        return presenter;
    };

	void setPresenter(const std::string &newPresenter){
        presenter = newPresenter;
    };

	[[nodiscard]] int getDuration() const{
        return duration;
    };

	void setDuration(int newDuration){
        duration = newDuration;
    };

	[[nodiscard]] int getLikes() const{
        return likes;
    };

	void setLikes(int newLikes){
        likes = newLikes;
    };

	[[nodiscard]] const std::string &getLink() const{
        return link;
    };

	void setLink(const std::string &newLink){
        link = newLink;
    };

	Tutorial()=default;

	Tutorial(std::string newTitle, std::string newPresenter, int newDuration, int newLikes, std::string newLink):
    title(std::move(newTitle)), presenter(std::move(newPresenter)), duration(newDuration), likes(newLikes), link(std::move(newLink))
    {};

	virtual ~Tutorial()= default;

	friend std::ostream &operator<<(std::ostream &os, const Tutorial &tutorial)
	{
		os << tutorial.title << "|" << tutorial.presenter << "|" << tutorial.duration<<"|"<< tutorial.likes
		<<"|"<< tutorial.link;
		return os;
	}
	std::string strung() const {
		std::string durationInStandardFormat= std::to_string(duration/60) +":";
		durationInStandardFormat+= (duration%60< 10) ? "0" : "";
		durationInStandardFormat+=std::to_string(duration%60);
		return std::string("\""+title+"\"- "+presenter+" " + std::to_string(likes) + " " + durationInStandardFormat);
	}
    std::string strungForGUI()const{
        return std::string("\""+title+"\"- "+presenter);
    }

	bool operator==(const Tutorial &other) const{
        return link == other.link;
    };

	bool operator!=(const Tutorial &other) const{
        return !(*this == other);
    };
	std::string strung_html_format()const{
		std::string html_form = "<tr>";
		html_form += "<td>" + title + "</td>";
		html_form += "<td>" + presenter + "</td>";
		std::string durationInStandardFormat= std::to_string(duration/60) +":";
		durationInStandardFormat+= (duration%60< 10) ? "0" : "";
		durationInStandardFormat+=std::to_string(duration%60);
		html_form += "<td>" + durationInStandardFormat + "</td>";
		html_form += "<td>" + std::to_string(likes) + "</td>";
		html_form += "<td> <a href=" + link + ">Link</a></td></tr>";
		return html_form;
	};
	std::string strung_csv_format()const{
		std::string csv_form =title+","+presenter+",";
		std::string durationInStandardFormat= std::to_string(duration/60) +":";
		durationInStandardFormat+= (duration%60< 10) ? "0" : "";
		durationInStandardFormat+=std::to_string(duration%60);
		csv_form += durationInStandardFormat +","+ std::to_string(likes)+","+ link;
		return csv_form;

	};
};

#endif //A7_VICTORS3136_1_TUTORIAL_H
