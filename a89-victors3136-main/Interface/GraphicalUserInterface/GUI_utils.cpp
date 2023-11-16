//
// Created by victor on 29/05/2023.
//
#include "GUI_utils.h"

std::string makeStandardTimeFormatIntoNumberOfSeconds(const QString& standardTimeFormat){
    QStringList tempDuration = standardTimeFormat.split(':');
    return std::to_string(tempDuration[0].toInt() * 60 + tempDuration[1].toInt());
};


void displayError(const std::string& message){
    QMessageBox ErrorPopup;
    ErrorPopup.setIcon(QMessageBox::Critical);
    ErrorPopup.setWindowTitle("Error");
    ErrorPopup.setText(QString::fromStdString(message));
    ErrorPopup.setStandardButtons(QMessageBox::Ok);
    ErrorPopup.exec();
};
std::string custom_to_lower(const std::string& input) {
    std::string lower_input;
    lower_input.reserve(input.size());
    for (char c : input) {
        lower_input += std::tolower(static_cast<unsigned char>(c));
    }
    return lower_input;
}
std::vector<Tutorial> getMatching(const std::string& text, const std::vector<Tutorial>& data){
    std::vector<Tutorial> v;
    std::copy_if(data.begin(), data.end(), std::back_inserter(v), [text](const Tutorial& t){
        return (custom_to_lower(t.getPresenter()).find(text)!= std::string::npos);
    });
    return v;
}