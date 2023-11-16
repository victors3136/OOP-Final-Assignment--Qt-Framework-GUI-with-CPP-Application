//
// Created by victor on 21/05/2023.
//

#include <iostream>
#include "AdminGUI.h"
#include "../../ErrorsAndValidators/Validator.h"

void AdminGUI::init() {
    videoList = new QListWidget{};

    videoTitle = new QLineEdit{};
    auto titleLabel = new QLabel{"Title: "};
    auto titleLayout = new QHBoxLayout();
    titleLayout->addWidget(titleLabel); titleLayout->addWidget(videoTitle);


    videoPresenter = new QLineEdit{};
    auto presenterLabel = new QLabel{"Presenter: "};
    auto presenterLayout = new QHBoxLayout();
    presenterLayout->addWidget(presenterLabel); presenterLayout->addWidget(videoPresenter);

    videoDuration = new QLineEdit{};
    auto durationLabel = new QLabel{"Duration: "};
    auto durationLayout = new QHBoxLayout();
    durationLayout->addWidget(durationLabel);  durationLayout->addWidget(videoDuration);


    videoLikes = new QLineEdit{};
    auto likesLabel = new QLabel{"Likes: "};
    auto likesLayout = new QHBoxLayout();
    likesLayout->addWidget(likesLabel); likesLayout->addWidget(videoLikes);

    videoLink = new QLineEdit{};
    auto linkLabel = new QLabel{"Link: "};
    auto linkLayout = new QHBoxLayout();
    linkLayout->addWidget(linkLabel); linkLayout->addWidget(videoLink);

    addButton = new QPushButton{"Add New"};
    removeButton = new QPushButton{"Remove Selected"};
    modifyButton = new QPushButton{"Confirm Selection Modification"};
    returnButton = new QPushButton{"Back to main menu"};
    auto main = new QHBoxLayout{this};
    auto list = new QVBoxLayout{};
    list->addWidget(videoList);
    main->addLayout(list);
    auto detailsAndButtons = new QVBoxLayout{};
    detailsAndButtons->addLayout(titleLayout);
    detailsAndButtons->addLayout(presenterLayout);
    detailsAndButtons->addLayout(durationLayout);
    detailsAndButtons->addLayout(likesLayout);
    detailsAndButtons->addLayout(linkLayout);
    auto buttons = new QVBoxLayout{};
    buttons->addWidget(addButton);
    buttons->addWidget(removeButton);
    buttons->addWidget(modifyButton);
    buttons->addWidget(returnButton);
    detailsAndButtons->addLayout(buttons);
    main->addLayout(detailsAndButtons);
    setMinimumSize(750, 300);
}

void AdminGUI::populateList() {
    videoList->clear();
    for(const auto& tutorial: manager.getByPresenter("")){
        videoList->addItem(QString::fromStdString(tutorial.getTitle()+ " " + tutorial.getPresenter()));
    }

}

void AdminGUI::connectSignalsAndSlots(){
    QObject::connect(videoList, &QListWidget::clicked, [this](){
        int id = getSelectedIndex();
        Tutorial t = manager.getByPresenter("")[id];
        videoTitle->setText(QString::fromStdString(t.getTitle()));
        videoPresenter->setText(QString::fromStdString(t.getPresenter()));
        videoDuration->setText(QString::number(t.getDuration()/60)+":"+((t.getDuration()%60<10)?"0":"")+QString::number(t.getDuration()%60));
        videoLikes->setText(QString::number(t.getLikes()));
        videoLink->setText(QString::fromStdString(t.getLink()));
    });
    QObject::connect(addButton, &QPushButton::clicked, this, &AdminGUI::addTutorial);
    QObject::connect(removeButton, &QPushButton::clicked, this, &AdminGUI::removeTutorial);
    QObject::connect(modifyButton, &QPushButton::clicked, this, &AdminGUI::modifyTutorial);
    QObject::connect(returnButton, &QPushButton::clicked, this, &AdminGUI::close);
}

