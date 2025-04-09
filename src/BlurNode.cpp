#include "BlurNode.h"
#include "imgui.h"

BlurNode::BlurNode(int _id) : Node(_id), ksize(3) {}

void BlurNode::render() {
    ImGui::Text("Blur Node");
    ImGui::SliderInt("Kernel Size", &ksize, 1, 15);
    if (ksize % 2 == 0) ksize += 1; // Ensure odd
}

cv::Mat BlurNode::process(const std::vector<cv::Mat>& inputs) {
    if (inputs.empty() || inputs[0].empty()) {
        std::cout << "BlurNode: No input image provided!\n";
        return {};
    }

    cv::Mat output;
    cv::GaussianBlur(inputs[0], output, cv::Size(15, 15), 0);
    return output;
}
