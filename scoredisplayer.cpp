#include "scoredisplayer.h"

ScoreDisplayer::ScoreDisplayer(QWidget *parent) : QTextBrowser(parent)
{

}


void ScoreDisplayer::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Escape:
    {
        QApplication::exit();
        break;
    }
    case Qt::Key_R:
    {
        emit resetTest();
        break;
    }
    case Qt::Key_S:
    {
        emit showScoreTable();
        break;
    }
    }
}
