// ImGui and ImNodes core
#include "imgui.h"
#include "imnodes.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// OpenGL / GLFW
#include <GLFW/glfw3.h>

// OpenCV
#include <opencv2/opencv.hpp>

// Node system headers
#include "ImageInputNode.h"
#include "BlurNode.h"
#include "BrightnessNode.h"
#include "ImageOutputNode.h"

// Optional: C++ std includes
#include <iostream>
#include <string>

#include <vector>
#include <memory>

// for std::pair
#include <utility>  

static int id_counter = 1;
std::vector<std::unique_ptr<Node>> nodes;
static ImageInputNode input(id_counter++);
static BlurNode blur(id_counter++);
static BrightnessNode bright(id_counter++);
static ImageOutputNode output(id_counter++);


int main() {
    // Init GLFW
    if (!glfwInit()) return -1;

    // OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Mixar Node Editor", NULL, NULL);
    if (!window) return -1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Init ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();

    // Init ImNodes
    ImNodes::CreateContext();

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // if (ImGui::BeginMenuBar()) {
        //     if (ImGui::BeginMenu("Add Node")) {
        //         if (ImGui::MenuItem("Blur Node")) {
        //             nodes.push_back(std::make_unique<BlurNode>(id_counter++));
        //         }
        //         if (ImGui::MenuItem("Brightness Node")) {
        //             nodes.push_back(std::make_unique<BrightnessNode>(id_counter++));
        //         }
        //         if (ImGui::MenuItem("Output Node")) {
        //             nodes.push_back(std::make_unique<ImageOutputNode>(id_counter++));
        //         }
        //         ImGui::EndMenu();
        //     }
        //     ImGui::EndMenuBar();
        // }
        
        // ImGui::Begin("Node Editor");
        ImGui::Begin("Node Editor", nullptr, ImGuiWindowFlags_MenuBar);

        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("Add Node")) {
                if (ImGui::MenuItem("Blur Node")) {
                    nodes.push_back(std::make_unique<BlurNode>(id_counter++));
                }
                if (ImGui::MenuItem("Brightness Node")) {
                    nodes.push_back(std::make_unique<BrightnessNode>(id_counter++));
                }
                if (ImGui::MenuItem("Output Node")) {
                    nodes.push_back(std::make_unique<ImageOutputNode>(id_counter++));
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
        ImNodes::BeginNodeEditor();

        // input.render();
        // blur.render();
        // bright.render();
        // output.render();
        for (auto& node : nodes) {
            node->render();
        }
        

        cv::Mat img1 = input.process({});
        if (!img1.empty()) {
            cv::Mat img2 = blur.process({img1});
            cv::Mat img3 = bright.process({img2});
            output.process({img3});
        } else {
            std::cout << "[Info] No valid image loaded yet.\n";
        }


        ImNodes::EndNodeEditor();
        ImGui::End();

        // Render
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImNodes::DestroyContext();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
