#include <iostream>
#include <QApplication>
#include <QPicture>
#include "editor.h"
#include "mainwindow.h"

using namespace std;

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainWindow window;

    window.show();
    app.exec();
    return 0;
}
