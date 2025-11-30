#include "Module.h"
#include "Transcript.h"
#include "main.h"

int main() {
    // Map containers for lookup
    map<string, Module> modules;
    map<string, Transcript> students;

    // Load modules from file, assuming all columns have values
    ifstream moduleFile("modules.txt");
    string code, name;
    int credits;
    while (moduleFile >> code >> credits >> name) {
        // Upsert module
        modules.emplace(code, Module(code, name, credits));
    }

    // Load grades from file, assuming all columns have values
    ifstream gradeFile("grades.txt");
    string studentId, moduleCode;
    int term, mark;
    while (gradeFile >> studentId >> term >> moduleCode >> mark) {
        auto search = students.find(studentId);
        // Upsert transcript
        if (search == students.end()) {
            auto result = students.emplace(studentId, Transcript(studentId));
            search = result.first;
        }
        // Add grade
        search -> second.addGrade(term, moduleCode, mark);
    }

    // Load requests from file, using istringstream for optional term arg
    ifstream requestsFile("requests.txt");
    string line;
    while (getline(requestsFile, line)) {
        if (line.empty()) continue;

        istringstream ss(line);
        string requestID;
        int requestTerm = 0;

        ss >> requestID;
        if (ss >> requestTerm) { 
        }

        // Find student and print transcript based on term request
        auto search = students.find(requestID);
        if (search != students.end()) {
            search -> second.printTranscript(modules, requestTerm);
        }
    }

    return 0;
}