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
    QString mAppPath;
    QImage *mImage;
    QWidget* mWindow;
    QLineEdit* mTxtSearchQuery;
    QLabel *mInfoLabel;

public:
    /**
     * Constructor / Destructor
     */
    WeatherUi(QString path): mAppPath(path) {};
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
        //Header layout
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
        // body widget
        QWidget *bodyWidget = new QWidget();
        // body layout
        QHBoxLayout *hBodyLayout = new QHBoxLayout(bodyWidget);
        hBodyLayout->setAlignment(Qt::AlignCenter);

        // weather icon
        // create label to hold image
        QLabel *imageLabel = new QLabel();
        // init global private image
        mImage = new QImage();
        // load the placeholder image
        mImage->load("icons/unknown.png");
        // replace the current image with the scaled one
        *mImage = mImage->scaled(200,200,Qt::KeepAspectRatio,Qt::SmoothTransformation);
        // add image to label
        imageLabel->setPixmap(QPixmap::fromImage(*mImage));
        imageLabel->setAlignment(Qt::AlignCenter);
        // add icon to widget
        hBodyLayout->addWidget(imageLabel);


        // configure body widget
        bodyWidget->setStyleSheet("background-color:green");

        /**
         * Footer Layout
         */
        // footer widget
        QWidget *footerWidget = new QWidget();
        // footer layout
        QHBoxLayout *hFooterLayout = new QHBoxLayout(footerWidget);
        hFooterLayout->setAlignment(Qt::AlignCenter);

        // Label
        mInfoLabel = new QLabel();
        mInfoLabel->setAlignment(Qt::AlignTop);
        mInfoLabel->setText("Please enter your location (city name)");
        hFooterLayout->addWidget(mInfoLabel);

        // configure footer widget
        footerWidget->setStyleSheet("background-color:yellow");

        // add sub layouts into Main Layout
        vMainLayout->addWidget(headerWidget);
        vMainLayout->addWidget(bodyWidget);
        vMainLayout->addWidget(footerWidget);

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

        mInfoLabel->setText(QString("%1").arg(weatherInfo.temp));

        // set focus and select current text
        mTxtSearchQuery->setFocus();
        mTxtSearchQuery->selectAll();
    };
};

#endif
