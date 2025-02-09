#ifndef API_H
#define API_H
#include "std_lib_inc.h"
#include "helper.h"

/**
 * Liest Assignment-File und stellt diese als C++ Struct-Vektoren zur Verfügung
 * Speichert mit update() die geänderten Daten wieder in angegebener Datei.
 * Änderungen zwischen Lese- und Speicherzugriff werden überschrieben.
 */

// User-Struct
struct User{
  unsigned int u_id;
  string name;
  string surname;
};

// Task-Struct
struct Task{
  unsigned int t_id;
  string name;
  string desciption;
  vector<unsigned int> follow_tasks;
};

// Assignment-Struct
struct Assignment{
  unsigned int u_id;
  unsigned int t_id;
};


// Task-Struct Überladung eines Eingabge-Streams
istream& operator>>(istream& is, Task& task);
// User-Struct Überladung eines Eingabe-Streams
istream& operator>>(istream& is, User& user);
// Assignment-Struct Überladung eines Eingabge-Streams
istream& operator>>(istream& is, Assignment& assignment);

class API{
  public:
    API(const string &file_name);
    map<int, User> user_list;
    map<int, Task> task_list;
    map<int, Assignment> assignment_list;
    void update(const string &file_name);
  private:
    void read_data(const string &file_name);
    void read_tasks(ifstream &is);
    void read_users(ifstream &is);
    void read_assignments(ifstream &is);
    string read_header(istream& is);
    //static vector<unsigned int> read_vector(istream& is);
    //static string read_string(istream& is);
    //static string read_enclosed_string(istream& is, char terminator);

    const string task_header = "[tasks]";
    const string user_header = "[users]";
    const string assignment_header = "[assignments]";
};
#endif