#include <QApplication>
#include "StartPage.h"
using namespace std;


int main(int argc, char *argv[]) {

    // Create Application
    QApplication app(argc, argv);

    // Create Start Page Window
    StartPage startPage(app.applicationDirPath());

    // Setup Window
    startPage.setupUi();

    // show Window
    startPage.showWindow();

    // Exit Programm
    return app.exec();
}