#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include "lsl_cpp.h"

int main() {
    auto window = sf::RenderWindow(sf::VideoMode({1280u, 720u}), "Blinking Background");

    lsl::stream_info info("PhotoDiodeTesterMarker", "Markers", 1, 0, lsl::cf_int32);
    lsl::stream_outlet outlet(info);
    std::vector<float> sample(1, 0);

    auto next_frame_time = std::chrono::high_resolution_clock::now();
    int32_t sample_dur_us_white = 1000000;
    int32_t sample_dur_us_black = 2000000;

    bool isWhite = true;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // Toggle color
        isWhite = !isWhite;

        // Clear screen with chosen color
        if (isWhite) {
            window.clear(sf::Color::White);
            window.display();

            sample[0] = 1;
            outlet.push_sample(sample);

            next_frame_time += std::chrono::microseconds(sample_dur_us_white);
            std::this_thread::sleep_until(next_frame_time);
        } else {
            window.clear(sf::Color::Black);
            window.display();

            sample[0] = 0;
            outlet.push_sample(sample);

            next_frame_time += std::chrono::microseconds(sample_dur_us_black);
            std::this_thread::sleep_until(next_frame_time);
        }

        std::cout << std::chrono::high_resolution_clock::now() << std::endl;
    }

    return 0;
}
