#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Client.h"
#include "IClientRepo.h"
#include "clsString.h"

using namespace std;

class FileClientRepo : public IClientRepo {
  string _fileName{};
  string _delim{};

  string _ConvertClientToLine(const Client &client) {
    return {client.getName() + _delim + client.getSurName() + _delim +
            client.getPhoneNumber() + _delim + client.getEmail() + _delim +
            client.getAccountNumber() + _delim +
            to_string(client.getPinCode()) + _delim +
            to_string(client.getBalance())};
  }

  Client _ConvertLineToClient(const string &line) {
    vector<string> partitions{clsString::Split(line, _delim)};
    return Client(partitions.at(0), partitions.at(1), partitions.at(2),
                  partitions.at(3), partitions.at(4),
                  static_cast<short>(stoi(partitions.at(5))),
                  stod(partitions.at(6)));
  }

  bool _ReSaveAll(vector<Client> clients) {
    ofstream oFile{_fileName, ios::out};
    if (oFile) {
      for (Client &client : clients) {
        oFile << _ConvertClientToLine(client) << '\n';
      }
      oFile.close();
      return true;
    }
    return false;
  }

public:
  FileClientRepo(const string &fileName, const string &delim = "#//#")
      : _fileName(fileName), _delim(delim) {}
  bool add(const Client &client) override {
    ofstream oFile{_fileName, ios::app};
    if (oFile) {
      oFile << _ConvertClientToLine(client) << '\n';
      oFile.close();
      return true;
    }
    return false;
  }
  bool update(const Client &client) override {
    vector<Client> clients = getAll();
    for (Client &C : clients) {
      if (C.getAccountNumber() == client.getAccountNumber()) {
        C = client;
        return _ReSaveAll(clients);
      }
    }
    return false;
  }
  bool remove(const string &account) override {
    vector<Client> clients{getAll()};
    for (auto it{clients.begin()}; it != clients.end(); ++it) {
      if (it->getAccountNumber() == account) {
        clients.erase(it);
        return _ReSaveAll(clients);
      }
    }
    return false;
  }
  Client find(const string &account) override {
    vector<Client> clients{getAll()};
    for (Client &client : clients) {
      if (client.getAccountNumber() == account)
        return client;
    }
    return Client();
  }
  
  vector<Client> getAll() override {
    ifstream iFile{_fileName, ios::in};
    vector<Client> Clients{};
    if (iFile) {
      string line{};
      while (getline(iFile, line)) {
        if (line.empty())
          continue;
        Client C{_ConvertLineToClient(line)};
        Clients.push_back(C);
      }
      iFile.close();
    }
    return Clients;
  }

  bool existAccount(const string& account) {
      return !find(account).isEmpty();
  }

};