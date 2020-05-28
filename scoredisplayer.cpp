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
        emit resetTest();
    break;
    }

    }
}
