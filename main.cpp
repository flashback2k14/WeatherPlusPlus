#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <iostream>
#include "ApiCall.h"

using namespace std;


int main(int argc, char *argv[]) {

    // Create Application
    QApplication a(argc, argv);

    // Horizontal layout with 3 buttons
    QHBoxLayout *hLayout = new QHBoxLayout;
    QPushButton *b1 = new QPushButton("A");
    QPushButton *b2 = new QPushButton("B");
    QPushButton *b3 = new QPushButton("C");
    hLayout->addWidget(b1);
    hLayout->addWidget(b2);
    hLayout->addWidget(b3);

    // Vertical layout with 3 buttons
    QVBoxLayout *vLayout = new QVBoxLayout;
    QPushButton *b4 = new QPushButton("D");
    QPushButton *b5 = new QPushButton("E");
    QPushButton *b6 = new QPushButton("F");
    vLayout->addWidget(b4);
    vLayout->addWidget(b5);
    vLayout->addWidget(b6);

    // Outer Layer
    QVBoxLayout *mainLayout = new QVBoxLayout;

    // Add the previous two inner layouts
    mainLayout->addLayout(hLayout);
    mainLayout->addLayout(vLayout);

    // Create a widget
    QWidget *w = new QWidget();

    // Set the outer layout as a main layout of the widget
    w->setLayout(mainLayout);

    // Window title
    w->setWindowTitle("layouts");

    // Display
    w->show();


    std::string uri = "http://api.openweathermap.org/data/2.5/forecast/city?id=524901&APPID=ba424016b92f34904aacdef3c4b65e1e";
    ApiCall forecastByCity(uri);
    std::string resp = forecastByCity.request();
    std::cout << resp << std::endl;

    return a.exec();
}