#include "BrightnessNode.h"
#include "imgui.h"

BrightnessNode::BrightnessNode(int _id) : Node(_id), brightness(0) {}

void BrightnessNode::render() {
    ImGui::Text("Brightness Node");
    ImGui::SliderInt("Brightness", &brightness, -100, 100);
}

cv::Mat BrightnessNode::process(const std::vector<cv::Mat>& inputs) {
    if (inputs.empty()) return {};
    cv::Mat output;
    inputs[0].convertTo(output, -1, 1, brightness);
    return output;
}
