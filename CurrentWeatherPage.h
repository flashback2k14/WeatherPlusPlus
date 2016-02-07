#ifndef WEATHERUI_H
#define WEATHERUI_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QByteArray>

#include "ApiUri.h"
#include "ApiCall.h"
#include "WeatherParser.h"
#include "WeatherData.h"
#include "WeatherMapper.h"

#include <iostream>
using namespace std;


class CurrentWeatherPage : public QMainWindow {

Q_OBJECT

private:
    /**
     * Global UI Widgets
     */
    QString mAppPath;
    QWidget *mWindow;
    // header
    QLineEdit *mTxtSearchQuery;
    // body
    QLabel *mImageLabel;
    QImage *mImage;
    QLabel *mImageDesc;
    // footer
    QLabel *mInfoTemp;
    QLabel *mInfoTempMin;
    QLabel *mInfoTempMax;
    QLabel *mInfoHumidity;
    QLabel *mInfoPressure;

public:
    /**
     * Constructor / Destructor
     */
    CurrentWeatherPage(QString path): mAppPath(path) {};
    ~CurrentWeatherPage() {};

    /**
     * Build and Show
     */
    void setupUi() {
        // build Layout
        QVBoxLayout *vMainLayout = new QVBoxLayout;
        QWidget *header = buildHeaderWidget();
        QWidget *body = buildBodyWidget();
        QWidget *footer = buildFooterWidget();

        // add sub layouts into Main Layout
        vMainLayout->addWidget(header);
        vMainLayout->addWidget(body);
        vMainLayout->addWidget(footer);

        //Main Window
        mWindow = new QWidget;
        mWindow->setLayout(vMainLayout);
        mWindow->setWindowTitle("Weather++ - Current Weather");
        mWindow->setFixedHeight(500);
        mWindow->setFixedWidth(900);
    };

    /**
     * show window
     */
    void showWindow() {
        mWindow->show();
    };

protected:
    /**
     * Build Header Layout
     */
    QWidget *buildHeaderWidget() {
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

        // return widget
        return headerWidget;
    }

    /**
     * Build Body Layout
     */
    QWidget *buildBodyWidget() {
        // body widget
        QWidget *bodyWidget = new QWidget();

        // body layout
        QVBoxLayout *vBodyLayout = new QVBoxLayout(bodyWidget);
        vBodyLayout->setAlignment(Qt::AlignCenter);

        // weather icon
        // create label to hold image
        mImageLabel = new QLabel();
        // init global private image
        mImage = new QImage();
        // load the placeholder image
        mImage->load("icons/unknown.png");
        // replace the current image with the scaled one
        *mImage = mImage->scaled(200, 200 ,Qt::KeepAspectRatio, Qt::SmoothTransformation);
        // add image to label
        mImageLabel->setPixmap(QPixmap::fromImage(*mImage));
        mImageLabel->setAlignment(Qt::AlignCenter);
        mImageLabel->setStyleSheet("background:lightgrey;border-radius:5px;margin:5px;");

        // weather description
        mImageDesc = new QLabel();
        mImageDesc->setAlignment(Qt::AlignCenter);
        mImageDesc->setStyleSheet("font-size:30pt;");
        mImageDesc->setText("Unknown");

        // add widgets to body layout
        vBodyLayout->addWidget(mImageLabel);
        vBodyLayout->addWidget(mImageDesc);

        // return widget
        return bodyWidget;
    }

