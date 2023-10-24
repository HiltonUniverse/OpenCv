#include <QDebug>
#include <opencv2/opencv.hpp>

using namespace cv;

class Histogram
{
public:
    //-----------------------------------
    Mat calculateHistogram(Mat scr)
    {
        Mat hist;
        hist = Mat::zeros(256, 1, CV_32F);
        scr.convertTo(scr, CV_32F);
        double value = 0;
        for (int i = 0; i < scr.rows; i++)
        {
            for (int j = 0; j < scr.cols; j++)
            {
                value = scr.at<float>(i, j);
                hist.at<float>(value) = hist.at<float>(value) + 1;
            }
        }

        return hist;
    }

    //-----------------------------------
    void plotHistogram(Mat histogram)
    {
        Mat histogram_image(400, 520, CV_8UC3, Scalar(0, 0, 0));
        Mat normalized_histogram;
        normalize(histogram, normalized_histogram, 0, 400, NORM_MINMAX, -1, Mat());

        for (int i = 0; i < 256; i++)
        {
            rectangle(histogram_image, Point(2*i, histogram_image.rows - normalized_histogram.at<float>(i)),
                Point(2*(i + 1), histogram_image.rows), Scalar(255, 0, 0));
        }

        namedWindow("Histogram", WINDOW_NORMAL);
        imshow("Histogram", histogram_image);
    }
};

//-----------------------------------
int main()
{
    cv::Mat img;
    img = cv::imread("/Users/Hilton/Desktop/grayscale_cat_image.jpeg", 0);


    Histogram h1;
    cv::Mat hist = h1.calculateHistogram(img);
    h1.plotHistogram(hist);
    cv::waitKey(0);
}
