#include "fansubTranslate.h"

FansubTransalte::FansubTransalte()
{
	currentHandleIndex = 0;
	jumpFrameNum = 3;
	fansubText = "";
	tran = NULL;
	minFuseResult=Mat(800, 600, CV_32FC1, 1);
	end = false;
}

FansubTransalte::~FansubTransalte()
{
}

void FansubTransalte::run()
{
	tran = new Translate();
	tran->setUser("20161115000031816", "WHl5ZGViIWzYoJXMiC5_");
	//50����һ����Ƶ�Ƿ��Ѿ���
	while (!videoHandleCheck())
	{
		sleep(10);
	}
	while (!end)
	{
		if (progressBarVary)
		{
			resultFrame.clear();
			fansubFuseFrame.clear();
			readFrame.clear();
		}
		if (resultFrame.size() < 60)
		{
			//������Ļ
			fansubHandle(currentHandleIndex);
			continue;
		}
		waitKey(2);
	}
	
	system("pause");

 }



void FansubTransalte::fansubHandle(int starFrame)
{
	//��������Ļǰ�ĳ�ʼ��
	fansubText = "";
	newVideo.set(CV_CAP_PROP_POS_FRAMES, starFrame);
	//��Ļ׷��
	while (!FansubTrack());
	if (!end)
	{
		//��Ļ֡�ں�
		minValueFuse(fansubFuseFrame, minFuseResult);
		//��Ļ�иʶ��
		fansubCut();
		qDebug() << "11111";
		QString textTranslation = tran->textTranslate(fansubText, "en", "zh");
		loadTranslation(readFrame.size() - fansubFuseFrame.size() * 3 + 1, readFrame.size() - 1, textTranslation);
		writeToShareSpace(readFrame);
		qDebug() << textTranslation;
		currentHandleIndex += readFrame.size();
		/*vector<Mat>().swap(readFrame);
		vector<Mat>().swap(fansubFuseFrame);*/
		//readFrame.clear();
		//fansubFuseFrame.clear();
	}
	vector<Mat>().swap(readFrame);
	vector<Mat>().swap(fansubFuseFrame);
}

//��Ļ׷��
bool  FansubTransalte::FansubTrack()
{

	bool ret = false;
	Mat  src_frame;
	Mat  temp;
	bool hasFindFansub = false;
	bool fansubChange = false;
	//fansubFuseFrame.clear();
	vector<Mat>().swap(fansubFuseFrame);
	//1.��鵱ǰ��Ļ��ʼ��֡��λ��
	do {
		if (!getNextfarme(src_frame))
		{
			end = true;
			ret = true;
			return ret;
		}
		//��鵽��Ļ���֣��ѵ�ǰ��⵽����Ļ֡��ջ
		if (existFansub(src_frame.clone()))                   
		{
			fansubFuseFrame.push_back(src_frame.clone());
			hasFindFansub = true;
			cout << "\n��⵽��Ļ\n";
		}
		else
		{
			cout << "\nδ��⵽��Ļ\n";
		}
	} while (!hasFindFansub);

	//2.��鵱ǰ��Ļ������֡��λ��
	do {
		//�������������ĵ�4֡
		if (!getNextfarme(src_frame))
		{
			end = true;
			ret = true;
			return ret;
		}
		//������ƾͽ�ջȻ�������3֡������������֡
		if (similarCompare(fansubFuseFrame.back().clone(), src_frame.clone()))
		{
			fansubFuseFrame.push_back(src_frame.clone());
		}
		else
		{//�����ƣ����֮ǰ׷�ٵ�����ͬ��Ļ�ĸ����Ƿ�С����ֵTn
			if (fansubFuseFrame.size() < 5)  //��죬�˴ν����Ҫ���¼��
			{
				//qDebug() << "5678";
				//vector<Mat>().swap(fansubFuseFrame);
				break;
			}
			else                           //��⵽��Ļ����ֹͣ׷��
			{
				fansubChange = true;
			}
		}
	} while (!fansubChange);
	if (fansubChange == true)
		ret = true;
	return ret;
}


