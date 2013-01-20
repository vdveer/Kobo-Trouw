#include "trouwmain.h"
#include "ui_trouwmain.h"
#include <QTemporaryFile>
#include <QtNetwork/QNetworkAccessManager>
#include <QtXml/QXmlStreamReader>
#include <QUrl>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QMessageBox>
#include <QRadioButton>
#include <QtXml/QXmlStreamAttributes>
#include <QtXml/QDomDocument>
#include <QBuffer>
#include <QTextStream>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileInfoList>
#include <QPrinter>
#include <QPainter>
#include <QImage>
#include <QListIterator>
#include <QProcess>
#include <QSize>
#include "quazip/quazip.h"
#include "quazip/quazipfile.h"
#include <QDebug>

TrouwMain::TrouwMain(QWidget *parent) : QMainWindow(parent),

ui(new Ui::TrouwMain)
{
    second = 0;
    parsing = 0;
    count = 0;
    total = 0;

    QNetworkAccessManager* mNetworkManager = new QNetworkAccessManager(this);
    QObject::connect(mNetworkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onNetworkReply(QNetworkReply*)));

    QUrl url("http://ipapercache.persgroep.net/home/8004/ANDROID_home.xml");
    QNetworkReply* reply = mNetworkManager->get(QNetworkRequest(url));

    ui->setupUi(this);



    //zipFiles();

    showFullScreen();
    QApplication::setFont(QFont("DejaVu Sans", 24));

    QFont font = ui->label->font();
    font.setPointSize(45);
    font.setBold(true);

    ui->label->setFont(font);

    QFont font1 = ui->label->font();
    font1.setPointSize(30);
    font1.setBold(true);
    ui->pushButton->setFont(font1);
    ui->pushButton_2->setFont(font1);

    QFile myFile("settings.ini"); // Create a file handle for the file named



    if (!myFile.open(QIODevice::ReadOnly)) // Open the file
    {
        ui->lineEdit->setText("Username and Password not found!");
    }

    QTextStream stream( &myFile ); // Set the stream to read from myFile
stream.readLine();
        line = stream.readLine();

        qDebug() << line;
    //exit(1);
    removeDir(line.split(";").at(2));
    QDir dir(QFileInfo(line.split(";").at(2)).absoluteDir());
    dir.mkdir(QFileInfo(line.split(";").at(2)).baseName());
    QFile(line.split(";").at(3)).remove();



}

void TrouwMain::on_pushButton_clicked()
{

        int i = 0;
        foreach( QRadioButton * item, check )
        {
            i++;
            if(item->isChecked() == true)
            {

                proccesTrouw(ids[i-1]);
            }

        }
}

