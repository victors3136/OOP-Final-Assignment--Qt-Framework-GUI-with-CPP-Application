//
// Created by victor on 17/05/2023.
//

#ifndef A89_VICTORS3136_GUI_H
#define A89_VICTORS3136_GUI_H


#include <QWidget>
#include <QMainWindow>
#include <QWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include "../../Headers/Manager.h"
#include "AdminGUI.h"
#include "UserGUI.h"

class GUI: QWidget {
    Manager man{};
    QMainWindow mainMenu{};
    AdminGUI admin{man};
    UserGUI user{man};
    QWidget * chooseRepoType;
    QWidget * mainMenuWidget;
    QPushButton * adminMode;
    QPushButton * userMode;
    QPushButton * quitButton;
    QPushButton * htmlMode;
    QPushButton * csvMode;
    void initMainMenu();
    void connectSignalsAndSlots();
public:
    GUI()= default;
    void run();

};


#endif //A89_VICTORS3136_GUI_H
