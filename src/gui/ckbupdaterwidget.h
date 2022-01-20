#ifndef CKBUPDATERWIDGET_H
#define CKBUPDATERWIDGET_H

#include <QDialog>
#include <QWidget>
#include <QNetworkAccessManager>

namespace Ui {
class CkbUpdaterWidget;
}

class CkbUpdaterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CkbUpdaterDialog(const QString& ver,  const QString& changelog, QWidget *parent = nullptr);
    ~CkbUpdaterDialog();

private Q_SLOTS:
    void on_remindMeLaterButton_clicked();
    void on_updateButton_clicked();
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void downloadFinished(QNetworkReply* reply);

private:
    Ui::CkbUpdaterWidget *const ui;
    QString _version, _changelog;
    QNetworkAccessManager* _manager = nullptr;
    QNetworkReply* _reply = nullptr;
    int _redirectCount;
    QString _url;
};

#endif // CKBUPDATERWIDGET_H
