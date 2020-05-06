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
    connect(ui->centralwidget, &Editor::progressChanged, ui->progressBar, &QProgressBar::setValue );
}

MainWindow::~MainWindow()
{
    delete  ui->centralwidget;
    delete ui;
}

void MainWindow::openFile()
{
    QFileInfo fileInfo;
    QString fileName = QFileDialog::getOpenFileName(this, "Open a file", fileInfo.absolutePath());
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly |QIODevice::Text))
    {
        QMessageBox::information(this, "Unable to open file.", file.errorString());
        //maybe add exception
    }
    QDataStream input(&file);
    input.setVersion(QDataStream::Qt_4_5);
    textToDisplay.clear();
    if(file.size() <= 1000000)//hardcoded, must be changed in the future
    {
        textToDisplay += file.readAll();
    }
    qDebug() << textToDisplay;
    file.close();
}
