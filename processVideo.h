#ifndef PROCESS_VIDEO_H
#define PROCESS_VIDEO_H

#include <string>
#include <opencv2/opencv.hpp>

void processVideo(const std::string& videoPath, const std::string& backgroundPath,
                  int hueLower, int saturationLower, int valueLower,
                  int hueUpper, int saturationUpper, int valueUpper);

#endif