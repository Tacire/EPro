#include "api.h"

int main(void){
    API api = API("./tasks");
    cout << api.assignment_list[2].u_id << api.assignment_list[2].t_id << endl;
    return 1;
}