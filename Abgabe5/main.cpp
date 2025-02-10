#include "api.h"

int main(void){
    API api = API("./tasks");
    api.user_list[17] = User{17, "Theodor"};
    api.update("./tasks");
    cout << api.assignment_list[2].u_id << api.assignment_list[2].t_id << endl;
    return 1;
}