#include <QDebug>
#include <opencv2/opencv.hpp>

namespace
{
    cv::Mat getColoredTestImage()
    {
        //change path to as required colored image
        return cv::imread("/Users/Hilton/Desktop/opencv_lesson/OpenCv/ShowImage/cat1.jpg");
    }
}

namespace grayscale
{
    //-----------------------------------
    cv::Mat convertToGrayScaleImage(const cv::Mat& colorImage)
    {
        cv::Mat gray(colorImage.size(), CV_8U);
        for(int x = 0; x < colorImage.rows; ++x)
        {
            for(int y=0; y < colorImage.cols; ++y)
            {
                cv::Vec3b rgb = colorImage.at<cv::Vec3b>(x,y);
                uchar gray_intensity = (rgb[0] + rgb[1] + rgb[2])/3;
                gray.at<uchar>(x,y) = gray_intensity;
            }
        }

        return gray;
    }

    //-----------------------------------
    //As simple as this!
    cv::Mat convertToGrayScaleImageEasy()
    {
        return cv::imread("/Users/Hilton/Desktop/opencv_lesson/OpenCv/ShowImage/cat1.jpg",cv::IMREAD_GRAYSCALE);
    }

    //-----------------------------------
    cv::Mat convertToGrayScaleImagecvtColor()
    {
        cv::Mat color_image = cv::imread("/Users/Hilton/Desktop/opencv_lesson/OpenCv/ShowImage/cat1.jpg",cv::IMREAD_COLOR);
        cv::Mat gray;

        cv::cvtColor(color_image, gray, cv::COLOR_RGB2GRAY);

        return gray;
    }

    int grayScaleConversion()
    {
        cv::Mat color_image = cv::imread("/Users/Hilton/Desktop/opencv_lesson/OpenCv/ShowImage/cat1.jpg",cv::IMREAD_COLOR);
        if(color_image.empty())
        {
            qWarning() << "Original color image not found or invalid!";
            return -1;
        }

        auto gray = grayscale::convertToGrayScaleImage(color_image);

        cv::imshow("Color", color_image);
        cv::imshow("Gray", gray);

        cv::waitKey(0);
        return 0;
    }
}

namespace binaryImage
{
    //binary image is 2 bit. Either 0 or 1, where 0 = black, 1 = white
    //in opencv we can use cv::threshold function to easily convert a grayscale image to binary image.
    //To convert an RGB image to a binary image in OpenCV, you can use a technique called thresholding.
    //Thresholding allows you to convert a grayscale image into a binary image based on a specified threshold value.

    //Example:
    //1. First, convert your RGB image to grayscale. You can do this using the cv::cvtColor function.
    //2. Apply thresholding to the grayscale image using the cv::threshold function.
    //-----------------------------------
    int convertToBinaryImageWithOpenCv()
    {
        cv::Mat color = getColoredTestImage();
        //convert to grayscale
        cv::Mat gray;
        cv::cvtColor(color, gray, cv::COLOR_RGB2GRAY);

        //convert to binary
        cv::Mat binary;
        cv::threshold(gray, binary,128,255, cv::THRESH_BINARY);

        //this replaces white with black and vice-versa, that's why it's called inverse
        cv::Mat binary_inv;
        cv::threshold(gray, binary_inv,128,255, cv::THRESH_BINARY_INV);

        cv::imshow("binary_inv", binary_inv);
        cv::imshow("binary", binary);

        cv::waitKey(0);
        return 0;
    }

    //-----------------------------------
    cv::Mat convertToBinary(const cv::Mat& gray, int threshold, int upperLimit)
    {
        cv::Mat binary(gray.size(), CV_8U);
        for(int x = 0; x < gray.rows; ++x)
        {
            for(int y = 0; y < gray.cols; ++y)
            {
                uchar current_intensity = gray.at<uchar>(x,y);
                if(current_intensity > threshold)
                {
                    binary.at<uchar>(x,y) = static_cast<uchar>(upperLimit);
                }
                else
                {
                    binary.at<uchar>(x,y) = 0;
                }
            }
        }

        return binary;
    }

    //-----------------------------------
    int convertToBinaryFullImplementation()
    {
        cv::Mat color = getColoredTestImage();
        //convert to grayscale
        cv::Mat gray;
        cv::cvtColor(color, gray, cv::COLOR_RGB2GRAY);

        auto binary_image = convertToBinary(gray, 128, 255);
        cv::imshow("binary-full-impl", binary_image);

        cv::waitKey(0);
        return 0;
    }
}

//-----------------------------------
int main()
{
    //return grayscale::grayScaleConversion();
    //return binaryImage::convertToBinaryImageWithOpenCv();
    return binaryImage::convertToBinaryFullImplementation();
}
