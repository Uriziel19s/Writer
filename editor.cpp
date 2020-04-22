#include "editor.h"


Editor::Editor(QWidget *parent) : QTextEdit(parent)
{
    mistakes = 0;
    setTextInteractionFlags(Qt::TextInteractionFlag::NoTextInteraction | Qt::TextInteractionFlag::TextSelectableByKeyboard);
    this->setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);
};

Editor::~Editor()
{

}
void Editor::setText(QString textToDisplay)
{
    this->clear();
    QTextCursor cursor = this->textCursor();
    for(int i = 0; i < textToDisplay.size(); i++)
    {
        insertHtml("<span style=\"color:black\">" + textToDisplay[i] + "</span>");
    }
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



void Editor::keyPressEvent(QKeyEvent *event)
{
    QTextCursor cursor = this->textCursor();
    switch(event->key())
    {
    case Qt::Key_Backspace:
    {
        if(!cursor.atStart())
        {
        QString previousChar = this->previousChar();
        qDebug() << previousChar;
        cursor.deletePreviousChar();
        cursor.insertHtml("<span style=\"color:black\">" + previousChar + "</span>");
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
    default:
    {
        QString nextChar = this->nextChar();
        cursor.deleteChar();
        if(event->text() == nextChar)
        {
            insertHtml("<span style=\"color:blue\">" + nextChar + "</span>");
            mistakesLog.append(0);
        }
        else
        {
            insertHtml("<span style=\"color:red\">" + nextChar + "</span>");
            mistakes++;
            mistakesLog.append(1);
        }
        break;
    }
    }
    this->setTextCursor(cursor);
    this->update();
}




