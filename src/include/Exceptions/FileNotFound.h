//
// Created by marc on 27/03/2018.
//

#ifndef MINILANG_COMPILER_FILENOTFOUND_H
#define MINILANG_COMPILER_FILENOTFOUND_H

#include <string>
#include <exception>

class FileNotFound : public std::exception {
public:
    FileNotFound();
    ~FileNotFound();
    const char * what() const;
};

#endif //MINILANG_COMPILER_FILENOTFOUND_H
