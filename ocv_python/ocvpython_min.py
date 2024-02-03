#!/usr/bin/env python3

# import cv2
from cv2 import VideoCapture, imshow, waitKey, destroyAllWindows

# Initialize webcam
# cap = cv2.VideoCapture(0)
cap = VideoCapture(0)

while True:
    # Get frame from webcam
    ret, frame = cap.read()

    # If the frame was successfully acquired
    if ret:
        # Display frame
        # cv2.imshow('Webcam', frame)
        imshow('Webcam', frame)

    # Exit by pressing the 'q' key
    # if cv2.waitKey(1) & 0xFF == ord('q'):
    if waitKey(1) & 0xFF == ord('q'):
        break

# Resizing
cap.release()
# cv2.destroyAllWindows()
destroyAllWindows()
