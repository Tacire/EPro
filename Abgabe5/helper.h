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
    string message = "401: Eine solche BenutzerIn existiert nicht.\n";

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


/**
 * Liest einen enclosed String aus dem Stream
 * Basiert auf Vorlesungsbeispiel
 */
static const string read_enclosed_string(istream& is, char terminator){
    char ch; string result = "";
    is >> ch;
    // Wenn der Stream nicht ok ist, oder der String nicht mit Terminator beginnt
    // wird direkt abgebrochen und ein Fehler ausgegeben
    if(!is.good() || ch != terminator) {
        is.setstate(ios_base::failbit);
        return "";
    }
    do{ 
        result += ch; 
        is.get(ch); 
    }
    while(is.good() && ch != terminator);
    
    //Fügt den finalen Terminator hinzu
    if(ch == terminator) { 
        result += terminator;
    }

    if(is.fail() || is.bad()) { 
        return ""; 
    }else{
        return result;
    }
}

/**
 * Liest Vektor an Zahlen bis Zeilenende
 * Gibt bei korrekter Syntax einen String aus,
 * Sonst wird ein Fehlerbit gesetzt und ein leerer Vektor returned
 */
static const vector<unsigned int> read_vector(istream& is){
    vector<unsigned int> result = {};
    unsigned int entry;
    char seperator;
    is >> noskipws;

    //Skippt bis zur nächsten Zahl / ZeilenEnde
    is >> seperator;
    while(is.good() && isspace(seperator) && seperator != '\n'){
        is >> seperator;
    }

    // Bei Zeilenende wird ein leerer Vektor zurückgegeben,
    // Bei Zahl wird der Vektor befüllt
    if(seperator == '\n'){
        is >> skipws;
        return {};
    }else if(isdigit(seperator)){
        is.unget();
        is >> entry;
    }

    //List bis Zeilenumbruch den Vektor in Format "int ws int ws int ws int"
    while(is.good())
    {
        result.push_back(entry);
        
        is >> seperator;
        if(seperator == '\n'){ //Bei Zeilenumbruch wird result returned
            is >> skipws;
            return result;
        }else if(seperator != ' '){
            is.setstate(ios_base::failbit);
            is >> skipws;
            return {};
        }

        is >> entry;
    }
    if(is.eof()){
        is.clear();
        return result;
    }else{
        return {};
    }
}


/**
 * Liest einen String aus dem Stream
 * Basiert auf Vorlesungsbeispiel
 */
static const string read_string(istream& is){
    char ch; string result;
    is >> ch;
    while(is.good() && !isspace(ch))
    {
        result += ch;
        is.get(ch);
    }
    if(is.fail() || is.bad()) { return ""; }
    return result;
}


#endif //HELPER_H