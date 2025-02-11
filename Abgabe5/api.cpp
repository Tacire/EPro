#include "api.h"

/**
 * Liest Assignment-File und stellt diese als C++ Struct-Vektoren zur Verfügung
 * Speichert mit update() die geänderten Daten wieder in angegebener Datei.
 * Änderungen zwischen Lese- und Speicherzugriff werden überschrieben.
 */
API::API(const string &file_name){
    read_data(file_name);
}

bool API::valid(){
    // Überprüft Task Einträge
    for(auto task : task_list){
        if(task.first != (int)task.second.t_id){
            return false;
        }else if(!task_valid(task.second)){
            return false;
        }else if(!follow_tasks_valid(task.second)){
            return false;
        }
    }
    // Überprüft User Einträge
    for(auto user : user_list){
        if(user.first != (int)user.second.u_id || user.second.name == "" || user.second.surname == ""){
            return false;
        }
    }
    // Überprüft Assignment Einträge
    for(auto assignment : assignment_list){
        //Überprüft ob angegebene ID's existieren
        if(user_list.find((int)assignment.second.u_id) == user_list.end()){
            return false;
        }else if(task_list.find((int)assignment.second.t_id) == task_list.end()){
            return false;
        }
    }
    return true;
}

// Überprüft ob eine Task valid ist. ID wird nicht überprüft
bool API::task_valid(const Task &task){
    if(task.name == "" || task.description == ""){
        return false;
    }else if(task.name[0] != '%' || task.name.back() != '%' ){
        return false;
    }else if(task.description[0] != '%' || task.description.back() != '%' ){
        return false;
    }
    return true;
}

// Überprüft alle Follow Tasks auf Korrektheit
bool API::follow_tasks_valid(const Task &task){
    for(unsigned int follow_tasks : task.follow_tasks){
        //Überprüft ob Task_ID nicht in task_list existiert
        if(task_list.find((int)follow_tasks) == task_list.end()){
            return false;
        }
    }
    return true;
}

void API::update(const string &file_name){
    ofstream os(file_name, ios_base::trunc);
    if(!os.good()) {throw File_not_writable_603();}

    os << "[tasks]\n";
    for(auto task : task_list){
        os << task.second;
        if(!os.good()) {throw File_not_writable_603();}
    }
    os << "\n[users]\n";
    for(auto user : user_list){
        os << user.second;
        if(!os.good()) {throw File_not_writable_603();}
    }
    os << "\n[assignments]\n";
    for(auto assignment : assignment_list){
        os << assignment.second;
        if(!os.good()) {throw File_not_writable_603();}
    }
    return;
}

/**
 * Liest Assignment-Verwaltungsdatei. Erstellt passende C++-Objekte
 */
void API::read_data(const string &file_name){
    ifstream is(file_name);
    if(!is) {
        update(file_name);
        return;
    }

    string header = read_header(is);
    while(true){ // Läuft bis zum Ende der Datei
        if(is.eof() && !is.bad()){
            return;
        }else if(is.fail() || is.bad()){
            throw File_format_unknown_602();
        }else{
            if(header == user_header){read_users(is);}
            else if(header == task_header){read_tasks(is);}
            else if(header == assignment_header){read_assignments(is);}
            else{throw File_format_unknown_602();} //Falscher Header
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

ostream& operator<<(ostream& os, User& user){
    os << user.u_id << " " << user.name << " " << user.surname << '\n';
    return os;
}

ostream& operator<<(ostream& os, Task& task){
    os << task.t_id << " " << task.name << " " << task.description;
    if(!os.good()) { return os; }
    for(unsigned int follow_id : task.follow_tasks){
        os << " " << follow_id;
        if(!os.good()) { return os; }
    }
    os << '\n';
    return os;
}

ostream& operator<<(ostream& os, Assignment& assignment){
    os << assignment.u_id << " " << assignment.t_id << '\n';
    return os;
}
