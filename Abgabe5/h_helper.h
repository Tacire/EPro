//
// Created by hendrik on 08.02.25.
//

#ifndef HELPER_H
#define HELPER_H

class Command_unknown_101 : public exception {
private:
    string message = "101: Befehl ist unbekannt.\n";

public:
    const char* what() const throw() {
        return message.c_str();
    }
};

class Parameter_unreadable_102 {
private:
    string message = "102: Ein Paramter eines Befehls konnte nicht gelesen werden.\n";

public:
    const char* what() const throw() {
        return message.c_str();
    }
};

class User_not_deletable_201 {
private:
    string message = "201: Benutzer kann nicht gelöscht werden.\n";

public:
    const char* what() const throw() {
        return message.c_str();
    }
};

class Task_not_deletable_202 {
private:
    string message = "202: Aufgabe kann nicht gelöscht werden.\n";

public:
    const char* what() const throw() {
        return message.c_str();
    }
};

class Assignment_does_not_exist_301 {
private:
    string message = "301: Eine solche Zuordnung existiert nicht.\n";

public:
    const char* what() const throw() {
        return message.c_str();
    }
};

class Assignment_already_exists_302 {
private:
    string message = "302: Eine solche Zuordnung existiert bereits.\n";

public:
    const char* what() const throw() {
        return message.c_str();
    }
};

class User_does_not_exist_401 {
private:
    string message = "Eine solche BenutzerIn existiert nicht.\n";

public:
    const char* what() const throw() {
        return message.c_str();
    }
};

class Task_does_not_exist_402 {
private:
    string message = "402: Eine solche Aufgabe existiert nicht.\n";

public:
    const char* what() const throw() {
        return message.c_str();
    }
};

class File_not_openable_601 {
private:
    string message = "601: Datei kann nicht geöffnet werden.\n";

public:
    const char* what() const throw() {
        return message.c_str();
    }
};

class File_format_unknown_602 {
private:
    string message = "602: Datei hat ein unbekanntes Format.\n";

public:
    const char* what() const throw() {
        return message.c_str();
    }
};

class File_not_writable_603 {
private:
    string message = "603: Datei kann nicht geschrieben werden.\n";

public:
    const char* what() const throw() {
        return message.c_str();
    }
};

#endif //HELPER_H