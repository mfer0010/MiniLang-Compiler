//
// Created by marc on 27/03/2018.
//


#include "../../include/Exceptions/FileNotFound.h"

FileNotFound::FileNotFound() {}

FileNotFound::~FileNotFound() {}

const char* FileNotFound::what() const throw() {
    return "Error: File Not Found";
}