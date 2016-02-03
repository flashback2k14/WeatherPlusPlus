#include <QtWidgets/qtextedit.h>
#include "WeatherUi.h"

WeatherUi::WeatherUi(QMainWindow *parent) :
        QMainWindow(parent)
    { }


void WeatherUi::setupUi(){
    // Main Layout
    QVBoxLayout *vMainLayout = new QVBoxLayout;
    // Header Layout
    QHBoxLayout *hHeaderLayout = new QHBoxLayout;
    hHeaderLayout->setAlignment(Qt::AlignTop);
    // Label
    QLabel *label = new QLabel;
    label->setAlignment(Qt::AlignCenter | Qt::AlignLeft);
    label->setText("Choose your City:");
    // Textfield
    QTextEdit *txtCity = new QTextEdit;
    txtCity->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    txtCity->setFixedHeight(25);
    // Button
    QPushButton *btnSearch = new QPushButton;
    btnSearch->setText("SEARCH");
    // add Widgets to Header Layout
    hHeaderLayout->addWidget(label);
    hHeaderLayout->addWidget(txtCity);
    hHeaderLayout->addWidget(btnSearch);

    // Body Layout
    QHBoxLayout *hBodyLayout = new QHBoxLayout;

    // add sub layouts into Main Layout
    vMainLayout->addLayout(hHeaderLayout);
    vMainLayout->addLayout(hBodyLayout);

    //Main Window
    QWidget *w = new QWidget;
    w->setLayout(vMainLayout);
    w->setWindowTitle("Weather++");
    w->setFixedHeight(500);
    w->setFixedWidth(900);

    // set Main Window for global use
    setWindow(w);
}

void WeatherUi::showWindow() {
    getWindow()->show();
}

WeatherUi::~WeatherUi() { }