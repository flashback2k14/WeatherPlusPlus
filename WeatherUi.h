#ifndef WEATHERUI_H
#define WEATHERUI_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>

#include <iostream>
#include "WeatherUi.h"
#include "ApiCall.h"
#include "ApiUri.h"

using namespace std;

class WeatherUi: public QMainWindow {

Q_OBJECT

private:
    QWidget* mWindow;
    QTextEdit* mTxtSearchQuery;

public:
    /**
     * Constructor / Destructor
     */
    WeatherUi() {};
    ~WeatherUi() {};
    /**
     * Build and Show
     */
    void setupUi() {
        /**
         * Main Layout
         */
        QVBoxLayout *vMainLayout = new QVBoxLayout;
        /**
         * Header Layout
         */
        QHBoxLayout *hHeaderLayout = new QHBoxLayout;
        hHeaderLayout->setAlignment(Qt::AlignTop);
        // Label
        QLabel *label = new QLabel;
        label->setAlignment(Qt::AlignCenter | Qt::AlignLeft);
        label->setText("Choose your City:");
        // Textfield
        mTxtSearchQuery = new QTextEdit;
        mTxtSearchQuery->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        mTxtSearchQuery->setFixedHeight(25);
        // Button
        QPushButton *btnSearch = new QPushButton;
        btnSearch->setText("SEARCH");
        // Click Listener
        connect(btnSearch, SIGNAL(clicked()), this, SLOT(requestWeatherData()));
        // add Widgets to Header Layout
        hHeaderLayout->addWidget(label);
        hHeaderLayout->addWidget(mTxtSearchQuery);
        hHeaderLayout->addWidget(btnSearch);

        /**
         * Body Layout
         */
        QHBoxLayout *hBodyLayout = new QHBoxLayout;
        hBodyLayout->setAlignment(Qt::AlignCenter);

        /**
         * Footer Layout
         */
        QHBoxLayout *hFooterLayout = new QHBoxLayout;
        hFooterLayout->setAlignment(Qt::AlignBottom);

        // add sub layouts into Main Layout
        vMainLayout->addLayout(hHeaderLayout);
        vMainLayout->addLayout(hBodyLayout);
        vMainLayout->addLayout(hFooterLayout);

        //Main Window
        mWindow = new QWidget;
        mWindow->setLayout(vMainLayout);
        mWindow->setWindowTitle("Weather++");
        mWindow->setFixedHeight(500);
        mWindow->setFixedWidth(900);
    };

    void showWindow() {
        mWindow->show();
    };

public slots:
    /**
     * Request Weather Data
     */
    void requestWeatherData() {
        cout << "Search Query: " << mTxtSearchQuery->toPlainText().toStdString() << endl;

        std::string uri = ApiUri::buildCurrentWeatherUri(mTxtSearchQuery->toPlainText().toStdString());
        ApiCall currentWeatherByCity(uri);
        std::string resp = currentWeatherByCity.request();
        cout << resp << endl;
    };
};

#endif
