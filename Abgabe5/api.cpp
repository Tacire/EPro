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
    ifstream is(file_name);
    if(!is) {
        throw CantOpen();
    }

    string header = read_header(is);
    while(true){ // Läuft bis zum Ende der Datei
        if(is.eof() && !is.bad()){
            return;
        }else if(is.fail() || is.bad()){
            throw BadFormat();
        }else{
            if(header == user_header){read_users(is);}
            else if(header == task_header){read_tasks(is);}
            else if(header == assignment_header){read_assignments(is);}
            else{throw BadFormat();} //Falscher Header
        }

        if(is.good()){
            header = read_header(is);
        }
    }
}

/**
 * Liest den Task-Abschnitt der Assignment-Verwaltungsdatei
 */
void API::read_tasks(ifstream &is){  
    Task task;

    is >> task;
    while(is.good()){
        task_list[task.t_id] = task; //Erzeugt einen Entry in der Task_List mit t_id und Inhalt der Task
        is >> task;
    }

    //Überprüfung ob Ende durch neuen Header, dann Stream wieder auf good() setzen
    if(!is.eof()){
        is.clear(); // Clear um die Fehlerursache zu untersuchen
        char last;
        is >> last;
        if(last == '['){
            // Fall das wir einen neuen Header gefunden haben, returned ohne Fehler
            is.unget();
            return;
        }else{
            // Setze Fehler wieder, da Syntaxproblem in Datei
            is.setstate(ios_base::failbit);
        }
    }
}

/**
 * Liest den User-Abschnitt der Assignment-Verwaltungsdatei
 */
void API::read_users(ifstream &is){
    User user;

    is >> user;
    while(is.good()){
        user_list[user.u_id] = user; //Erzeugt einen Entry in der User_List mit u_id und Inhalt der Task
        is >> user;
    }

    //Überprüfung ob Ende durch neuen Header, dann Stream wieder auf good() setzen
    if(!is.eof()){
        is.clear(); // Clear um die Fehlerursache zu untersuchen
        char last;
        is >> last;
        if(last == '['){
            // Fall das wir einen neuen Header gefunden haben, returned ohne Fehler
            is.unget();
            return;
        }else{
            // Setze Fehler wieder, da Syntaxproblem in Datei
            is.setstate(ios_base::failbit);
        }
    }
}

/**
 * Liest den Assignment-Abschnitt der Assignment-Verwaltungsdatei
 */
void API::read_assignments(ifstream &is){
    Assignment assignment;

    is >> assignment;
    int i = 0;
    while(is.good()){
        assignment_list[i] = assignment; //Erzeugt einen Entry in der Assigment-List
        i++;
        is >> assignment;
    }

    //Überprüfung ob Ende durch neuen Header, dann Stream wieder auf good() setzen
    if(!is.eof()){
        is.clear(); // Clear um die Fehlerursache zu untersuchen
        char last;
        is >> last;
        if(last == '['){
            // Fall das wir einen neuen Header gefunden haben, returned ohne Fehler
            is.unget();
            return;
        }else{
            // Setze Fehler wieder, da Syntaxproblem in Datei
            is.setstate(ios_base::failbit);
        }
    }
}

/**
 * Sucht den nächsten Header und gibt diesen zurück
 */
string API::read_header(istream& is){
    char ch;
    string header;
    is >> ch;
    if(is.good() && ch == '['){
        header = '['+ read_string(is);
    }
    if(is.fail() || is.bad()){
        return "";
    }else{
        return header;
    }
}

istream& operator>>(istream& is, User& user){
    unsigned int u_id; string name; string surname;
    is >> u_id;
    if(!is.good()) { return is; }
    name = read_string(is);
    if(!is.good()) { return is; }
    surname = read_string(is);
    if(is.fail() || is.bad()) { return is; }
    user = User{u_id, name, surname};
    return is;
}

istream& operator>>(istream& is, Task& task){
    unsigned int t_id; string name; string description; vector<unsigned int> follow_tasks;
    is >> t_id;
    if(!is.good()) { return is; }
    name = read_enclosed_string(is,'%');
    if(!is.good()) { return is; }
    description = read_enclosed_string(is,'%');
    if(!is.good()) { return is; }
    follow_tasks = read_vector(is);
    if(is.fail() || is.bad()) { return is; }
    task = Task{t_id, name, description, follow_tasks};
    return is;
}

istream& operator>>(istream& is, Assignment& assignment){
    unsigned int u_id; unsigned int t_id;;
    is >> u_id;
    if(!is.good()) { return is; }
    is >> t_id;
    if(is.fail() || is.bad()) { return is; }
    assignment = Assignment{u_id, t_id};
    return is;
}