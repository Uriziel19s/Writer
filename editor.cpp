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
    textToDisplay.replace("\n","<br>");
    QTextCursor cursor = this->textCursor();

        insertHtml("<span style=\"color:black\">" + textToDisplay + "</span>");

    cursor.setPosition(QTextCursor::Start);
    cursor.movePosition(QTextCursor::MoveOperation::PreviousCharacter);
    this->setTextCursor(cursor);
    this->update();
    qDebug() << this->toHtml();
}

QString Editor::nextChar()
{
    QTextCursor cursor = this->textCursor();
    cursor.insertText(" ");
    int lastCursorPosition = cursor.position();
    cursor.select(QTextCursor::SelectionType::WordUnderCursor);
    qDebug() << lastCursorPosition << " " << cursor.position();
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



void Editor::keyPressEvent(QKeyEvent *event)
{
    QTextCursor cursor = this->textCursor();
    switch(event->key())
    {
    case Qt::Key_Backspace:
    {
        qDebug() << cursorPosition << " " << cursor.position();
        if(!cursor.atStart())
        {
            cursorPosition--;
            cursor.deletePreviousChar();
            if(textToDisplay[cursorPosition] == " ")
            {
                insertHtml("<span style=\"color:blue\">&nbsp;</span>");
            }
            else if(textToDisplay[cursorPosition] == "\n")
            {
                insertHtml("<br>");
            }
            else
            {
                cursor.insertHtml("<span style=\"color:black\">" + textToDisplay[cursorPosition] + "</span>");
            }
            cursor.movePosition(QTextCursor::MoveOperation::PreviousCharacter);
        }
        break;
    }
    case Qt::Key_Escape:
    {
        QPixmap pixmap;
        qDebug() << pixmap.size();
        pixmap = this->grab(QRect(QPoint(-1,-1), QSize(this->width()-50, this->height()-50)));
        qDebug() << pixmap.size();
        QPalette pallete = this->palette();
        pallete.setBrush(QPalette::Base,QBrush(pixmap));
        this->setPalette(pallete);
        qDebug() << "asdfasf ";
        this->update();
        break;
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
            insertHtml("<span style=\"color:blue\">&nbsp;</span>");
            mistakesLog.append(false);
        }
        else if(event->text() != textToDisplay[cursorPosition] && textToDisplay[cursorPosition] == " ")
        {
            insertHtml("<span style=\"color:red\">&nbsp;</span>");
            mistakesLog.append(true);
        }
        else if(event->text() == textToDisplay[cursorPosition])
        {
            insertHtml("<span style=\"color:blue\">" + textToDisplay[cursorPosition] + "</span>");
            mistakesLog.append(false);
        }
        else if(textToDisplay[cursorPosition] == "\n" && event->key() == Qt::Key_Enter)
        {
            insertHtml("<br>");
        }
        else if(textToDisplay[cursorPosition] == "\n" && event->key() != Qt::Key_Enter)
        {
            insertHtml("<br>");//ENTER BUT IN RED
        }
        else
        {
            insertHtml("<span style=\"color:red\">" + textToDisplay[cursorPosition] + "</span>");
            mistakes++;
            mistakesLog.append(true);
        }
        cursorPosition++;
        break;
    }
    }
    emit progressChanged(float(cursorPosition)/float(sizeOfText)*100);
    this->setTextCursor(cursor);
    this->update();
}




