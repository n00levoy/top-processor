#include "album.h"

Album::Album(QObject *parent) : QObject(parent)
{
    m_position = 0;
    m_score    = 0;

    m_artist = QString();
    m_album  = QString();
}

Album::Album(QString string, QObject* parent) : QObject(parent)
{
    if(!string.contains(QRegExp("[0-9]{1,2}\\. .{1,} - .{1,}")))
    {
        m_position = 0;
        m_score    = 0;

        m_artist = QString();
        m_album  = QString();

        return;
    }

    QStringList parts = string.split(QRegExp("[0-9]{1,2}\\. "));

    m_position = 0;
    QString number = string.left(2);
    QTextStream stream(&number);
    int readNumber;
    stream >> readNumber;
    m_score = 21 - readNumber;

    QStringList albumParts = parts.at(1).split(QRegExp(" - "));
    m_artist = albumParts.at(0);
    m_album  = albumParts.at(1);
}

int Album::position() const
{
    return m_position;
}

int Album::score() const
{
    return m_score;
}

void Album::setPosition(int position)
{
    m_position = position;
}

void Album::setScore(int score)
{
    m_score = score;
}

void Album::addScore(int score)
{
    m_score += score;
}

QString Album::artist() const
{
    return m_artist;
}

QString Album::album() const
{
    return m_album;
}

bool Album::isEmpty()
{
    if(this->position() == 0 &&
       this->score()    == 0 &&
       this->album()    == QString() &&
       this->artist()   == QString())
        return true;
    else
        return false;
}
