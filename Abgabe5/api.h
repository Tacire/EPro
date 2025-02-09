#ifndef API_H
#define API_H
#include "std_lib_inc.h"

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

// User-Struct Überladung eines Eingabe-Streams
istream& operator>>(istream& eingabe_stream, User& user){};

// Task-Struct
struct Task{
  unsigned int t_id;
  string name;
  string desciption;
  vector<unsigned int> follow_tasks;
};

// Task-Struct Überladung eines Eingabge-Streams
istream& operator>>(istream& eingabe_stream, Task& task){};

// Assignment-Struct
struct Assginment{
  unsigned int u_id;
  unsigned int t_id;
};

// Assignment-Struct Überladung eines Eingabge-Streams
istream& operator>>(istream& eingabe_stream, Assignment& assignment){};





class API{
    public:
      API(string file_name);
      vector(user) user_list;
      vector(task) task_list;
      vector(assignment) assignments;  
      void update();
    private:
      read_data(string file_name);
      string read_string(istream& is);
      vector<unsigned int> read_vector(istream& is);
      string read_enclosed_string(istream& is, char terminator);
}
#endif