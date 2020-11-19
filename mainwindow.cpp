#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    testDisplayer = std::make_unique<Editor>(this);
    scoreDisplayer = std::make_unique<ScoreDisplayer>(this);
    stackedWidget = std::make_unique<QStackedWidget>(this);
    stackedWidget->addWidget(testDisplayer.get());
    stackedWidget->addWidget(scoreDisplayer.get());
    ui->setupUi(this);
    setCentralWidget(stackedWidget.get());
    ui->statusbar->addWidget(ui->fingerDisplayer);
    ui->statusbar->addPermanentWidget(ui->progressBar);
    ui->statusbar->addPermanentWidget(ui->lcdMistakesCounter);
    ui->lcdMistakesCounter->setMode(QLCDNumber::Dec);
    ui->progressBar->setValue(0);
    ui->fingerDisplayer->setText("");
    ui->fingerDisplayer->setMaximumSize(250,20);
    ui->fingerDisplayer->setMinimumSize(250,20);
    setBackgroundsColor("#ccffff");
    setTextSize(20);
    connect(testDisplayer.get(), &Editor::mistakesChanged, ui->lcdMistakesCounter, static_cast<void (QLCDNumber::*)(int)>(&QLCDNumber::display));
    connect(testDisplayer.get(), &Editor::progressChanged, ui->progressBar, &QProgressBar::setValue);
    connect(testDisplayer.get(), &Editor::testEnded, this, &MainWindow::showScore);
    connect(testDisplayer.get(), &Editor::resetTest, this, &MainWindow::startTest);
    connect(scoreDisplayer.get(), &ScoreDisplayer::resetTest, this, &MainWindow::startTest);
    connect(scoreDisplayer.get(), &ScoreDisplayer::showScoreTable, this, &MainWindow::showScoreTable);
    connect(testDisplayer.get(), &Editor::fingerChanged, ui->fingerDisplayer,&QLabel::setText);
    showStartMenu();
}

MainWindow::~MainWindow()
{
}

void MainWindow::openFile()
{
    QFileInfo fileInfo;
    fileName = QFileDialog::getOpenFileName(this, "Open a file", fileInfo.absolutePath());
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly |QIODevice::Text))
    {
        QMessageBox::information(this, "Unable to open file.", "Return to menu.");
        showStartMenu();
        return;
    }
    textToDisplay.clear();
    if(file.size() <= kMaxFileSize && file.size() >= 10)
    {
        textToDisplay += file.readAll();
    }
    else
    {
        QMessageBox::information(this, "Wrong size of the file", "Return to menu.");
        showStartMenu();
    }
    file.close();
}

void MainWindow::showScore(double time, double percentageMistakes, double percentageAbsoluteMistakes, double correctness)
{
    scoreDisplayer->clear();
    displayInformation("<p style=\"text-align: center\">Time: " + QString::number(time/1000) + "s<br>Mistakes: " + QString::number(percentageMistakes)
                       + "%<br>Absolute mistakes: "+ QString::number(percentageAbsoluteMistakes)
                       + "%<br>The correctness: " + QString::number(correctness) + "%</p>");
    saveScoreIfBetter(fileName, time, percentageMistakes, percentageAbsoluteMistakes, correctness);
    displayBestScore(fileName);
    displayInformation("<p style=\"text-align:center\">Press R to Start, S to show scoreboard or Esc to quit</p>");
}
void MainWindow::displayInformation(QString htmlText)
{
    scoreDisplayer->append(htmlText);
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::showStartMenu()
{
    stackedWidget->setCurrentIndex(1);
    scoreDisplayer->clear();
    displayInformation("<p style=\"text-align:center\">Press R to Start, S to show scoreboard or Esc to quit</p>");
}

void MainWindow::showScoreTable()
{
    stackedWidget->setCurrentIndex(1);
    scoreDisplayer->clear();
    QFile file("scores.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(this, "Unable to open score file.", "Return to menu.");
        showStartMenu();
        return;
    }
    QStringList scoresList = QString(file.readAll()).split("\n");
    scoresList.removeFirst();
    int numberOfScores = scoresList.size()/5;
    for(int i = 0; i < numberOfScores * 5; i += 5)
    {
        displayInformation("<p style=\"font-weight: bold; text-align: center\">" +scoresList[i] + "</p>"
                           + "<p style=\"text-align: center\">Time: " + QString::number(scoresList[i+ 1].toDouble()/1000)
                + "s<br>Mistakes: " + scoresList[i + 2]
                + "%<br>Absolute mistakes: "+ scoresList[i + 3]
                + "%<br>The correctness: " + scoresList[i + 4] + "%</p>");
    }
    displayInformation("<p style=\"text-align:center\">Press R to Start, S to show scoreboard or Esc to quit</p>");
    file.close();

}

void MainWindow::setBackgroundsColor(QColor color)
{
    QPalette palette = testDisplayer->palette();
    palette.setColor(QPalette::Base, color);
    testDisplayer->setPalette(palette);
    palette = scoreDisplayer->palette();
    palette.setColor(QPalette::Base, color);
    scoreDisplayer->setPalette(palette);
}

void MainWindow::setTextSize(const unsigned int size)
{
   setStyleSheet("QTextEdit{font-size:" + QString::number(size) + "px;}");
}

void MainWindow::saveScoreIfBetter(QString name, double time, double percentageMistakes, double percentageAbsoluteMistakes, double correctness)
{
    name = name.right(name.size() - name.lastIndexOf("/") - 1);//get name of file
    QFile file("scores.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::WriteOnly |QIODevice::Text))
    {
        QMessageBox::information(this, "Unable to open score file.", "Return to menu.");
        showStartMenu();
        return;
    }
    QStringList scoresList = QString(file.readAll()).split("\n");
    int position = scoresList.indexOf(name);
    if(position != -1)
    {
        if(scoresList[position+4].toDouble() <= correctness && scoresList[position+1].toDouble() > time)
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
        QMessageBox::information(this, "Unable to open score file.", "Return to menu.");
        showStartMenu();
        return;
    }
    QStringList scoresList = QString(file.readAll()).split("\n");
    int position = scoresList.indexOf(name);
    if(position != -1)
    {
        displayInformation("<p style=\"font-weight: bold; text-align: center\">Best score:</p>"
                           "<p style=\"text-align: center\">Time: " + QString::number(scoresList[position + 1].toDouble()/1000)
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
    testDisplayer->updateFinger();
}

