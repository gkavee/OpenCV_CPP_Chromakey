#ifndef PROCESS_IMAGE_RGB_H
#define PROCESS_IMAGE_RGB_H

#include <string>
#include <opencv2/opencv.hpp>

void processImageRGB(const std::string& inputImagePath, const std::string& backgroundImagePath, const std::string& outputDir,
                     const cv::Vec3b& chromaKeyColor, int tolerance);

#endif // PROCESS_IMAGE_RGB_H
