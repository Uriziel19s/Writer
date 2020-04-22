#ifndef EDITOR_H
#define EDITOR_H
#include <QTextEdit>
#include <QKeyEvent>
#include <QDebug>

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
};

#endif // EDITOR_H
