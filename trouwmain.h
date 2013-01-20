#ifndef TROUWMAIN_H
#define TROUWMAIN_H

#include <QMainWindow>
#include <QtNetwork/QHttpResponseHeader>
#include <QtXml/QXmlStreamReader>
#include <QtNetwork/QNetworkReply>
#include <QRadioButton>
#include <QPrinter>
#include <QPainter>
#include <QFileInfo>
namespace Ui {
class TrouwMain;
}

class TrouwMain : public QMainWindow
{
    Q_OBJECT
    
public slots:
    void onNetworkReply(QNetworkReply* reply);
    void parseXml(QString xmlet);
    void proccesTrouw(QString id);
    void LijstDoorlopen();
    bool packFiles( QString zip_name, QFileInfoList files );
    void zipFiles();
    void delay();


public:
    explicit TrouwMain(QWidget *parent = 0);
    ~TrouwMain();
    QList<QRadioButton*> check;
    QList<QString> ids;
    int second;
    int parsing;
    int count;
    int total;
    QByteArray bytes;
    QList<QByteArray> bytes_list;
    QList<QString> names;
    QList<QFileInfo> test;
    QList<QString> urls;
    QString line;
    static bool removeDir(const QString &dirName);
    QPrinter printer;
    QPainter painter;




private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();



private:
    Ui::TrouwMain *ui;


};

#endif // TROUWMAIN_H
