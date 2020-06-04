#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

namespace Ui {
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
    void showScore(float time, float percentageMistakes, float percentageAbsoluteMistakes, float correctness);
    void startTest();

private:
    QVector<QString> checkEalierScore(QString name);
    void saveScoreIfBetter(QString name, float time, float percentageMistakes, float percentageAbsoluteMistakes, float correctness);
    void displayBestScore(QString name);
    void displayInformation(QString htmlText);
    void showStartMenu();
    void showScoreTable();
    Ui::MainWindow *ui;
    QString textToDisplay;
    ScoreDisplayer *scoreDisplayer;
    Editor *testDisplayer;
    QString fileName;
    QStackedWidget *stackedWidget;
};

#endif // MAINWINDOW_H
