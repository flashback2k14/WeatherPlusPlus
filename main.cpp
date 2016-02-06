#include <QApplication>
#include "WeatherUi.h"
using namespace std;


int main(int argc, char *argv[]) {

    // Create Application
    QApplication app(argc, argv);

    // Create WeatherUi Window
    WeatherUi wui(app.applicationDirPath());

    // Setup Window
    wui.setupUi();

    // show Window
    wui.showWindow();

    // Exit Programm
    return app.exec();
}