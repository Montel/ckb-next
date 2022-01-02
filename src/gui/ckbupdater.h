#ifndef CKBUPDATER_H
#define CKBUPDATER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class CkbUpdater : public QObject
{
    Q_OBJECT
public:
    explicit CkbUpdater(QObject *parent = nullptr);
    void checkForNewVersion();

private:
    QNetworkAccessManager* _accessManager;
    QString getVersionString(QByteArray* bytes);
    QString _latestVerStr;
    QString parseChangeLog(QByteArray* bytes);

Q_SIGNALS:
    void checkedForNewVer(const QString &ver, const QString &changelog);

private Q_SLOTS:
    void finished(QNetworkReply* reply);
};

#endif // CKBUPDATER_H
