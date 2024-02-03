#!/usr/bin/env python3

import cv2

# Initialize webcam
cap = cv2.VideoCapture(0)

while True:
    # Get frame from webcam
    ret, frame = cap.read()

    # If the frame was successfully acquired
    if ret:
        # Display frame
        cv2.imshow('Webcam', frame)

    # Exit by pressing the 'q' key
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Resizing
cap.release()
cv2.destroyAllWindows()
