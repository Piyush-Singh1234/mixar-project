#pragma once
#include "Node.h"

class ImageOutputNode : public Node {
public:
    explicit ImageOutputNode(int _id);
    void render() override;
    cv::Mat process(const std::vector<cv::Mat>& inputs) override;
};
