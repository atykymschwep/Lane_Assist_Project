#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

class LaneDetector {
public:
    LaneDetector();

    // Create a trapezoidal region of interest mask
    cv::Mat regionOfInterest(const cv::Mat& edges, const std::vector<cv::Point>& pts);

    // Average, smooth, and draw the detected lane lines
    void averageAndDrawLines(cv::Mat& img, const std::vector<cv::Vec4i>& lines);

private:
    // Program memory for smooth exponential smoothing between frames
    double prev_left_m;
    double prev_left_b;
    double prev_right_m;
    double prev_right_b;
};