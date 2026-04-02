#pragma once
#include <iostream>

class Person {
private:
  std::string _Name{};
  std::string _SurName{};
  std::string _PhoneNumber{};
  std::string _Mail{};

public:
  Person() = default;
  Person(const std::string &name, const std::string &surName,
         const std::string &phoneNumber, const std::string &email) {
    _Name = name;
    _SurName = surName;
    _PhoneNumber = phoneNumber;
    _Mail = email;
  }
  void setName(const std::string &name) { _Name = name; }
  std::string getName() const { return _Name; }

  void setSurName(const std::string &surName) { _SurName = surName; }
  std::string getSurName() const { return _SurName; }

  void setPhoneNumber(const std::string &phoneNumber) {
    _PhoneNumber = phoneNumber;
  }
  std::string getPhoneNumber() const { return _PhoneNumber; }

  void setEmail(const std::string &email) { _Mail = email; }
  std::string getEmail() const { return _Mail; }
};