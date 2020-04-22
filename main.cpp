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
    //Editor *editor = new Editor;
    //window.setCentralWidget(editor);
    //editor->setText("aafdaffafsfasdf");
            qDebug() << "asdfasf";
//    QPixmap pixmap;
//    editor->render(&pixmap,QPoint(),editor->rect());
//    pixmap.scaled(editor->size(), Qt::IgnoreAspectRatio);
//    QPalette palette;
//    palette.setBrush(QPalette::Background, pixmap);
//    editor->setPalette(palette);
    //editor->show();
    window.show();
            qDebug() << "asdfasf";
    return app.exec();
}
