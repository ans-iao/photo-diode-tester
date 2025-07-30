#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include "lsl_cpp.h"

int main() {
    auto window = sf::RenderWindow(sf::VideoMode({1280u, 720u}), "Blinking Background");

    lsl::stream_info info("PhotoDiodeTesterMarker", "Markers", 1, 0, lsl::cf_int32);
    lsl::stream_outlet outlet(info);
    std::vector<float> sample(1, 0);

    const auto dur_white = std::chrono::microseconds(1'000'000);
    const auto dur_black = std::chrono::microseconds(2'000'000);

    bool isWhite = true;
    auto next_frame_time = std::chrono::high_resolution_clock::now();

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        auto now = std::chrono::high_resolution_clock::now();
        if (now >= next_frame_time) {
            isWhite = !isWhite;

            window.clear(isWhite ? sf::Color::White : sf::Color::Black);
            window.display();

            sample[0] = isWhite ? 1 : 0;
            outlet.push_sample(sample);

            next_frame_time = next_frame_time + (isWhite ? dur_white : dur_black);

            std::cout << now << std::endl;
        }

        // std::this_thread::sleep_for(std::chrono::microseconds(1000));
    }

    return 0;
}
