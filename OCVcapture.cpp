#include <opencv2/opencv.hpp>

int main() {
    cv::VideoCapture screenCapture(0);

    if (!screenCapture.isOpened()) {
        std::cerr << "Error: Cannot open camera." << std::endl;
        return -1;
    }

    int frame_width = static_cast<int>(screenCapture.get(cv::CAP_PROP_FRAME_WIDTH));
    int frame_height = static_cast<int>(screenCapture.get(cv::CAP_PROP_FRAME_HEIGHT));
    cv::VideoWriter videoWriter("output.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, cv::Size(frame_width, frame_height));

    if (!videoWriter.isOpened()) {
        std::cerr << "Error: Cannot create video writer." << std::endl;
        return -1;
    }

    while (true) {
        cv::Mat frame;
        screenCapture >> frame;

        if (frame.empty())
            break;

        videoWriter.write(frame);

        if (cv::waitKey(30) >= 0)
            break;
    }

    screenCapture.release();
    videoWriter.release();

    return 0;
}
