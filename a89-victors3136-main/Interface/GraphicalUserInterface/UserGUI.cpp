//
// Created by victor on 21/05/2023.
//

#include "UserGUI.h"

int UserGUI::getSelectedIndex() {
    if(videoList->selectionModel()->selectedIndexes().isEmpty()){
        displayError("No video selected");
        return -1;
    }
    QModelIndexList idList = videoList->selectionModel()->selectedIndexes();
    return idList.at(0).row();
}

void UserGUI::connectSignalsAndSlots() {

    QObject::connect(textBox, &QLineEdit::textChanged, [this](){
        std::string name;
        if(textBox->text().isEmpty()){
            name = "";
        }else{
            name = textBox->text().toStdString();
        }
        current.clear();
        auto temp = manager.getByPresenter(name);
        std::copy(temp.begin(), temp.end(), std::back_inserter(current));
        populateList();
    });

    QObject::connect(like, &QPushButton::clicked, [this](){
        int id = getSelectedIndex();
        if( id == -1) {
            return;
        }
        Tutorial t {manager.getByPresenter("")[id]};
        if(std::find(liked.begin(), liked.end(), t) == liked.end())
            liked.push_back(t);
    });

    QObject::connect(remove, &QPushButton::clicked, [this](){
        int id = getSelectedIndex();
        if( id == -1) {
            return;
        }
        current.erase(current.begin()+id);
        populateList();
    });

    QObject::connect(viewLiked, &QPushButton::clicked, [this](){
        current = liked;
        populateList();
    });

    QObject::connect(open, &QPushButton::clicked, [this](){
        manager.openVectorExternally(current);
    });

    QObject::connect(back, &QPushButton::clicked, this, &UserGUI::close);

    QObject::connect(next, &QPushButton::clicked, [this](){
        QList<QListWidgetItem *> selectedItems = videoList->selectedItems();
        if (selectedItems.isEmpty()) {
            displayError("No video selected");
            return;
        }
        if (videoList->count() == 1)
            return;

        QListWidgetItem *selectedItem = selectedItems.first();
        int currentIndex = videoList->row(selectedItem);

        int nextIndex;
        if (videoList->count() > 1) {
            nextIndex = (currentIndex + 1) % videoList->count();
        } else {
            nextIndex = 0;
        }

        QListWidgetItem *nextItem = videoList->item(nextIndex);
        nextItem->setSelected(true);
        for(auto item: selectedItems){
            item->setSelected(false);
        }

        int id = videoList->selectionModel()->selectedIndexes().at(0).row();
        Tutorial t = current[id];
        videoTitle->setText(QString::fromStdString(t.getTitle()));
        videoPresenter->setText(QString::fromStdString(t.getPresenter()));
        videoDuration->setText(QString::number(t.getDuration()/60)+":"+((t.getDuration()%60<10)?"0":"")+QString::number(t.getDuration()%60));
        videoLikes->setText(QString::number(t.getLikes()));
        videoLink->setText(QString::fromStdString(t.getLink()));

    });
    QObject::connect(videoList, &QListWidget::itemSelectionChanged, [this](){
        if(videoList->selectionModel()->selectedIndexes().isEmpty())
            return;
        int id = videoList->selectionModel()->selectedIndexes().at(0).row();
        Tutorial t = current[id];
        videoTitle->setText(QString::fromStdString(t.getTitle()));
        videoPresenter->setText(QString::fromStdString(t.getPresenter()));
        videoDuration->setText(QString::number(t.getDuration()/60)+":"+((t.getDuration()%60<10)?"0":"")+QString::number(t.getDuration()%60));
        videoLikes->setText(QString::number(t.getLikes()));
        videoLink->setText(QString::fromStdString(t.getLink()));
    });

    QObject::connect(watch, &QPushButton::clicked, [this](){
        int id = getSelectedIndex();
        if(id == -1)
            return;
        const std::string& url = manager.getByPresenter("")[id].getLink();
        std::string op = std::string("start ").append(url);
        system(op.c_str());
    });

    QObject::connect(textBox, &QLineEdit::textChanged, [this]{
        std::string text = textBox->text().toStdString();
        text = custom_to_lower(text);
        current.clear();
        current = getMatching(text, manager.getByPresenter(""));
        populateList();
    });

}

void UserGUI::init() {
    videoList = new QListWidget;
    textBox = new QLineEdit;
    like = new QPushButton{"Like current"};
    remove = new QPushButton{"Remove current"};
    back = new QPushButton{"Go back"};
    viewLiked = new QPushButton{"View liked videos"};
    open = new QPushButton{"Open externally"};
    watch = new QPushButton{"Watch in browser"};
    next = new QPushButton{"Next"};
    auto mainLayout = new QHBoxLayout(this);
    auto leftLayout = new QVBoxLayout;
    auto rightLayout = new QVBoxLayout;
    auto buttonLayout1 = new QHBoxLayout;
    auto buttonLayout2 = new QHBoxLayout;
    auto buttonLayout3 = new QHBoxLayout;

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

    auto detailsLayout = new QVBoxLayout;
    detailsLayout->addLayout(titleLayout);
    detailsLayout->addLayout(presenterLayout);
    detailsLayout->addLayout(durationLayout);
    detailsLayout->addLayout(likesLayout);
    detailsLayout->addLayout(linkLayout);

    leftLayout->addWidget(textBox);
    leftLayout->addWidget(videoList);
    buttonLayout1->addWidget(like);
    buttonLayout1->addWidget(remove);
    buttonLayout1->addWidget(next);
    buttonLayout2->addWidget(viewLiked);
    buttonLayout2->addWidget(open);
    buttonLayout2->addWidget(watch);
    buttonLayout3->addWidget(back);
    rightLayout->addLayout(detailsLayout);
    rightLayout->addLayout(buttonLayout1);
    rightLayout->addLayout(buttonLayout2);
    rightLayout->addLayout(buttonLayout3);
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    setMinimumSize(750, 450);
}
void UserGUI::populateList(){
    videoList->clear();
    for(const auto& tutorial: current){
        videoList->addItem(QString::fromStdString(tutorial.strungForGUI()));
    }
}