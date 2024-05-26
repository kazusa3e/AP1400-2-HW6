#ifndef Q2_H
#define Q2_H

#include <algorithm>
#include <cstddef>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace q2 {
struct Patient {
    std::string name;
    int age;
    std::size_t smokes;
    std::size_t area_q;
    std::size_t alkhol;
};

inline std::vector<Patient> read_file(std::string filename) {
    std::ifstream ifs{filename};
    if (!ifs.is_open()) throw std::runtime_error{"file not found"};
    std::vector<Patient> ret;
    std::string line;
    std::getline(ifs, line);
    std::getline(ifs, line);
    while (std::getline(ifs, line)) {
        std::stringstream ss{line};
        std::vector<std::string> tokens;
        std::string token;
        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        if (tokens.size() != 6) continue;

        tokens.at(0).erase(std::remove_if(tokens.at(0).begin(), tokens.at(0).end(), ::isspace), tokens.at(0).end());
        tokens.at(1).erase(std::remove_if(tokens.at(1).begin(), tokens.at(1).end(), ::isspace), tokens.at(1).end());

        Patient p{
            tokens.at(0) + " " + tokens.at(1),
            std::stoi(tokens.at(2)),
            std::stoul(tokens.at(3)),
            std::stoul(tokens.at(4)),
            std::stoul(tokens.at(5))};
        ret.push_back(p);
    }
    ifs.close();
    return ret;
}

inline void sort(std::vector<Patient> &patients) {
    std::sort(patients.begin(), patients.end(), [](const Patient &a, const Patient &b) {
        std::size_t sa = 3 * a.age + 5 * a.smokes + 2 * a.area_q + 4 * a.alkhol;
        std::size_t sb = 3 * b.age + 5 * b.smokes + 2 * b.area_q + 4 * b.alkhol;
        return sa > sb;
    });
}

};  // namespace q2

#endif  // Q2_H