#include <QApplication>
#include <QPushButton>
#include "Interface/GraphicalUserInterface/GUI.h"

int main(int argc, char *argv[]) {
    QApplication a {argc, argv};
    GUI g;
    g.run();
    return QApplication::exec();
}
