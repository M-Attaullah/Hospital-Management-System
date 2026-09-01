#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <map>
#include <string>
#include <stack>
#include <fstream>
#include <iomanip>
#include <conio.h>  // For console input/output manipulation
#include <sstream>  // For stringstream
#include <ctime>    // For time functions

using namespace std;

// Function to get current date and time as a string
string getCurrentDateTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << 1900 + ltm->tm_year << "-"
        << 1 + ltm->tm_mon << "-"
        << ltm->tm_mday << " "
        << ltm->tm_hour << ":"
        << ltm->tm_min << ":"
        << ltm->tm_sec;
    return ss.str();
}

// Patient Class
class Patient {
private:
    string id;
    string name;
    int age;
    string medicalHistory;

public:
    // Default Constructor
    Patient() : id(""), name(""), age(0), medicalHistory("") {}

    // Parameterized Constructor
    Patient(string patientId, string patientName, int patientAge, string history)
        : id(patientId), name(patientName), age(patientAge), medicalHistory(history) {
    }

    // Accessors
    string getId() const { return id; }
    string getName() const { return name; }
    int getAge() const { return age; }
    string getMedicalHistory() const { return medicalHistory; }

    // Mutators
    void setId(const string& patientId) { id = patientId; }
    void setName(const string& patientName) { name = patientName; }
    void setAge(int patientAge) { age = patientAge; }
    void setMedicalHistory(const string& history) { medicalHistory = history; }

    // File I/O
    void saveToFile(ofstream& outFile) const {
        outFile << id << "," << name << "," << age << "," << medicalHistory << endl;
    }

    static Patient loadFromFile(const string& data) {
        stringstream ss(data);
        string patientId, patientName, medicalHistory;
        int patientAge;

        getline(ss, patientId, ',');
        getline(ss, patientName, ',');
        ss >> patientAge;
        getline(ss, medicalHistory);
        getline(ss, medicalHistory, ',');

        return Patient(patientId, patientName, patientAge, medicalHistory);
    }
};

// Emergency Class
struct Emergency {
    int severity;  // Lower value means higher priority
    string patientId;

    bool operator<(const Emergency& e) const {
        return severity > e.severity;  // Higher priority for lower severity numbers
    }
};

// Doctor Class
class Doctor {
private:
    string id;
    string name;
    bool isEmergencyAvailable;
    int emergencyCasesTreated; // Counter for emergency cases treated
    int appointmentCasesTreated; // Counter for appointment cases treated

public:
    Doctor() : id(""), name(""), isEmergencyAvailable(false), emergencyCasesTreated(0), appointmentCasesTreated(0) {}

    Doctor(string doctorId, string doctorName, bool emergencyAvailable)
        : id(doctorId), name(doctorName), isEmergencyAvailable(emergencyAvailable), emergencyCasesTreated(0), appointmentCasesTreated(0) {
    }

    // Accessors
    string getId() const { return id; }
    string getName() const { return name; }
    bool isAvailableForEmergency() const { return isEmergencyAvailable; }
    int getEmergencyCasesTreated() const { return emergencyCasesTreated; }
    int getAppointmentCasesTreated() const { return appointmentCasesTreated; }

    // Mutators
    void setId(const string& doctorId) { id = doctorId; }
    void setName(const string& doctorName) { name = doctorName; }
    void setEmergencyAvailability(bool availability) { isEmergencyAvailable = availability; }
    void incrementEmergencyCasesTreated() { emergencyCasesTreated++; }
    void incrementAppointmentCasesTreated() { appointmentCasesTreated++; }

    // File I/O
    void saveToFile(ofstream& outFile) const {
        outFile << id << "," << name << "," << (isEmergencyAvailable ? "1" : "0") << "," << emergencyCasesTreated << "," << appointmentCasesTreated << endl;
    }

