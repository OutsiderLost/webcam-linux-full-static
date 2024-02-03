// webcamcheck.cpp
#include <opencv2/opencv.hpp>

int main() {
    cv::VideoCapture cap(0); // Open the default camera (camera index 0)

    if (!cap.isOpened()) {
        std::cerr << "Error: Couldn't open the webcam." << std::endl;
        return -1;
    }

    cv::namedWindow("Webcam Feed", cv::WINDOW_NORMAL);

    while (true) {
        cv::Mat frame;
        cap >> frame; // Capture frame from the camera

        if (frame.empty()) {
            std::cerr << "Error: Couldn't capture a frame." << std::endl;
            break;
        }

        cv::imshow("Webcam Feed", frame);

        if (cv::waitKey(30) == 27) { // Press 'ESC' to exit
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}
