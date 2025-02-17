/**
 * Database-Management System. Nutzt die Schnittstelle zur Textfile (api) um Datenmanagement durchzuführen.
 */

#include "dbms.h"

//Ruft im Konstruktor den API-Konstruktor auf. Dieser lädt alle Daten
DBMS::DBMS() : api(file_name){}

//überprüft gesammelte Daten und startet den Schreibvorgang
void DBMS::update(){
    api.valid();
    api.update(file_name);
}

vector<User> DBMS::get_user_list(){
    vector<User> users;
    for(auto user : api.user_list){
        users.push_back(user.second);
    }
    return users;
}

vector<Task> DBMS::get_task_list(){
    vector<Task> tasks;
    for(auto task : api.task_list){
        tasks.push_back(task.second);
    }
    return tasks;
}

vector<Assignment> DBMS::get_assignment_list(){
    vector<Assignment> assignments;
    for(auto assignment : api.assignment_list){
        assignments.push_back(assignment.second);
    }
    return assignments;
}

User DBMS::get_user(const unsigned int &u_id){
    if(api.user_list.find(u_id) != api.user_list.end()){
        return api.user_list[u_id];
    }else{
        throw User_does_not_exist_401();
    }
}

Task DBMS::get_task(const unsigned int &t_id){
    if(api.task_list.find(t_id) != api.task_list.end()){
        return api.task_list[t_id];
    }else{
        throw Task_does_not_exist_402();
    }
}

//Findet nächste freie ID und speichert den Nutzer, wenn Syntax korrekt
void DBMS::add_user(User user){
    int next_smallest_index = 0;
    if(!api.user_list.empty()){
        next_smallest_index = api.user_list.rbegin()->first + 1;
    }
    if(user.name != "" && user.surname != ""){
        user.u_id = (unsigned)next_smallest_index;
        api.user_list[next_smallest_index] = user;
    }else{
        throw Parameter_unreadable_102();
    }
    update();
    return;

}

//Überprüft ob die Übergebene Task korrektes Format und Inhalt hat, speichert diese mit der nächsten ID in der Task-Map
void DBMS::add_task(Task task){
    int next_smallest_index = 0;
    if(!api.task_list.empty()){
        next_smallest_index = api.task_list.rbegin()->first + 1;
    }
    if(!api.task_valid(task)){
        throw Parameter_unreadable_102();
    }else if(!api.follow_tasks_valid(task)){
        throw Task_does_not_exist_402();
    }
    task.t_id = (unsigned)next_smallest_index;
    api.task_list[next_smallest_index] = task;
    update();
    return;
}

// Überprüft ob eine Task die Folgetask einer anderen ist
bool DBMS::is_followtask(const unsigned int &task_id){
    for(auto other_tasks : api.task_list){
        for(unsigned int follow_task : other_tasks.second.follow_tasks){
            if(follow_task == task_id){
                return true;
            }
        }
    }
    return false;
}

//Deleted ein Objekt von der ID und spezifizierten Typen
void DBMS::delete_entry(Entry_Type type, const unsigned int &id){
    if(type == USER){
      if(api.user_list.find((int)id) != api.user_list.end()){
        for(auto assignment : api.assignment_list){
          if(assignment.second.u_id == id){
            throw User_not_deletable_201();
          }
        }
        api.user_list.erase((int)id); // Lösche User wenn existierend und nicht zugeordnet
        update();
      }else{
        throw User_does_not_exist_401();
      }
    }else if(type == TASK){
      if(api.task_list.find((int)id) != api.task_list.end()){
        for(auto assignment : api.assignment_list){
          if(assignment.second.t_id == id){
            throw Task_not_deletable_202();
          }
        }
        // Überprüft ob die Task eine Folgetask ist
        if(is_followtask(id)){
          throw Task_not_deletable_202();
        }
        api.task_list.erase((int)id); // Lösche Task wenn existierend und nicht zugeordnet
        update();
      }else{
        throw Task_does_not_exist_402();
      }
    }else(throw Parameter_unreadable_102());
}

//Überprüft ob die ID's existieren und erzeugt dann eine Zuordnung
void DBMS::assign(const unsigned int &u_id, const unsigned int &t_id){
    for(auto assignment : api.assignment_list){
        if(assignment.second.u_id == u_id && assignment.second.t_id == t_id){
            // Zuordnung existiert schon
            throw Assignment_already_exists_302();
        }
    }
    if(api.user_list.find((int)u_id) == api.user_list.end()){
        throw User_does_not_exist_401();
    }else if(api.task_list.find((int)t_id) == api.task_list.end()){
        throw Task_does_not_exist_402();
    }
    // Finde erste freie ID in der Assignment-Liste
    int a_id = 0;
    while(api.assignment_list.find(a_id) != api.assignment_list.end()){
        a_id++;
    }
    Assignment new_assignment = {u_id,t_id};
    api.assignment_list[a_id] = new_assignment;
    update();
    return;
}

// Löscht ein Assignment, wenn es existiert
void DBMS::unassign(const unsigned int &u_id, const unsigned int &t_id){
    for(auto assignment : api.assignment_list){
        if(assignment.second.u_id == u_id && assignment.second.t_id == t_id){
            // Zuordnung existiert schon
            api.assignment_list.erase(assignment.first);
            update();
            return;
        }
    }
    throw Assignment_does_not_exist_301();
}

//Gibt alle Tasks aus, die einem Nutzer zugeordnet sind und keine Folgetasks sind
vector<unsigned int> DBMS::get_active_tasks(const unsigned int &u_id){
    vector<unsigned int> list_active_tasks;
    if(api.user_list.find((int)u_id) == api.user_list.end()){
        throw User_does_not_exist_401();
    }
    
    for(auto assignment : api.assignment_list){
        if(assignment.second.u_id == u_id){
            if(!is_followtask(assignment.second.t_id)){
                list_active_tasks.push_back(assignment.second.t_id);
            }
        }
    }
    return list_active_tasks;
}