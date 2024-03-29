#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>
#include <string>
#include "processImageHSV.h"
#include "processImageRGB.h"

using namespace cv;
namespace fs = std::filesystem;

int main() {
    // пути к входному изображению
    std::string inputDir;
    std::cout << "input dir: ";
    std::getline(std::cin, inputDir);

    // Запрос пути для сохранения выходного изображения
    std::string backgroundDir;
    std::cout << "background dir: ";
    std::getline(std::cin, backgroundDir);

    std::string outputDir = "C:\\Users\\gkave\\CLionProjects\\OpenCV\\output_images\\";

    // создание каталога для выходных изображений если он не существует
    fs::create_directory(outputDir);

    std::cout << "method RGB/HSV: ";
    std::string method;
    std::cin >> method;
    if (method == "RGB" || method == "rgb") {
        int r, g, b, tolerance;
        std::cout << "input Red: ";
        std::cin >> r;
        std::cout << "input Green: ";
        std::cin >> g;
        std::cout << "input Blue: ";
        std::cin >> b;
        std::cout << "input tolerance: ";
        std::cin >> tolerance;
        Vec3b chromaKeyColor(r, g, b);

        // Обработка каждого изображения
        for (const auto& entry : fs::directory_iterator(inputDir)) {
            std::string inputImagePath = entry.path().string();
            std::string backgroundImagePath = backgroundDir + fs::path(inputImagePath).filename().string();
            processImageRGB(inputImagePath, backgroundImagePath, outputDir, chromaKeyColor, tolerance);
        }
    }

    else if (method == "HSV" || method == "hsv") {
        int h_lower, s_lower, v_lower, h_upper, s_upper, v_upper;
        std::cout << "input Hue(lower): ";
        std::cin >> h_lower;
        std::cout << "input Saturation(lower): ";
        std::cin >> s_lower;
        std::cout << "input Value(lower): ";
        std::cin >> v_lower;
        std::cout << "input Hue(upper): ";
        std::cin >> h_upper;
        std::cout << "input Saturation(upper): ";
        std::cin >> s_upper;
        std::cout << "input Value(upper): ";
        std::cin >> v_upper;

        // Обработка каждого изображения
        for (const auto& entry : fs::directory_iterator(inputDir)) {
            std::string inputImagePath = entry.path().string();
            std::string backgroundImagePath = backgroundDir + fs::path(inputImagePath).filename().string();
            processImageHSV(inputImagePath, backgroundImagePath, outputDir, h_lower, s_lower, v_lower, h_upper, s_upper, v_upper);
        }
    }

    else {
        std::cout << "wrong color scheme";
    }

    return 0;
}
