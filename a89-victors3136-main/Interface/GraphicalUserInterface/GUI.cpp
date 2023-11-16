//
// Created by victor on 17/05/2023.
//

#include <iostream>
#include "GUI.h"


void GUI::initMainMenu() {

    mainMenuWidget = new QWidget(&mainMenu);
    adminMode = new QPushButton("Admin");
    userMode = new QPushButton("User");
    quitButton = new QPushButton("Quit");

    mainMenu.setWindowTitle("Main Menu");
    chooseRepoType = new QWidget();
    chooseRepoType->setWindowTitle("Application type");
    htmlMode = new QPushButton("Website");
    csvMode = new QPushButton("Spreadsheet");

    auto mainLayout = new QVBoxLayout();
    auto repoLayout = new QVBoxLayout();

    chooseRepoType->setLayout(repoLayout);
    repoLayout->addWidget(htmlMode);
    repoLayout->addWidget(csvMode);
    chooseRepoType->setMinimumSize(300, 100);
    mainLayout->addWidget(adminMode);
    mainLayout->addWidget(userMode);
    mainLayout->addWidget(quitButton);
    mainMenuWidget->setMinimumSize(300, 100);
    mainMenuWidget->setLayout(mainLayout);
    mainMenu.setCentralWidget(mainMenuWidget);
}

void GUI::connectSignalsAndSlots() {

    QObject::connect(adminMode, &QPushButton::clicked, [this](){
        admin.run();
    });

    QObject::connect(userMode, &QPushButton::clicked, [this](){
        user.run();
    });

    QObject::connect(quitButton, &QPushButton::clicked, [this]{
        mainMenu.close();
    });

    QObject::connect(htmlMode, &QPushButton::clicked, [this](){
        man.setRepoType("init_load_file.txt", "html", "data.txt");
        chooseRepoType->close();
        mainMenu.show();
    });

    QObject::connect(csvMode, &QPushButton::clicked, [this](){
        man.setRepoType("init_load_file.txt", "csv", "data.txt");
        chooseRepoType->close();
        mainMenu.show();
    });

}

void GUI::run() {
    initMainMenu();
    connectSignalsAndSlots();
    chooseRepoType->show();
}
