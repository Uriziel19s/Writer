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
    qDebug() << textToDisplay;
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
    QTextCursor cursor = this->textCursor();
    qDebug() << cursorPosition << " " << cursor.position() << " " << textToDisplay[cursorPosition] << " " << toPlainText()[cursor.position()];
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
            insertTextInColor(" ", "blue");
            mistakesLog.append(false);
        }
        else if(event->text() != textToDisplay[cursorPosition] && textToDisplay[cursorPosition] == " ")
        {
            insertTextInColor(" ", "red");
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
        }
        else if(textToDisplay[cursorPosition] == "\n" && event->key() != Qt::Key_Enter)
        {
            insertTextInColor("\n", "red");//ENTER BUT IN RED
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
    emit progressChanged(float(cursorPosition)/float(sizeOfText)*100);
    emit mistakesChanged(mistakes);
    this->setTextCursor(cursor);
    this->update();
}




