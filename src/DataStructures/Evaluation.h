//
// Created by marc on 11/05/2018.
//

#ifndef MINILANG_COMPILER_EVALUATION_H
#define MINILANG_COMPILER_EVALUATION_H

#include <string>

class Evaluation {
private:
    std::string stringValue = "";
    int intValue = 0;
    double realValue = 0;
    bool boolValue = false;

public:
    //type of evaluation, to be used when storing ints into reals
    std::string type;

    //constructors
    Evaluation();
    Evaluation(std::string stringValue);
    Evaluation(int intValue);
    Evaluation(double realValue);
    Evaluation(bool boolValue);
    ~Evaluation();

    //getter methods
    std::string getStringVaue();
    int getIntValue();
    double getRealValue();
    bool getBoolValue();

    //setter methods
    void setStringValue(std::string stringValue);
    void setIntValue(int intValue);
    void setRealValue(double realValue);
    void setBoolValue(bool boolValue);
};


#endif //MINILANG_COMPILER_EVALUATION_H
