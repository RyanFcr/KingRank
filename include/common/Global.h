#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "Config.h"
#include "Macro.h"

#include <fstream>

const int maxTerminalLenghth = 50;

/// Text Type
const int plain = RESET_;
const int request = CYAN_;
const int reward = YELLOW_;
const int warning = RED_;
const int buff = GREEN_;
const int title = YELLOW_;

/// Error Type
enum KRerror { OPEN_FILE_FAIL, HAS_PARSE_ERROR, UNKNOWN_ITEM };

/// Position Type
struct Position {
    int fieldX;
    int fieldY;
    int sceneX;
    int sceneY;

    void Normalize();
    void GoUp();
    void GoDown();
    void GoLeft();
    void GoRight();

    template <typename Writer>
    void Serialize(Writer& writer) const {
        writer.StartObject();

        writer.String("fieldX");
        writer.Int(fieldX);
        writer.String("fieldY");
        writer.Int(fieldY);
        writer.String("sceneX");
        writer.Int(sceneX);
        writer.String("sceneY");
        writer.Int(sceneY);

        writer.EndObject();
    }
};

/// FieldPosition
struct FieldPosition {
    int fieldX;
    int fieldY;

    template <typename Writer>
    void Serialize(Writer& writer) const {
        writer.StartObject();

        writer.String("fieldX");
        writer.Int(fieldX);
        writer.String("fieldY");
        writer.Int(fieldY);

        writer.EndObject();
    }
};

/// possibility
/** 
 * @brief Generate a possibility according to normal distribution 
 * @param mu expectation
 * @param sigma variance
 * @return possibility
 */
double NormalDistribution(double mu, double sigma);

/// read format json
/**
 * @brief Read from file and generate a json string
 * @param ifs json file
 * @return string: json string
 */
std::string ReadFormatJson(std::ifstream& ifs);
#endif