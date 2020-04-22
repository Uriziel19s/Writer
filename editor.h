#ifndef EDITOR_H
#define EDITOR_H
#include <QTextEdit>
#include <QKeyEvent>
#include <QDebug>
#include <QVector>

class Editor : public QTextEdit
{
public:
    Editor(QWidget *parent = 0);
    ~Editor();
    void setText(QString text);
private:
    QTextCursor *cursor;
    void keyPressEvent(QKeyEvent *event);
    QString nextChar();
    QString previousChar();
    unsigned int mistakes;
    QVector<bool> mistakesLog;
};

#endif // EDITOR_H
