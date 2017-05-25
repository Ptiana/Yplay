#include "imgDispose.h"
bool existFansub(Mat src)
{
	bool backValue = false;
	Mat twoValue;
	//重新设置图片大小
	cv::resize(src, src, Size(src.cols / 2, src.rows / 2), 0, 0, CV_INTER_LINEAR);
	//Rect rect(0, src.rows / 4 * 3, src.cols, src.rows / 4);
	threshold(src, twoValue, 170, 255, CV_THRESH_BINARY);
	vector<int>rowsJumpNum;
	countJumpPixel(twoValue, rowsJumpNum);
	if (jumpCharactJudge(rowsJumpNum))
		backValue = true;

	return backValue;
}

//统计二值化图片中每行的跳变点数量
bool countJumpPixel(Mat src, vector <int> &jumpArr)
{
	bool ret = false;
	if (src.data != NULL)
	{
		ret = true;
		int currentJumpNum = 0;
		uchar currentPixel = 0;
		uchar nextPixel = 0;
		//将整个图片按列分为3部分，取中间一部分作为跳变统计的区域，因为字幕总是出现在中间
		int starCols = src.cols / 3;
		int endCols = src.cols - starCols;
		for (int i = 0; i < src.rows; i++)
		{
			for (int j = starCols; j < endCols - 1; j++)
			{
				currentPixel = src.at<uchar>(i, j);
				nextPixel = src.at<uchar>(i, j + 1);
				if (currentPixel != nextPixel)
				{
					currentJumpNum++;
				}
			}
			jumpArr.push_back(currentJumpNum);
			currentJumpNum = 0;
		}
	}
	return ret;
}


//很据跳变特征点判断是否存在字幕
bool jumpCharactJudge(vector <int> &jumpArr)
{
	bool ret = false;
	int jumpLineCount = 0;
	//连续6行的跳变均大于15说明存在字幕
	for (int i = 2; i < jumpArr.size() - 2; i++)
	{
		if (jumpArr[i] > 15)
		{
			jumpLineCount++;
		}
		else
		{
			//连续6行的跳变均大于15说明是字幕所在的位置
			if (jumpLineCount >= 5)
			{
				ret = true;
				break;
			}
			jumpLineCount = 0;
		}

	}

	return ret;
}

//字幕相似比较，判定相似返回true
bool similarCompare(Mat targetImg, Mat testImg)
{

	bool backValue = true;

	//用来记录targetCut,testCut,result中像素值为255的个数
	int targetWhiteCount = 0;
	int testWhiteCount = 0;
	int resultWhiteCount = 0;

	//剪切图片中间的一段用来进行相似性比较
	Rect rect(targetImg.cols / 4, targetImg.rows / 10, targetImg.cols / 2, targetImg.rows * 7 / 10);
	Mat targetCut = targetImg(rect);
	Mat testCut = testImg(rect);
	Mat result = targetImg(rect).clone();
	GaussianBlur(targetCut, targetCut, Size(5, 5), 0, 0);
	GaussianBlur(testCut, testCut, Size(5, 5), 0, 0);
	medianBlur(targetCut, targetCut, 3);
	medianBlur(testCut, testCut, 3);


	//重新设置图片大小,加快处理速度
	cv::resize(targetCut, targetCut, Size(targetCut.cols / 3, targetCut.rows / 3), 0, 0, CV_INTER_LINEAR);
	cv::resize(testCut, testCut, Size(testCut.cols / 3, testCut.rows / 3), 0, 0, CV_INTER_LINEAR);


	//二值化
	threshold(targetCut, targetCut, 170, 255, CV_THRESH_BINARY);
	threshold(testCut, testCut, 170, 255, CV_THRESH_BINARY);

	//边缘化
	Canny(targetCut, targetCut, 50, 150);
	Canny(testCut, testCut, 50, 150);



	for (int i = 0; i < targetCut.rows; i++)
	{
		for (int j = 0; j < targetCut.cols; j++)
		{
			//统计像素值为255的个数
			if (targetCut.at<uchar>(i, j) == 255)
				targetWhiteCount++;
			if (testCut.at<uchar>(i, j) == 255)
				testWhiteCount++;
			//比较两幅图像素值不同的位置
			if (targetCut.at<uchar>(i, j) != testCut.at<uchar>(i, j))
			{
				result.at<uchar>(i, j) = 255;
				resultWhiteCount++;
			}
			else
			{
				result.at<uchar>(i, j) = 0;
			}
		}
	}
	if ((resultWhiteCount > targetWhiteCount) || (resultWhiteCount > testWhiteCount))
		backValue = false;

	if (backValue == true)
	{
		cout << "相似";
	}
	else
	{
		cout << "不相似";
	}
	return backValue;
}


