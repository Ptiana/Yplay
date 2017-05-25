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
	//50秒检查一次视频是否已经打开
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
			//处理字幕
			fansubHandle(currentHandleIndex);
			continue;
		}
		waitKey(2);
	}
	
	system("pause");

 }



void FansubTransalte::fansubHandle(int starFrame)
{
	//处理新字幕前的初始化
	fansubText = "";
	newVideo.set(CV_CAP_PROP_POS_FRAMES, starFrame);
	//字幕追踪
	while (!FansubTrack());
	if (!end)
	{
		//字幕帧融合
		minValueFuse(fansubFuseFrame, minFuseResult);
		//字幕切割并识别
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

//字幕追踪
bool  FansubTransalte::FansubTrack()
{

	bool ret = false;
	Mat  src_frame;
	Mat  temp;
	bool hasFindFansub = false;
	bool fansubChange = false;
	//fansubFuseFrame.clear();
	vector<Mat>().swap(fansubFuseFrame);
	//1.检查当前字幕开始的帧的位置
	do {
		if (!getNextfarme(src_frame))
		{
			end = true;
			ret = true;
			return ret;
		}
		//检查到字幕出现，把当前检测到的字幕帧进栈
		if (existFansub(src_frame.clone()))                   
		{
			fansubFuseFrame.push_back(src_frame.clone());
			hasFindFansub = true;
			cout << "\n检测到字幕\n";
		}
		else
		{
			cout << "\n未检测到字幕\n";
		}
	} while (!hasFindFansub);

	//2.检查当前字幕结束的帧的位置
	do {
		//继续读接下来的第4帧
		if (!getNextfarme(src_frame))
		{
			end = true;
			ret = true;
			return ret;
		}
		//如果相似就进栈然后继续跳3帧读接下来第四帧
		if (similarCompare(fansubFuseFrame.back().clone(), src_frame.clone()))
		{
			fansubFuseFrame.push_back(src_frame.clone());
		}
		else
		{//不相似，检测之前追踪到的相同字幕的个数是否小于阈值Tn
			if (fansubFuseFrame.size() < 5)  //误检，此次结果不要重新检测
			{
				//qDebug() << "5678";
				//vector<Mat>().swap(fansubFuseFrame);
				break;
			}
			else                           //检测到字幕结束停止追踪
			{
				fansubChange = true;
			}
		}
	} while (!fansubChange);
	if (fansubChange == true)
		ret = true;
	return ret;
}


//字幕切割
void FansubTransalte::fansubCut()
{
	Rect rect;
	Mat temp;                                //供存储图像处理数据的临时变量
	Mat minFuseOTSU = minFuseResult.clone();
	cv::threshold(minFuseResult, minFuseOTSU, 170, 255, CV_THRESH_BINARY);
	//imshow("最小值大津法二值化", minFuseOTSU);
	vector<vector<int>>rowStaAndEnd;          //当前融合处理帧中所有的字幕的开始行和结束行
	vector<int>singleFansubStaAndEnd;         //单条字幕的开始列和结束列
	vector<vector<int>>charStaAndEnd;         //某行字幕中所含的每个字符的开始列和结束列       

	 //行切割
	fansubRowCut(minFuseOTSU, rowStaAndEnd);
	//cout << rowStaAndEnd[0][0] << rowStaAndEnd[0][1];
	//对每条字幕单独进行列切割
	for (int i = 0; i < rowStaAndEnd.size(); i++)
	{
		//获取行切割后的区域
		rect = Rect(0, rowStaAndEnd[i][0], minFuseOTSU.cols, rowStaAndEnd[i][1] - rowStaAndEnd[i][0]);
		temp = minFuseOTSU(rect).clone();		
		//列切割
		fansubColCut(temp, singleFansubStaAndEnd);
		rect = Rect(singleFansubStaAndEnd[0], rowStaAndEnd[i][0], singleFansubStaAndEnd[1] - singleFansubStaAndEnd[0], rowStaAndEnd[i][1] - rowStaAndEnd[i][0]);
		temp = minFuseResult(rect).clone();
		cv::resize(temp, temp, Size(temp.cols* 2, temp.rows * 2), 0, 0, CV_INTER_LINEAR);
		//从最小值平均图中获取字幕精确位置再使用大津法可以为单个字符分割提供更好的条件
		cv::threshold(temp, temp, 200, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
		//单个切割
		charCutDistinguish(temp, fansubText);
		
	}
}

//字符切割与识别
void FansubTransalte::charCutDistinguish(Mat src,QString& strText)
{
	Mat ch;
	int starCol = 0;
	int endCol = 0;
	//两个单词间最大距离，也就是空格宽度
	int wordMaxDistance = src.rows / 4;
	int nowSpaceWidth = 0;
	//两个字符之间最大的连接像素数
	int charConnectWdith = src.rows / 15;
	size_t nowCharLen = 0;
	vector<int>colWhitePixel;
	verticalProjection(src, colWhitePixel);
	
	//遍历垂直投影后的结果进行垂直方向字符分割
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
			//并没到字符结尾，而是到了字符临近边界的地方所以像素稀薄
			if ((colWhitePixel[i] != 0) && (findNextColZeo(i, colWhitePixel) < src.rows / 3) && (i < (colWhitePixel.size() - 1)))
			{
				nowCharLen++;
			}
			else    //以下包括两种情况1.到了字符末尾 2.到了两个字符的黏连处
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




//字幕行分割对一张图片进行扫描，并返回一条或多条的字幕起始位置
void FansubTransalte::fansubRowCut(Mat src, vector<vector<int>>&rowStaAndEnd)
{
	vector<int>minMatJumpArr;
	//用来记录连续跳变大于15的行数
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
			//连续6行的跳变均大于15说明是字幕所在的位置
			if (jumpLineCount >= 5)
			{
				fansubRowPlace[0] = i - jumpLineCount;
				fansubRowPlace[1] = i - 1;
				rowStaAndEnd.push_back(fansubRowPlace);
				jumpLineCount = 0;
			}
		}

	}
	//精确扩展字幕在图像中的起始和终结行
	for (int i = 0; i < rowStaAndEnd.size(); i++)
	{
		//向上扩展
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
		//向下扩展
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



// 字幕列分割 对输入的图片上的内容进行列切割
void FansubTransalte::fansubColCut(Mat src, vector<int>&colStaAndEnd)
{
	
	int star = 0;
	int end = 0;
	int width = 0;
	int wordMaxDistance = src.rows;
	vector<int>minVerticalProjection;
	verticalProjection(src, minVerticalProjection);
	//字幕列开始切割
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
	//列末尾查找前要先初始化width
	width = 0;
	//字幕列结尾切割
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
	
	CvxText text("C:\\Windows\\Fonts\\simhei.ttf"); // "zenhei.ttf"为黑体常规 
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


//跳过接下来的jumpFrameNum帧取第jumpFrameNum+1帧
bool FansubTransalte::getNextfarme(Mat& src_frame)
{
	Mat currentFarme;
	bool ret = true;
	for (int i = 0; i < jumpFrameNum; i++)
	{
		newVideo >> currentFarme;
		readFrame.push_back(currentFarme.clone());
	}
	//如果没获取到有效的视频帧就直接退出
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


