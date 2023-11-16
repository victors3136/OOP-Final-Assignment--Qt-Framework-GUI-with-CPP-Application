//
// Created by victor on 29/05/2023.
//

#ifndef A89_VICTORS3136_GUI_UTILS_H
#define A89_VICTORS3136_GUI_UTILS_H

#include <string>
#include <QString>
#include <QStringList>
#include <QMessageBox>
#include "../../Headers/Tutorial.h"
std::string makeStandardTimeFormatIntoNumberOfSeconds(const QString& standardTimeFormat);
void displayError(const std::string& message);
std::string custom_to_lower(const std::string& input);
std::vector<Tutorial> getMatching(const std::string& text, const std::vector<Tutorial>& data);
#endif //A89_VICTORS3136_GUI_UTILS_H