int AdminGUI::getSelectedIndex(){
    if(videoList->selectionModel()->selectedIndexes().isEmpty()){
        displayError("No video selected");
        return -1;
    }
    QModelIndexList idList = videoList->selectionModel()->selectedIndexes();
    if(idList.empty())
        return -1;
    return idList.at(0).row();
}

void AdminGUI::addTutorial() {
    if(videoTitle->text().isEmpty() || videoPresenter->text().isEmpty() || videoDuration->text().isEmpty() || videoLikes->text().isEmpty()|| videoLink->text().isEmpty()){
        displayError("Empty text boxes");
        return;
    }
    std::string name;
    std::string presenter;
    std::string duration;
    std::string likes;
    std::string link;
    try{
        validateTextBoxes();
        name = videoTitle->text().toStdString();
        presenter = videoPresenter->text().toStdString();
        duration = makeStandardTimeFormatIntoNumberOfSeconds(videoDuration->text());
        likes = videoLikes->text().toStdString();
        link = videoLink->text().toStdString();
    }catch(const ValidatorError& err){
        displayError(err.what());
        return;
    }
    try{
        if(manager.linkIndex(link)!= -1)
            throw RepositoryError("There is already a tutorial with this link");
        manager.addTutorial(name, presenter, std::stoi(duration), std::stoi(likes), link);
        populateList();
    }catch(const RepositoryError& err){
        displayError(err.what());
        return;
    }
}

void AdminGUI::removeTutorial() {
    if(videoTitle->text().isEmpty() || videoPresenter->text().isEmpty() || videoDuration->text().isEmpty() || videoLikes->text().isEmpty()|| videoLink->text().isEmpty()){
        displayError("Empty text boxes");
        return;
    }
    try{
        validateTextBoxes();
    }catch(const ValidatorError& err){
        displayError(err.what());
        return;
    }
    int id = manager.linkIndex(videoLink->text().toStdString());
    if(id == -1){
        displayError("No item with these fields");
        return;
    }
    manager.removeTutorial(videoLink->text().toStdString());
    populateList();
}

void AdminGUI::modifyTutorial() {
    if(videoTitle->text().isEmpty() || videoPresenter->text().isEmpty() || videoDuration->text().isEmpty() || videoLikes->text().isEmpty()|| videoLink->text().isEmpty()){
        displayError("Empty text boxes");
        return;
    }
    try{
        validateTextBoxes();
    }catch(const ValidatorError& err){
        displayError(err.what());
        return;
    }

    bool changed = false;
    int id = getSelectedIndex();
    if(id == -1){
        return;
    }
    Tutorial toBeChanged = manager.getByPresenter("")[id];
    if(toBeChanged.getTitle()!= videoTitle->text().toStdString()){
        manager.modifyField(id, "title", videoTitle->text().toStdString());
        changed = true;
    }
    if(toBeChanged.getPresenter()!= videoPresenter->text().toStdString()){
        manager.modifyField(id, "presenter", videoPresenter->text().toStdString());
        changed = true;
    }
    if(std::to_string(toBeChanged.getDuration()) != makeStandardTimeFormatIntoNumberOfSeconds(videoDuration->text())){
        manager.modifyField(id, "duration", makeStandardTimeFormatIntoNumberOfSeconds(videoDuration->text()));
        changed = true;
    }
    if(std::to_string(toBeChanged.getLikes()) != videoLikes->text().toStdString()){
        manager.modifyField(id, "likes", videoLikes->text().toStdString());
        changed = true;
    }
    if(toBeChanged.getLink() != videoLink->text().toStdString()){
        manager.modifyField(id, "link", videoLink->text().toStdString());
        changed = true;
    }
    if(changed)
        populateList();
    else displayError("No field was modified.");
}

void AdminGUI::validateTextBoxes() {
    Validator::validateTitle(videoTitle->text().toStdString());
    Validator::validatePresenter(videoPresenter->text().toStdString());
    Validator::validateStandardTimeFormat(videoDuration->text().toStdString());
    Validator::validateDuration(makeStandardTimeFormatIntoNumberOfSeconds(videoDuration->text()));
    Validator::validateLikes(videoLikes->text().toStdString());
    Validator::validateLink(videoLink->text().toStdString());
}

