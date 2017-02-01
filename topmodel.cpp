#include "topmodel.h"

#include <QMessageBox>

bool albumMore(Album* alb1, Album* alb2);

TopModel::TopModel(QObject *parent) : QAbstractListModel(parent)
{
    m_list = QList<Album*>();
}

QHash<int, QByteArray> TopModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[PositionRole] = "position";
    roles[ArtistRole]   = "artist";
    roles[AlbumRole]    = "album";
    roles[ScoreRole]    = "score";

    return roles;
}

int TopModel::rowCount(const QModelIndex& index) const
{
    return m_list.count();
}

QVariant TopModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    QVariant nData;
    switch(role)
    {
        case PositionRole:
            nData = QVariant(m_list.at(index.row())->position());
            break;
        case ArtistRole:
            nData = QVariant(m_list.at(index.row())->artist());
            break;
        case AlbumRole:
            nData = QVariant(m_list.at(index.row())->album());
            break;
        case ScoreRole:
            nData = QVariant(m_list.at(index.row())->score());
            break;
        default:
            nData = QVariant();
            break;
    }

    return nData;
}

void TopModel::addAlbum(Album *album)
{
    foreach(Album* alb, m_list)
    {
        if(album->artist().toLower() == alb->artist().toLower() && album->album().toLower() == alb->album().toLower())
        {
            alb->addScore(album->score());
            refresh();
            return;
        }
    }

    beginInsertRows(QModelIndex(), m_list.size(), m_list.size());
    m_list.append(album);
    endInsertRows();

    refresh();
}

void TopModel::addAlbumsFromTextArea(QVariant text)
{
    QStringList albums = text.toString().split("\n");
    foreach (QString albumString, albums)
    {
        Album* album = new Album(albumString);
        if(!album->isEmpty())
            addAlbum(album);
    }
}

bool albumMore(Album *alb1, Album *alb2)
{
    if(alb1->score() > alb2->score())
        return true;
    else
        return false;
}

void TopModel::refresh()
{
    std::sort(m_list.begin(), m_list.end(), albumMore);

    int index = 1;
    foreach (Album *alb, m_list)
    {
        alb->setPosition(index);
        index++;
    }

    for(int i = 0; i < m_list.count(); i++)
        emit dataChanged(createIndex(i, 0), createIndex(i, 0));
}

void TopModel::saveResults(QVariant filename)
{
    QFile file(filename.toString().remove("file:///"));
    if(file.open(QIODevice::WriteOnly))
    {
        QString text;
        foreach (Album* album, m_list)
            text += QString::number(album->position()) + ". " +
                    album->artist() + " - " + album->album() + " - " +
                    QString::number(album->score()) + "\n";

        file.write(text.toStdString().c_str());

        file.close();
    }
}

void TopModel::searchOverlapsByArtist()
{
    int somethingChanged = 0;
    foreach (Album* album, m_list)
    {
        foreach (Album* insAlbum, m_list)
        {
            if(album->artist() == insAlbum->artist())
            {
                if(!(album->album() == insAlbum->album()))
                {
                    QMessageBox msgBox;
                    msgBox.setText(album->artist() + " - " + album->album() + " и " +
                                   insAlbum->artist() + " - " + insAlbum->album());
                    msgBox.setInformativeText("Слить эти альбомы?");
                    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                    msgBox.setDefaultButton(QMessageBox::Yes);
                    int res = msgBox.exec();

                    switch (res)
                    {
                        case QMessageBox::Yes:
                            album->addScore(insAlbum->score());
                            m_list.removeAt(m_list.indexOf(insAlbum));
                            delete insAlbum;
                            somethingChanged++;
                            break;

                        default:
                            break;
                    }
                }
            }
            if(somethingChanged)
            {
                refresh();
                break;
            }
        }
        if(somethingChanged)
            break;
    }

    if(somethingChanged)
        searchOverlapsByArtist();
}
