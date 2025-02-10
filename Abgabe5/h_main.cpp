//
// Created by hendrik on 08.02.25.
//
#include "std_lib_inc.h"
#include "helper.h"
#include "parameter_reader.h"

const string commands_array[] =
{
  "add", "delete", "list", "show",
  "assign", "unassign", "active", "help"
};

const string type_array[] = {"user", "task"};

const string type_plural_array[] = {"users", "tasks", "assignments"};

/**
 * Liest einen String aus dem Stream bis zum ersten Space
 * Basiert auf Vorlesungsbeispiel
 */
string read_string(stringstream& sstream)
{
  char ch; string result;
  sstream.get(ch);
  while(sstream.good() && !isspace(ch))
  {
    result += ch;
    sstream.get(ch);
  }
  if(sstream.fail() || sstream.bad()) { return ""; }
  return result;
}


int read_int(stringstream& sstream)
{
  int zahl; string result;
  if (!(sstream >> zahl)) {
    throw Parameter_unreadable_102();
  }
  return zahl;
}


/**
 * Liest einen enclosed String aus dem Stream
 * Basiert auf Vorlesungsbeispiel
 */
string read_enclosed_string(stringstream& sstream, char terminator)
{
  char ch; string result;
  sstream.get(ch);
  //Wenn der Stream nicht ok ist, oder der String nicht mit Terminator beginnt
  // Wird direkt abgebrochen und ein Fehler ausgegeben
  if(!sstream.good() || ch != terminator) {
    sstream.setstate(ios_base::failbit);
    return "";
  }
  while(sstream.good() && ch != terminator)
  {
    result += ch;
    sstream.get(ch);
  }
  //Falls String nicht mit Terminator beendet ist, ist ein Fehler aufgetreten
  if(ch != terminator) {
    sstream.setstate(ios_base::failbit);
  }
  if(sstream.fail() || sstream.bad()) {
    return "";
  }
  return result;
}


struct Command_struct {
  string command;
  string type;
};

// Exceptions sollten später alle am Ende der main in einem switch case für die richtige ausgabe stehen, denke ich
//Jetzt zum Testen erstmal immer direktes werfen und catchen am Ort, wo sie passieren


string read_command(stringstream& stream) {
  string command = read_string(stream);
  const string *cmd = std::find(std::begin(commands_array), std::end(commands_array), command);
  if (cmd == std::end(commands_array)) {
    throw Command_unknown_101();
  }
  return command; //Hier wird nur durchgeführt, wenn Befehl gültig war , also keine Exception geworfen wurde
}


string read_type(stringstream& stream) {
  string type = read_string(stream);
  const string *type_ptr = std::find(std::begin(type_array), std::end(type_array), type);
  if (type_ptr == std::end(type_array)) {
    throw Parameter_unreadable_102();
  }
  return type; //Hier wird nur durchgeführt, wenn Befehl gültig war , also keine Exception geworfen wurde
}


string read_type_plural(stringstream& stream) {
  string type = read_string(stream);
  const string *type_ptr = std::find(std::begin(type_plural_array), std::end(type_plural_array), type);
  if (type_ptr == std::end(type_array)) {
    throw Parameter_unreadable_102();
  }
  return type; //Hier wird nur durchgeführt, wenn Befehl gültig war , also keine Exception geworfen wurde
}


int main(int argc, char** argv)
{
  stringstream stream = make_string_stream(argc, argv);

  try {
    string command = read_command(stream);
    cout << command << ".\n";

    string type = "";
    int user_ID = 0;
    int task_ID = 0;
    int formless_ID = 0;

    if (command == "add") {
      type = read_type(stream);
      //Nutzer oder Aufgabe lesen
    }
    else if (command == "delete") {
      type = read_type(stream);
      //Nutzer oder Aufgabe lesen
    }
    else if (command == "show") {
      type = read_type(stream);
      formless_ID = read_int(stream);
    }
    else if (command == "list") {
      type = read_type_plural(stream);
    }
    else if (command == "assign") {
      user_ID = read_int(stream);
      task_ID = read_int(stream);
    }
    else if (command == "unassign") {
      user_ID = read_int(stream);
      task_ID = read_int(stream);
    }
    else if (command == "active") {
      user_ID = read_int(stream);
    }
    else if (command == "help") {
      cout << "Hier soll eine Hilfe ausgegeben werden, OHNE CODE 100";
    }

    cout << type << ".\n" << user_ID << ".\n" << task_ID << ".\n" << formless_ID << ".\n";
  }
  catch (Command_unknown_101& e101) {
    cout << e101.what();
  }
  catch (Parameter_unreadable_102& e102) {
    cout << e102.what();
  }


  return 0;
}