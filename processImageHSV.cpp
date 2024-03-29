#include "processImageHSV.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;
using namespace cv;

void processImageHSV(const std::string& inputImagePath, const std::string& backgroundImagePath, const std::string& outputDir,
                     int h_lower, int s_lower, int v_lower,
                     int h_upper, int s_upper, int v_upper) {
    // загрузка входного изображения
    Mat inputImage = imread(inputImagePath, IMREAD_COLOR);
    if (inputImage.empty()) {
        std::cerr << "Error: Could not read input image " << inputImagePath << std::endl;
        return;
    }

    // загрузка фонового изображения
    Mat backgroundImage = imread(backgroundImagePath, IMREAD_COLOR);
    if (backgroundImage.empty()) {
        std::cerr << "Error: Could not read background image " << backgroundImagePath << std::endl;
        return;
    }

    // подгон размера изображения под размер хромакея
    resize(backgroundImage, backgroundImage, inputImage.size());

    // преобразование изображения в HSV
    Mat hsvInput, hsvBackground;
    cvtColor(inputImage, hsvInput, COLOR_BGR2HSV);
    cvtColor(backgroundImage, hsvBackground, COLOR_BGR2HSV);

    // создание нижних и верхних границ HSV
    Scalar lower(h_lower, s_lower, v_lower);
    Scalar upper(h_upper, s_upper, v_upper);

    // создание маски
    Mat mask;
    inRange(hsvInput, lower, upper, mask);

    // замена цветового фона на фоновое изображение
    Mat outputImage = inputImage.clone();
    for (int y = 0; y < inputImage.rows; ++y) {
        for (int x = 0; x < inputImage.cols; ++x) {
            if (mask.at<uchar>(y, x) > 0) { // Если пиксель находится в маске
                outputImage.at<Vec3b>(y, x) = backgroundImage.at<Vec3b>(y, x);
            }
        }
    }

    // сохранение результата
    std::string outputImagePath = outputDir + fs::path(inputImagePath).filename().string();
    imwrite(outputImagePath, outputImage);
    std::cout << "Image saved as: " << outputImagePath << std::endl;
}
