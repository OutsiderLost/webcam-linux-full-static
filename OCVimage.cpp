#include <opencv2/opencv.hpp>

int main() {
    cv::VideoCapture cap(0);  // 0 is the first webcam: /dev/video0
    if (!cap.isOpened()) {
        std::cerr << "Error opening camera." << std::endl;
        return -1;
    }

    cv::Mat frame;
    cap >> frame;

    if (frame.empty()) {
        std::cerr << "Error capturing frame." << std::endl;
        return -1;
    }

    cv::imwrite("output.png", frame);

    std::cout << "Image saved to output.png" << std::endl;

    return 0;
}
