#ifndef Q3_H
#define Q3_H

#include <cstddef>
#include <fstream>
#include <numeric>
#include <queue>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace q3 {
struct Flight {
    explicit Flight(const std::string &s) {
        auto split = [](const std::string &s) {
            std::vector<std::string> tokens;
            std::string token;
            std::istringstream iss{s};
            while (std::getline(iss, token, ',')) {
                tokens.push_back(token);
            }
            return tokens;
        };

        auto duration_time = [](const std::string &s) {
            std::regex pattern{R"((\d+)h(?:(\d+)m)?)"};
            std::smatch match;
            if (std::regex_search(s, match, pattern)) {
                std::size_t s = 0;
                s += std::stoi(match[1]) * 60;
                if (match[2].length() != 0) {
                    s += std::stoi(match[2]);
                }
                return s;
            }
            return 0UL;
        };

        std::regex pattern{R"(\d+- flight_number:([A-Z0-9]+) - duration:((?:(?:(?:\d)+h)(?:(?:\d+)m)?,?)) - connections:(\d+) - connection_times:((?:(?:(?:\d)+h)(?:(?:\d+)m)?,?)+) - price:(\d+))"};
        std::smatch match;
        if (std::regex_search(s, match, pattern)) {
            flight_number = match[1];
            duration = duration_time(match[2]);
            connections = std::stoul(match[3]);

            auto durs = split(match[4]);
            connection_times = 0;
            for (auto i : durs) {
                connection_times += duration_time(i);
            }

            price = std::stoul(match[5]);
        }
    }
    std::string flight_number;
    std::size_t duration;
    std::size_t connections;
    std::size_t connection_times;
    std::size_t price;
};

struct CompareFlight {
    bool operator()(const Flight &a, const Flight &b) {
        std::size_t sa = a.duration + a.connection_times + 3 * a.price;
        std::size_t sb = b.duration + b.connection_times + 3 * b.price;
        return sa > sb;
    }
};

inline std::priority_queue<Flight, std::vector<Flight>, CompareFlight> gather_flights(std::string filename) {
    std::ifstream ifs{filename};
    if (!ifs.is_open()) throw std::runtime_error{"failed to open file"};
    std::priority_queue<Flight, std::vector<Flight>, CompareFlight> ret;
    std::string line;
    while (std::getline(ifs, line)) {
        Flight f{line};
        ret.push(f);
    }
    return ret;
}
}  // namespace q3

#endif  // Q3_H