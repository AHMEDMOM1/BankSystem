#pragma once 

#include <vector>
#include <fstream>
#include <string>

#include "Employee.h"
#include "clsString.h"
#include "IEmployeeRepo.h"
#include "EmployeeManager.h"


class FileEmployeeRepo : public IEmployeeRepo {
    std::string _fileName{ };
    std::string _delim{ };


    std::string _ConvertUserToLine(const Employee& Employee) {
        return { Employee.getName() + _delim +
                Employee.getSurName() + _delim +
                Employee.getPhoneNumber() + _delim +
                Employee.getEmail() + _delim +
                Employee.getUserName() + _delim +
                clsUtil::_Encryption(Employee.getPassword()) + _delim +
                std::to_string(Employee.getPermissions())};
    }

    Employee _ConvertLineToUser(const std::string& line) {
        vector<std::string>partitions{ clsString::Split(line, _delim) };
        return Employee(partitions.at(0), partitions.at(1),
            partitions.at(2), partitions.at(3),
            partitions.at(4), partitions.at(5),
            std::stoi(partitions.at(6)));
    }

public:
    FileEmployeeRepo(const std::string& fileName, const std::string& delim = "#//#") : _fileName(fileName), _delim("#//#") {}
    bool add(const Employee& Employee) override {
        std::ofstream oFile{ _fileName, std::ios::app };
        if (oFile) {
            oFile << _ConvertUserToLine(Employee) << '\n';
            oFile.close();
            return true;
        }
        return false;
    }
    bool update(const Employee& employee) override {
        std::vector<Employee>users{ getAll() };
        for (Employee& U : users) {
            if (U.getUserName() == employee.getUserName()) {
                U = employee;
                return reSaveAll(users);
            }
        }
        return false;
    }
    bool remove(const std::string& account) override {
        vector<Employee>employees{ getAll() };
        for (auto it{ employees.begin() }; it != employees.end(); ++it) {
            if (it->getUserName() == account) {
                employees.erase(it);
                return reSaveAll(employees);
            }
        }
        return false;
    }
    Employee find(const std::string& accountNumber) override {
        std::vector<Employee>employees{ getAll() };
        for (const Employee& employee : employees) {
            if (employee.getUserName() == accountNumber)
                return employee;
        }
        return Employee();
    }
    std::vector<Employee> getAll() override {
        std::ifstream iFile{ _fileName, std::ios::in };
        std::vector<Employee> users{};

        if (iFile) {
            string line{};

            while (getline(iFile, line)) {
                if (line.empty())continue;

                Employee Employee{ _ConvertLineToUser(line) };
                std::string decryptedPassword = clsUtil::_Decryption(Employee.getPassword());

                Employee.setPassword(decryptedPassword);
                users.push_back(Employee);
            }
            iFile.close();
        }

        return users;
    }

    bool reSaveAll(vector<Employee>& users) {
        ofstream oFile{ _fileName, ios::out };
        if (oFile) {
            for (Employee& Employee : users) {
                oFile << _ConvertUserToLine(Employee) << '\n';
            }
            oFile.close();
            return true;
        }
        return false;
    }

    bool isExistAccount(const std::string& account) {
        return !find(account).isEmpty();
    }


};