#ifndef ALBUM_H
#define ALBUM_H

#include <QtCore>
#include <QObject>

class Album : public QObject
{
    Q_OBJECT

public:
    Album(QObject *parent = 0);
    Album(QString string, QObject* parent = 0);

    bool isEmpty();

    int position() const;
    int score()    const;

    QString artist() const;
    QString album()  const;

    void setPosition(int);
    void setScore(int);
    void addScore(int);

private:
    int m_position;
    int m_score;
    QString m_artist;
    QString m_album;

signals:

public slots:
};

#endif // ALBUM_H
