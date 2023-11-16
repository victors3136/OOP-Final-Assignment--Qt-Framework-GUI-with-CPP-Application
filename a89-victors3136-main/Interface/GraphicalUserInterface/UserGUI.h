//
// Created by victor on 21/05/2023.
//

#ifndef A89_VICTORS3136_USERGUI_H
#define A89_VICTORS3136_USERGUI_H


#include <QWidget>
#include <QListWidget>
#include <QMediaPlayer>
#include <QMessageBox>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

#include "../../Headers/Manager.h"
#include "GUI_utils.h"

class UserGUI: public QWidget {
private:
    Manager& manager;
    std::vector<Tutorial> liked;
    std::vector<Tutorial> current;
    QListWidget * videoList;
    QLineEdit * textBox;
    QPushButton * like;
    QPushButton * remove;
    QPushButton * next;
    QPushButton * back;
    QPushButton * viewLiked;
    QPushButton * open;
    QPushButton * watch;
    QLineEdit * videoTitle;
    QLineEdit * videoPresenter;
    QLineEdit * videoDuration;
    QLineEdit * videoLikes;
    QLineEdit * videoLink;

    int getSelectedIndex();
    void populateList();
    void connectSignalsAndSlots();
    void init();
public:
    explicit UserGUI(Manager& m):manager(m){
        init();
    };
    void run(){
        current = manager.getByPresenter("");
        populateList();
        connectSignalsAndSlots();
        show();
    };

};


#endif //A89_VICTORS3136_USERGUI_H
