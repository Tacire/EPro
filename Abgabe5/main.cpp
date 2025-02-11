//
// Created by hendrik on 08.02.25.
//
#include "std_lib_inc.h"
#include "helper.h"
#include "parameter_reader.h"
#include "dbms.h"

const string commands_array[] =
{
  "add", "delete", "list", "show",
  "assign", "unassign", "active", "help"
};

const string type_array[] = {"user", "task"};

const string type_plural_array[] = {"users", "tasks", "assignments"};


unsigned int read_int(stringstream& sstream)
{
  unsigned int zahl; string result;
  if (!(sstream >> zahl)) {
    throw Parameter_unreadable_102();
  }
  return zahl;
}


// User-Struct ohne ID
struct User_without_ID{
  string name;
  string surname;
};


// Task-Struct ohne ID
struct Task_without_ID{
  string name;
  string description;
  vector<unsigned int> follow_tasks;
};


//Output Overload Operator für User ohne ID, für show() Funktion
ostream& operator<<(ostream& os, const User_without_ID& user){
  os << user.name << " " << user.surname << '\n';
  return os;
}


//Output Overload Operator für Task ohne ID, für show() Funktion
ostream& operator<<(ostream& os, Task_without_ID& task){
  os << task.name << " " << task.description;
  if(!os.good()) { return os; }
  for(unsigned int follow_id : task.follow_tasks){
    cout << " " << follow_id;
    if(!os.good()) { return os; }
  }
  os << '\n';
  return os;
}


// User-Struct
struct User_local{
  unsigned int u_id;
  string name;
  string surname;
};

// Task-Struct
struct Task_local{
  unsigned int t_id;
  string name;
  string description;
  vector<unsigned int> follow_tasks;
};


//Overload Input Operator für Task Objekt, aus stream einlesen
istream& operator>>(istream& is, Task_local& task){
  string name; string description; vector<unsigned int> follow_tasks;
  name = read_enclosed_string(is,'%');
  if(!is.good()) { return is; }
  description = read_enclosed_string(is,'%');
  if(!is.good()) { return is; }
  follow_tasks = read_vector(is);
  if(is.fail() || is.bad()) { return is; }
  task = Task_local{0, name, description, follow_tasks};
  return is;
}


//Overload Input Operator für User, wird von stream eingelesen
istream& operator>>(istream& is, User_local& user){
  string name; string surname;
  name = read_string(is);
  if(!is.good()) { return is; }
  surname = read_string(is);
  if(is.fail() || is.bad()) { return is; }
  user = User_local{0, name, surname};
  return is;
}


// Exceptions sollten später alle am Ende der main in einem switch case für die richtige ausgabe stehen, denke ich
//Jetzt zum Testen erstmal immer direktes werfen und catchen am Ort, wo sie passieren


string read_command(stringstream& stream) {
  string command = read_string(stream);
  for(string template_string : commands_array){
    if(template_string == command){
        return command;
    }
  }
  throw Command_unknown_101();
}


string read_type(stringstream& stream) {
  string type = read_string(stream);
  for(string template_string : type_array){
    if(template_string == type){
        return type;
    }
  }
  throw Parameter_unreadable_102();
}


string read_type_plural(stringstream& stream) {
  string type = read_string(stream);
  for(string template_string : type_plural_array){
    if(template_string == type){
        return type;
    }
  }
  throw Parameter_unreadable_102();
}


