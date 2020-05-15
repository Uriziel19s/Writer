#ifndef EDITOR_H
#define EDITOR_H
#include <QTextEdit>
#include <QKeyEvent>
#include <QDebug>
#include <QVector>

class Editor : public QTextEdit
{
    Q_OBJECT
public:
    Editor(QWidget *parent = 0);
    ~Editor();
    void setText(QString text);
private:
    QString textToDisplay;
    unsigned int cursorPosition = 0;
    QTextCursor *cursor;
    void keyPressEvent(QKeyEvent *event);
    QString nextChar();
    QString previousChar();
    unsigned int mistakes = 0;
    QVector<bool> mistakesLog;
    unsigned int sizeOfText;
    template<class T> void insertTextInColor(T textToinsert, QString color);//T class must be casteble to QString

signals:
    int progressChanged(int value);
    void mistakesChanged(int value);
};

#endif // EDITOR_H
