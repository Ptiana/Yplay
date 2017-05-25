#include"knn.h"

char compared(Mat src)
{
	int K = 5;
	src.convertTo(src, CV_32F);
	static Ptr<KNearest> model = StatModel::load<KNearest>("Letter.xml");
	model->setDefaultK(K);
	model->setIsClassifier(true);
	float k = model->predict(src.reshape(0, 1));
	int index = (int)k;
	if (index >= 52)
		return symbol[index - 52];
	else if (index >= 26)
		return capital[index - 26];
	else
		return smallLetter[index];
}