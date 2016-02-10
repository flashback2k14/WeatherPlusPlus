#include <QApplication>
#include <qsplashscreen.h>
#include "StartPage.h"
#include <unistd.h>
#include <thread>

using namespace std;


int main(int argc, char *argv[]) {

    // Create Application
    QApplication app(argc, argv);

    QPixmap pixmap("icons/splash.png");
    QSplashScreen splash(pixmap);
    splash.show();
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    // Create Start Page Window
    WeatherPages startPage(app.applicationDirPath(), &splash);

    // Setup Window
    startPage.setupUi();

    // show Window
    startPage.showWindow();

    // Exit Programm
    return app.exec();
}