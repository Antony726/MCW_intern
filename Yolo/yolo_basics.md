# YOLO
- YOLO - <b>You Only Look Once</b>

## What is object detection?
- Object detection is a computer vision task that involves identifying and locating objects in images or videos. 
- One of the earliest successful attempts to address the object detection problem using deep learning was the R-CNN (Regions with CNN features) model

- Object detection algorithms are broadly <b>classified into two categories</b> based on how many times the same input image is passed through a network.

## Single-shot object detection
- Single-shot object detection uses a single pass of the input image to make predictions about the presence and location of objects in the image.
- It processes an entire image in a single pass, making them computationally efficient.
- single-shot object detection is generally less accurate than other methods, and it’s less effective in detecting small objects.
- Such algorithms can be used to detect objects in real time in resource-constrained environments.
- <b>YOLO is a single-shot detector that uses a fully convolutional neural network (CNN) to process an image.</b>

## Two-shot object detection
