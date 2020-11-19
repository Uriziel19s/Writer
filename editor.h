#ifndef EDITOR_H
#define EDITOR_H
#include <QTextEdit>
#include <QKeyEvent>
#include <QDebug>
#include <QVector>
#include <QElapsedTimer>

class Editor : public QTextEdit
{
    Q_OBJECT

public:
<<<<<<< HEAD
    Editor(QWidget *parent = nullptr);
=======
    Editor(QWidget *parent = 0);
>>>>>>> 2b2702bb354cd6160fd74fe4c3cc689edf5a7168
    ~Editor();
    void setText(QString text);
    void reset();
    void updateFinger();

private:
    void isTestEnded();
    void keyPressEvent(QKeyEvent *event);
    template<class T> void insertTextInColor(T textToinsert, QString color);//T class must be casteble to QString
    QTextCursor *cursor;
    QVector<bool> mistakesLog;
    QElapsedTimer timer;
    QString textToDisplay;
    QStringList tableOfFingers;
    QStringList tableOfShiftFingers;
    QStringList namesOfFingers;
    unsigned int cursorPosition = 0;
<<<<<<< HEAD
    int sizeOfText;
=======
    unsigned int sizeOfText;
>>>>>>> 2b2702bb354cd6160fd74fe4c3cc689edf5a7168
    unsigned int mistakes = 0;

signals:
    int progressChanged(int value);
    void mistakesChanged(int value);
    void testEnded(float time, float percentageMistakes, float percentageAbsoluteMistakes, float correctness);
    void resetTest();
    void fingerChanged(QString textToDisplay);
};

#endif // EDITOR_H
