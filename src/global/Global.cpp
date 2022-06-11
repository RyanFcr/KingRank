#include "common/Global.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

#include <sstream>
using std::stringstream;

#include <random>

/**
 * @brief Normalize the position
 */
void Position::Normalize() {
    while (sceneX < 0) {
        sceneX += fieldSize;
        fieldX -= 1;
    }
    while (sceneX >= fieldSize) {
        sceneX -= fieldSize;
        fieldX += 1;
    }

    while (sceneY < 0) {
        sceneY += fieldSize;
        fieldY -= 1;
    }
    while (sceneY >= fieldSize) {
        sceneY -= fieldSize;
        fieldY += 1;
    }
}

void Position::GoUp() {
    sceneX++;
    Normalize();
}

void Position::GoDown() {
    sceneX--;
    Normalize();
}

void Position::GoLeft() {
    sceneY--;
    Normalize();
}

void Position::GoRight() {
    sceneY++;
    Normalize();
}

double NormalDistribution(double mu, double sigma) {
    std::random_device rd;
    std::default_random_engine rng{rd()};
    std::normal_distribution norm{mu, sigma};
    return std::max(norm(rng), 0.0);
}

std::string ReadFormatJson(std::ifstream& ifs) {
    stringstream json;
    char ch;

    while (ifs.get(ch).good()) {
        if (!isspace(ch))
            json << ch;
    }
    return json.str();
}

std::string RandomString(int len) {
    char tmp;							
    string buffer;					
    
    for (int i = 0; i < len; i++) {
        tmp = rand() % 26;
        if (i == 0)	
            tmp += 'A';
        else
            tmp += 'a';
        buffer += tmp;
    }
    return buffer;
}