    static Doctor loadFromFile(const string& data) {
        stringstream ss(data);
        string doctorId, doctorName;
        bool isEmergencyAvailable;
        int emergencyCasesTreated, appointmentCasesTreated;

        getline(ss, doctorId, ',');
        getline(ss, doctorName, ',');
        string availability;
        getline(ss, availability, ',');
        isEmergencyAvailable = (availability == "1");
        ss >> emergencyCasesTreated;
        ss.ignore();
        ss >> appointmentCasesTreated;

        return Doctor(doctorId, doctorName, isEmergencyAvailable);
    }
};

// HospitalManagementSystem Class
class HospitalManagementSystem {
private:
    map<string, Patient> patientDatabase;  // Patient records
    map<string, Doctor> doctorDatabase;    // Doctor records
    priority_queue<Emergency> emergencyQueue;  // Emergency cases
    queue<string> appointmentQueue;            // Normal appointments
    stack<string> treatmentHistory;            // Treatment history

    Doctor* emergencyDoctor;

public:
    HospitalManagementSystem() : emergencyDoctor(NULL) {}

    // Register a patient
    void registerPatient() {
        string patientId, patientName, medicalHistory;
        int patientAge;
        cout << "\t\t\t\t\t\t _________________________________________________________________ \n";
        cout << "\t\t\t\t\t\t|                                           	                  |\n";
        cout << "\t\t\t\t\t\t|             Enter Patient Details:                              |\n";
        cout << "\t\t\t\t\t\t|_________________________________________________________________|\n\n";

        cout << "Enter patient ID: ";
        cin >> patientId;

        if (patientDatabase.find(patientId) != patientDatabase.end()) {
            cout << "Patient with this ID already exists.\n";
            return;
        }

        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, patientName);
        cout << "Enter Age: ";
        cin >> patientAge;
        cout << "Enter Medical History: ";
        cin.ignore();
        getline(cin, medicalHistory);

        Patient p(patientId, patientName, patientAge, medicalHistory);
        patientDatabase[patientId] = p;

