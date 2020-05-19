#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    openFile();
    ui->centralwidget->setText(this->textToDisplay);
    ui->statusbar->addPermanentWidget(ui->progressBar);
    ui->statusbar->addPermanentWidget(ui->lcdMistakesCounter);
    ui->lcdMistakesCounter->setMode(QLCDNumber::Dec);
    ui->progressBar->setValue(0);
    connect(ui->centralwidget, &Editor::mistakesChanged, ui->lcdMistakesCounter, static_cast<void (QLCDNumber::*)(int)>(&QLCDNumber::display));
    connect(ui->centralwidget, &Editor::progressChanged, ui->progressBar, &QProgressBar::setValue);
    connect(ui->centralwidget, &Editor::testEnded, this, &MainWindow::showScore);
}

MainWindow::~MainWindow()
{
    delete  ui->centralwidget;

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
    qDebug() << textToDisplay;
    file.close();
}

void MainWindow::showScore(float time, float percentageMistakes, float percentageAbsoluteMistakes, float correctness)
{
    qDebug() << time << " " << percentageMistakes << " " << percentageAbsoluteMistakes;
    setCentralWidget(&scoreDisplayer);
    scoreDisplayer.setHtml("<p style=\"text-align: center\">Time: " + QString::number(time/1000) + "s<br>Mistakes: " + QString::number(percentageMistakes)
                           + "%<br>Absolute mistakes: "+ QString::number(percentageAbsoluteMistakes)
                           + "%<br>The correctness: " + QString::number(correctness) + "%</p>");
    saveScoreIfBetter(fileName, time, percentageMistakes, percentageAbsoluteMistakes, correctness);

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
    for(auto x : scoresList)
    {
        qDebug() << x << " ";
    }
    int position = scoresList.indexOf(name);
    qDebug() << position << " ";
    if(position != -1)
    {
        if(scoresList[position+4].toFloat() < correctness || scoresList[position+4].toFloat() == correctness && scoresList[position+1].toFloat() > time)
        {
            scoresList[position + 1] = QString::number(time);
            scoresList[position + 2] = QString::number(percentageMistakes);
            scoresList[position + 3] = QString::number(percentageAbsoluteMistakes);
            scoresList[position + 4] = QString::number(correctness);
            for(auto x : scoresList)
            {
                qDebug() << x << " ";
            }
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


