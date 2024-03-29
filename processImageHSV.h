#ifndef PROCESS_IMAGE_HSV_H
#define PROCESS_IMAGE_HSV_H

#include <string>

void processImageHSV(const std::string& inputImagePath, const std::string& backgroundImagePath, const std::string& outputDir,
                     int h_lower, int s_lower, int v_lower,
                     int h_upper, int s_upper, int v_upper);

#endif // PROCESS_IMAGE_HSV_H
