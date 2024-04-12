#include "processImageRGB.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;
using namespace cv;

double calculateDistanceRGB(Vec3b color1, Vec3b color2) {
    return norm(color1 - color2);
}

void processImageRGB(const std::string& inputImagePath, const std::string& backgroundImagePath, const std::string& outputDir, const Vec3b& chromaKeyColor,
                     int tolerance) {
    // загрузка входного изображения
    Mat inputImage = imread(inputImagePath, IMREAD_COLOR);
    if (inputImage.empty()) {
        std::cerr << "Error: Could not read input image " << inputImagePath;
        return;
    }

    // загрузка фонового изображения
    Mat backgroundImage = imread(backgroundImagePath, IMREAD_COLOR);
    if (backgroundImage.empty()) {
        std::cerr << "Error: Could not read background image " << backgroundImagePath;
        return;
    }

    // подгон размера изображения под размер хромакея
    resize(backgroundImage, backgroundImage, inputImage.size());

    // замена цветового фона на фоновое изображение
    Mat outputImage = inputImage.clone();
    for (int y = 0; y < inputImage.rows; ++y) {
        for (int x = 0; x < inputImage.cols; ++x) {
            Vec3b color = inputImage.at<Vec3b>(y, x);
            double distance = calculateDistanceRGB(color, chromaKeyColor);
            if (distance < tolerance) { // Проверка расстояния до целевого цвета
                outputImage.at<Vec3b>(y, x) = backgroundImage.at<Vec3b>(y, x);
            }
        }
    }

    // сохранение результата
    std::string outputImagePath = outputDir + fs::path(inputImagePath).filename().string();
    imwrite(outputImagePath, outputImage);
    std::cout << "image saved as: " << outputImagePath;

    // отображение окна с результатом
    namedWindow("result", WINDOW_AUTOSIZE);
    moveWindow("result", 500, 250);
    imshow("result", outputImage);
    waitKey(0);
    destroyAllWindows();
}
