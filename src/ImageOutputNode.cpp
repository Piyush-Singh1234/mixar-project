#include "ImageOutputNode.h"
#include "imgui.h"

ImageOutputNode::ImageOutputNode(int _id) : Node(_id) {}

void ImageOutputNode::render() {
    ImGui::Text("Output Node");
}

cv::Mat ImageOutputNode::process(const std::vector<cv::Mat>& inputs) {
    if (inputs.empty()) return {};
    if (!inputs[0].empty()) {
        cv::imshow("Final Output", inputs[0]);
        cv::waitKey(1);
    }
    return inputs[0];
}
