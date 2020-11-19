#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
<<<<<<< HEAD
    testDisplayer = std::make_unique<Editor>(this);
    scoreDisplayer = std::make_unique<ScoreDisplayer>(this);
    stackedWidget = std::make_unique<QStackedWidget>(this);
    stackedWidget->addWidget(testDisplayer.get());
    stackedWidget->addWidget(scoreDisplayer.get());
    ui->setupUi(this);
    setCentralWidget(stackedWidget.get());
=======
    testDisplayer = new Editor(this);
    scoreDisplayer = new ScoreDisplayer(this);
    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(testDisplayer);
    stackedWidget->addWidget(scoreDisplayer);
    ui->setupUi(this);
    setCentralWidget(stackedWidget);
>>>>>>> 2b2702bb354cd6160fd74fe4c3cc689edf5a7168
    ui->statusbar->addWidget(ui->fingerDisplayer);
    ui->statusbar->addPermanentWidget(ui->progressBar);
    ui->statusbar->addPermanentWidget(ui->lcdMistakesCounter);
    ui->lcdMistakesCounter->setMode(QLCDNumber::Dec);
    ui->progressBar->setValue(0);
    ui->fingerDisplayer->setText("");
    ui->fingerDisplayer->setMaximumSize(250,20);
    ui->fingerDisplayer->setMinimumSize(250,20);
<<<<<<< HEAD
    setBackgroundsColor("#ccffff");
    setTextSize(20);
    connect(testDisplayer.get(), &Editor::mistakesChanged, ui->lcdMistakesCounter, static_cast<void (QLCDNumber::*)(int)>(&QLCDNumber::display));
    connect(testDisplayer.get(), &Editor::progressChanged, ui->progressBar, &QProgressBar::setValue);
    connect(testDisplayer.get(), &Editor::testEnded, this, &MainWindow::showScore);
    connect(testDisplayer.get(), &Editor::resetTest, this, &MainWindow::startTest);
    connect(scoreDisplayer.get(), &ScoreDisplayer::resetTest, this, &MainWindow::startTest);
    connect(scoreDisplayer.get(), &ScoreDisplayer::showScoreTable, this, &MainWindow::showScoreTable);
    connect(testDisplayer.get(), &Editor::fingerChanged, ui->fingerDisplayer,&QLabel::setText);
=======
    connect(testDisplayer, &Editor::mistakesChanged, ui->lcdMistakesCounter, static_cast<void (QLCDNumber::*)(int)>(&QLCDNumber::display));
    connect(testDisplayer, &Editor::progressChanged, ui->progressBar, &QProgressBar::setValue);
    connect(testDisplayer, &Editor::testEnded, this, &MainWindow::showScore);
    connect(testDisplayer, &Editor::resetTest, this, &MainWindow::startTest);
    connect(scoreDisplayer, &ScoreDisplayer::resetTest, this, &MainWindow::startTest);
    connect(scoreDisplayer, &ScoreDisplayer::showScoreTable, this, &MainWindow::showScoreTable);
    connect(testDisplayer, &Editor::fingerChanged, ui->fingerDisplayer,&QLabel::setText);
>>>>>>> 2b2702bb354cd6160fd74fe4c3cc689edf5a7168
    showStartMenu();
}

MainWindow::~MainWindow()
{
<<<<<<< HEAD
=======
    delete testDisplayer;
    delete scoreDisplayer;
    delete stackedWidget;
    delete ui;
>>>>>>> 2b2702bb354cd6160fd74fe4c3cc689edf5a7168
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
<<<<<<< HEAD
    if(file.size() <= kMaxFileSize && file.size() >= 10)
=======
    if(file.size() <= 1000000 and file.size() >= 10)//hardcoded, must be changed in the future
>>>>>>> 2b2702bb354cd6160fd74fe4c3cc689edf5a7168
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

<<<<<<< HEAD
void MainWindow::showScore(double time, double percentageMistakes, double percentageAbsoluteMistakes, double correctness)
=======
void MainWindow::showScore(float time, float percentageMistakes, float percentageAbsoluteMistakes, float correctness)
>>>>>>> 2b2702bb354cd6160fd74fe4c3cc689edf5a7168
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
<<<<<<< HEAD
                           + "<p style=\"text-align: center\">Time: " + QString::number(scoresList[i+ 1].toDouble()/1000)
=======
                           + "<p style=\"text-align: center\">Time: " + QString::number(scoresList[i+ 1].toFloat()/1000)
>>>>>>> 2b2702bb354cd6160fd74fe4c3cc689edf5a7168
                + "s<br>Mistakes: " + scoresList[i + 2]
                + "%<br>Absolute mistakes: "+ scoresList[i + 3]
                + "%<br>The correctness: " + scoresList[i + 4] + "%</p>");
    }
    displayInformation("<p style=\"text-align:center\">Press R to Start, S to show scoreboard or Esc to quit</p>");
    file.close();

}

<<<<<<< HEAD
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
=======
void MainWindow::saveScoreIfBetter(QString name, float time, float percentageMistakes, float percentageAbsoluteMistakes, float correctness)
>>>>>>> 2b2702bb354cd6160fd74fe4c3cc689edf5a7168
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
<<<<<<< HEAD
        if(scoresList[position+4].toDouble() <= correctness && scoresList[position+1].toDouble() > time)
=======
        if(scoresList[position+4].toFloat() < correctness || (scoresList[position+4].toFloat() == correctness && scoresList[position+1].toFloat() > time))
>>>>>>> 2b2702bb354cd6160fd74fe4c3cc689edf5a7168
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
<<<<<<< HEAD
                           "<p style=\"text-align: center\">Time: " + QString::number(scoresList[position + 1].toDouble()/1000)
=======
                           "<p style=\"text-align: center\">Time: " + QString::number(scoresList[position + 1].toFloat()/1000)
>>>>>>> 2b2702bb354cd6160fd74fe4c3cc689edf5a7168
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

