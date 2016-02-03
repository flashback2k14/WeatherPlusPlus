#include <QtCore>
#include <QtGui>
#include <QtWidgets/qapplication.h>

#include "ApiCall.h"
#include "WeatherUi.h"

using namespace std;


int main(int argc, char *argv[]) {

    // Create Application
    QApplication a(argc, argv);

    // Create WeatherUi Window
    WeatherUi wui;

    // Setup Window
    wui.setupUi();

    // show Window
    wui.showWindow();

    // Exit Programm
    return a.exec();
}