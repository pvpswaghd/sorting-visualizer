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
#include <chrono>
#include <thread>

static int sort_pos = 0;
static int limit = 15;
int temp = 0;
static bool isPaused = false;
static bool isReset = false;
static double lastPos = 0.0;
static int arrSize = 20;
static std::vector<int> heights(arrSize);
sf::Clock sortClock;
sf::Time delay = sf::milliseconds(50);
sf::Time lastUpdate = sortClock.getElapsedTime();

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

void draw(sf::RenderWindow& window) {
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

    float plotSizeHeight = ImGui::GetWindowContentRegionMax().y - ImGui::GetTextLineHeightWithSpacing() - 40;
    ImGui::Begin("Menu", nullptr, ImGuiWindowFlags_NoTitleBar);

    if (ImGui::Button("Pause / Resume")) {
        isPaused = !isPaused;
    }

    ImGui::SameLine();
    if (ImGui::Button("Reset")) {
        isReset = true;
    }
    ImGui::SameLine();

    int delayMs = delay.asMilliseconds();
    if (ImGui::SliderInt("Delay", &delayMs, 50, 200, "%d ms")) {
        delay = sf::milliseconds(delayMs);
    }

    ImGui::Separator();

    ImPlotAxisFlags axisFlags = ImPlotAxisFlags_NoGridLines | ImPlotAxisFlags_NoSideSwitch | ImPlotAxisFlags_NoHighlight;
    static ImS8 cursorBar[1] = { 1 };
    if (ImPlot::BeginPlot("Main Plot", { -1, plotSizeHeight }, ImPlotFlags_NoMenus | ImPlotFlags_NoMouseText)) {
        axisFlags += ImPlotAxisFlags_NoTickLabels | ImPlotAxisFlags_NoTickMarks;
        ImPlot::SetupAxes(NULL, NULL, axisFlags, axisFlags);
        ImPlot::PlotBars("Vertical", heights.data(), arrSize, 1.0);
        ImPlot::PushStyleColor(ImPlotCol_Fill, { 1.f, 0.f, 0.f, 1.f });
        ImPlot::PlotBars("Cursor", &cursorBar[0], 1, 0.3, lastPos); // ImPlot::PlotBars(name, height of the bar,
        ImPlot::PopStyleColor();
        ImPlot::EndPlot();
    }
    if (sortClock.getElapsedTime() - lastUpdate >= delay) {

        if (lastPos < heights.size() - 1) {
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
        lastUpdate = sortClock.getElapsedTime();
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

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed) {
                ImPlot::DestroyContext();
                ImGui::DestroyContext();
                window.close();
                return 0;
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