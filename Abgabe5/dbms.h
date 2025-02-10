#ifndef DBMS_H
#define DBMS_H

/**
 * Database-Management System. Nutzt die Schnittstelle zur Textfile (api) um Datenmanagement durchzuführen.
 */

#include "std_lib_inc.h"
#include "helper.h"
#include "api.h"


enum Entry_Type {
  USER,
  TASK,
}; 

class DBMS{
  public:
    DBMS();
    vector<User> get_user_list();
    vector<Task> get_task_list();
    vector<Assignment> get_assignment_list();
    User get_user(const unsigned Int &u_id);
    Task get_task(const unsigned Int &t_id);
    void add_user(User user);
    void add_task(Task task);
    void delete(Entry_Type type, const unsigned int &u_id);
    void assign(const unsigned Int &u_id, const unsigned Int &t_id);
    void unassign(const unsigned Int &u_id, const unsigned Int &t_id);
    vector<unsigned int> get_active_tasks(const unsigned Int &u_id);
  private:
    constexpr string file_name = "./tasks";
    API api;
}

#endif