    /**
     * Build Footer Layout
     */
    QWidget *buildFooterWidget() {
        // footer widget
        QWidget *footerWidget = new QWidget();

        // footer layout
        QVBoxLayout *vFooterLayout = new QVBoxLayout(footerWidget);
        vFooterLayout->setAlignment(Qt::AlignCenter);

        // 1. footer row
        QHBoxLayout *hFooterFirstRowLayout = new QHBoxLayout();
        hFooterFirstRowLayout->setAlignment(Qt::AlignCenter);
        // label temp
        mInfoTemp = new QLabel();
        mInfoTemp->setAlignment(Qt::AlignCenter);
        mInfoTemp->setText("unknown °C");
        mInfoTemp->setStyleSheet("font-size:20pt;margin:5px");
        // add label to 1. footer row
        hFooterFirstRowLayout->addWidget(mInfoTemp);

        // 2. footer row
        QHBoxLayout *hFooterSecondRowLayout = new QHBoxLayout();
        hFooterSecondRowLayout->setAlignment(Qt::AlignCenter);
        // Label temp min
        mInfoTempMin = new QLabel();
        mInfoTempMin->setAlignment(Qt::AlignCenter);
        mInfoTempMin->setText("MIN: unknown °C");
        mInfoTempMin->setStyleSheet("font-size:20pt;margin:5px");
        // Label temp max
        mInfoTempMax = new QLabel();
        mInfoTempMax->setAlignment(Qt::AlignCenter);
        mInfoTempMax->setText("MAX: unknown °C");
        mInfoTempMax->setStyleSheet("font-size:20pt;margin:5px");
        // add labels to 2. footer row
        hFooterSecondRowLayout->addWidget(mInfoTempMin);
        hFooterSecondRowLayout->addWidget(mInfoTempMax);

        // 3. footer row
        QHBoxLayout *hFooterThirdRowLayout = new QHBoxLayout();
        hFooterThirdRowLayout->setAlignment(Qt::AlignCenter);
        // Label humidity
        mInfoHumidity = new QLabel();
        mInfoHumidity->setAlignment(Qt::AlignCenter);
        mInfoHumidity->setText("Humidity:\t unknown %");
        mInfoHumidity->setStyleSheet("font-size:15pt;margin:5px");
        // Label pressure
        mInfoPressure = new QLabel();
        mInfoPressure->setAlignment(Qt::AlignCenter);
        mInfoPressure->setText("Pressure:\t unknown hPa");
        mInfoPressure->setStyleSheet("font-size:15pt;margin:5px");
        // add labels to 3. footer row
        hFooterThirdRowLayout->addWidget(mInfoHumidity);
        hFooterThirdRowLayout->addWidget(mInfoPressure);

        // add layout to footer layout
        vFooterLayout->addLayout(hFooterFirstRowLayout);
        vFooterLayout->addLayout(hFooterSecondRowLayout);
        vFooterLayout->addLayout(hFooterThirdRowLayout);

        // return widget
        return footerWidget;
    }

    /**
     * Load image for the current weather
     */
    void loadNewImage(QString imageName) {
        // create new image
        QImage *img = new QImage();
        // load the new image
        img->load("icons/" + imageName + ".png");
        // replace the current image with the scaled one
        *img = img->scaled(200,200,Qt::KeepAspectRatio,Qt::SmoothTransformation);
        mImageLabel->setPixmap(QPixmap::fromImage(*img));
    }

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
        // Parse JSON to Objects
        WeatherParser parser(ba);

        //get all descriptions
        std::vector<WeatherDescription> weatherDescriptions = parser.getWeatherDescription();
        WeatherDescription weatherDescription = weatherDescriptions[0];
        //get detailed information
        WeatherInfo weatherInfo = parser.getWeatheInfo();

        // Get Weather Icon
        WeatherMapper *mapper = new WeatherMapper();
        std::string weatherIcon;
        weatherIcon = mapper->getWeatherIconByDesc(weatherDescription.description);
        // fallback solution, if icon is not found with description
        if (weatherIcon.empty()) {
            weatherIcon = mapper->getWeatherIconByIcon(weatherDescription.icon);
        }
        // if fallback fails, show unknown icon
        if (weatherIcon.empty()) {
            weatherIcon = "unknown";
        }
        // Set Weather Icon
        loadNewImage(QString::fromStdString(weatherIcon));
        // Set Weather Description
        mImageDesc->setText(QString::fromStdString(weatherDescription.description));

        // Footer Text
        mInfoTemp->setText(QString("%1 °C").arg(weatherInfo.temp));
        mInfoTempMin->setText(QString("MIN: %1°C").arg(weatherInfo.temp_min));
        mInfoTempMax->setText(QString("MAX: %1 °C").arg(weatherInfo.temp_max));
        mInfoHumidity->setText(QString("Humidity:\t %1 %").arg(weatherInfo.humidity));
        mInfoPressure->setText(QString("Pressure:\t %1 hPa").arg(weatherInfo.pressure));

        // set focus and select current text
        mTxtSearchQuery->setFocus();
        mTxtSearchQuery->selectAll();

        // free memory
        delete mapper;
    }
};

#endif
