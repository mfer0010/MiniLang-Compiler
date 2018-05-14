//
// Created by marc on 11/05/2018.
//

#include "Evaluation.h"

Evaluation::Evaluation() {}

Evaluation::~Evaluation() {}

Evaluation::Evaluation(std::string stringValue) {
    type = "STRING";
    this->stringValue = stringValue;
}

Evaluation::Evaluation(int intValue) {
    type = "INT";
    this->intValue = intValue;
}

Evaluation::Evaluation(double realValue) {
    type = "REAL";
    this->realValue = realValue;
}

Evaluation::Evaluation(bool boolValue) {
    type = "BOOL";
    this->boolValue = boolValue;
}

bool Evaluation::getBoolValue() {
    return boolValue;
}

int Evaluation::getIntValue() {
    return intValue;
}

double Evaluation::getRealValue() {
    return realValue;
}

std::string Evaluation::getStringVaue() {
    return stringValue;
}

void Evaluation::setBoolValue(bool boolValue) {
    type = "BOOL";
    this->boolValue = boolValue;
}

void Evaluation::setIntValue(int intValue) {
    type = "INT";
    this->intValue = intValue;
}

void Evaluation::setRealValue(double realValue) {
    type = "REAL";
    this->realValue = realValue;
}

void Evaluation::setStringValue(std::string stringValue) {
    type = "STRING";
    this->stringValue = stringValue;
}