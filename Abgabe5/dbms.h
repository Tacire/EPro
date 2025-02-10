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
    void update();
    vector<User> get_user_list();
    vector<Task> get_task_list();
    vector<Assignment> get_assignment_list();
    User get_user(const unsigned int &u_id);
    Task get_task(const unsigned int &t_id);
    void add_user(User user);
    void add_task(Task task);
    void delete_entry(Entry_Type type, const unsigned int &id);
    void assign(const unsigned int &u_id, const unsigned int &t_id);
    void unassign(const unsigned int &u_id, const unsigned int &t_id);
    vector<unsigned int> get_active_tasks(const unsigned int &u_id);
    
  private:
    bool is_followtask(const unsigned int &task_id);
    const string file_name = "tasks";
    API api;
};

#endif