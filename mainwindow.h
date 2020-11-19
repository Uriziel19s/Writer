#ifndef MAINWINDOW_H
#define MAINWINDOW_H

<<<<<<< HEAD
#include <memory>
#include <iomanip>
#include <iostream>
=======
>>>>>>> 2b2702bb354cd6160fd74fe4c3cc689edf5a7168
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

<<<<<<< HEAD

namespace Ui
{
=======
namespace Ui {
>>>>>>> 2b2702bb354cd6160fd74fe4c3cc689edf5a7168
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
<<<<<<< HEAD
    void showScore(double time, double percentageMistakes, double percentageAbsoluteMistakes, double correctness);
=======
    void showScore(float time, float percentageMistakes, float percentageAbsoluteMistakes, float correctness);
>>>>>>> 2b2702bb354cd6160fd74fe4c3cc689edf5a7168
    void startTest();

private:
    QVector<QString> checkEalierScore(QString name);
<<<<<<< HEAD
    void saveScoreIfBetter(QString name, double time, double percentageMistakes, double percentageAbsoluteMistakes, double correctness);
=======
    void saveScoreIfBetter(QString name, float time, float percentageMistakes, float percentageAbsoluteMistakes, float correctness);
>>>>>>> 2b2702bb354cd6160fd74fe4c3cc689edf5a7168
    void displayBestScore(QString name);
    void displayInformation(QString htmlText);
    void showStartMenu();
    void showScoreTable();
<<<<<<< HEAD
    void setBackgroundsColor(QColor color);
    void setTextSize(unsigned int size);
    std::unique_ptr<Ui::MainWindow> ui;
    std::unique_ptr<ScoreDisplayer> scoreDisplayer;
    std::unique_ptr<Editor> testDisplayer;
    std::unique_ptr<QStackedWidget> stackedWidget;
    QString fileName;
    QString textToDisplay;
    const unsigned int kMaxFileSize = 1024 * 1024;
=======
    Ui::MainWindow *ui;
    QString textToDisplay;
    ScoreDisplayer *scoreDisplayer;
    Editor *testDisplayer;
    QString fileName;
    QStackedWidget *stackedWidget;
>>>>>>> 2b2702bb354cd6160fd74fe4c3cc689edf5a7168
};

#endif // MAINWINDOW_H
