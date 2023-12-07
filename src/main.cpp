#include "imgui.h"
#include "implot.h"
#include "imgui-SFML.h"
#include "Algorithm.h"
#include "BubbleSort.h"
#include "HeapSort.h"
#include "Variables.h"
#include "Thread.h"
#include "Setup.h"
//#include "Sound.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>
#include <numeric>
#include <random>
#include <iostream>


void draw(sf::RenderWindow& window) {
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

    float plotSizeHeight = ImGui::GetWindowContentRegionMax().y - ImGui::GetTextLineHeightWithSpacing() - 40;
    ImGui::Begin("Menu", nullptr, ImGuiWindowFlags_NoTitleBar);
    ImGui::PushItemWidth(130);
    if (ImGui::Combo("Algorithms", &Variables::option, Variables::algoNames, IM_ARRAYSIZE(Variables::algoNames))) {
        Setup::switchAlgo();
    }
    ImGui::PopItemWidth();
    ImGui::SameLine();
    if (ImGui::Button(!Variables::start ? "Start" : "Pause / Resume")) {
        Variables::start = !Variables::start;
    }


    ImGui::SameLine();
    if (ImGui::Button("Reset")) {
        Variables::reset = true;
    }
    ImGui::SameLine();
    ImGui::PushItemWidth(130);
    if (ImGui::SliderInt("Delay", &Variables::delayMs, 50, 200, "%d ms")) {
        
    }
    ImGui::PopItemWidth();
    ImGui::Separator();

    ImPlotAxisFlags axisFlags = ImPlotAxisFlags_NoGridLines | ImPlotAxisFlags_NoSideSwitch | ImPlotAxisFlags_NoHighlight;
    
    if (ImPlot::BeginPlot("Main Plot", { -1, plotSizeHeight }, ImPlotFlags_NoMenus | ImPlotFlags_NoMouseText | ImPlotFlags_NoTitle)) {
        axisFlags += ImPlotAxisFlags_NoTickLabels | ImPlotAxisFlags_NoTickMarks;
        ImPlot::SetupAxes(NULL, NULL, axisFlags, axisFlags);
        //ImPlot::SetupAxesLimits(0, 1, 0, 1, ImPlotCond_Always);
        ImPlot::PlotBars("Vertical", heights.data(), 20, 1.0);
        if (Variables::start) {
            ImPlot::PushStyleColor(ImPlotCol_Fill, { 1.f, 0.f, 0.f, 1.f });
            ImPlot::PlotBars("Cursor", &(heights[Variables::cursorPos]), 1, 0.3, Variables::cursorPos); // ImPlot::PlotBars(name, height of the bar,
            //Sound::playSound(heights[Variables::cursorPos]);
            ImPlot::PopStyleColor();
        }
        //else Sound::stopSound();
        ImPlot::EndPlot();
    }

    ImGui::End();
    
}


int main() {
    std::cout << "Print" << std::endl;
    sf::ContextSettings contextSettings;

    sf::RenderWindow window(sf::VideoMode(1290, 720), "Bubble Sort", sf::Style::Default, contextSettings);
    ImGui::SFML::Init(window);
    ImGui::CreateContext();
    ImPlot::CreateContext();
    Setup::initialize();
    std::cout << "Print" << std::endl;
    for (auto i : heights) {
        std::cout << i << std::endl;
    }

    sf::Clock deltaClock;


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            //std::cout << "In the main thread" << std::endl;
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed) {
                window.close();
                Variables::start = false;
                Variables::finished = true;
            }
        }
        ImGui::SFML::Update(window, deltaClock.restart());
        window.clear();
        draw(window);
        ImGui::SFML::Render(window);
        window.display();
    }
    
    ImPlot::DestroyContext();
    std::cout << "ImPlot Destroyed" << std::endl;
    ImGui::SFML::Shutdown();
    return 0;
    std::cout << "SFML Destroyed" << std::endl;
    
}