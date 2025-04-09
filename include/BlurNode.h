#pragma once
#include "Node.h"

class BlurNode : public Node {
public:
    int ksize;
    explicit BlurNode(int _id);
    void render() override;
    cv::Mat process(const std::vector<cv::Mat>& inputs) override;
};
