#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

class Node {
public:
    int id;
    explicit Node(int _id) : id(_id) {}
    virtual void render() = 0;
    virtual cv::Mat process(const std::vector<cv::Mat>& inputs) = 0;
};
