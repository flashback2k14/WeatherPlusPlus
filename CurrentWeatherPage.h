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
#include <qstackedwidget.h>
#include <qcombobox.h>
#include <sstream>

using namespace std;

struct ImageData {
    QLabel *mImageLabel;
    QImage *mImage;
    QLabel *mImageDesc;
};

struct WeatherInformation {
    QLabel *mInfoTemp;
    QLabel *mInfoTempMin;
    QLabel *mInfoTempMax;
    QLabel *mInfoHumidity;
    QLabel *mInfoPressure;
};
class CurrentWeatherPage : public QMainWindow {

Q_OBJECT

private:
    /**
     * Global UI Widgets
     */
    QString mAppPath;
    QWidget *mWindow;
    QStackedWidget *stack;
    int dayTimeIndex;
    // header
    QLineEdit *mTxtSearchQueryCurrent;
    QLineEdit *mTxtSearchQueryForecast;
    // body
    // Current Weather
    QLabel *mImageLabelCurrent;
    QImage *mImageCurrent;
    QLabel *mImageDescCurrent;
    // Forecast
    QWidget *timeSelectionWidget;
    QComboBox *dayTimes;

    ImageData img1;
    ImageData img2;
    ImageData img3;
    ImageData img4;
    ImageData img5;
    // footer
    // Current Weather
    QLabel *mInfoTempCurrent;
    QLabel *mInfoTempMinCurrent;
    QLabel *mInfoTempMaxCurrent;
    QLabel *mInfoHumidityCurrent;
    QLabel *mInfoPressureCurrent;
    // Forecast
    WeatherInformation wInfo1;
    WeatherInformation wInfo2;
    WeatherInformation wInfo3;
    WeatherInformation wInfo4;
    WeatherInformation wInfo5;
    // Forecast data
    std::vector<WeatherDescription> weatherDescriptions;
    std::vector<WeatherInfo> weatherInfos;

public:
    /**
     * Constructor / Destructor
     */
    CurrentWeatherPage(QString path): mAppPath(path), dayTimeIndex(0) {};
    ~CurrentWeatherPage() {};

    /**
     * Build and Show
     */
    void setupUi() {
        // build Layout
        QVBoxLayout *vMainLayout = new QVBoxLayout;
        // build stack widget for multiple pages
        stack = new QStackedWidget();

        // First page with single weather
        QWidget *singleWeatherPage = new QWidget();
        QVBoxLayout *hSingleWeather = new QVBoxLayout(singleWeatherPage);
        // Widgets of the first page
        QWidget *header = buildHeaderWidget();
        QWidget *body = buildBodyWidget(&mImageCurrent, &mImageLabelCurrent, &mImageDescCurrent, QSize(200, 200));
        QWidget *footer = buildFooterWidget();

        hSingleWeather->addWidget(header);
        hSingleWeather->addWidget(body);
        hSingleWeather->addWidget(footer);

        // Second page with forecast
        QWidget *forecastWeatherPage = new QWidget();
        QVBoxLayout *hForecastWeather = new QVBoxLayout(forecastWeatherPage);
        // Widgets of the second page
        QWidget *forecastHeader = buildForecastHeaderWidget();
        QWidget *forecastFooter = buildForecastFooterWidget();

        hForecastWeather->addWidget(forecastHeader);
        hForecastWeather->addWidget(forecastFooter);

        // add first page to stack at index 0
        stack->insertWidget(0, singleWeatherPage);
        // add second page to stack at index 1
        stack->insertWidget(1, forecastWeatherPage);
        // add stack to the main layout
        vMainLayout->addWidget(buildWeatherSelectionWidget());
        vMainLayout->addWidget(stack);

        //Main Window
        mWindow = new QWidget;
        mWindow->setLayout(vMainLayout);
        mWindow->setWindowTitle("Weather++");
        mWindow->setFixedHeight(700);
        mWindow->setFixedWidth(900);
    };

    /**
     * show window
     */
    void showWindow() {
        mWindow->show();
    };

protected:

