#ifndef TRANSCRIPT_H
#define TRANSCRIPT_H

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "Module.h"

// Grade class container
class Grade {
public:
    int term;
    int mark;
    std::string moduleCode;

    // Constructor type definition
    Grade(int term, int mark, const std::string& moduleCode);
};

// Student transcript container
class Transcript {
    std::string studentId;
    std::vector<Grade> grades;

public:
    // Constructor and accessor type definitions
    Transcript(const std::string& transcriptId);
    void addGrade(int term, const std::string& moduleCode, int mark);
    void printTranscript(const std::map<std::string, Module>& modules, int term = 0) const;
};

#endif