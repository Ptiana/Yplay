#ifndef _TRANSLATE_H_
#define _TRANSLATE_H_
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonDocument>
#include"QTime"
#include <QCryptographicHash>
#include <QtNetwork>
#include<QtNetwork/QAbstractNetworkCache>
#include<QDebug>
#include "QObject"
#include "iostream"

using namespace std;




class Translate : public QObject
{

	Q_OBJECT
public:
	Translate();
	~Translate();
	//�����û�ID��Key
	bool setUser(QString appId, QString key);
	//��ȡǩ��
	QString getSign(QString text);
	//��������ת���ı�����UrlEncodeת��
	QString strToUrlEncode(QString text);
	//�ı�����
	QString textTranslate(QString text, QString from, QString to);
	//��ȡ����
	QString getUrl(QString text, QString frome, QString to);
	QString getResult();

	QString jsonAnalysis(QNetworkReply *reply);
	

private:
	QString userAppId;
	QString userKey;
	int randomSalt;
	QNetworkAccessManager *manager;
	QString translateResult;
private slots:


};


#endif//_TRANSLATE_H_