    QWidget *buildWeatherSelectionWidget() {
        // Page selection widget
        QWidget *pageSelectionWidget = new QWidget();
        // Horizontal Layout
        QHBoxLayout *hPageSelectionLayout = new QHBoxLayout(pageSelectionWidget);
        // Place the combo box at the center
        hPageSelectionLayout->setAlignment(Qt::AlignCenter);

        // Combobox + Entries
        QComboBox *pages = new QComboBox();
        pages->addItem(tr("Current Weather"));
        pages->addItem(tr("Forecast"));

        // Add Listener
        connect(pages, SIGNAL(activated(int)),
                this, SLOT(swapPage(int)));

        hPageSelectionLayout->addWidget(pages);

        return pageSelectionWidget;
    }

    QWidget *buildDayTimeSelectionWidget() {
        // Page selection widget
        QWidget *dayTimeSelectionWidget = new QWidget();
        // Horizontal Layout
        QHBoxLayout *hDayTimeSelectionLayout = new QHBoxLayout(dayTimeSelectionWidget);
        // Place the combo box at the center
        hDayTimeSelectionLayout->setAlignment(Qt::AlignCenter);

        // Combobox + Entries
        dayTimes = new QComboBox();
        dayTimes->addItem(tr("not available"));
        dayTimes->addItem(tr("not available"));
        dayTimes->addItem(tr("not available"));
        dayTimes->addItem(tr("not available"));
        dayTimes->addItem(tr("not available"));
        dayTimes->addItem(tr("not available"));
        dayTimes->addItem(tr("not available"));
        dayTimes->addItem(tr("not available"));

        // Add Listener
        connect(dayTimes, SIGNAL(activated(int)),
                this, SLOT(setAllForecastData(int)));

        dayTimes->setFixedWidth(300);
        hDayTimeSelectionLayout->addWidget(dayTimes);

        return dayTimeSelectionWidget;
    }

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
        mTxtSearchQueryCurrent = new QLineEdit;
        mTxtSearchQueryCurrent->setAlignment(Qt::AlignCenter | Qt::AlignLeft);
        mTxtSearchQueryCurrent->setFixedHeight(25);

        // Button
        QPushButton *btnSearch = new QPushButton;
        btnSearch->setText("SEARCH");
        btnSearch->setDefault(true);
        // Click Listener
        connect(btnSearch, SIGNAL(clicked()), this, SLOT(requestWeatherData()));

        // add Widgets to Header Layout
        hHeaderLayout->addWidget(label);
        hHeaderLayout->addWidget(mTxtSearchQueryCurrent);
        hHeaderLayout->addWidget(btnSearch);

        // configure header widget
        headerWidget->setFixedHeight(50);

