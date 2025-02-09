#include "api.h"

/**
 * Liest Assignment-File und stellt diese als C++ Struct-Vektoren zur Verfügung
 * Speichert mit update() die geänderten Daten wieder in angegebener Datei.
 * Änderungen zwischen Lese- und Speicherzugriff werden überschrieben.
 */
API::API(const string &file_name){
    read_data(file_name);
}

/**
 * Liest Assignment-Verwaltungsdatei. Erstellt passende C++-Objekte
 */
void API::read_data(const string &file_name){
    ifstream eingabe_stream(file_name);
    if(!eingabe_stream) {
        throw CantOpen("Datei kann nicht geöffnet werden: " + file_name);
    }

    string header = read_header(eingabe_stream);
    for(int i = 0; i<3; ++i){
        if(eingabe_stream.eof() && !eingabe_stream.bad()){
            return;
        }else if(eingabe_stream.fail() || eingabe_stream.bad()){
            throw BadFormat("Datei hat falsches Format");
        }else{
            switch(header){
                case user_header:
                    read_user;
                    break;
                case task_header:
                    read_tasks
                    break;
                case assignment_header:
                    read_assignemnts;
                    break;
                default:
                    throw BadFormat("Datei hat falsches Format");
            }
        }
        header = read_header(eingabe_stream);
    }
}

/**
 * Liest den Task-Abschnitt der Assignment-Verwaltungsdatei
 */
void API::read_tasks(ifstream &eingabe_stream){  
    Task task;

    eingabe_stream >> task;
    while(eingabe_stream.good()){
        task_list[task.t_id] = task; //Erzeugt einen Entry in der Task_List mit t_id und Inhalt der Task
        eingabe_stream >> task;
    }
}

/**
 * Liest den User-Abschnitt der Assignment-Verwaltungsdatei
 */
void API::read_users(ifstream &eingabe_stream){
    User user;

    eingabe_stream >> user;
    while(eingabe_stream.good()){
        user_list[user.u_id] = user; //Erzeugt einen Entry in der User_List mit u_id und Inhalt der Task
        eingabe_stream >> user;
    }
}

/**
 * Liest den Assignment-Abschnitt der Assignment-Verwaltungsdatei
 */
void API::read_assignemnts(ifstream &eingabe_stream){
    Assginment assignment;

    eingabe_stream >> assignment;
    int i = 0;
    while(eingabe_stream.good()){
        assignment_list[i] = assignment; //Erzeugt einen Entry in der Assigment-List
        eingabe_stream >> assignment;
    }
}

/**
 * Sucht den nächsten Header und gibt diesen zurück
 */
string API::read_header(istream& is){
    char ch;
    string header;
    cin >> ch;
    if(is.good() && ch == '['){
        header = '['+ read_string();
    }
    if(is.fail() || is.bad()){
        return "";
    }else{
        return header;
    }
}

/**
 * Liest einen String aus dem Stream
 * Basiert auf Vorlesungsbeispiel
 */
string API::read_string(istream& is){
    char ch; string result;
    is.get(ch);
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
string API::read_enclosed_string(istream& is, char terminator){
    char ch; string result;
    is.get(ch);
    //Wenn der Stream nicht ok ist, oder der String nicht mit Terminator beginnt
    // Wird direkt abgebrochen und ein Fehler ausgegeben
    if(!is.good() || ch != terminator) {
        is.setstate(ios_base::failbit);
        return "";
    }
    while(is.good() && ch != terminator)
    {
        result += ch;
        is.get(ch);
    }
    //Falls String nicht mit Terminator beendet ist, ist ein Fehler aufgetreten
    if(ch != terminator) { is.setstate(ios_base::failbit)};
    if(is.fail() || is.bad()) { return ""; }
    return result;
}

/**
 * Liest Vektor an Zahlen bis Zeilenende
 * Gibt bei korrekter Syntax einen String aus,
 * Sonst wird ein Fehlerbit gesetzt und ein leerer Vektor returned
 */
vector<unsigned int> read_vector(istream& is){
    vector<unsigned int> result = {};
    unsigned int entry;
    char seperator;
    is >> entry >> noskipws;
    while(is.good())
    {
        result.push_back(entry);
        is >> seperator;
        if(seperator == '\n'){ //Bei Zeilenumbruch wird result returned
            is >> skipws;
            return result;
        }else if(seperator != " "){
            is.setstate(ios_base::failbit);
            is >> skipws;
            return {};
        }else 

        is >> entry;
    }
    is >> seperator; // Falls die Schleife nicht betreten wird(keine Zahl lesbar)
    if(seperator == '\n'){ // Fall Zeilenumsprung -> Der Vektor ist einfach leer
        is.clear(); // Stream wird wieder auf good gesetzt. Korrektes Verhalten
    }
    is >> skipw;
    return {};
}

istream& operator>>(istream& eingabe_stream, User& user){
    unsigned int u_id; string name; string surname;
    eingabe_stream >> u_id;
    if(!eingabe_stream.good()) { return eingabe_stream; }
    name = read_string(eingabe_stream);
    if(!eingabe_stream.good()) { return eingabe_stream; }
    surname = read_string(eingabe_stream);
    if(eingabe_stream.fail() || eingabe_stream.bad()) { return eingabe_stream; }
    user = User{u_id, name, surname};
    return eingabe_stream;
}

istream& operator>>(istream& eingabe_stream, Task& task){
    unsigned int t_id; string name; string desciption; vector<unsigned int> follow_tasks;
    eingabe_stream >> t_id;
    if(!eingabe_stream.good()) { return eingabe_stream; }
    name = read_enclosed_string(eingabe_stream);
    if(!eingabe_stream.good()) { return eingabe_stream; }
    desciption = read_enclosed_string(eingabe_stream);
    if(!eingabe_stream.good()) { return eingabe_stream; }
    follow_tasks = read_vector(eingabe_stream);
    if(eingabe_stream.fail() || eingabe_stream.bad()) { return eingabe_stream; }
    task = Task{t_id, name, desciption, follow_tasks};
    return eingabe_stream;
}

istream& operator>>(istream& eingabe_stream, Assginment& assignment){
    unsigned int u_id; unsigned int t_id;;
    eingabe_stream >> u_id;
    if(!eingabe_stream.good()) { return eingabe_stream; }
    eingabe_stream >> t_id;
    if(eingabe_stream.fail() || eingabe_stream.bad()) { return eingabe_stream; }
    assignment = Assignment{u_id, t_id};
    return eingabe_stream;
}