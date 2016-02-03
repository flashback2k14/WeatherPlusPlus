#ifndef WEATHERUI_H
#define WEATHERUI_H

#include <QtCore>
#include <QtGui>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qlabel.h>

class WeatherUi: public QMainWindow {

private:
    QWidget* mWindow;

public:
    /**
     * Constructor / Deconstructor
     */
    WeatherUi(QMainWindow *parent = 0);
    ~WeatherUi();
    /**
     * Getter / Setter
     */
    void setWindow(QWidget* w) { mWindow = w; }
    QWidget* getWindow() { return mWindow; }
    /**
     * Build and Show
     */
    void setupUi();
    void showWindow();
};

#endif
