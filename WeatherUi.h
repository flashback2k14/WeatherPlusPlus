#ifndef WEATHERUI_H
#define WEATHERUI_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QNetworkRequest>
#include <QByteArray>

#include <iostream>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include "WeatherUi.h"
#include "ApiCall.h"
#include "ApiUri.h"
#include "ApiCall.h"
#include "WeatherParser.h"
#include "WeatherData.h"


using namespace std;


class WeatherUi : public QMainWindow {

Q_OBJECT

private:
    QWidget* mWindow;
    QLineEdit* mTxtSearchQuery;
    QLabel *minfoLabel;

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
        //Header widget
        QWidget *headerWidget = new QWidget();
        QHBoxLayout *hHeaderLayout = new QHBoxLayout(headerWidget);
        hHeaderLayout->setAlignment(Qt::AlignTop);
        // Label
        QLabel *label = new QLabel;
        label->setAlignment(Qt::AlignCenter | Qt::AlignLeft);
        label->setText("Choose your City:");
        // Textfield
        mTxtSearchQuery = new QLineEdit;
        mTxtSearchQuery->setAlignment(Qt::AlignCenter | Qt::AlignLeft);
        mTxtSearchQuery->setFixedHeight(25);
        // Button
        QPushButton *btnSearch = new QPushButton;
        btnSearch->setText("SEARCH");
        btnSearch->setDefault(true);
        // Click Listener
        connect(btnSearch, SIGNAL(clicked()), this, SLOT(requestWeatherData()));
        // add Widgets to Header Layout
        hHeaderLayout->addWidget(label);
        hHeaderLayout->addWidget(mTxtSearchQuery);
        hHeaderLayout->addWidget(btnSearch);
        // configure header widget
        headerWidget->setFixedHeight(50);
        headerWidget->setStyleSheet("background-color:red");

        /**
         * Body Layout
         */
        QHBoxLayout *hBodyLayout = new QHBoxLayout;
        hBodyLayout->setAlignment(Qt::AlignCenter);

        // Label
        minfoLabel = new QLabel();
        minfoLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        minfoLabel->setText("TEST");
        hBodyLayout->addWidget(minfoLabel);


        /**
         * Footer Layout
         */
        QHBoxLayout *hFooterLayout = new QHBoxLayout;
        hFooterLayout->setAlignment(Qt::AlignBottom);

        // add sub layouts into Main Layout
        vMainLayout->addWidget(headerWidget);
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
        // create api uri to call
        QString uri = ApiUri::buildCurrentWeatherUri(mTxtSearchQuery->text());
        // create api caller object
        ApiCall currentWeatherByCity(uri);

        // get data response
        QByteArray ba = currentWeatherByCity.sendRequest();

        WeatherParser parser(ba);
        //get all descriptions
        std::vector<WeatherDescription> descriptions = parser.getWeatherDescription();
        WeatherDescription description = descriptions[0];
        cout << "Short desc: " << description.main << endl;
        cout << "Long desc: " << description.description << endl;

        //get detailed information
        WeatherInfo weatherInfo = parser.getWeatheInfo();
        std::string tempAsString = std::to_string(weatherInfo.temp);
        cout << "Temp: " << tempAsString << endl;
        cout << "Max temp: " << weatherInfo.temp_max << endl;
        cout << "Min temp: " << weatherInfo.temp_min << endl;
        cout << "Humidity: " << weatherInfo.humidity << endl;
        cout << "Pressure: " << weatherInfo.pressure << endl;

        // set focus and select current text
        mTxtSearchQuery->setFocus();
        mTxtSearchQuery->selectAll();
    };
};

#endif
