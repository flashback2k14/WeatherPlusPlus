#include <QApplication>
#include <qsplashscreen.h>
#include "StartPage.h"
using namespace std;


int main(int argc, char *argv[]) {

    // Create Application
    QApplication app(argc, argv);

    QPixmap pixmap("icons/unknown.png");
    QSplashScreen splash(pixmap);
    splash.show();

    // Create Start Page Window
    StartPage startPage(app.applicationDirPath(), &splash);

    // Setup Window
    startPage.setupUi();

    // show Window
    startPage.showWindow();

    // Exit Programm
    return app.exec();
}