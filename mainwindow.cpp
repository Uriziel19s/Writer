#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    testDisplayer = new Editor(this);
    scoreDisplayer = new ScoreDisplayer(this);
    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(testDisplayer);
    stackedWidget->addWidget(scoreDisplayer);

    stackedWidget->setCurrentIndex(0);

    ui->setupUi(this);
    setCentralWidget(stackedWidget);
    openFile();
    testDisplayer->setText(this->textToDisplay);
    ui->statusbar->addPermanentWidget(ui->progressBar);
    ui->statusbar->addPermanentWidget(ui->lcdMistakesCounter);
    ui->lcdMistakesCounter->setMode(QLCDNumber::Dec);
    ui->progressBar->setValue(0);
    connect(testDisplayer, &Editor::mistakesChanged, ui->lcdMistakesCounter, static_cast<void (QLCDNumber::*)(int)>(&QLCDNumber::display));
    connect(testDisplayer, &Editor::progressChanged, ui->progressBar, &QProgressBar::setValue);
    connect(testDisplayer, &Editor::testEnded, this, &MainWindow::showScore);
    connect(testDisplayer, &Editor::resetTest, this, &MainWindow::startTest);
    connect(scoreDisplayer, &ScoreDisplayer::resetTest, this, &MainWindow::startTest);

}

MainWindow::~MainWindow()
{
    delete testDisplayer;
    delete scoreDisplayer;
    delete stackedWidget;
    delete ui;
}

void MainWindow::openFile()
{
    QFileInfo fileInfo;
    fileName = QFileDialog::getOpenFileName(this, "Open a file", fileInfo.absolutePath());
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly |QIODevice::Text))
    {
        QMessageBox::information(this, "Unable to open file.", file.errorString());
        //maybe add exception
    }
    textToDisplay.clear();
    if(file.size() <= 1000000)//hardcoded, must be changed in the future
    {
        textToDisplay += file.readAll();
    }
    file.close();
}

void MainWindow::showScore(float time, float percentageMistakes, float percentageAbsoluteMistakes, float correctness)
{
    stackedWidget->setCurrentIndex(1);

    scoreDisplayer->setHtml("<p style=\"text-align: center\">Time: " + QString::number(time/1000) + "s<br>Mistakes: " + QString::number(percentageMistakes)
                           + "%<br>Absolute mistakes: "+ QString::number(percentageAbsoluteMistakes)
                           + "%<br>The correctness: " + QString::number(correctness) + "%</p>");
    saveScoreIfBetter(fileName, time, percentageMistakes, percentageAbsoluteMistakes, correctness);
    displayBestScore(fileName);
}

void MainWindow::saveScoreIfBetter(QString name, float time, float percentageMistakes, float percentageAbsoluteMistakes, float correctness)
{
    name = name.right(name.size() - name.lastIndexOf("/") - 1);//get name of file
    QFile file("scores.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::WriteOnly |QIODevice::Text))
    {
        QMessageBox::information(this, "Unable to open file.", file.errorString());
        //maybe add exception
    }
    QStringList scoresList = QString(file.readAll()).split("\n");
    int position = scoresList.indexOf(name);
    if(position != -1)
    {
        if(scoresList[position+4].toFloat() < correctness || (scoresList[position+4].toFloat() == correctness && scoresList[position+1].toFloat() > time))
        {
            scoresList[position + 1] = QString::number(time);
            scoresList[position + 2] = QString::number(percentageMistakes);
            scoresList[position + 3] = QString::number(percentageAbsoluteMistakes);
            scoresList[position + 4] = QString::number(correctness);
        }
    }
    else
    {
        scoresList.append(name);
        scoresList.append(QString::number(time));
        scoresList.append(QString::number(percentageMistakes));
        scoresList.append(QString::number(percentageAbsoluteMistakes));
        scoresList.append(QString::number(correctness));
    }
    file.resize(0);
    file.write((scoresList.join("\n")).toUtf8());
    file.close();
}

void MainWindow::displayBestScore(QString name)
{
    name = name.right(name.size() - name.lastIndexOf("/") - 1);//get name of file
    QFile file("scores.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(this, "Unable to open file.", file.errorString());
        //maybe add exception
    }
    QStringList scoresList = QString(file.readAll()).split("\n");
    int position = scoresList.indexOf(name);
    if(position != -1)
    {
        scoreDisplayer->setHtml(scoreDisplayer->toHtml() + "<p style=\"font-weight: bold; text-align: center\">Best score:</p>"
                                  "<p style=\"text-align: center\">Time: " + QString::number(scoresList[position + 1].toFloat()/1000)
                                  + "s<br>Mistakes: " + scoresList[position + 2]
                                  + "%<br>Absolute mistakes: "+ scoresList[position + 3]
                                  + "%<br>The correctness: " + scoresList[position + 4] + "%</p>");
    }
}

void MainWindow::startTest()
{
    stackedWidget->setCurrentIndex(0);
    openFile();
    testDisplayer->reset();
    testDisplayer->setText(textToDisplay);
}

