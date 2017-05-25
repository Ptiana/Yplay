#include "imgDispose.h"
bool existFansub(Mat src)
{
	bool backValue = false;
	Mat twoValue;
	//��������ͼƬ��С
	cv::resize(src, src, Size(src.cols / 2, src.rows / 2), 0, 0, CV_INTER_LINEAR);
	//Rect rect(0, src.rows / 4 * 3, src.cols, src.rows / 4);
	threshold(src, twoValue, 170, 255, CV_THRESH_BINARY);
	vector<int>rowsJumpNum;
	countJumpPixel(twoValue, rowsJumpNum);
	if (jumpCharactJudge(rowsJumpNum))
		backValue = true;

	return backValue;
}

//ͳ�ƶ�ֵ��ͼƬ��ÿ�е����������
bool countJumpPixel(Mat src, vector <int> &jumpArr)
{
	bool ret = false;
	if (src.data != NULL)
	{
		ret = true;
		int currentJumpNum = 0;
		uchar currentPixel = 0;
		uchar nextPixel = 0;
		//������ͼƬ���з�Ϊ3���֣�ȡ�м�һ������Ϊ����ͳ�Ƶ�������Ϊ��Ļ���ǳ������м�
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


//�ܾ������������ж��Ƿ������Ļ
bool jumpCharactJudge(vector <int> &jumpArr)
{
	bool ret = false;
	int jumpLineCount = 0;
	//����6�е����������15˵��������Ļ
	for (int i = 2; i < jumpArr.size() - 2; i++)
	{
		if (jumpArr[i] > 15)
		{
			jumpLineCount++;
		}
		else
		{
			//����6�е����������15˵������Ļ���ڵ�λ��
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

//��Ļ���ƱȽϣ��ж����Ʒ���true
bool similarCompare(Mat targetImg, Mat testImg)
{

	bool backValue = true;

	//������¼targetCut,testCut,result������ֵΪ255�ĸ���
	int targetWhiteCount = 0;
	int testWhiteCount = 0;
	int resultWhiteCount = 0;

	//����ͼƬ�м��һ���������������ԱȽ�
	Rect rect(targetImg.cols / 4, targetImg.rows / 10, targetImg.cols / 2, targetImg.rows * 7 / 10);
	Mat targetCut = targetImg(rect);
	Mat testCut = testImg(rect);
	Mat result = targetImg(rect).clone();
	GaussianBlur(targetCut, targetCut, Size(5, 5), 0, 0);
	GaussianBlur(testCut, testCut, Size(5, 5), 0, 0);
	medianBlur(targetCut, targetCut, 3);
	medianBlur(testCut, testCut, 3);


	//��������ͼƬ��С,�ӿ촦���ٶ�
	cv::resize(targetCut, targetCut, Size(targetCut.cols / 3, targetCut.rows / 3), 0, 0, CV_INTER_LINEAR);
	cv::resize(testCut, testCut, Size(testCut.cols / 3, testCut.rows / 3), 0, 0, CV_INTER_LINEAR);


	//��ֵ��
	threshold(targetCut, targetCut, 170, 255, CV_THRESH_BINARY);
	threshold(testCut, testCut, 170, 255, CV_THRESH_BINARY);

	//��Ե��
	Canny(targetCut, targetCut, 50, 150);
	Canny(testCut, testCut, 50, 150);



	for (int i = 0; i < targetCut.rows; i++)
	{
		for (int j = 0; j < targetCut.cols; j++)
		{
			//ͳ������ֵΪ255�ĸ���
			if (targetCut.at<uchar>(i, j) == 255)
				targetWhiteCount++;
			if (testCut.at<uchar>(i, j) == 255)
				testWhiteCount++;
			//�Ƚ�����ͼ����ֵ��ͬ��λ��
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
		cout << "����";
	}
	else
	{
		cout << "������";
	}
	return backValue;
}


//��ͼ��Сֵ�ں��ں�
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

// ��ȡ��֡ͼ��ָ���������ص���Сֵ
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


//ͳ��ÿ��ֵΪ255�����ظ���----��ֱͶӰ
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

//Ѱ�ҽ����ŵİ�ɫ�����ڴ�ֱ����ͶӰ����Ϊ��ľ���
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

// ͼ���ʽת��
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
		//���������ͼ�� 
		const uchar *pSrc = (const uchar*)mat.data;
		// �½�һ��������ͼ����ͬ��ͼ��   
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



//ɾ���и�������ַ������¿հײ���
bool clearEmpty(Mat src, Mat &dst)
{
	bool ret = false;
	int star = 0, end = 0;
	bool flag = false;
	vector<int>test;
	HorizontalProjection(src, test);
	//ɾ�������հ�
	for (int i = 0; i < src.rows; i++)
	{
		if (test[i] > 1 && test[i + 2] > 1)
		{
			star = i;
			break;
		}
	}

	//ɾ���ײ��հ�
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



//ͳ��ÿ��ֵΪ255�����ظ���---------ˮƽͶӰ
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
