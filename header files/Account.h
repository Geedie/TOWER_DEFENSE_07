#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>

using namespace std;

bool checkValid(const string& password) {
    if (password.length() < 8) {
        return false;
    }
    for (char c : password) {
        if (isspace(c)) {
            return false;
        }
    }
    return true;
}
void login() {
    string* name = new string;
    string* password = new string;

    fstream file("UserFile.txt", ios::in);
    if (!file.is_open()) {
        cout << "System error" << endl;
        delete name;
        delete password;
        return;
    }

    bool isLoggedIn = false;

    while (!isLoggedIn) {
        cout << "User: ";
        cin >> *name;
        cout << "Password: ";
        cin >> *password;
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string fileUser, filePassword;
            ss >> fileUser >> filePassword;

            if (*name == fileUser && *password == filePassword) {
                isLoggedIn = true;
                break;
            }
        }
        if (isLoggedIn) {
            cout << "Welcome back, " << *name << "!" << endl;
        }
        else {
            cout << "Invalid username or password. Please try again." << endl;
            file.clear();
            file.seekg(0);
        }
    }
    file.close();
    delete name;
    delete password;
}
void signup() {
    string* name = new string;
    string* password = new string;
    fstream file("UserFile.txt", ios::out);
    if (!file.is_open()) {
        cout << "System error" << endl;
        return;
    }
    else {
        cout << "User name: ";
        cin >> *name;
        while (true) {
            cout << "Password: ";
            cin >> *password;
            if (checkValid(*password)) {
                break;
            }
            else {
                cout << "Password invalid (Password needs to be 8 characters long and no spaces)";
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
            }
        }
        file << name << " " << password << "\n\n";
        cout << "Sign up successful!" << endl;

    }
    file.close();
    delete name;
    delete password;
}