        // return widget
        return headerWidget;
    }

    /**
     * Build Body Layout
     */
    QWidget *buildBodyWidget(QImage **img, QLabel **label, QLabel **desc, QSize imgSize, bool labeled = true) {
        // body widget
        QWidget *bodyWidget = new QWidget();

        // body layout
        QVBoxLayout *vBodyLayout = new QVBoxLayout(bodyWidget);
        vBodyLayout->setAlignment(Qt::AlignCenter);

        // weather icon
        // create label to hold image
        *label = new QLabel();
        // init global private image
        *img = new QImage();
        // load the placeholder image
        (*img)->load("icons/unknown.png");
        // replace the current image with the scaled one
        **img = (*img)->scaled(imgSize , Qt::KeepAspectRatio, Qt::SmoothTransformation);
        // add image to label
        (*label)->setPixmap(QPixmap::fromImage(**img));
        (*label)->setAlignment(Qt::AlignCenter);
        (*label)->setStyleSheet("background:lightgrey;border-radius:5px;margin:5px;");

        if(labeled == true){
            // weather description
            *desc = new QLabel();
            (*desc)->setAlignment(Qt::AlignCenter);
            (*desc)->setStyleSheet("font-size:30pt;");
            (*desc)->setText("Unknown");
            // add widgets to body layout
            vBodyLayout->addWidget(*desc);
        }
        // add widgets to body layout
        vBodyLayout->addWidget(*label);


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
        mInfoTempCurrent = new QLabel();
        mInfoTempCurrent->setAlignment(Qt::AlignCenter);
        mInfoTempCurrent->setText("unknown °C");
        mInfoTempCurrent->setStyleSheet("font-size:20pt;margin:5px");
        // add label to 1. footer row
        hFooterFirstRowLayout->addWidget(mInfoTempCurrent);

        // 2. footer row
        QHBoxLayout *hFooterSecondRowLayout = new QHBoxLayout();
        hFooterSecondRowLayout->setAlignment(Qt::AlignCenter);
        // Label temp min
        mInfoTempMinCurrent = new QLabel();
        mInfoTempMinCurrent->setAlignment(Qt::AlignCenter);
        mInfoTempMinCurrent->setText("MIN: unknown °C");
        mInfoTempMinCurrent->setStyleSheet("font-size:20pt;margin:5px");
        // Label temp max
        mInfoTempMaxCurrent = new QLabel();
        mInfoTempMaxCurrent->setAlignment(Qt::AlignCenter);
        mInfoTempMaxCurrent->setText("MAX: unknown °C");
        mInfoTempMaxCurrent->setStyleSheet("font-size:20pt;margin:5px");
        // add labels to 2. footer row
        hFooterSecondRowLayout->addWidget(mInfoTempMinCurrent);
        hFooterSecondRowLayout->addWidget(mInfoTempMaxCurrent);

        // 3. footer row
        QHBoxLayout *hFooterThirdRowLayout = new QHBoxLayout();
        hFooterThirdRowLayout->setAlignment(Qt::AlignCenter);
        // Label humidity
        mInfoHumidityCurrent = new QLabel();
        mInfoHumidityCurrent->setAlignment(Qt::AlignCenter);
        mInfoHumidityCurrent->setText("Humidity:\t unknown %");
        mInfoHumidityCurrent->setStyleSheet("font-size:15pt;margin:5px");
        // Label pressure
        mInfoPressureCurrent = new QLabel();
        mInfoPressureCurrent->setAlignment(Qt::AlignCenter);
        mInfoPressureCurrent->setText("Pressure:\t unknown hPa");
        mInfoPressureCurrent->setStyleSheet("font-size:15pt;margin:5px");
        // add labels to 3. footer row
        hFooterThirdRowLayout->addWidget(mInfoHumidityCurrent);
        hFooterThirdRowLayout->addWidget(mInfoPressureCurrent);

        // add layout to footer layout
        vFooterLayout->addLayout(hFooterFirstRowLayout);
        vFooterLayout->addLayout(hFooterSecondRowLayout);
        vFooterLayout->addLayout(hFooterThirdRowLayout);

        // return widget
        return footerWidget;
    }

    /**
     * Build Header Layout
     */
    QWidget *buildForecastHeaderWidget() {
        //Header widget
        QWidget *headerWidget = new QWidget();
        QVBoxLayout *hHeaderLayout = new QVBoxLayout(headerWidget);

        QWidget *searchBar = new QWidget();
        //Header layout
        QHBoxLayout *hSearchBarLayout = new QHBoxLayout(searchBar);
        hSearchBarLayout->setAlignment(Qt::AlignTop);

        // Label
        QLabel *label = new QLabel;
        label->setAlignment(Qt::AlignCenter | Qt::AlignLeft);
        label->setText("Choose your City:");

        // Textfield
        mTxtSearchQueryForecast = new QLineEdit;
        mTxtSearchQueryForecast->setAlignment(Qt::AlignCenter | Qt::AlignLeft);
        mTxtSearchQueryForecast->setFixedHeight(25);

        // Button
        QPushButton *btnSearch = new QPushButton;
        btnSearch->setText("SEARCH");
        btnSearch->setDefault(true);
        // Click Listener
        connect(btnSearch, SIGNAL(clicked()), this, SLOT(requestForecastWeatherData()));

        // add Widgets to Header Layout
        hSearchBarLayout->addWidget(label);
        hSearchBarLayout->addWidget(mTxtSearchQueryForecast);
        hSearchBarLayout->addWidget(btnSearch);

        searchBar->setFixedHeight(50);

        hHeaderLayout->addWidget(searchBar);
        timeSelectionWidget = buildDayTimeSelectionWidget();
        timeSelectionWidget->setDisabled(true);
        hHeaderLayout->addWidget(timeSelectionWidget);

        // return widget
        return headerWidget;
    }

    /**
     * Build Footer Layout
     */
    QWidget *buildForecastFooterWidget() {
        // footer widget
        QWidget *forecastFooterWidget = new QWidget();

        QHBoxLayout *hForecastColumnLayout = new QHBoxLayout(forecastFooterWidget);

        hForecastColumnLayout->addWidget(buildOneForecastElementWidget(&img1, &wInfo1));
        hForecastColumnLayout->addWidget(buildOneForecastElementWidget(&img2, &wInfo2));
        hForecastColumnLayout->addWidget(buildOneForecastElementWidget(&img3, &wInfo3));
        hForecastColumnLayout->addWidget(buildOneForecastElementWidget(&img4, &wInfo4));
        hForecastColumnLayout->addWidget(buildOneForecastElementWidget(&img5, &wInfo5));
        // return widget
        return forecastFooterWidget;
    }

    /**
     * Build Element for Forecast
     */
    QWidget *buildOneForecastElementWidget(ImageData *img, WeatherInformation *wInfo) {
        // footer widget
        QWidget *footerWidget = new QWidget();

        // footer layout
        QVBoxLayout *vFooterLayout = new QVBoxLayout(footerWidget);
        vFooterLayout->setAlignment(Qt::AlignCenter);

        // label temp
        (*wInfo).mInfoTemp = new QLabel();
        (*wInfo).mInfoTemp->setAlignment(Qt::AlignCenter);
        (*wInfo).mInfoTemp->setText("unknown °C");
        (*wInfo).mInfoTemp->setStyleSheet("font-size:14pt;margin:15px");

        // 2. footer row
        //QHBoxLayout *hFooterSecondRowLayout = new QHBoxLayout();
        //hFooterSecondRowLayout->setAlignment(Qt::AlignCenter);
        // Label temp min
        (*wInfo).mInfoTempMin = new QLabel();
        (*wInfo).mInfoTempMin->setAlignment(Qt::AlignCenter);
        (*wInfo).mInfoTempMin->setText("MIN:\t unknown °C");
        (*wInfo).mInfoTempMin->setStyleSheet("font-size:10pt;margin:5px");
        // Label temp max
        (*wInfo).mInfoTempMax = new QLabel();
        (*wInfo).mInfoTempMax->setAlignment(Qt::AlignCenter);
        (*wInfo).mInfoTempMax->setText("MAX:\t unknown °C");
        (*wInfo).mInfoTempMax->setStyleSheet("font-size:10pt;margin:5px");
        // add labels to 2. footer row

        // Label humidity
        (*wInfo).mInfoHumidity = new QLabel();
        (*wInfo).mInfoHumidity->setAlignment(Qt::AlignCenter);
        (*wInfo).mInfoHumidity->setText("Humidity:\t unknown %");
        (*wInfo).mInfoHumidity->setStyleSheet("font-size:10pt;margin:5px");
        // Label pressure
        (*wInfo).mInfoPressure = new QLabel();
        (*wInfo).mInfoPressure->setAlignment(Qt::AlignCenter);
        (*wInfo).mInfoPressure->setText("Pressure:\t unknown hPa");
        (*wInfo).mInfoPressure->setStyleSheet("font-size:10pt;margin:5px");

        // add layout to footer layout
        vFooterLayout->addWidget(buildBodyWidget(&((*img).mImage), &((*img).mImageLabel), &((*img).mImageDesc), QSize(100, 100),
                                                 false));
        vFooterLayout->addWidget((*wInfo).mInfoTemp);
        vFooterLayout->addWidget((*wInfo).mInfoTempMax);
        vFooterLayout->addWidget((*wInfo).mInfoTempMin);
        vFooterLayout->addWidget((*wInfo).mInfoHumidity);
        vFooterLayout->addWidget((*wInfo).mInfoPressure);

        // return widget
        return footerWidget;
    }

    /**
     * Load image for the current weather
     */
    void loadNewImage(QString imageName, QLabel **currentImgLabel, QSize imgSize = QSize(200,200)) {
        // create new image
        QImage *imgLocal = new QImage();
        // load the new image
        imgLocal->load("icons/" + imageName + ".png");
        // replace the current image with the scaled one
        *imgLocal = imgLocal->scaled(imgSize ,Qt::KeepAspectRatio,Qt::SmoothTransformation);
        (*currentImgLabel)->setPixmap(QPixmap::fromImage(*imgLocal));
    }

