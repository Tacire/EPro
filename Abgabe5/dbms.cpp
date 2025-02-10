/**
 * Database-Management System. Nutzt die Schnittstelle zur Textfile (api) um Datenmanagement durchzuführen.
 */

#include dbms.h

DBMS::DBMS(){
    api = API(file_name);
};

vector<User> DBMS::get_user_list(){
    vector<User> users;
    for(auto user : api.user_list){
        users.push_back(user.second);
    }
    return users;
}
vector<Task> DBMS::get_task_list(){
    vector<task> taks;
    for(auto task : api.task_list){
        task.push_back(task.second);
    }
    return tasks;
}
vector<Assignment> DBMS::get_assignment_list(){
    vector<User> assignments;
    for(auto assignment : api.assignment_list){
        assignments.push_back(assignment.second);
    }
    return assignments;
}

User DBMS::get_user(const unsigned Int &u_id){
    if(api.user_list.find(u_id) != api.user_list.end()){
        return api.user_list[u_id];
    }else{
        throw User_does_not_exist_401();
    }
}

Task DBMS::get_task(const unsigned Int &t_id){
    if(task_list.find(t_id) != tasl_list.end()){
        return task_list[t_id];
    }else{
        throw Task_does_not_exist_402();
    }
}

void DBMS::add_user(User user){
    unsigned int i = 0;
    while(api.user_list.find((int)i) != api.user_list.end()){
        i++;
        //Sucht die nächst freie User_ID
    }
    if(user.name != "" && user.surname != ""){
        user.u_id = i;
        api.user_list[(int)i] = user;
    }else{
        throw Parameter_unreadable_102();
    }
    return;

}
void DBMS::add_task(Task task){
    unsigned int i = 0;
    if(!api.task_valid(task)){
        throw Parameter_unreadable_102();
    }else if(!api.follow_tasks_valid(task)){
        throw Task_does_not_exist_402();
    }
    while(api.task_list.find((int)i) != api.task_list.end()){
        i++;
        //Sucht die nächst freie Task_ID
    }
    task.t_id = i;
    api.task_list[(int)i] = task;
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
}

//Deleted ein Objekt von der ID
void DBMS::delete(Entry_Type type, const unsigned int &id){
    if(type == USER){
      if(api.user_list.find((int)id) != api.user_list.end()){
        for(auto assignment : api.assignment_list){
          if(assignment.second.u_id == id){
            throw User_not_deletable_201("Benutzer zugeordnet");
          }
        }
        api.user_list.erase((int)id); // Lösche User wenn existierend und nicht zugeordnet
      }else{
        throw User_does_not_exist_401();
      }
    }else if(type == TASK){
      if(api.task_list.find((int)id) != api.task_list.end()){
        for(auto assignment : api.assignment_list){
          if(assignment.second.t_id == id){
            throw Task_not_deletable_202("Task zugeordnet");
          }
        }
        // Überprüft ob die Task eine Folgetask ist
        if(is_followtask(id)){
          throw Task_not_deletable_202("Task Folgetask eines anderen Tasks");
        }
        api.task_list.erase((int)id); // Lösche Task wenn existierend und nicht zugeordnet
      }else{
        throw Task_does_not_exist_402();
      }
    }else(throw Parameter_unreadable_102);
}

void DBMS::assign(const unsigned Int &u_id, const unsigned Int &t_id){
    for(auto assignment : api.assignment_list){
        if(assignment.second.u_id == u_id && assignment.second.t_id == t_id){
            // Zuordnung existiert schon
            throw Assignment_already_exists_302();
        }
    }
    if(api.user_list.find((int)id) == api.user_list.end()){
        throw User_does_not_exist_401();
    }else if(api.task_list.find((int)id) == api.task_list.end()){
        throw Task_does_not_exist_402();
    }
    // Finde erste freie ID in der Assignment-Liste
    int a_id = 0;
    while(api.assignment_list.find(id) != api.assignment_list.end()){
        i++;
    }
    Assignment new_assignment = {u_id,t_id}
    assignment_list[a_id] = new_assignment;
    return;
}

// Löscht ein Assignment, wenn es existiert
void DBMS::unassign(const unsigned Int &u_id, const unsigned Int &t_id){
    for(auto assignment : api.assignment_list){
        if(assignment.second.u_id == u_id && assignment.second.t_id == t_id){
            // Zuordnung existiert schon
            api.assignment_list.erase(assignment.first);
            return;
        }
    }
    throw Assignment_does_not_exist_301();
}

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