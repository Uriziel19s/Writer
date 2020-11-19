#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <iomanip>
#include <iostream>
#include <QMainWindow>
#include <QFileInfo>
#include <QFileDialog>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QDataStream>
#include <QTimer>
#include <QTextBrowser>
#include <QStackedWidget>
#include <QSizePolicy>
#include "editor.h"
#include "scoredisplayer.h"


namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void openFile();

public slots:
    void showScore(double time, double percentageMistakes, double percentageAbsoluteMistakes, double correctness);
    void startTest();

private:
    QVector<QString> checkEalierScore(QString name);
    void saveScoreIfBetter(QString name, double time, double percentageMistakes, double percentageAbsoluteMistakes, double correctness);
    void displayBestScore(QString name);
    void displayInformation(QString htmlText);
    void showStartMenu();
    void showScoreTable();
    void setBackgroundsColor(QColor color);
    void setTextSize(unsigned int size);
    std::unique_ptr<Ui::MainWindow> ui;
    std::unique_ptr<ScoreDisplayer> scoreDisplayer;
    std::unique_ptr<Editor> testDisplayer;
    std::unique_ptr<QStackedWidget> stackedWidget;
    QString fileName;
    QString textToDisplay;
    const unsigned int kMaxFileSize = 1024 * 1024;
};

#endif // MAINWINDOW_H