public slots:
    /**
     * Request Weather Data
     */
    void requestWeatherData() {
        // create api uri to call
        QString uri = ApiUri::buildCurrentWeatherUri(mTxtSearchQueryCurrent->text());
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
        // Set Weather Icon
        loadNewImage(QString::fromStdString(
                getWeatherIcon(weatherDescription.description, weatherDescription.icon)
        ), &mImageLabelCurrent);
        // Set Weather Description
        mImageDescCurrent->setText(QString::fromStdString(weatherDescription.description));
        // Footer Text
        setWeatherDetails(weatherInfo,
                          mInfoTempCurrent,
                          mInfoTempMinCurrent,
                          mInfoTempMaxCurrent,
                          mInfoHumidityCurrent,
                          mInfoPressureCurrent);
        // set focus and select current text
        mTxtSearchQueryCurrent->setFocus();
        mTxtSearchQueryCurrent->selectAll();
    }

    std::string getWeatherIcon(std::string name, std::string icon){
        // Get Weather Icon
        WeatherMapper *mapper = new WeatherMapper();
        std::string weatherIcon;
        weatherIcon = mapper->getWeatherIconByDesc(name);
        // fallback solution, if icon is not found with description
        if (weatherIcon.empty()) {
            weatherIcon = mapper->getWeatherIconByIcon(icon);
        }
        // if fallback fails, show unknown icon
        if (weatherIcon.empty()) {
            weatherIcon = "unknown";
        }
        // free memory
        delete mapper;
        return weatherIcon;
    }

    void requestForecastWeatherData(){
        // create api uri to call
        QString uri = ApiUri::buildForecastWeatherUri(mTxtSearchQueryForecast->text());
        // create api caller object
        ApiCall forecastWeatherByCity(uri);
        // get data response
        QByteArray ba = forecastWeatherByCity.sendRequest();
        // Parse JSON to Objects
        WeatherParser parser(ba);
        //get all descriptions
        weatherDescriptions = parser.getForecastDescriptions();
        weatherInfos = parser.getForecastInfos();

        setAllForecastData(dayTimeIndex);

        mTxtSearchQueryForecast->setFocus();
        mTxtSearchQueryForecast->selectAll();

        timeSelectionWidget->setDisabled(false);
    }

    void setAllItemTexts(time_t time){
        const time_t ONE_DAY = 3 * 60 * 60;
        time_t dayTime = time;
        tm *gmtm = gmtime(&dayTime);
        std::stringstream ss;
        ss << (gmtm->tm_hour) << "-" << (gmtm->tm_min) << "-" << (gmtm->tm_sec);
        std::string firstTimeString= ss.str();
        //cout << "First time: " << asctime(gmtm) << endl;
        //std::string firstTimeString = asctime(gmtm);
        QString s = QString("%1").fromStdString(firstTimeString);
        for(int i = 0; i < 8; ++i){
            setItemText(i, dayTime,  s);
            dayTime += ONE_DAY;
            tm *gmtm = gmtime(&dayTime);
            std::stringstream ss;
            ss << (gmtm->tm_hour) << "-" << (gmtm->tm_min) << "-" << (gmtm->tm_sec);
            firstTimeString = ss.str();
            //std::string firstTimeString = asctime(gmtm);
            s = QString("%1").fromStdString(firstTimeString);
            cout << "DAY TIME: " << s.toStdString() << endl;
        }
    }

    void setItemText(int index, time_t time, QString value){
        if(containsDayTime(time)){
            dayTimes->setItemText(index, value);
        }
    }

    bool containsDayTime(time_t time){
        for(WeatherInfo const &wInfo : weatherInfos){
            if(wInfo.dt == time){
                return true;
            }
        }
        return false;
    }

    void setWeatherDetails(WeatherInfo details, QLabel *temp, QLabel *max, QLabel *min, QLabel *humidity, QLabel *pressure){
        temp->setText(QString("%1 °C").arg(details.temp));
        max->setText(QString("MIN: %1°C").arg(details.temp_min));
        min->setText(QString("MAX: %1 °C").arg(details.temp_max));
        humidity->setText(QString("Humidity: %1 %").arg(details.humidity));
        pressure->setText(QString("Pressure: %1 hPa").arg(details.pressure));
    }

    void setForecastData(ImageData iData, WeatherInformation wInformation, WeatherDescription wDesc, WeatherInfo details){
        std::string icon = getWeatherIcon(wDesc.description, wDesc.icon);
        loadNewImage(QString::fromStdString(icon), &(iData).mImageLabel, QSize(100,100));

        setWeatherDetails(details,
                          wInformation.mInfoTemp,
                          wInformation.mInfoTempMax,
                          wInformation.mInfoTempMin,
                          wInformation.mInfoHumidity,
                          wInformation.mInfoPressure);
    }

    void setDummiForecastData(ImageData iData, WeatherInformation wInformation){
        cout << "SET DUMMY DATA: " << endl;
        WeatherDescription wDesc;
        WeatherInfo details;

        time_t time = details.dt;
        //if(containsDayTime(time)){
            std::string icon = getWeatherIcon(wDesc.description, wDesc.icon);
            cout << "SET ICON: " << icon << endl;
            loadNewImage(QString::fromStdString(icon), &(iData).mImageLabel, QSize(100,100));

            setWeatherDetails(details,
                              wInformation.mInfoTemp,
                              wInformation.mInfoTempMax,
                              wInformation.mInfoTempMin,
                              wInformation.mInfoHumidity,
                              wInformation.mInfoPressure);
       // }


    }

    void setAllForecastData(int index = 0){

        dayTimeIndex = index;
        time_t now = time(0);
        cout << "Current time: " << ctime(&now) << endl;
        cout << "Current index: " << dayTimeIndex << endl;
        if(weatherDescriptions.size() > 0 && weatherInfos.size() > 0){
            time_t initialTime = weatherInfos[0].dt;
            if(weatherDescriptions.size() > dayTimeIndex && weatherInfos.size() > dayTimeIndex){
                WeatherDescription wDesc1 = weatherDescriptions[dayTimeIndex];
                WeatherInfo details1 = weatherInfos[dayTimeIndex];
                time_t firstTime = details1.dt;
                if(containsDayTime(firstTime)){
                    setForecastData(img1, wInfo1, wDesc1, details1);
                }
            }else{
                setDummiForecastData(img1, wInfo1);
            }
            if(weatherDescriptions.size() > (dayTimeIndex+8) && weatherInfos.size() > (dayTimeIndex+8)) {
                WeatherDescription wDesc2 = weatherDescriptions[dayTimeIndex + 8];
                WeatherInfo details2 = weatherInfos[dayTimeIndex + 8];
                time_t secondTime = details2.dt;
                if (containsDayTime(secondTime)) {
                    setForecastData(img2, wInfo2, wDesc2, details2);
                }
            }else{
                setDummiForecastData(img2, wInfo2);
            }
            if(weatherDescriptions.size() > (dayTimeIndex+16) && weatherInfos.size() > (dayTimeIndex+16)) {
                WeatherDescription wDesc3 = weatherDescriptions[dayTimeIndex + 16];
                WeatherInfo details3 = weatherInfos[dayTimeIndex + 16];
                time_t thirdTime = details3.dt;
                if (containsDayTime(thirdTime)) {
                    setForecastData(img3, wInfo3, wDesc3, details3);
                }
            }else{
                setDummiForecastData(img3, wInfo3);
            }
            if(weatherDescriptions.size() > (dayTimeIndex+32) && weatherInfos.size() > (dayTimeIndex+32)) {
                WeatherDescription wDesc4 = weatherDescriptions[dayTimeIndex + 24];
                WeatherInfo details4 = weatherInfos[dayTimeIndex + 24];
                time_t fourthTime = details4.dt;
                if (containsDayTime(fourthTime)) {
                    setForecastData(img4, wInfo4, wDesc4, details4);
                }
            }else{
                setDummiForecastData(img4, wInfo4);
            }
            if(weatherDescriptions.size() > (dayTimeIndex+32) && weatherInfos.size() > (dayTimeIndex+32)) {
                WeatherDescription wDesc5 = weatherDescriptions[dayTimeIndex + 32];
                WeatherInfo details5 = weatherInfos[dayTimeIndex + 32];
                time_t fifthTime = details5.dt;
                if (containsDayTime(fifthTime)) {
                    setForecastData(img5, wInfo5, wDesc5, details5);
                }
            }else{
                setDummiForecastData(img5, wInfo5);
            }
            if(initialTime > 0){
                setAllItemTexts(initialTime);
            }
        }
    }

    void swapPage(int pageIndex) {
        stack->setCurrentIndex(pageIndex);
    }
};

#endif
