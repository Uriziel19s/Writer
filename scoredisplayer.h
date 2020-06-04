#ifndef SCOREDISPLAYER_H
#define SCOREDISPLAYER_H
#include <QTextBrowser>
#include <QObject>
#include <QKeyEvent>
#include <QApplication>

class ScoreDisplayer : public QTextBrowser
{
    Q_OBJECT
public:
    explicit ScoreDisplayer(QWidget *parent = nullptr);
private:
    void keyPressEvent(QKeyEvent *event);
signals:
    void resetTest();
    void showScoreTable();

public slots:
};

#endif // SCOREDISPLAYER_H
