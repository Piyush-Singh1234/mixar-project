#include "ImageInputNode.h"
#include "imgui.h"
#include "imnodes.h"                      // ✅ This is the missing piece!
#include <opencv2/opencv.hpp>
#include <iostream>

ImageInputNode::ImageInputNode(int id) : Node(id) {}

cv::Mat ImageInputNode::process(const std::vector<cv::Mat>&) {
    return image;
}

void ImageInputNode::render() {
    ImNodes::BeginNode(id);
    ImNodes::BeginNodeTitleBar();
    ImGui::Text("Image Input");
    ImNodes::EndNodeTitleBar();

    static char buffer[256];
    strncpy(buffer, path.c_str(), sizeof(buffer));
    if (ImGui::InputText("Image Path", buffer, sizeof(buffer))) {
        path = std::string(buffer);
        image = cv::imread(path);
        if (image.empty())
            std::cout << "Failed to load image: " << path << std::endl;
        else
            std::cout << "Loaded image: " << image.cols << "x" << image.rows << "\n";
    }

    if (!image.empty()) {
        ImGui::Text("Image loaded!");
    }

    ImNodes::BeginOutputAttribute(id + 1);
    ImGui::Text("Out");
    ImNodes::EndOutputAttribute();

    ImNodes::EndNode();
}
