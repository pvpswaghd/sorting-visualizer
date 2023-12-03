#include "imgui.h"
#include "implot.h"
#include "imgui-SFML.h"
#include <memory>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>
#include <numeric>
#include <random>
#include <iostream>
#include "../include/Thread.h"
#include "../include/Algorithm.h"

static int sort_pos = 0;
static int limit = 15;
int temp = 0;
std::mutex mtx;
static bool start = false;
static bool isReset = false;
static double lastPos = 0.0;
static int arrSize = 20;
static std::vector<int> heights(arrSize);
static std::atomic<bool> startSorting = false;
static int delayMs = 50;
static ImS8 cursorBar[1] = { 1 };

void resetSortVisualizer() {
    
    std::iota(heights.begin(), heights.end(), 1); // #include <numeric> for std::iota

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(heights.begin(), heights.end(), g);

    for (int i : heights) {
        std::cout << i << std::endl;
    }
    sort_pos = 0;
    limit = arrSize - 1;
}

void sort() {
    while (1) {
        std::cout << "Hello" << std::endl;
        while (startSorting) {
            if (lastPos < heights.size() - 1) {
                std::lock_guard<std::mutex> lock(mtx);
                if (heights[lastPos] < heights[lastPos + 1]) {
                    std::swap(heights[lastPos], heights[lastPos + 1]);
                }
                lastPos++;
                cursorBar[0] = heights[(int)lastPos];
            }
            std::cout << lastPos << " " << limit << std::endl;
            if (lastPos >= (double)limit) {
                lastPos = 0.0;
                cursorBar[0] = heights[0];
                std::cout << "Return" << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
        }
    }
}

void draw(sf::RenderWindow& window) {
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

    float plotSizeHeight = ImGui::GetWindowContentRegionMax().y - ImGui::GetTextLineHeightWithSpacing() - 40;
    ImGui::Begin("Menu", nullptr, ImGuiWindowFlags_NoTitleBar);

    if (ImGui::Button("Start")) {
        startSorting = true;
        start = true;
    }

    ImGui::SameLine();
    if (ImGui::Button("Pause / Resume")) {
        startSorting = !startSorting;
    }

    ImGui::SameLine();
    if (ImGui::Button("Reset")) {
        isReset = true;
    }
    ImGui::SameLine();

    if (ImGui::SliderInt("Delay", &delayMs, 50, 200, "%d ms")) {
        
    }

    ImGui::Separator();

    ImPlotAxisFlags axisFlags = ImPlotAxisFlags_NoGridLines | ImPlotAxisFlags_NoSideSwitch | ImPlotAxisFlags_NoHighlight;
    
    if (ImPlot::BeginPlot("Main Plot", { -1, plotSizeHeight }, ImPlotFlags_NoMenus | ImPlotFlags_NoMouseText | ImPlotFlags_NoTitle)) {
        axisFlags += ImPlotAxisFlags_NoTickLabels | ImPlotAxisFlags_NoTickMarks;
        ImPlot::SetupAxes(NULL, NULL, axisFlags, axisFlags);
        ImPlot::PlotBars("Vertical", heights.data(), arrSize, 1.0);
        if (start) {
            ImPlot::PushStyleColor(ImPlotCol_Fill, { 1.f, 0.f, 0.f, 1.f });
            ImPlot::PlotBars("Cursor", &cursorBar[0], 1, 0.3, lastPos); // ImPlot::PlotBars(name, height of the bar,
            ImPlot::PopStyleColor();
        }
        ImPlot::EndPlot();
    }

    ImGui::End();
    
}


int main() {
    sf::ContextSettings contextSettings;

    sf::RenderWindow window(sf::VideoMode(1290, 720), "Bubble Sort my ass :)", sf::Style::Default, contextSettings);
    ImGui::SFML::Init(window);
    ImGui::CreateContext();
    ImPlot::CreateContext();

    sf::Clock deltaClock;
    resetSortVisualizer();

    Thread sortThread((std::thread(sort)));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed) {
                ImPlot::DestroyContext();
                ImGui::DestroyContext();
                window.close();
                startSorting = false;
            }
        }
        ImGui::SFML::Update(window, deltaClock.restart());
        window.clear();
        draw(window);
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
    return 0;
}