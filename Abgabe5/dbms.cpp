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

Task get_task(const unsigned Int &t_id){
    if(task_list.find(t_id) != tasl_list.end()){
        return task_list[t_id];
    }else{
        throw Task_does_not_exist_402();
    }
}

void add_user(User user){
    int i = 0;
    while(api.user_list.find(i) != api.user_list.end()){
        i++;
        //Sucht die nächst freie User_ID
    }
    if(user.name != "" && user.surname != ""){
        user.u_id = i;
        api.user_list[i] = user;
    }

}
void add_task(Task task){
    int i = 0;
    while(api.task_list.find(i) != api.task_list.end()){
        i++;
        //Sucht die nächst freie Task_ID
    }
}