int main(int argc, char** argv)
{
  stringstream stream = make_string_stream(argc, argv);

  try {
    string command = read_command(stream);

    string type = "";
    unsigned int user_ID = 0;
    unsigned int task_ID = 0;
    unsigned int formless_ID = 0;

    if (command == "add") {
      type = read_type(stream);
      if (type == "user") {
        User_local local_user_to_add;
        stream >> local_user_to_add;
        User user_to_add;
        user_to_add.u_id = 0;
        user_to_add.name = local_user_to_add.name;
        user_to_add.surname = local_user_to_add.surname;
        if (!stream) {throw Parameter_unreadable_102(); }
        DBMS daten_objekt = DBMS();
        daten_objekt.add_user(user_to_add); //hier wird wenn erfolgreich 100 zurückgegeben
        cout << "100: Alles erfolgreich\n";
      }
      else if (type == "task") {
        Task_local local_task_to_add;
        stream >> local_task_to_add;
        Task task_to_add;
        task_to_add.t_id = local_task_to_add.t_id;
        task_to_add.name = local_task_to_add.name;
        task_to_add.description = local_task_to_add.description;
        task_to_add.follow_tasks = local_task_to_add.follow_tasks;
        if (!stream) {throw Parameter_unreadable_102(); }
        DBMS daten_objekt = DBMS();
        daten_objekt.add_task(task_to_add);
        cout << "100: Alles erfolgreich\n";
      }
    }
    else if (command == "delete") {
      type = read_type(stream);
      Entry_Type type_delete;
      if (type == "user") {
        type_delete = USER;
      }
      else if (type == "task") {
        type_delete = TASK;
      }
      user_ID = read_int(stream);
      DBMS daten_objekt = DBMS();
      daten_objekt.delete_entry(type_delete, user_ID);
      cout << "100: Alles erfolgreich\n";
    }
    else if (command == "list") {
      type = read_type_plural(stream);
      if (type == "tasks") {
        DBMS daten_objekt = DBMS();
        vector<Task> task_list = daten_objekt.get_task_list();
        for (Task task: task_list) {
          cout << task;
        }
      }
      if (type == "users") {
        DBMS daten_objekt = DBMS();
        vector<User> user_list = daten_objekt.get_user_list();
        for (User user: user_list) {
          cout << user;
        }
      }
      if (type == "assignments") {
        DBMS daten_objekt = DBMS();
        vector<Assignment> assignment_list = daten_objekt.get_assignment_list();
        for (Assignment assignment: assignment_list) {
          cout << assignment;
        }
      }
    }
    else if (command == "show") {
      type = read_type(stream);
      formless_ID = read_int(stream);
      if (type == "user") {
        DBMS daten_objekt = DBMS();
        User user_to_show = daten_objekt.get_user(formless_ID);
        User_without_ID user_without_id;
        user_without_id.name = user_to_show.name;
        user_without_id.surname = user_to_show.surname;
        cout << user_without_id << "\n";
      }
      if (type == "task") {
        DBMS daten_objekt = DBMS();
        Task task_to_show = daten_objekt.get_task(formless_ID);
        Task_without_ID task_without_id;
        task_without_id.name = task_to_show.name;
        task_without_id.description = task_to_show.description;
        task_without_id.follow_tasks = task_to_show.follow_tasks;
        cout << task_without_id;
      }
    }
    else if (command == "assign") {
      DBMS daten_objekt = DBMS();
      user_ID = read_int(stream);
      task_ID = read_int(stream);
      daten_objekt.assign(user_ID, task_ID);
      cout << "100: Alles erfolgreich\n";
    }
    else if (command == "unassign") {
      DBMS daten_objekt = DBMS();
      user_ID = read_int(stream);
      task_ID = read_int(stream);
      daten_objekt.unassign(user_ID, task_ID);
      cout << "100: Alles erfolgreich\n";
    }
    else if (command == "active") {
      DBMS daten_objekt = DBMS();
      user_ID = read_int(stream);
      vector<unsigned int> active_tasks = daten_objekt.get_active_tasks(user_ID);
      if (!active_tasks.empty()) {
        for (int i: active_tasks) {
          cout << i << "\n";
        }
      }
      else {
        cout << "\n";
      }
    }
    else if (command == "help") {
      cout << "Hier soll eine Hilfe ausgegeben werden, OHNE CODE 100" << "\n";
      return 0;
    }
  }
  catch (Command_unknown_101& e101) {
    cout << e101.what();
  }
  catch (Parameter_unreadable_102& e102) {
    cout << e102.what();
  }
  catch (User_not_deletable_201& e201) {
    cout << e201.what();
  }
  catch (Task_not_deletable_202& e202) {
    cout << e202.what();
  }
  catch (Assignment_does_not_exist_301& e301) {
    cout << e301.what();
  }
  catch (Assignment_already_exists_302& e302) {
    cout << e302.what();
  }
  catch (User_does_not_exist_401& e401) {
    cout << e401.what();
  }
  catch (Task_does_not_exist_402& e402) {
    cout << e402.what();
  }
  catch (File_not_openable_601& e601) {
    cout << e601.what();
  }
  catch (File_format_unknown_602& e602) {
    cout << e602.what();
  }
  catch (File_not_writable_603& e603) {
    cout << e603.what();
  }


  return 0;
}