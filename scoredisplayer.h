#ifndef SCOREDISPLAYER_H
#define SCOREDISPLAYER_H
#include <QTextBrowser>
#include <QObject>
#include <QKeyEvent>

class ScoreDisplayer : public QTextBrowser
{
    Q_OBJECT
public:
    explicit ScoreDisplayer(QWidget *parent = nullptr);
private:
    void keyPressEvent(QKeyEvent *event);
signals:
    void resetTest();

public slots:
};

#endif // SCOREDISPLAYER_H
