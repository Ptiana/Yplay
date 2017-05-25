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
	//设置用户ID和Key
	bool setUser(QString appId, QString key);
	//获取签名
	QString getSign(QString text);
	//将待翻译转换文本进行UrlEncode转换
	QString strToUrlEncode(QString text);
	//文本翻译
	QString textTranslate(QString text, QString from, QString to);
	//获取链接
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
