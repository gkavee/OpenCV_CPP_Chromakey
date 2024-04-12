#include "addMask.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void applyFilter(const Mat& inputImage, Mat& outputImage, const string& filterName) {

    if (filterName == "bw") {
        cvtColor(inputImage, outputImage, COLOR_BGR2GRAY);
    }

    else if (filterName == "blur") {
        GaussianBlur(inputImage, outputImage, Size(5, 5), 0);
    }

    else if (filterName == "neg" || filterName == "negative") {
        bitwise_not(inputImage, outputImage);
    }

    else if (filterName == "vintage" || filterName == "vin") {
        // Сглаживание изображения с помощью фильтра Гаусса
        Mat blurred;
        GaussianBlur(inputImage, blurred, Size(0, 0), 3);

        // Создание винтажного эффекта с помощью наложения фильтров
        addWeighted(inputImage, 1.5, blurred, -0.5, 0, outputImage);
    }

    else {
        outputImage = inputImage.clone();
        Point textOrg((outputImage.cols - 100) / 2, (outputImage.rows) / 2); // координаты верхнего левого угла текста
        int fontFace = FONT_HERSHEY_SIMPLEX; // шрифт
        Scalar color(0, 0, 255);
        putText(outputImage, "no filter", textOrg, fontFace, 1, color, 2);
    }
}

void addMask(const string& imagePath, const string& filterName) {
    Mat image = imread(imagePath);

    if (image.empty()) {
        cout << "Не удалось загрузить изображение." << endl;
        return;
    }

    Mat filteredImage;
    applyFilter(image, filteredImage, filterName);

    namedWindow("result", WINDOW_AUTOSIZE);
    moveWindow("result", 500, 250);
    imshow("result", filteredImage);

    waitKey(0);
    destroyAllWindows();
}
