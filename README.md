# 🏦 Bank System (OOP Console Application)

> 🚧 **Status:** This project is actively **Under Development**. New features, architectural improvements, and refactoring are continuously being pushed.

A fully-featured, console-based Banking Management System built entirely in C++ using advanced Object-Oriented Programming (OOP) concepts, Clean Architecture, and SOLID principles. 

## ✨ Features
* **Secure Authentication:** Robust login system for employees with session handling.
* **Role-Based Access Control (RBAC):** Permissions system ensuring employees only access screens they are authorized for.
* **Client Management:** Complete CRUD operations (Add, Update, Delete, Find, List) for bank clients.
* **Transactions System:** Handling deposits, withdrawals, and displaying total balances safely.
* **Employee Management:** Admin-level features to manage staff and system users.
* **Clean UI & Routing:** A dynamic console UI utilizing screen routing and method injection.
* **Data Persistence:** File-based Repository pattern protecting data integrity across sessions.

## 🛠️ Architecture & Tech Stack
* **Language:** C++
* **Design Patterns:** Repository Pattern, Dependency Injection (Scoped DI), Single Responsibility, State Management.
* **Architecture:** Decoupled architecture separating User Interfaces (UI), Business Logic (Services), Models, and Storage (Repository).

## 🚀 How to Run
1. Clone the repository: `git clone https://github.com/AHMEDMOM1/BankSystem.git`
2. Open the solution file `TestOopBank.sln` using **Microsoft Visual Studio**.
3. Compile and Run the project (x64/Release or Debug).
4. Login using the default admin credentials (configured in `.txt` database).

---
*Developed with a focus on writing clean, scalable, and maintainable enterprise-level C++ code.*
