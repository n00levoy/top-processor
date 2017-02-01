#ifndef TOPMODEL_H
#define TOPMODEL_H

#include <QAbstractListModel>

#include "album.h"

class TopModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum TopRoles {
        PositionRole = Qt::UserRole + 1,
        ArtistRole,
        AlbumRole,
        ScoreRole
    };

    TopModel(QObject* parent = 0);

    Q_INVOKABLE int      rowCount(const QModelIndex &parent = QModelIndex())        const;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void addAlbumsFromTextArea(QVariant text);
    Q_INVOKABLE void saveResults(QVariant filename);

    Q_INVOKABLE void searchOverlapsByArtist(QMap<QString, QString> rejectedOverlaps = QMap<QString, QString>());

    void addAlbum(Album* album);

private:
    void refresh();

    QList<Album*> m_list;

};

#endif // TOPMODEL_H
