#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

Mat colorHistogram(Mat img) {
	Mat hist;
	const int histSize = 256;
	const float range[] = { 0, 256 };
	const float * ranges = { range };
	calcHist(&img, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false);
	return hist;
}
int main(int argc, char *argv[])
{
	Mat starMap, smallPic, smallHist;

	smallPic = imread(argv[1], IMREAD_GRAYSCALE);
	if (smallPic.empty())
	{
		cout << "First image could not be read!" << endl << "Terminating..." << endl;
		return EXIT_FAILURE;
	}

	starMap = imread(argv[2], IMREAD_GRAYSCALE);
	if (starMap.empty())
	{
		cout << "First image could not be read!" << endl << "Terminating..." << endl;
		return EXIT_FAILURE;
	}
	else
	{
		smallHist = colorHistogram(smallPic);

		const int roiRows = smallPic.rows,
			roiCols = smallPic.cols,
			seekRows = starMap.rows - roiRows,
			seekCols = starMap.cols - roiCols;
		int minDiff = INT32_MAX,
			minRow,
			minCol;

		for (int r = 0; r < seekRows; r++) {
			Range rowRange = Range(r, r + roiRows);
			for (int c = 0; c < seekCols; c++) {
				Range colRange = Range(c, c + roiCols);
				Mat roi = starMap(rowRange, colRange);
				Mat roiHist = colorHistogram(roi);
				Mat diffMat;
				absdiff(roiHist, smallHist, diffMat);
				Scalar diff = sum(diffMat);
				//cout << r << "   " << c << endl;
				if (diff[0] < minDiff)
				{
					minDiff = diff[0];
					minRow = r;
					minCol = c;
				}
			}
		}
		Rect roiRect = Rect(minCol, minRow, roiCols, roiRows);
		cout << "Small image location in the StarMap is : (" <<
		minCol << ", " << minRow << ", "<< minCol + roiCols << ", " << minRow + roiRows<< ")" << endl;  
	}

	return EXIT_SUCCESS;
}
