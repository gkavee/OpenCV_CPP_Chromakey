#include "processVideo.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

void processVideo(const std::string& videoPath, const std::string& backgroundPath,
                  int hueLower, int saturationLower, int valueLower,
                  int hueUpper, int saturationUpper, int valueUpper) {
    VideoCapture cap(videoPath);
    if (!cap.isOpened()) {
        std::cerr << "Ошибка при открытии видео!" << std::endl;
        return;
    }

    Mat background = imread(backgroundPath);
    if (background.empty()) {
        std::cerr << "Ошибка при загрузке изображения для фона!" << std::endl;
        return;
    }

    Scalar chromaKeyLower(hueLower, saturationLower, valueLower);
    Scalar chromaKeyUpper(hueUpper, saturationUpper, valueUpper);

    int backgroundWidth = background.cols;
    int backgroundHeight = background.rows;

    Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty())
            break;

        resize(frame, frame, Size(backgroundWidth, backgroundHeight));

        Mat hsv;
        cvtColor(frame, hsv, COLOR_BGR2HSV);

        Mat mask;
        inRange(hsv, chromaKeyLower, chromaKeyUpper, mask);

        Mat result;
        bitwise_and(frame, frame, result, ~mask);
        bitwise_or(result, background, result, mask);

        namedWindow("result", WINDOW_AUTOSIZE);
        moveWindow("result", 500, 250);
        imshow("result", result);
        int key = cv::waitKey(1);
        if (key == 27) break; //esc для закрытия
    }

    destroyAllWindows();
}