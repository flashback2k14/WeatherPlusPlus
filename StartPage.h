#ifndef STARTPAGE_H
#define STARTPAGE_H

#include <QMainWindow>
#include <QString>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <qsplashscreen.h>
#include "WeatherPages.h"


class StartPage : public QMainWindow {

Q_OBJECT

private:
    QString mAppPath;
    QWidget *mStartWindow;
    WeatherPages *mCurrentWeatherWindow;
    QSplashScreen *mSplash;

public:
    /**
     * Constructor
     */
    StartPage(QString appPath, QSplashScreen *splash) : mAppPath(appPath){
        this->mSplash = splash;
    }

    /**
     * setup start page
     */
    void setupUi() {
        // create main widget for holding main layout
        QWidget *mainWidget = new QWidget;
        // create main layout
        QVBoxLayout *vMainLayout = new QVBoxLayout(mainWidget);

        // create label for project name
        QLabel *headlineLabel = new QLabel;
        headlineLabel->setAlignment(Qt::AlignCenter);
        headlineLabel->setText("Weather++");
        headlineLabel->setStyleSheet(*configureHeadlineStyling("monospace", "#FFFFFF"));

        // create label for project contributors
        QLabel *headlineContributorLabel = new QLabel;
        headlineContributorLabel->setAlignment(Qt::AlignCenter);
        headlineContributorLabel->setText("by\n\n\nPatrick Hebner\n&\nSebastian Kloppe");
        headlineContributorLabel->setStyleSheet(*configureHeadlineContributorStyling("sans", "#FFFFFF"));

        // create button to open current weather window
        QPushButton *btnOpenCurrentWeatherWindow = new QPushButton;
        btnOpenCurrentWeatherWindow->setFixedHeight(50);
        btnOpenCurrentWeatherWindow->setText("OPEN");
        btnOpenCurrentWeatherWindow->setCursor(Qt::PointingHandCursor);
        btnOpenCurrentWeatherWindow->setStyleSheet(*configureButtonStyling("sans", "rgba(242,0,63,1.0)", "#FFFFFF"));

        // click listener
        connect(btnOpenCurrentWeatherWindow, SIGNAL(clicked()), this, SLOT(openCurrentWeatherWindow()));

        // add widgets to main layout
        vMainLayout->addWidget(headlineLabel);
        vMainLayout->addWidget(headlineContributorLabel);
        vMainLayout->addWidget(btnOpenCurrentWeatherWindow);

        // create start page
        mStartWindow = new QWidget;
        mStartWindow->setLayout(vMainLayout);
        mStartWindow->setWindowTitle("Weather++ - Start");
        mStartWindow->setFixedWidth(350);
        mStartWindow->setFixedHeight(350);
        mStartWindow->setStyleSheet("background-color:#003580;");
    }

    /**
     * show start page
     */
    void showWindow() {
        mSplash->finish(mStartWindow);
        mStartWindow->show();
    }


protected:
    /**
     * configure styling for headline
     */
    QString* configureHeadlineStyling(std::string labelFontFamily, std::string labelColor) {
        QString *styling = new QString;
        styling->append("font-family:" + QString::fromStdString(labelFontFamily) + ";");
        styling->append("font-size:40pt;");
        styling->append("font-weight:bold;");
        styling->append("color:" + QString::fromStdString(labelColor) + ";");
        return styling;
    }

    /**
     * configure styling for contributor headline
     */
    QString* configureHeadlineContributorStyling(std::string labelFontFamily, std::string labelColor) {
        QString *styling = new QString;
        styling->append("font-family:" + QString::fromStdString(labelFontFamily) + ";");
        styling->append("font-size:15pt;");
        styling->append("color:" + QString::fromStdString(labelColor) + ";");
        styling->append("margin-bottom:20px;");
        styling->append("padding:5px;");
        return styling;
    }

    /**
     * configure styling for button
     */
    QString* configureButtonStyling(std::string btnFontFamily, std::string btnBg, std::string btnColor) {
        QString *styling = new QString;
        styling->append("font-family:" + QString::fromStdString(btnFontFamily) + ";");
        styling->append("margin-bottom:20px;");
        styling->append("background-color:qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 " + QString::fromStdString(btnBg) + ", stop: 1 " + QString::fromStdString(btnBg) + ");");
        styling->append("color:" + QString::fromStdString(btnColor) + ";");
        styling->append("border:none;");
        styling->append("border-radius:5px;");
        return styling;
    }

public slots:

    /**
     * open current weather window
     */
    void openCurrentWeatherWindow() {
        mCurrentWeatherWindow = new WeatherPages(mAppPath);
        mCurrentWeatherWindow->setupUi();
        mCurrentWeatherWindow->showWindow();
    };
};

#endif