void TrouwMain::onNetworkReply(QNetworkReply* reply)
{
    QString replyString;

    if(reply->error() == QNetworkReply::NoError)
    {
        int httpstatuscode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();
        //ui->label_2->setText(blaat.append(QString("%1").arg(httpstatuscode)));




        switch(httpstatuscode)
        {
            case 200: //goede http code
            if (reply->isReadable())
            {
                if(second == 3)
                {
                    count++;
                    ui->lineEdit->setText(QString::number(count));
                    ui->progressBar->setValue(double(count) / total * 100);
                    delay();
                    QFileInfo fileInf(reply->url().toString());
                    //QUrl blaat(reply->attribute(QNetworkRequest::Url));
                    names << fileInf.fileName();
                    //ui->lineEdit->setText(fileInf.fileName());

                   // ui->lineEdit->setText("second 3 aangeroepen");
                   // QString aString=QString::number(total);
                   // ui->lineEdit->setText(aString);
                    bytes = reply->readAll();
                    bytes_list << bytes;
                    QFile imageFile( line.split(";").at(2) + "/" + fileInf.fileName());

                    imageFile.open(QIODevice::WriteOnly);

                    // Saving ByteArray on File

                    QImage image;

                    image =  QImage::fromData(bytes,"JPG");


                        QDir myDir(line.split(";").at(2));
                       int test = myDir.count()-2;
                      if(total == count )
                      {
                          qDebug() << total;
                          qDebug() << count;
                          ui->lineEdit->setText("Please wait...");
                          if(total == test)
                          {
                          ui->progressBar->setValue(100);
                            ui->lineEdit->setText("Aan het zippen");
                           zipFiles();
                            }

                      }



                    imageFile.write(bytes);

                   imageFile.close();


                }
                else
                {

                    //Assuming this is a human readable file replyString now contains the file
                    replyString = QString::fromUtf8(reply->readAll().data());
                }
                if(second == 0)
                {
                    parseXml(replyString);

                }
                if(second == 1)
                {
                     QString urleel = replyString.replace("<redirect><url>", "").replace("</url></redirect>","").replace("&amp;","&").trimmed();

                     second = 2;

                     QNetworkAccessManager* mNetworkManager = new QNetworkAccessManager(this);
                     QObject::connect(mNetworkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onNetworkReply(QNetworkReply*)));

                     QUrl url(urleel);
                     QNetworkReply* reply = mNetworkManager->get(QNetworkRequest(url));

                }
                if(second == 2)
                {
                    parsing = 1;

                   // QFile file("/home/koen/out.txt");

                   // file.open(QIODevice::WriteOnly | QIODevice::Text);
                   // QTextStream out (&file);
                   // out << replyString;
                    //ui->label->setText(replyString);
                   // file.close();
                    parseXml(replyString);


                }


            }
            break;

            default:
                 QMessageBox::critical(this, "FOUT","Er ging iets mis", QMessageBox::Ok);
            return;
            break;
        }
    }

    reply->deleteLater();
}



void TrouwMain::parseXml(QString xmlet)
{
    QXmlStreamReader xmlReader(xmlet);

    QString blaat;

    //Parse the XML until we reach end of it
    while(!xmlReader.atEnd() && !xmlReader.hasError())
    {
        // Read next element
        QXmlStreamReader::TokenType token = xmlReader.readNext();
        //If token is just StartDocument - go to next
        if(token == QXmlStreamReader::StartDocument)
        {
                continue;
        }

        //If token is StartElement - read it
        if(token == QXmlStreamReader::StartElement)
        {
            if(parsing == 0)
            {
                if(xmlReader.name() == "paper")
                {

                    QXmlStreamAttributes attrib = xmlReader.attributes();

                    QString id = attrib.value("id").toString();

                    ids << id;

                }
                if(xmlReader.name() == "pubDate")
                {
                    blaat = xmlReader.readElementText();
                    QRadioButton *rd;
                    rd = new QRadioButton();
                    QFont font2 = ui->label->font();
                    font2.setPointSize(25);
                    font2.setBold(false);
                    rd->setText(blaat);
                    rd->setFont(font2);
                    rd->setIconSize(QSize(40,40));

                    ui->verticalLayout->addWidget(rd);
                    check << rd;

                }

            }
            if(parsing == 1)
            {
                if(xmlReader.name() == "id")
                {
                    ui->label->setText(xmlReader.readElementText());
                }

                if(xmlReader.name() == "fullHighresUrl")
                {

                    urls << xmlReader.readElementText();

                    second = 3;



                     //disconnect(mNetworkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onNetworkReply(QNetworkReply*)));
                    //return;
                }
            }
        }
    }
    if(xmlReader.atEnd() == true && parsing == 1 && xmlReader.hasError() == false)
    {
        ui->lineEdit->setText("");
        QMessageBox msgbox;
        msgbox.setText("Total pages: " + QString::number(urls.count()));
        msgbox.exec();
        LijstDoorlopen();
    }

    if(xmlReader.hasError())
    {
            ui->lineEdit->setText(xmlReader.errorString());
            return;
    }

    xmlReader.clear();
}


