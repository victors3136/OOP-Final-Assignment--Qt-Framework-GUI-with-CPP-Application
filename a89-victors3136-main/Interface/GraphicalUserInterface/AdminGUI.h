//
// Created by victor on 21/05/2023.
//

#ifndef A89_VICTORS3136_ADMINGUI_H
#define A89_VICTORS3136_ADMINGUI_H


#include <QWidget>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QMessageBox>
#include "../../Headers/Manager.h"
#include "GUI_utils.h"
class AdminGUI: public QWidget {
private:
    Manager& manager;
    QListWidget* videoList{};
    QLineEdit* videoTitle{};
    QLineEdit* videoPresenter{};
    QLineEdit* videoDuration{};
    QLineEdit* videoLikes{};
    QLineEdit* videoLink{};
    QPushButton* addButton{};
    QPushButton* removeButton{};
    QPushButton* modifyButton{};
    QPushButton* returnButton{};

    int getSelectedIndex();
    void populateList();
    void connectSignalsAndSlots();
    void validateTextBoxes();
    void init();
    void addTutorial();
    void removeTutorial();
    void modifyTutorial();
public:
    explicit AdminGUI(Manager& m):manager(m){
        init();
    };
    void run(){
        populateList();
        connectSignalsAndSlots();
        show();
    };

};

#endif //A89_VICTORS3136_ADMINGUI_H