        cout << "\nPatient registered successfully!\n";
        cout << "***************************\n";
    }

    // Register a doctor
    void registerDoctor() {
        string doctorId, doctorName;
        bool emergencyAvailable;

        cout << "\t\t\t\t\t\t _________________________________________________________________ \n";
        cout << "\t\t\t\t\t\t|                                           	                  |\n";
        cout << "\t\t\t\t\t\t|             Enter Doctors Details:                              |\n";
        cout << "\t\t\t\t\t\t|_________________________________________________________________|\n\n";

        cout << "\nEnter Doctor ID: ";
        cin >> doctorId;
        cout << "Enter Doctor Name: ";
        cin.ignore();
        getline(cin, doctorName);
        cout << "Is Doctor available for emergency 24/7? (1 for Yes, 0 for No): ";
        cin >> emergencyAvailable;

        Doctor doctor(doctorId, doctorName, emergencyAvailable);
        doctorDatabase[doctorId] = doctor;

        if (emergencyAvailable && emergencyDoctor == NULL) {
            emergencyDoctor = &doctor;  // Assign the first available doctor as emergency doctor
        }

        cout << "\nDoctor registered successfully!\n";
        cout << "***************************\n";
    }

    // View all patients
    void viewPatients() {
        if (patientDatabase.empty()) {
            cout << "\nNo patients found.\n";
            return;
        }

        cout << "\t\t\t\t\t\t _________________________________________________________________ \n";
        cout << "\t\t\t\t\t\t|                                           	                  |\n";
        cout << "\t\t\t\t\t\t|             Patients Records                                    |\n";
        cout << "\t\t\t\t\t\t|_________________________________________________________________|\n\n";
        cout << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Age" << setw(30) << "Medical History\n";
        cout << string(70, '-') << endl;

        for (const auto& pair : patientDatabase) {
            cout << setw(10) << pair.second.getId()
                << setw(20) << pair.second.getName()
                << setw(10) << pair.second.getAge()
                << setw(30) << pair.second.getMedicalHistory() << endl;
        }
        cout << "\n***************************\n";
    }

    // View all doctors
    void viewDoctors() {
        if (doctorDatabase.empty()) {
            cout << "\nNo doctors found.\n";
            return;
        }

        cout << "\t\t\t\t\t\t _________________________________________________________________ \n";
        cout << "\t\t\t\t\t\t|                                           	                  |\n";
        cout << "\t\t\t\t\t\t|             Doctors Records                                     |\n";
        cout << "\t\t\t\t\t\t|_________________________________________________________________|\n\n";
        cout << setw(10) << "ID" << setw(20) << "Name" << setw(25) << "Emergency Availability\n";
        cout << string(60, '-') << endl;

        for (const auto& pair : doctorDatabase) {
            cout << setw(10) << pair.second.getId()
                << setw(20) << pair.second.getName()
                << setw(25) << (pair.second.isAvailableForEmergency() ? "Yes" : "No") << endl;
        }
        cout << "\n***************************\n";
    }

    // Handle emergency case
    void handleEmergency() {
        string patientId;
        int severity;
        cout << "\t\t\t\t\t\t __________________________________________________________________\n";
        cout << "\t\t\t\t\t\t|                                           	                  |\n";
        cout << "\t\t\t\t\t\t|             Emergency Case                                      |\n";
        cout << "\t\t\t\t\t\t|_________________________________________________________________|\n\n";
        cout << "\nEnter Patient ID for emergency: ";
        cin >> patientId;

        if (patientDatabase.find(patientId) == patientDatabase.end()) {
            cout << "\nPatient not found in the database.\n";
            return;
        }

        cout << "Enter Severity Level (1-10, 1 is highest priority): ";
        cin >> severity;

        Emergency emergency;
        emergency.severity = severity;
        emergency.patientId = patientId;

        emergencyQueue.push(emergency);
        cout << "\nEmergency case added successfully!\n";
        cout << "\n***************************\n";
    }

    // Treat an emergency case
    void treatEmergency() {
        if (emergencyQueue.empty()) {
            cout << "\nNo emergency cases in the queue.\n";
            return;
        }

        if (emergencyDoctor == NULL || emergencyDoctor->getEmergencyCasesTreated() >= 2) {
            // Find an available emergency doctor
            emergencyDoctor = NULL;
            for (auto& pair : doctorDatabase) {
                if (pair.second.isAvailableForEmergency() && pair.second.getEmergencyCasesTreated() < 2) {
                    emergencyDoctor = &pair.second;
                    break;
                }
            }

            if (emergencyDoctor == NULL) {
                cout << "\nNo emergency doctor available.\n";
                return;
            }
        }

        Emergency emergency = emergencyQueue.top();
        emergencyQueue.pop();

        // Get current date and time
        string dt = getCurrentDateTime();

        // Display patient details
        Patient patient = patientDatabase[emergency.patientId];
        cout << "\nEmergency case treated successfully by Dr. " << emergencyDoctor->getName() << "\n";
        cout << "Patient Details:\n";
        cout << "ID: " << patient.getId() << "\n";
        cout << "Name: " << patient.getName() << "\n";
        cout << "Age: " << patient.getAge() << "\n";
        cout << "Medical History: " << patient.getMedicalHistory() << "\n";
        cout << "Treatment Date and Time: " << dt;
        cout << "\n***************************\n";

        // Save treatment details to history
        stringstream treatmentDetails;
        treatmentDetails << patient.getId() << "," << patient.getName() << "," << patient.getAge() << "," << patient.getMedicalHistory() << ","
            << emergencyDoctor->getId() << "," << emergencyDoctor->getName() << "," << dt;
        treatmentHistory.push(treatmentDetails.str());

        // Increment the emergency cases treated counter
        emergencyDoctor->incrementEmergencyCasesTreated();
        if (emergencyDoctor->getEmergencyCasesTreated() >= 2) {
            // Remove the doctor from the database
            doctorDatabase.erase(emergencyDoctor->getId());
            emergencyDoctor = NULL;
        }
    }

    // Book an appointment for a general patient
    void bookAppointment() {
        string patientId;
        cout << "\t\t\t\t\t\t _________________________________________________________________ \n";
        cout << "\t\t\t\t\t\t|                                           	                  |\n";
        cout << "\t\t\t\t\t\t|             Book Appointment                                    |\n";
        cout << "\t\t\t\t\t\t|_________________________________________________________________|\n\n";
        cout << "\nEnter Patient ID for appointment: ";
        cin >> patientId;

        if (patientDatabase.find(patientId) == patientDatabase.end()) {
            cout << "\nPatient not found in the database.\n";
            return;
        }

        appointmentQueue.push(patientId);
        cout << "\nAppointment booked successfully!\n";
        cout << "\n***************************\n";
    }

    // Treat a general patient appointment
    void treatAppointment() {
        if (appointmentQueue.empty()) {
            cout << "\nNo appointments in the queue.\n";
            return;
        }

        string patientId = appointmentQueue.front();
        appointmentQueue.pop();

        Doctor* assignedDoctor = nullptr;

        // Find an available doctor
        for (auto& pair : doctorDatabase) {
            if (pair.second.getAppointmentCasesTreated() < 4) {
                assignedDoctor = &pair.second;
                break;
            }
        }

        if (assignedDoctor == nullptr) {
            cout << "\nNo available doctor to treat the appointment.\n";
            return;
        }

        // Get current date and time
        string dt = getCurrentDateTime();

        // Display patient details
        Patient patient = patientDatabase[patientId];
        cout << "\nAppointment treated successfully by Dr. " << assignedDoctor->getName() << "\n";
        cout << "Patient Details:\n";
        cout << "ID: " << patient.getId() << "\n";
        cout << "Name: " << patient.getName() << "\n";
        cout << "Age: " << patient.getAge() << "\n";
        cout << "Medical History: " << patient.getMedicalHistory() << "\n";
        cout << "Treatment Date and Time: " << dt;
        cout << "\n***************************\n";

        // Save treatment details to history
        stringstream treatmentDetails;
        treatmentDetails << patient.getId() << "," << patient.getName() << "," << patient.getAge() << "," << patient.getMedicalHistory() << ","
            << assignedDoctor->getId() << "," << assignedDoctor->getName() << "," << dt;
        treatmentHistory.push(treatmentDetails.str());

        // Increment the appointment cases treated counter
        assignedDoctor->incrementAppointmentCasesTreated();
        if (assignedDoctor->getAppointmentCasesTreated() >= 4) {
            // Remove the doctor from the database
            doctorDatabase.erase(assignedDoctor->getId());
        }
    }

    // Discharge a patient
    void dischargePatient() {
        string patientId;
        cout << "\t\t\t\t\t\t _________________________________________________________________ \n";
        cout << "\t\t\t\t\t\t|                                           	                  |\n";
        cout << "\t\t\t\t\t\t|             Discharge Patient                                   |\n";
        cout << "\t\t\t\t\t\t|_________________________________________________________________|\n\n";
        cout << "\nEnter Patient ID to discharge: ";
        cin >> patientId;

        if (patientDatabase.find(patientId) == patientDatabase.end()) {
            cout << "\nPatient not found in the database.\n";
            return;
        }

        patientDatabase.erase(patientId);
        cout << "\nPatient discharged successfully!\n";
        cout << "\n***************************\n";
        return;
    }

    // View treatment history with date and time
    void viewTreatmentHistory() {
        if (treatmentHistory.empty()) {
            cout << "\nNo treatment history available.\n";
            return;
        }

        cout << "\t\t\t\t\t\t _________________________________________________________________ \n";
        cout << "\t\t\t\t\t\t|                                           	                  |\n";
        cout << "\t\t\t\t\t\t|             Treatment History with Date and Time                |\n";
        cout << "\t\t\t\t\t\t|_________________________________________________________________|\n\n";

        stack<string> tempStack = treatmentHistory;
        while (!tempStack.empty()) {
            string treatmentDetails = tempStack.top();
            tempStack.pop();

            stringstream ss(treatmentDetails);
            string patientId, patientName, patientAge, medicalHistory, doctorId, doctorName;

            getline(ss, patientId, ',');
            getline(ss, patientName, ',');
            getline(ss, patientAge, ',');
            getline(ss, medicalHistory, ',');
            getline(ss, doctorId, ',');
            getline(ss, doctorName, ',');

            cout << "Patient ID: " << patientId << "\n";
            cout << "Name: " << patientName << "\n";
            cout << "Age: " << patientAge << "\n";
            cout << "Medical History: " << medicalHistory << "\n";
            cout << "Doctor ID: " << doctorId << "\n";
            cout << "Doctor Name: " << doctorName << "\n";
            cout << string(70, '-') << endl;
        }
    }

    // Save Data to Files
    void saveDataToFile() {
        ofstream patientFile("patients.txt");
        for (const auto& pair : patientDatabase) {
            pair.second.saveToFile(patientFile);
        }
        patientFile.close();

        ofstream doctorFile("doctors.txt");
        for (const auto& pair : doctorDatabase) {
            pair.second.saveToFile(doctorFile);
        }
        doctorFile.close();

        ofstream treatmentFile("treatment_history.txt");
        stack<string> tempStack = treatmentHistory;
        while (!tempStack.empty()) {
            treatmentFile << tempStack.top() << endl;
            tempStack.pop();
        }
        treatmentFile.close();
    }

    // Load Data from Files
    void loadDataFromFile() {
        ifstream patientFile("patients.txt");
        string line;
        while (getline(patientFile, line)) {
            Patient p = Patient::loadFromFile(line);
            patientDatabase[p.getId()] = p;
        }
        patientFile.close();

        ifstream doctorFile("doctors.txt");
        while (getline(doctorFile, line)) {
            Doctor d = Doctor::loadFromFile(line);
            doctorDatabase[d.getId()] = d;
        }
        doctorFile.close();

        ifstream treatmentFile("treatment_history.txt");
        while (getline(treatmentFile, line)) {
            treatmentHistory.push(line);
        }
        treatmentFile.close();
    }

    // Clear Console
    void clearScreen() {
#if defined(_WIN32) || defined(_WIN64)
        system("cls"); // Windows
#else
        system("clear"); // Unix-based systems (Linux, macOS)
#endif
    }

    // Display Main Menu
    void displayMenu() {
        clearScreen();
        cout << "\n";
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t  HOSPITAL MANAGEMENT SYSTEM \n\n";
        cout << "\n\n\t\t\t\t\t\tPlease,  Choose from the following Options: \n\n";
        cout << "\t\t\t\t\t\t _______________________________________________________________ \n";
        cout << "\t\t\t\t\t\t|                                           	               |\n";
        cout << "\t\t\t\t\t\t|             1  >> Register Patient                           |\n";
        cout << "\t\t\t\t\t\t|             2  >> Register Doctor                            |\n";
        cout << "\t\t\t\t\t\t|             3  >> View All Patients                          |\n";
        cout << "\t\t\t\t\t\t|             4  >> View All Doctors                           |\n";
        cout << "\t\t\t\t\t\t|             5  >> Handle Emergency                           |\n";
        cout << "\t\t\t\t\t\t|             6  >> Treat Emergency                            |\n";
        cout << "\t\t\t\t\t\t|             7  >> Book Appointment                           |\n";
        cout << "\t\t\t\t\t\t|             8  >> Treat Appointment                          |\n";
        cout << "\t\t\t\t\t\t|             9  >> View Treatment History                     |\n";
        cout << "\t\t\t\t\t\t|             10 >> Discharge Patient                          |\n";
        cout << "\t\t\t\t\t\t|             11 >> Exit                                       |\n";
        cout << "\t\t\t\t\t\t|______________________________________________________________|\n\n";
    }
};

