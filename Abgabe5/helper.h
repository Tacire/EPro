#ifndef HELPER_H
#define HELPER_H

// Exception fuer nicht erlaubte Bewegungen
class CantOpen {};

// Exception fuer unbekannte Eingaben
class BadFormat {};

// Exception fuer eine falsche Labyrinth-Eingabe
class CantWrite {};


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
        return result;
    }else{
        return {};
    }
}


#endif