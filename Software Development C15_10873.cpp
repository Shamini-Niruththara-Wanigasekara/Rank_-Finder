#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Student {
    std::string name;
    int bioMarks;
    int physicsMarks;
    int chemMarks;
    int totalMarks;
    int classNumber;
};

class SchoolRankingSystem {
private:
    std::vector<Student> students;

public:
    void readMarksFromFile(const std::string& fileName) {
        std::ifstream file(fileName);

        if (!file) {
            std::cerr << "Error opening file: " << fileName << std::endl;
            return;
        }

        while (!file.eof()) {
            Student student;
            file >> student.name >> student.bioMarks >> student.physicsMarks >> student.chemMarks;
            student.totalMarks = student.bioMarks + student.physicsMarks + student.chemMarks;
            students.push_back(student);
        }

        file.close();
    }

    void calculateRanks() {
        // Calculate School Rank
        std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.totalMarks > b.totalMarks;
        });

        // Calculate Class Rank
        for (int i = 0; i < students.size(); ++i) {
            students[i].classNumber = i / 40 + 1;
        }
    }

    void printRanks() {
        std::cout << "Student\t\tTotal Marks\tSchool Rank\tClass Rank" << std::endl;

        for (const auto& student : students) {
            std::cout << student.name << "\t\t" << student.totalMarks << "\t\t"
                      << std::distance(students.begin(), std::find(students.begin(), students.end(), student)) + 1 << "\t\t"
                      << student.classNumber << std::endl;
        }
    }

    void writeRanksToFile(const std::string& fileName) {
        std::ofstream file(fileName);

        if (!file) {
            std::cerr << "Error opening file for writing: " << fileName << std::endl;
            return;
        }

        file << "Student\t\tTotal Marks\tSchool Rank\tClass Rank" << std::endl;

        for (const auto& student : students) {
            file << student.name << "\t\t" << student.totalMarks << "\t\t"
                 << std::distance(students.begin(), std::find(students.begin(), students.end(), student)) + 1 << "\t\t"
                 << student.classNumber << std::endl;
        }

        file.close();
    }
};

int main() {
    SchoolRankingSystem rankingSystem;

    // Assuming marks are stored in a file named "marks.txt"
    rankingSystem.readMarksFromFile("marks.txt");

    rankingSystem.calculateRanks();

    rankingSystem.printRanks();

    // Assuming output should be stored in a file named "ranks.txt"
    rankingSystem.writeRanksToFile("ranks.txt");

    return 0;
}
