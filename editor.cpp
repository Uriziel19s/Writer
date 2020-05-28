#include "editor.h"


Editor::Editor(QWidget *parent) : QTextEdit(parent)
{
    setTextInteractionFlags(Qt::TextInteractionFlag::NoTextInteraction | Qt::TextInteractionFlag::TextSelectableByKeyboard);
    this->setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);

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
    insertHtml("<span style=\"color:black\">" + textToDisplay + "</span>");
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

QString Editor::nextChar()
{
    QTextCursor cursor = this->textCursor();
    cursor.insertText(" ");
    int lastCursorPosition = cursor.position();
    cursor.select(QTextCursor::SelectionType::WordUnderCursor);
    QString nextChar = cursor.selectedText().left(1);
    cursor.clearSelection();
    cursor.setPosition(lastCursorPosition);
    cursor.deletePreviousChar();
    return nextChar;
}

QString Editor::previousChar()
{
    QTextCursor cursor = this->textCursor();
    cursor.movePosition(QTextCursor::MoveOperation::PreviousCharacter);
   this->setTextCursor(cursor);
    QString previousChar = this->nextChar();
    cursor.movePosition(QTextCursor::MoveOperation::NextCharacter);
    return previousChar;
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
}


void Editor::keyPressEvent(QKeyEvent *event)
{
    qDebug() << toHtml() << "\n";
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
        return;
    }
    emit progressChanged(float(cursorPosition + 1)/float(sizeOfText)*100);
    emit mistakesChanged(mistakes);
    this->setTextCursor(cursor);
    this->update();
}




