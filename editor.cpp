#include "editor.h"


Editor::Editor(QWidget *parent) : QTextEdit(parent)
{
    setTextInteractionFlags(Qt::TextInteractionFlag::NoTextInteraction | Qt::TextInteractionFlag::TextSelectableByKeyboard);
    this->setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);
    tableOfFingers << "1qa`" << "2wsx" << "3edx" << "456rtfgcvb" << "7uyjhmn" << "89ik," << "0ol." << "-p;/=[]'\n" << " ";
    tableOfShiftFingers << "!QAZ~" << "@WSX" << "#EDC" << "$%^RTYFGVB" << "&YUJNM"<< "*IK<(" << ")OL>" << "_+P{}|:\"?" << "";
    namesOfFingers << "left little finger" << "left ring finger" << "left middle finger" << "left index" <<
                      "right index" << "right middle finger" << "right ring finger" << "right little finger" << "thumb";
};

Editor::~Editor()
{

}

void Editor::setText(QString textToDisplay)
{
    sizeOfText = textToDisplay.size();
    this->textToDisplay = textToDisplay;
    this->clear();
    textToDisplay.replace(" ", "&nbsp;");
    textToDisplay.replace("<", "&lt;");
    textToDisplay.replace(">", "&gt;");
    textToDisplay.replace("\n","<br>");
    QTextCursor cursor = this->textCursor();
    insertHtml("<span style=\"color:black; text-align: center\">" + textToDisplay + "</span>");
    setAlignment(Qt::AlignCenter);
    cursor.setPosition(0);
    this->setTextCursor(cursor);
    this->update();
}

void Editor::reset()
{
    textToDisplay.clear();
    cursorPosition = 0;
    mistakes = 0;
    mistakesLog.clear();
    sizeOfText = 0;
    timer.invalidate();
    clear();
    update();
}

void Editor::isTestEnded()
{
    if(cursorPosition == sizeOfText - 1)
    {
        int relativeMistakes = 0;
        for(bool i : mistakesLog)
        {
            if(i == true)
            {
                relativeMistakes++;
            }
        }
        emit testEnded(timer.elapsed(), float(mistakes)/sizeOfText*100, float(relativeMistakes)/sizeOfText*100, float(sizeOfText-relativeMistakes)/sizeOfText*100);
        emit fingerChanged(" ");
    }
}

template<class T>
void Editor::insertTextInColor(T textToinsert, QString color)
{
    QString stringToinsert = QString(textToinsert);
    stringToinsert.replace("<", "&lt;");
    stringToinsert.replace(">", "&gt;");
    stringToinsert.replace(" ", "&nbsp;");
    stringToinsert.replace("\n", "<br>");
    insertHtml("<span style=\"color:"+ color + "\">" + stringToinsert + "</span>");
    setAlignment(Qt::AlignCenter);
}


void Editor::keyPressEvent(QKeyEvent *event)
{
    if(!timer.isValid())
    {
        timer.start();
    }
    QTextCursor cursor = this->textCursor();//synchronization between edit cursor and my cursor
    switch(event->key())
    {
    case Qt::Key_Backspace:
    {
        if(!cursor.atStart())
        {
            cursorPosition--;
            cursor.deletePreviousChar();
            if(textToDisplay[cursorPosition] == " ")
            {
                insertTextInColor(" ", "black");
            }
            else if(textToDisplay[cursorPosition] == "\n")
            {
                insertTextInColor("\n", "");
            }
            else
            {
                insertTextInColor(QString(textToDisplay[cursorPosition]), "black");
            }
            cursor.movePosition(QTextCursor::MoveOperation::PreviousCharacter);
            mistakesLog.removeLast();
        }
        break;
    }
    case Qt::Key_Escape:
    {
        emit resetTest();
        return;
    }
    case Qt::Key_Shift:
    {
        break;
    }
    case Qt::Key_Control:
    {
        break;
    }
    case Qt::Key_Alt:
    {
        break;
    }
    case Qt::Key_AltGr:
    {
        break;
    }
    default:
    {
        cursor.deleteChar();
        if(event->text() == textToDisplay[cursorPosition] && textToDisplay[cursorPosition] == " ")
        {
            insertTextInColor(" ", "blue");
            mistakesLog.append(false);
        }
        else if(event->text() != textToDisplay[cursorPosition] && textToDisplay[cursorPosition] == " ")
        {
            insertTextInColor(" ", "red");
            mistakes++;
            mistakesLog.append(true);
        }
        else if(event->text() == textToDisplay[cursorPosition])
        {
            insertTextInColor(textToDisplay[cursorPosition], "blue");
            mistakesLog.append(false);
        }
        else if(textToDisplay[cursorPosition] == "\n" && event->key() == Qt::Key_Enter)
        {
            insertTextInColor("\n", "blue");
            mistakesLog.append(false);
        }
        else if(textToDisplay[cursorPosition] == "\n" && event->key() != Qt::Key_Enter)
        {
            insertTextInColor("\n", "red");//ENTER BUT IN RED
            mistakes++;
            mistakesLog.append(true);
        }
        else
        {
            insertTextInColor(textToDisplay[cursorPosition], "red");
            mistakes++;
            mistakesLog.append(true);
        }
        cursorPosition++;
        break;
    }
    }
    emit progressChanged(static_cast<int>(static_cast<float>(cursorPosition + 1) / sizeOfText * 100));
    emit mistakesChanged(static_cast<int>(mistakes));
    updateFinger();
    isTestEnded();
    this->setTextCursor(cursor);
    this->update();
}

void Editor::updateFinger()
{
    for(int i = 0; i < namesOfFingers.size(); ++i)
    {
        if(cursorPosition < sizeOfText)
        {
            if(tableOfFingers[i].indexOf(textToDisplay[cursorPosition]) > -1)
            {
                emit fingerChanged(namesOfFingers[i]);
                return;
            }
            else if(tableOfShiftFingers[i].indexOf(textToDisplay[cursorPosition]) > -1)
            {
                emit fingerChanged(namesOfFingers[i]);
                return;
            }
        }
    }
}






