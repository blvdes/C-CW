#include "Transcript.h"
#include <iomanip>

// Constructors
Grade::Grade(int term, int mark, const std::string& moduleCode) : term(term), mark(mark), moduleCode(moduleCode) {}
Transcript::Transcript(const std::string& id) : studentId(id) {}

// Adds student grade to transcript vector
void Transcript::addGrade(int term, const std::string& moduleCode, int mark) {
    grades.push_back(Grade(term, mark, moduleCode));
}

// Prints transcript based on filterTerm argument
void Transcript::printTranscript(std::ostream& out, const std::map<std::string, Module>& modules, int filterTerm) const {
    out << "Student ID: " << studentId << "\n";

    double totalWeightedScore = 0.0;
    int totalCredits = 0;

    // Maps all grades for term
    std::map<int, std::vector<const Grade*>> termGroups;
    for (const Grade& grade : grades) {
        if (filterTerm != 0 && grade.term != filterTerm) {
            continue;
        }
        termGroups[grade.term].push_back(&grade);
    }

    // Iterate over terms to calculate score
    for (const auto& termEntry : termGroups) {
        int currentTerm = termEntry.first;
        const auto& gradeList = termEntry.second;

        out << "  Term " << currentTerm << ":\n";

        double termWeightedScore = 0.0;
        int termCredits = 0;
        
        // Find module details for grade record
        for (const Grade* grade : gradeList) {
            auto moduleRecord = modules.find(grade -> moduleCode);
            
            if (moduleRecord != modules.end()) {
                const Module& module = moduleRecord->second;
                
                // Print module line
                out << "    " << module.code() << " " << module.name() << " (" << module.credits() << " credits): " << grade -> mark << "\n";

                // Accumulate marks and weighting for averages
                termWeightedScore += grade -> mark * module.credits();
                termCredits += module.credits();
            } 
        }

        // Calculates and prints term average
        if (termCredits > 0) {
            double termAvg = termWeightedScore / termCredits;
            out << "  Term Average: " << std::fixed << std::setprecision(2) << termAvg << "\n";
            
            totalWeightedScore += termWeightedScore;
            totalCredits += termCredits;
        }
    }

    // Calculates and prints overall average, if filterTerm undefined
    if (filterTerm == 0 && totalCredits > 0) {
        double overallAvg = totalWeightedScore / totalCredits;
        out << "  Overall Average: " << std::fixed << std::setprecision(2) << overallAvg << "\n";
    }
}