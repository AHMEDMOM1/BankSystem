<div align="center">
  <img src="https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++" />
  <img src="https://img.shields.io/badge/Visual_Studio-5C2D91?style=for-the-badge&logo=visual%20studio&logoColor=white" alt="Visual Studio" />
  <img src="https://img.shields.io/badge/Architecture-Clean%20Architecture-brightgreen?style=for-the-badge" alt="Clean Architecture" />
  <img src="https://img.shields.io/badge/Status-Actively%20Developed-blue?style=for-the-badge" alt="Status" />
</div>

<h1 align="center">🏦 Enterprise Bank System (C++)</h1>

<p align="center">
  <strong>A fully-featured, console-based Banking Management System built entirely in C++ demonstrating advanced Software Engineering concepts, Clean Architecture, and SOLID principles.</strong>
</p>

---

## 📖 About The Project

This project is not just a standard console application; it is a **showroom of modern Object-Oriented Programming (OOP) patterns**. It was meticulously refactored to break away from traditional procedural spaghetti code into a highly decoupled, maintainable, and scalable **N-Tier Architecture**.

### 🌟 Key Architectural Highlights
* **🧠 Clean Architecture & N-Tier separation:** Code is strictly segregated into `Models`, `Repositories`, `Services`, `Interfaces`, and `UI` layers.
* **💉 Dependency Injection (DI) & Inversion of Control (IoC):** The `TestOopBank.cpp` (now `BankSystem.cpp`) acts as a dedicated **Composition Root**. Repositories are injected into Managers, and Managers are injected into UI Screens, achieving zero hard-dependencies between the UI and the data source.
* **🛡️ SOLID Principles strictly followed:** 
  * **Single Responsibility (SRP):** Each UI Screen and each Manager has one distinct job.
  * **Open/Closed (OCP):** Interface-driven (`IClientRepo`, `ICurrenciesRepo`) allowing smooth transition to SQL databases in the future without touching the UI or Business Logic.
  * **Don't Repeat Yourself (DRY):** Aggressively refactored to extract shared UI logic into generic base classes (`ClientScreenBase`, `EmployeeScreenBase`).

---

## 🔥 Features & Modules

### 👤 1. Authentication & Security (RBAC)
* Robust **Login/Logout Session Handling** via `CurrentUser` object.
* **Role-Based Access Control (RBAC):** Granular bitwise permission system ensuring employees can only access the screens they are explicitly authorized for.
* Login tracking logs.

### 💰 2. Core Banking System
* **Client Management:** Complete CRUD (Create, Read, Update, Delete) operations.
* **Transactions Operations:** Safely process Deposits and Withdrawals with real-time balance checks.
* **Total Balances Dashboard:** View cumulative statistics for the bank's liquidity.
* **Transfer & Logging:** Transfer funds between clients and maintain a permanent auditing log for transfers (`TransferLogScreen`).

### 💱 3. Foreign Currency Exchange Module
* View real-time exchange rates against the USD.
* Find specific currency rates by **Country Name** or **Currency Code**.
* Update active currency exchange rates seamlessly.

### 👔 4. Employee Management
* Full Admin-Level controls to Add, Remove, Update, and List Employees.
* Dynamic permission assignment mechanism.

### 🎨 5. Next-Level UI/UX (For Console)
* Overhauled UI engine utilizing **Windows APIs for terminal coloring**.
* Professional structured Tables, formatted Cards, and aligned visual separators.
* Interactive dialogs (Yes/No confirmations, error handling, warnings).

---

## 🛠️ Project Structure

```text
📂 BankSystem/
 ├── 📁 Interface/      # Interfaces (Contracts) like IClientRepo, ICurrenciesRepo
 ├── 📁 Models/         # Pure Data Structures (Client, Employee, CurrencyRecord)
 ├── 📁 Repository/     # Concrete Implementations (File storage handling)
 ├── 📁 Services/       # Business Logic Managers (ClientManager, CurrencyManager)
 ├── 📁 UI/             # Routing, Screens, and Menus
 └── 📁 Utility/        # Helper functions (Date, String styling, Data Validation)
```

## 🚀 How to Build & Run

1. **Clone the repository:** 
   ```bash
   git clone https://github.com/AHMEDMOM1/BankSystem.git
   ```
2. **Open the Solution:** Open the `BankSystem.sln` file using **Microsoft Visual Studio**.
3. **Compile:** Build the project in `x64/Debug` or `x64/Release`.
4. **Run:** Execute the compiled program.
5. **Login:** Check the `Employee.txt` file (or equivalent) for default Admin credentials.

---

> 👨‍💻 *Developed with a relentless focus on writing clean, scalable, and beautifully structured enterprise-level C++ code.*