int login() {
    string pass = "";
    char ch;
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t  HOSPITAL MANAGEMENT SYSTEM \n\n";
    cout << "\t\t\t\t\t\t\t\t------------------------------";

    cout << "\n\t\t\t\t\t\t\t\t\t     LOGIN \n";
    cout << "\t\t\t\t\t\t\t\t------------------------------\n\n";
    cout << "\t\t\t\t\t\t\t\tEnter Password: ";
    ch = _getch();
    while (ch != 13) { // character 13 is enter
        pass.push_back(ch);
        cout << '*';
        ch = _getch();
    }
    if (pass == "pass") {
        cout << "\n\n\t\t\t\t\t\t\t\tAccess Granted! \n";
        system("PAUSE");
    }
    else {
        cout << "\n\n\t\t\t\t\t\t\t\tAccess Aborted...\n\t\t\t\t\t\t\t\tPlease Try Again\n\n";
        system("PAUSE");
        system("CLS");
        login();
    }
    return 1;
}

// Main Function
int main() {
    HospitalManagementSystem hms;
    hms.loadDataFromFile();

    int choice;

    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
    cout << "\t\t\t\t\t@@ _______________________________________________________________________________________ @@\n";
    cout << "\t\t\t\t\t@@|                                           		                                  |@@\n";
    cout << "\t\t\t\t\t@@|                                           		                                  |@@\n";
    cout << "\t\t\t\t\t@@|                                           		                                  |@@\n";
    cout << "\t\t\t\t\t@@|                                           		                                  |@@\n";
    cout << "\t\t\t\t\t@@|                                           		                                  |@@\n";
    cout << "\t\t\t\t\t@@|                                           		                                  |@@\n";
    cout << "\t\t\t\t\t@@|                                  WELCOME TO                                           |@@\n";
    cout << "\t\t\t\t\t@@|                                                                                       |@@\n";
    cout << "\t\t\t\t\t@@|                           HOSPITAL MANAGEMENT SYSTEM                                  |@@\n";
    cout << "\t\t\t\t\t@@|                                                                                       |@@\n";
    cout << "\t\t\t\t\t@@|                                                                                       |@@\n";
    cout << "\t\t\t\t\t@@|                                                                                       |@@\n";
    cout << "\t\t\t\t\t@@|                                                                                       |@@\n";
    cout << "\t\t\t\t\t@@|                                                                                       |@@\n";
    cout << "\t\t\t\t\t@@|_______________________________________________________________________________________|@@\n";
    cout << "\t\t\t\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n\n\n\t\t\t\t\t";
    system("pause");
    system("cls");
    login();

    do {
        hms.displayMenu();
        cout << "Choose an option: ";
        cin >> choice; // Get user input for menu selection
        system("cls");

        switch (choice) {
        case 1:
            hms.registerPatient();
            system("pause");
            break;
        case 2:
            hms.registerDoctor();
            system("pause");
            break;
        case 3:
            hms.viewPatients();
            system("pause");
            break;
        case 4:
            hms.viewDoctors();
            system("pause");
            break;
        case 5:
            hms.handleEmergency();
            system("pause");
            break;
        case 6:
            hms.treatEmergency();
            system("pause");
            break;
        case 7:
            hms.bookAppointment();
            system("pause");
            break;
        case 8:
            hms.treatAppointment();
            system("pause");
            break;
        case 9:
            hms.viewTreatmentHistory();
            system("pause");
            break;
        case 10:
            hms.dischargePatient();
            system("pause");
            break;
        case 11:
            cout << "Exiting the program. Godbye!!" << endl;
            break;
        default:
            cout << "Invalid option. Try again.\n";
        }

        hms.saveDataToFile(); // Save data after each operation
    } while (choice != 11);

    return 0;
}