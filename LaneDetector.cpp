#include "LaneDetector.hpp"
#include <cmath>

LaneDetector::LaneDetector()
    : prev_left_m(0.0), prev_left_b(0.0),
      prev_right_m(0.0), prev_right_b(0.0) {}

cv::Mat LaneDetector::regionOfInterest(const cv::Mat& edges, const std::vector<cv::Point>& pts) {
    cv::Mat mask = cv::Mat::zeros(edges.size(), edges.type());
    std::vector<std::vector<cv::Point>> polygons = {pts};
    cv::fillPoly(mask, polygons, cv::Scalar(255));
    
    cv::Mat maskedImage;
    cv::bitwise_and(edges, mask, maskedImage);
    return maskedImage;
}

void LaneDetector::averageAndDrawLines(cv::Mat& img, const std::vector<cv::Vec4i>& lines) {
    std::vector<double> left_m, left_b;
    std::vector<double> right_m, right_b;

    // SEPARATE INTO LEFT AND RIGHT LANES
    for (size_t i = 0; i < lines.size(); i++) {
        cv::Vec4i l = lines[i];
        double x1 = l[0], y1 = l[1], x2 = l[2], y2 = l[3];

        if (x1 == x2) continue; 

        double m = (y2 - y1) / (x2 - x1);
        double b = y1 - m * x1;

        if (std::abs(m) < 0.3 || std::abs(m) > 5.0) continue;

        if (m < 0) {
            left_m.push_back(m);
            left_b.push_back(b);
        } else {
            right_m.push_back(m);
            right_b.push_back(b);
        }
    }

    // AVERAGE THE LEFT LANE
    double avg_left_m = prev_left_m;
    double avg_left_b = prev_left_b;

    if (!left_m.empty()) {
        double sum_m = 0, sum_b = 0;
        for (size_t i = 0; i < left_m.size(); i++) {
            sum_m += left_m[i];
            sum_b += left_b[i];
        }
        avg_left_m = sum_m / left_m.size();
        avg_left_b = sum_b / left_b.size();

        if (prev_left_m != 0) {
            avg_left_m = prev_left_m * 0.8 + avg_left_m * 0.2;
            avg_left_b = prev_left_b * 0.8 + avg_left_b * 0.2;
        }
        prev_left_m = avg_left_m;
        prev_left_b = avg_left_b;
    }

    // AVERAGE THE RIGHT LANE
    double avg_right_m = prev_right_m;
    double avg_right_b = prev_right_b;

    if (!right_m.empty()) {
        double sum_m = 0, sum_b = 0;
        for (size_t i = 0; i < right_m.size(); i++) {
            sum_m += right_m[i];
            sum_b += right_b[i];
        }
        avg_right_m = sum_m / right_m.size();
        avg_right_b = sum_b / right_b.size();

        if (prev_right_m != 0) {
            avg_right_m = prev_right_m * 0.8 + avg_right_m * 0.2;
            avg_right_b = prev_right_b * 0.8 + avg_right_b * 0.2;
        }
        prev_right_m = avg_right_m;
        prev_right_b = avg_right_b;
    }

    // EXTRAPOLATION AND DRAWING
    int y1 = img.rows;                   
    int y2 = img.rows / 2 + 180;         

    int x1_left = 0, x2_left = 0;
    int x1_right = 0, x2_right = 0;
    bool draw_left = false, draw_right = false;

    if (avg_left_m != 0) {
        x1_left = (y1 - avg_left_b) / avg_left_m;
        x2_left = (y2 - avg_left_b) / avg_left_m;
        draw_left = true;
    }

    if (avg_right_m != 0) {
        x1_right = (y1 - avg_right_b) / avg_right_m;
        x2_right = (y2 - avg_right_b) / avg_right_m;
        draw_right = true;
    }

    // Draw the semi-transparent lane corridor
    if (draw_left && draw_right) {
        cv::Mat overlay;
        img.copyTo(overlay);

        std::vector<cv::Point> lane_polygon = {
            cv::Point(x1_left, y1),
            cv::Point(x2_left, y2),
            cv::Point(x2_right, y2),
            cv::Point(x1_right, y1)
        };

        cv::fillPoly(overlay, std::vector<std::vector<cv::Point>>{lane_polygon}, cv::Scalar(0, 255, 0));
        cv::addWeighted(overlay, 0.3, img, 0.7, 0, img);
    }

    // Draw the solid lane lines
    if (draw_left) cv::line(img, cv::Point(x1_left, y1), cv::Point(x2_left, y2), cv::Scalar(0, 255, 0), 7, cv::LINE_AA);
    if (draw_right) cv::line(img, cv::Point(x1_right, y1), cv::Point(x2_right, y2), cv::Scalar(0, 255, 0), 7, cv::LINE_AA);
}