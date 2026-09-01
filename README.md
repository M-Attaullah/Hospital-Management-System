# 🏥 Hospital Management System

A console-based Hospital Management System developed in **C++** to manage patient records, doctor records, emergency cases, appointments, and treatment history using fundamental **Data Structures and Algorithms** concepts.

## 📋 Features

### 👤 Patient Management

* Register new patients with:

  * Patient ID
  * Name
  * Age
  * Medical History
* Prevent duplicate patient IDs during registration
* View all registered patients
* Discharge patients from the system

### 👨‍⚕️ Doctor Management

* Register doctors with:

  * Doctor ID
  * Doctor Name
  * Emergency Availability
* View all registered doctors
* Track doctors' emergency availability
* Track the number of emergency and appointment cases treated by each doctor

### 🚨 Emergency Management

* Add registered patients to the emergency queue
* Assign a severity level to emergency cases
* Process emergency cases according to priority
* Assign an available emergency doctor to an emergency case
* Track emergency cases treated by doctors

### 📅 Appointment Management

* Book appointments for registered patients
* Store appointments in a queue
* Process appointments in FIFO order
* Assign an available doctor for appointment treatment
* Track appointment cases treated by doctors

### 📋 Treatment History

* Store completed treatment records
* Record patient and doctor information
* Display treatment history using a stack
* Store treatment date and time

### 💾 File Handling

* Save patient records to `patients.txt`
* Save doctor records to `doctors.txt`
* Save treatment history to `treatment_history.txt`
* Load existing records when the application starts
* Save updated records after each menu operation

### 🔐 Login System

* Password-protected access to the system
* Password input is hidden using console input handling
* Access is granted only when the correct password is entered

## 🧠 Data Structures Used

The project demonstrates the practical use of multiple C++ Standard Template Library data structures.

| Data Structure   | Purpose                                           |
| ---------------- | ------------------------------------------------- |
| `map`            | Stores patient and doctor records using their IDs |
| `priority_queue` | Manages emergency cases according to severity     |
| `queue`          | Manages normal appointments in FIFO order         |
| `stack`          | Stores and displays treatment history             |

### 🚨 Emergency Priority

Emergency cases use a `priority_queue`, where a **lower severity value represents a higher priority**.

```text
Severity 1 → Highest Priority
Severity 2
Severity 3
...
Severity 10 → Lower Priority
```

This allows emergency cases to be treated according to their assigned severity.

## 🏗️ Object-Oriented Programming

The system is implemented using classes and structures to organize its functionality.

### `Patient` Class

Stores and manages patient information:

* Patient ID
* Patient Name
* Age
* Medical History

The class also provides functions for accessing and modifying patient data and saving/loading records.

### `Doctor` Class

Stores and manages doctor information:

* Doctor ID
* Doctor Name
* Emergency Availability
* Emergency Cases Treated
* Appointment Cases Treated

The class also provides functions for accessing, modifying, and saving/loading doctor records.

### `Emergency` Structure

Represents an emergency case using:

* Severity
* Patient ID

It also defines a comparison operation to determine the priority of emergency cases.

### `HospitalManagementSystem` Class

Controls the main functionality of the system, including:

* Patient registration
* Doctor registration
* Patient and doctor records
* Emergency handling
* Emergency treatment
* Appointment booking
* Appointment treatment
* Treatment history
* Patient discharge
* File handling
* Main menu

## 🚀 Getting Started

### Prerequisites

* Windows operating system
* Visual Studio
* C++ development tools
* C++ compiler supporting the project

### Installation

1. Download or clone the project.
2. Open the Visual Studio project file:

```text
HMS.vcxproj
```

3. Build the project using Visual Studio.
4. Run the application.
5. Enter the login password to access the system.

### Login Password

The current implementation uses:

```text
pass
```

as the login password.

> The password is hard-coded in the source code for this academic project.

## 🎮 How to Use

After starting the application, the system displays a login screen.

Once the correct password is entered, the main menu provides the following options:

```text
1  → Register Patient
2  → Register Doctor
3  → View All Patients
4  → View All Doctors
5  → Handle Emergency
6  → Treat Emergency
7  → Book Appointment
8  → Treat Appointment
9  → View Treatment History
10 → Discharge Patient
11 → Exit
```

### Register Patient

Enter:

* Patient ID
* Patient Name
* Age
* Medical History

The system checks whether the patient ID already exists before registering the patient.

### Register Doctor

Enter:

* Doctor ID
* Doctor Name
* Emergency Availability

The system stores the doctor information and maintains doctor case counters.

### Handle Emergency

Select a registered patient and enter an emergency severity value. The emergency case is added to the priority queue.

### Treat Emergency

The highest-priority emergency case is processed and an emergency-available doctor is assigned for treatment.

### Book Appointment

Select a registered patient and add the appointment to the appointment queue.

### Treat Appointment

Appointments are processed according to **FIFO (First In, First Out)** order and an available doctor is assigned.

### View Treatment History

Completed treatments are displayed from the treatment history stack along with patient and doctor information.

### Discharge Patient

A registered patient can be removed from the patient database using the patient's ID.

## 💾 Data Storage

The application uses local text files for storing data.

```text
HMS/
│
├── patients.txt
├── doctors.txt
└── treatment_history.txt
```

### `patients.txt`

Stores patient information including:

* Patient ID
* Name
* Age
* Medical History

### `doctors.txt`

Stores:

* Doctor ID
* Doctor Name
* Emergency Availability
* Emergency Cases Treated
* Appointment Cases Treated

### `treatment_history.txt`

Stores treatment history records containing patient and doctor information.

## 📁 Project Structure

```text
HMS/
│
├── main.cpp
├── HMS.vcxproj
├── HMS.vcxproj.filters
├── HMS.vcxproj.user
├── HMS.rc
├── resource.h
│
├── patients.txt
├── doctors.txt
└── treatment_history.txt
```

> The project also contains Visual Studio generated build/output files such as `Debug` and `x64` directories.

## 🛠️ Technologies Used

* **C++** — Main programming language
* **STL** — Standard Template Library data structures
* **Object-Oriented Programming** — Classes, constructors, accessors, and mutators
* **Data Structures** — `map`, `priority_queue`, `queue`, and `stack`
* **File Handling** — `ifstream` and `ofstream`
* **Console I/O** — `iostream`
* **String Processing** — `string` and `stringstream`
* **Date & Time** — C++ time functions
* **Console Input Handling** — `conio.h`
* **Visual Studio** — Development environment

## 🎓 Academic Concepts Demonstrated

This project demonstrates:

* Object-Oriented Programming
* Classes and Objects
* Constructors
* Encapsulation
* Accessors and Mutators
* STL Containers
* Priority Queue
* Queue
* Stack
* Map
* File Input/Output
* Data Persistence
* Basic Console-Based Authentication
* Date and Time Handling

## 📌 Project Purpose

This project was developed as an academic implementation of **Data Structures, Algorithms, and Object-Oriented Programming concepts** through a practical Hospital Management System.

It demonstrates how different data structures can be used to manage different types of hospital operations, such as prioritizing emergency cases, processing appointments, and maintaining treatment history.

## 📝 License

This project is created for **educational and academic purposes**.