void TrouwMain::proccesTrouw(QString id)
{

    QString user = line.split(";").at(0);
    QString pass = line.split(";").at(1);


    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    QUrl url("http://ipaperservice.persgroep.be/ipaper-ws/ws/v2/8004/paper/" + id + "/NL?device=ANDROID&osVersion=4.0.4&appVersion=14&uaid=BiC6z6fPfjBX26kbhrGi1353942378789");
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrl params;
    params.addQueryItem("email", user);
    params.addQueryItem("password", pass);

    // etc
    second = 1;
    QObject::connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(onNetworkReply(QNetworkReply *)));

    manager->post(request, params.encodedQuery());

}

bool TrouwMain::removeDir(const QString &dirName)
{
    bool result = true;
    QDir dir(dirName);

    if (dir.exists(dirName)) {
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
            if (info.isDir()) {
                result = removeDir(info.absoluteFilePath());
            }
            else {
                result = QFile::remove(info.absoluteFilePath());
            }

            if (!result) {
                return result;
            }
        }
        result = dir.rmdir(dirName);
    }

    return result;
}
void TrouwMain::LijstDoorlopen()
{

    foreach( QString link, urls )
    {
        total++;

        QNetworkAccessManager* mNetworkManager = new QNetworkAccessManager(this);
        connect(mNetworkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onNetworkReply(QNetworkReply*)));

        QUrl url(link);
        QNetworkReply* reply = mNetworkManager->get(QNetworkRequest(url));


   // sleep(2);
    }
}

TrouwMain::~TrouwMain()
{
    delete ui;
}

void TrouwMain::on_pushButton_2_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Wait for nickel");
    msgBox.exec();
    QProcess *proc = new QProcess();
    proc->start(QApplication::applicationDirPath() + "/nickel_start.sh", QStringList());
     QApplication::quit();
}

bool TrouwMain::packFiles( QString zip_name, QFileInfoList files )
{
    QuaZip zip(zip_name);
    zip.setFileNameCodec("IBM866");
    if( !zip.open( QuaZip::mdCreate ) )
    {
    //return false;
    }

    QFile inFile;
    QuaZipFile outFile(&zip);

    char c;
    int j = 0;
    int blaat = 0;
    ui->progressBar->setValue(0);

    foreach(QFileInfo fileInfo, files)
    {
        blaat++;

        ui->progressBar->setValue(double(blaat) / total *100);
        delay();
        if (!fileInfo.isFile())
        continue;

        inFile.setFileName( fileInfo.absoluteFilePath() );

        if (!inFile.open(QIODevice::ReadOnly))
        {
        return false;
        }

        if (!outFile.open(QIODevice::WriteOnly, QuaZipNewInfo(fileInfo.fileName(), fileInfo.filePath())))
        {
        return false;
        }

        while (inFile.getChar(&c) )
        outFile.putChar(c);

        if (outFile.getZipError() != ZIP_OK)
        {
       return false;
        }

        outFile.close();

        if (outFile.getZipError() != ZIP_OK)
        {
        return false;
        }

        inFile.close();


    }

    zip.close();

    if (zip.getZipError() != 0)
    {
    return false;
    }


    return true;
}

void TrouwMain::zipFiles()
{
   // if(count == total)
   // {
    QDir myDir(line.split(";").at(2));
    QFileInfoList list = myDir.entryInfoList();
    foreach( QFileInfo los, list)
    {
     qDebug() << los.absoluteFilePath();
        test << los;

    }

    ui->label->setText("BEZIG MET ZIPPEN");
   // QApplication::quit();
    delay();

    packFiles(line.split(";").at(3),test);
    ui->label->setText(line.split(";").at(3)+" is klaar!");
    ui->lineEdit->setText("Het bestand is opgeslagen op de plek: " + line.split(";").at(3));
  //  return;
   // }
   // else
   // {
    delay();
    //}
}

void TrouwMain::delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

