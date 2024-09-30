#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

const int MAX_OFFICERS = 100; // Maximum number of officers

class Officer {
private:
    std::string name;
    std::string designation;
    std::string email;
    std::string phone;
    std::string room;
    std::string adminClass;

public:
    Officer() : name(""), designation(""), email(""), phone(""), room(""), adminClass("") {}

    void setOfficerDetails(const std::string& name, const std::string& designation, const std::string& email,
                           const std::string& phone, const std::string& room, const std::string& adminClass) {
        this->name = name;
        this->designation = designation;
        this->email = email;
        this->phone = phone;
        this->room = room;
        this->adminClass = adminClass;
    }

    std::string getName() const {
        return name;
    }

    void printDetails() const {
        std::cout << "Designation: " << designation << "\n"
                  << "Room: " << room << "\n"
                  << "Phone: " << phone << "\n"
                  << "Email: " << email << "\n";
    }
};

class OfficerDatabase {
private:
    Officer officers[MAX_OFFICERS];
    int officerCount;

public:
    OfficerDatabase() : officerCount(0) {}

    void loadOfficers(const std::string& filename) {
        std::ifstream file(filename);
        std::string line;

        if (!file.is_open()) {
            std::cerr << "Could not open the file: " << filename << std::endl;
            return;
        }

        while (std::getline(file, line) && officerCount < MAX_OFFICERS) {
            std::stringstream ss(line);
            std::string name, designation, email, phone, room, adminClass;

            std::getline(ss, name, ',');
            std::getline(ss, designation, ',');
            std::getline(ss, email, ',');
            std::getline(ss, phone, ',');
            std::getline(ss, room, ',');
            std::getline(ss, adminClass);

            officers[officerCount].setOfficerDetails(name, designation, email, phone, room, adminClass);
            officerCount++;
        }

        file.close();
    }

    void fetchOfficerDetails(const std::string& name) const {
        for (int i = 0; i < officerCount; i++) {
            if (officers[i].getName() == name) {
                officers[i].printDetails();
                return;
            }
        }
        std::cout << "Officer not found!" << std::endl;
    }
};

int main() {
    OfficerDatabase database;
    database.loadOfficers("officers.csv"); // Ensure your CSV file is named 'officers.csv'

    std::string name;
    std::cout << "Enter the name of the officer: ";
    std::getline(std::cin, name);

    database.fetchOfficerDetails(name);
    return 0;
}