//多图最小值融合融合
void minValueFuse(vector<Mat>src,Mat& dst)
{
	int pixelSum = 0;
	dst = src.at(0).clone();
	int rows = src.at(0).rows;
	int cols = src.at(0).cols;
	//system("pause");
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			dst.at<uchar>(i, j) = getMinPixel(src,i, j);
		}
	}
}

// 获取多帧图像指定坐标像素的最小值
uchar getMinPixel(vector<Mat>src,int row, int col)
{
	uchar min = src.at(0).at<uchar>(row, col);
	for (int count = 1; count < src.size(); count++)
	{
		if (src.at(count).at<uchar>(row, col) < min)
			min = src.at(count).at<uchar>(row, col);
	}
	return min;
}


//统计每列值为255的像素个数----垂直投影
void verticalProjection(Mat src, vector<int>&colWhitePixel)
{
	colWhitePixel.clear();
	int colWhitePixelNum = 0;
	for (int i = 0; i < src.cols; i++)
	{
		colWhitePixelNum = 0;
		for (int j = 0; j < src.rows; j++)
		{
			if (src.at<uchar>(j, i) == 255)
				colWhitePixelNum++;
		}
		colWhitePixel.push_back(colWhitePixelNum);
	}
}

//寻找紧接着的白色像素在垂直方向投影数量为零的距离
int findNextColZeo(int currentIndex,vector<int>colWhitePixel)
{
	int  distance = 0;
	for (int i = currentIndex; i < colWhitePixel.size(); i++)
	{
		if (colWhitePixel[i] == 0)
			break;
		distance++;
	}
	return distance;
}

// 图像格式转换
QImage MatToQImage(const cv::Mat& mat)
{
	// 8-bits unsigned, NO. OF CHANNELS = 1    
	if (mat.type() == CV_8UC1)
	{
		QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
		// Set the color table (used to translate colour indexes to qRgb values)    
		image.setColorCount(256);
		for (int i = 0; i < 256; i++)
		{
			image.setColor(i, qRgb(i, i, i));
		}
		// Copy input Mat    
		uchar *pSrc = mat.data;
		for (int row = 0; row < mat.rows; row++)
		{
			uchar *pDest = image.scanLine(row);
			memcpy(pDest, pSrc, mat.cols);
			pSrc += mat.step;
		}
		return image;
	}
	// 8-bits unsigned, NO. OF CHANNELS = 3    
	else if (mat.type() == CV_8UC3)
	{
		//复制输入的图像 
		const uchar *pSrc = (const uchar*)mat.data;
		// 新建一个和输入图像相同的图像   
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	else if (mat.type() == CV_8UC4)
	{
		qDebug() << "CV_8UC4";
		const uchar *pSrc = (const uchar*)mat.data;
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
		return image.copy();
	}
	else
	{
		qDebug() << "ERROR: Mat could not be converted to QImage.";
		return QImage();
	}
}



//删掉切割出来的字符的上下空白部分
bool clearEmpty(Mat src, Mat &dst)
{
	bool ret = false;
	int star = 0, end = 0;
	bool flag = false;
	vector<int>test;
	HorizontalProjection(src, test);
	//删除顶部空白
	for (int i = 0; i < src.rows; i++)
	{
		if (test[i] > 1 && test[i + 2] > 1)
		{
			star = i;
			break;
		}
	}

	//删除底部空白
	for (int i = src.rows - 1; i > 0; i--)
	{
		if (test[i] > 1 && test[i - 2] > 1)
		{
			end = i;
			break;
		}
	}
	if (star == 0)
		star++;
	if (end == src.rows)
		end--;
	Rect rect(0, star - 1, src.cols, end - star + 2);
	dst = src(rect).clone();
	if (star < 2)
		ret = true;
	return ret;
}



//统计每行值为255的像素个数---------水平投影
void HorizontalProjection(Mat src, vector<int>&rowWhitePixel)
{
	int rowWhitePixelNum = 0;
	for (int i = 0; i < src.rows; i++)
	{
		rowWhitePixelNum = 0;
		for (int j = 0; j < src.cols; j++)
		{
			if (src.at<uchar>(i, j) == 255)
				rowWhitePixelNum++;
		}
		rowWhitePixel.push_back(rowWhitePixelNum);
	}
}