//��Ļ�и�
void FansubTransalte::fansubCut()
{
	Rect rect;
	Mat temp;                                //���洢ͼ�������ݵ���ʱ����
	Mat minFuseOTSU = minFuseResult.clone();
	cv::threshold(minFuseResult, minFuseOTSU, 170, 255, CV_THRESH_BINARY);
	//imshow("��Сֵ��򷨶�ֵ��", minFuseOTSU);
	vector<vector<int>>rowStaAndEnd;          //��ǰ�ںϴ���֡�����е���Ļ�Ŀ�ʼ�кͽ�����
	vector<int>singleFansubStaAndEnd;         //������Ļ�Ŀ�ʼ�кͽ�����
	vector<vector<int>>charStaAndEnd;         //ĳ����Ļ��������ÿ���ַ��Ŀ�ʼ�кͽ�����       

	 //���и�
	fansubRowCut(minFuseOTSU, rowStaAndEnd);
	//cout << rowStaAndEnd[0][0] << rowStaAndEnd[0][1];
	//��ÿ����Ļ�����������и�
	for (int i = 0; i < rowStaAndEnd.size(); i++)
	{
		//��ȡ���и�������
		rect = Rect(0, rowStaAndEnd[i][0], minFuseOTSU.cols, rowStaAndEnd[i][1] - rowStaAndEnd[i][0]);
		temp = minFuseOTSU(rect).clone();		
		//���и�
		fansubColCut(temp, singleFansubStaAndEnd);
		rect = Rect(singleFansubStaAndEnd[0], rowStaAndEnd[i][0], singleFansubStaAndEnd[1] - singleFansubStaAndEnd[0], rowStaAndEnd[i][1] - rowStaAndEnd[i][0]);
		temp = minFuseResult(rect).clone();
		cv::resize(temp, temp, Size(temp.cols* 2, temp.rows * 2), 0, 0, CV_INTER_LINEAR);
		//����Сֵƽ��ͼ�л�ȡ��Ļ��ȷλ����ʹ�ô�򷨿���Ϊ�����ַ��ָ��ṩ���õ�����
		cv::threshold(temp, temp, 200, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
		//�����и�
		charCutDistinguish(temp, fansubText);
		
	}
}

//�ַ��и���ʶ��
void FansubTransalte::charCutDistinguish(Mat src,QString& strText)
{
	Mat ch;
	int starCol = 0;
	int endCol = 0;
	//�������ʼ������룬Ҳ���ǿո���
	int wordMaxDistance = src.rows / 4;
	int nowSpaceWidth = 0;
	//�����ַ�֮����������������
	int charConnectWdith = src.rows / 15;
	size_t nowCharLen = 0;
	vector<int>colWhitePixel;
	verticalProjection(src, colWhitePixel);
	
	//������ֱͶӰ��Ľ�����д�ֱ�����ַ��ָ�
	for (int i = 0; i < colWhitePixel.size(); i++)
	{

		if (colWhitePixel[i] > charConnectWdith && (i < (colWhitePixel.size() - 1)))
		{
			if (nowSpaceWidth >= wordMaxDistance)
			{
				strText += " ";
				nowSpaceWidth = 0;
			}

			nowCharLen++;
			continue;
		}
		if (nowCharLen > (src.rows / 10))
		{
			//��û���ַ���β�����ǵ����ַ��ٽ��߽�ĵط���������ϡ��
			if ((colWhitePixel[i] != 0) && (findNextColZeo(i, colWhitePixel) < src.rows / 3) && (i < (colWhitePixel.size() - 1)))
			{
				nowCharLen++;
			}
			else    //���°����������1.�����ַ�ĩβ 2.���������ַ��������
			{
				starCol = i - nowCharLen - 2;
				endCol = i + 1;
				ch = src(Rect(starCol, 0, endCol - starCol, src.rows)).clone();
				clearEmpty(ch, ch);
				cv::resize(ch, ch, Size(20, 20), 0, 0, CV_INTER_LINEAR);
				static char c;
			
				c = compared(ch);
				strText[strText.size()] = c;
				nowCharLen = 0;
				nowSpaceWidth = 0;
			}
		}
		else if (colWhitePixel[i] == 0)
		{
			nowSpaceWidth++;
		}
	}
}




//��Ļ�зָ��һ��ͼƬ����ɨ�裬������һ�����������Ļ��ʼλ��
void FansubTransalte::fansubRowCut(Mat src, vector<vector<int>>&rowStaAndEnd)
{
	vector<int>minMatJumpArr;
	//������¼�����������15������
	int jumpLineCount = 0;
	countJumpPixel(src, minMatJumpArr);
	vector<int>fansubRowPlace(2);

	int fansubLineCount = 0;
	for (int i = 0; i < minMatJumpArr.size(); i++)
	{
		if (minMatJumpArr[i] > 15)
		{
			jumpLineCount++;
		}
		else
		{
			//����6�е����������15˵������Ļ���ڵ�λ��
			if (jumpLineCount >= 5)
			{
				fansubRowPlace[0] = i - jumpLineCount;
				fansubRowPlace[1] = i - 1;
				rowStaAndEnd.push_back(fansubRowPlace);
				jumpLineCount = 0;
			}
		}

	}
	//��ȷ��չ��Ļ��ͼ���е���ʼ���ս���
	for (int i = 0; i < rowStaAndEnd.size(); i++)
	{
		//������չ
		while (rowStaAndEnd[i][0] - 1 >= 0)
		{
			if (minMatJumpArr[rowStaAndEnd[i][0] - 1] >= 2)
				rowStaAndEnd[i][0]--;
			else
			{
				rowStaAndEnd[i][0] -= 2;
				break;
			}

		}
		//������չ
		while (rowStaAndEnd[i][1] + 1 <= minMatJumpArr.size())
		{
			if (minMatJumpArr[rowStaAndEnd[i][1] + 1] >= 2)
				rowStaAndEnd[i][1]++;
			else
			{
				rowStaAndEnd[i][1] += 2;
				break;
			}

		}
	}
}



// ��Ļ�зָ� �������ͼƬ�ϵ����ݽ������и�
void FansubTransalte::fansubColCut(Mat src, vector<int>&colStaAndEnd)
{
	
	int star = 0;
	int end = 0;
	int width = 0;
	int wordMaxDistance = src.rows;
	vector<int>minVerticalProjection;
	verticalProjection(src, minVerticalProjection);
	//��Ļ�п�ʼ�и�
	for (int i = src.cols / 2; i >= 0; i--)
	{
		if (minVerticalProjection[i] > 0)
			width = 0;
		else
		{
			width++;
			if (width > wordMaxDistance)
			{
				colStaAndEnd.push_back(i + width - 2);
				break;
			}
		}
	}
	//��ĩβ����ǰҪ�ȳ�ʼ��width
	width = 0;
	//��Ļ�н�β�и�
	for (int i = src.cols / 2; i < src.cols; i++)
	{
		if (minVerticalProjection[i] > 0)
		{
			width = 0;
		}
		else
		{

			if (width > wordMaxDistance)
			{
				colStaAndEnd.push_back(i - width + 2);
				break;
			}
			width++;
		}
	}

	Rect rect(star, 0, end - star, src.rows);
}

void FansubTransalte::loadTranslation(int star,int end,QString txt)
{
	IplImage ipl_img;
	QByteArray arr=txt.toLocal8Bit();
	char *cstr = arr.data();
	int type = 10;
	CvScalar size;
	
	CvxText text("C:\\Windows\\Fonts\\simhei.ttf"); // "zenhei.ttf"Ϊ���峣�� 
	for (size_t i = star; i < end; i++)
	{
		text.restoreFont();
		ipl_img=IplImage(readFrame[i]);
		text.putText(&ipl_img, cstr,cvPoint(220, 600), CV_RGB(255, 0, 255));
	}

}

void FansubTransalte::writeToShareSpace(vector<Mat>src)
{
	for (size_t i = 0; i < src.size(); i++)
	{
		resultFrame.push_back(src[i].clone());
	}
	dealFansubNum += src.size();
}


//������������jumpFrameNum֡ȡ��jumpFrameNum+1֡
bool FansubTransalte::getNextfarme(Mat& src_frame)
{
	Mat currentFarme;
	bool ret = true;
	for (int i = 0; i < jumpFrameNum; i++)
	{
		newVideo >> currentFarme;
		readFrame.push_back(currentFarme.clone());
	}
	//���û��ȡ����Ч����Ƶ֡��ֱ���˳�
	if (currentFarme.data == NULL)
	{
		writeToShareSpace(readFrame);
		ret = false;
	}
	else
	{
		cv::resize(currentFarme, currentFarme, Size(1366, 768), 0, 0, CV_INTER_LINEAR);
		Rect rect(0, currentFarme.rows / 4 * 3, currentFarme.cols, currentFarme.rows / 4);
		src_frame = currentFarme(rect).clone();
		cvtColor(src_frame, src_frame, CV_RGB2GRAY);
	}
	return ret;
}

bool FansubTransalte::videoHandleCheck()
{
	bool ret = false;
	do
	{
		qDebug() << "1 ";
		if (!existVideo)
			break;
		newVideo = VideoCapture(filePath.toStdString());
		frameRate = newVideo.get(CV_CAP_PROP_FPS);
		ret = true;
	} while (false);
	return ret;
}


