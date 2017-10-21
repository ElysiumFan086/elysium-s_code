Here I give an example of how to use seld-modified Caffe to extractor feature 
vector for a given image with pre-trained deep learning model.
A class is defined to conseal related functions and numbers to finish feature 
extracting work, and the input image format is cv::Mat in OpenCV, which is now 
widely used for image processing.

If you want to learn more about how feature extraction is worked inside Caffe 
architecture, you can check what is modified in Caffe source code:
    https://github.com/ElysiumFan086/caffe
