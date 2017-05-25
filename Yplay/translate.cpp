#include "translate.h"


Translate::Translate()
{
	manager = new QNetworkAccessManager(this);
	translateResult = "";
	userAppId = "";
	userKey = "";
	randomSalt = 0;
	
}

Translate::~Translate()
{
}

bool Translate::setUser(QString appId, QString key)
{
	bool ret=false;
	do {
		if (appId == NULL)
			break;
		if(key==NULL)
			break;
		userAppId = appId;
		userKey = key;
		ret = true;
	} while (false);
	return ret;
}

QString Translate::getSign(QString text)
{
	//生成随机数
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
	randomSalt= qrand();
	//拼接得到字符串
	// QString str1 = "2015063000000001apple143566028812345678";
	QString pendSign = userAppId + text + QString::number(randomSalt)+userKey;
	QByteArray byteSign = pendSign.toLatin1();
	QByteArray byteSignMd5 = QCryptographicHash::hash(byteSign, QCryptographicHash::Md5);
	QString finishSign = byteSignMd5.toHex();
	return finishSign;
} 

QString Translate::strToUrlEncode(QString text)
{
	QString output=NULL;
	text.toUtf8();
	do 
	{
		if (text.isEmpty())
		{
			break;
		}
		QTextCodec * codecGB2312 = QTextCodec::codecForName("UTF-8");
		QByteArray byteArrayGB2312 = codecGB2312->fromUnicode(text);
		QByteArray byteArrayPercentEncoded = byteArrayGB2312.toPercentEncoding();
		output = QString(byteArrayPercentEncoded);
	} while (false);

	return output;
}


QString Translate::getUrl(QString text, QString frome, QString to)
{
	QString sign = getSign(text);
	QString textP = strToUrlEncode(text);
	QString apiHttp = "http://api.fanyi.baidu.com/api/trans/vip/translate?";
	QString url = apiHttp + QString("q=%1&from=%2&to=%3&appid=%4&salt=%5&sign=%6").arg(textP, frome, to, userAppId,QString::number(randomSalt), sign);
	return url;
}


QString Translate::textTranslate(QString text, QString from, QString to)
{
	QString retResult = "";;
	QString url = getUrl(text, from, to);
	QEventLoop loop;
	QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(url)));
	//manager->get(QNetworkRequest(QUrl(url)));
	QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
	/*connect(manager, SIGNAL(finished(QNetworkReply*)),
		this, SLOT(replyFinished(QNetworkReply*)));*/
	loop.exec();
	retResult = jsonAnalysis(reply);
	return retResult;
}

QString Translate::getResult()
{
	return translateResult;
}





QString Translate::jsonAnalysis(QNetworkReply *reply)
{
	QByteArray all = reply->readAll();
	QString result="";
	QJsonObject backValue = QJsonDocument::fromJson(all).object();
	QJsonValue value = backValue.value("trans_result");
	if (value.isArray())
	{
		QJsonArray array = value.toArray();
		//qDebug()<< array.size() << array.at(0).toObject().value("dst").toString();
		result = array.at(0).toObject().value("dst").toString();
	}
	reply->deleteLater();
	return result;
}

