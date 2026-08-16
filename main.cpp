#include "LaneDetector.hpp"
#include <iostream>

int main() {
    std::string videoPath = "../test_video.mp4"; 
    cv::VideoCapture cap(videoPath); // Open the video file

    if (!cap.isOpened()) {
        std::cerr << "Error opening video file" << std::endl;
        return -1;
    }

    // Initialize the lane detection helper
    LaneDetector detector;

    cv::Mat frame, gray, blurred, edges, croppedEdges, resultFrame; 

    while (true) {
        cap >> frame; // Read the next frame
        if (frame.empty()) break; // Exit if the video ends

        frame.copyTo(resultFrame);
        int height = frame.rows;
        int width = frame.cols;

        // Define the Region of Interest (ROI) polygon dynamically
        std::vector<cv::Point> pts = {
            cv::Point(100, height - 200),                             
            cv::Point(width / 2 - 60, height / 2 + 150),         
            cv::Point(width / 2 + 40, height / 2 + 150),         
            cv::Point(width - 450, height - 200)                      
        };

        // Preprocessing: Grayscale, Blur, and Edge Detection
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::GaussianBlur(gray, blurred, cv::Size(5, 5), 0);
        cv::Canny(blurred, edges, 50, 150);
        
        // Apply the ROI mask to keep only the road area
        croppedEdges = detector.regionOfInterest(edges, pts);

        // Detect line segments using Probabilistic Hough Transform
        std::vector<cv::Vec4i> lines;
        cv::HoughLinesP(croppedEdges, lines, 1, CV_PI / 180, 25, 20, 150);

        // Calculate, smooth, and draw the final lanes on the result frame
        detector.averageAndDrawLines(resultFrame, lines);

        // Display the result
        cv::imshow("Lane Assist (Final)", resultFrame); 

        // Exit if the 'ESC' key (27) is pressed
        if (cv::waitKey(30) == 27) break; 
    }

    // Clean up
    cap.release();
    cv::destroyAllWindows();
    return 0;
}