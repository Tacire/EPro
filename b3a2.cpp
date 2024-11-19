#include <iostream>
#include "std_lib_inc.h"

int main(void){
    double eins;
    double zwei;
    while(true){
        cin >> eins >> zwei;

        if(!cin){
            simple_error("Falsche Eingabe");
        }

        if((eins < zwei + (zwei * 1/100) && eins > zwei - (zwei * 1/100)) || (eins > zwei + (zwei * 1/100) && eins < zwei - (zwei * 1/100))){
            cout << eins << " und " << zwei << " sind fast gleich groß." << endl;
        }else if(eins < zwei){
            cout << eins << " ist kleiner als " << zwei << endl; 
        }else if(zwei < eins){
            cout << eins << " ist größer als " << zwei << endl;
        }else if(zwei == eins){
            cout << eins << " und " << zwei << " sind gleich." << endl;
        }
    }
}