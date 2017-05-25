#ifndef _KNN_H_
#define _KNN_H_

#include<iostream>
#include<opencv2\opencv.hpp>

using namespace std;
using namespace cv;
using namespace cv::ml;


//static char english[41] = { 'A','B','L','N','S','T', 'a','b', 'c','d','e','f','g','h','i','k','l','m','n','o','p','r','s','t','u','v','w','y','`','!',',' };
static string smallLetter = { 'a','b', 'c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
static string capital = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
static string symbol = { '`','!',',' };

//20*20的单通道图
char compared(Mat src);
#endif // !_KNN_H_
