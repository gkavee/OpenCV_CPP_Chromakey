#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>
#include <string>
#include "processImageHSV.h"
#include "processImageRGB.h"
#include "processVideo.h"
#include "addMask.h"

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

    std::string outputDir = "C:\\Users\\gkave\\CLionProjects\\OpenCV\\out\\";

    // создание каталога для выходных изображений если он не существует
    fs::create_directory(outputDir);

    std::cout << "method RGB/HSV: ";
    std::string method;
    std::cin >> method;
    if (method == "RGB" || method == "rgb") {
        int r, g, b, tolerance;
        std::cout << "input Red(0-255): ";
        std::cin >> r;
        std::cout << "input Green(0-255): ";
        std::cin >> g;
        std::cout << "input Blue(0-255): ";
        std::cin >> b;
        std::cout << "input tolerance(0-255): ";
        std::cin >> tolerance;
        Vec3b chromaKeyColor(r, g, b);

        std::string filterName;
        std::cout << "choose mask(: ";
        std::cin >> filterName;

        // обработка каждого изображения
        for (const auto& entry : fs::directory_iterator(inputDir)) {
            std::string inputImagePath = entry.path().string();
            std::string backgroundImagePath = backgroundDir + fs::path(inputImagePath).filename().string();
            processImageRGB(inputImagePath, backgroundImagePath, outputDir, chromaKeyColor, tolerance);
            std::string outputImagePath = outputDir + fs::path(inputImagePath).filename().string();
            addMask(outputImagePath, filterName);
        }
    }

    else if (method == "HSV" || method == "hsv") {
        int h_lower, s_lower, v_lower, h_upper, s_upper, v_upper;
        std::cout << "input Hue(lower)(0-180): ";
        std::cin >> h_lower;
        std::cout << "input Saturation(lower)(0-255): ";
        std::cin >> s_lower;
        std::cout << "input Value(lower)(0-255): ";
        std::cin >> v_lower;
        std::cout << "input Hue(upper)(0-180): ";
        std::cin >> h_upper;
        std::cout << "input Saturation(upper)(0-255): ";
        std::cin >> s_upper;
        std::cout << "input Value(upper)(0-255): ";
        std::cin >> v_upper;

        std::string filterName;
        std::cout << "choose mask(: ";
        std::cin >> filterName;

        // обработка каждого изображения
        for (const auto& entry : fs::directory_iterator(inputDir)) {
            std::string inputImagePath = entry.path().string();
            std::string backgroundImagePath = backgroundDir + fs::path(inputImagePath).filename().string();
            processImageHSV(inputImagePath, backgroundImagePath, outputDir, h_lower, s_lower, v_lower, h_upper, s_upper, v_upper);
            std::string outputImagePath = outputDir + fs::path(inputImagePath).filename().string();
            addMask(outputImagePath, filterName);
        }

        for (const auto& entry : fs::directory_iterator(inputDir)) {
            if (fs::is_regular_file(entry.path())) {
                std::string inputVideoPath = entry.path().string();

                std::string extension = entry.path().extension().string();
                if (extension == ".mp4") {
                    std::string filenameWithoutExtension = entry.path().stem().string(); //без расширения
                    std::string backgroundVideoPath = backgroundDir + filenameWithoutExtension + ".png";
                    processVideo(inputVideoPath, backgroundVideoPath,
                                 h_lower, s_lower, v_lower, h_upper, s_upper, v_upper);
                } else {
                    std::cout << "Skipping file: " << inputVideoPath << " (unsupported file type)" << std::endl;
                }
            }
        }
    }

    else {
        std::cout << "wrong method";
    }

    return 0;
}

