#include <iostream>
#include "std_lib_inc.h"

string comment = "\033[32m";
string m_error = "\033[31m";
string letter = "\033[34m";

string get_input(){
    string korrekte_eingabe = " ";
    cin >> korrekte_eingabe;
    while(true){
        if(!cin){
            cout << m_error + "Bitte einen Namen eingeben:" << endl;
            cin.clear();
            cin.ignore();
            cin >> korrekte_eingabe;
        }else if(cin){
            return korrekte_eingabe;
        }
    }
}

char get_char_input(){
    char korrekte_eingabe = '0';
    cin >> korrekte_eingabe;
    while(true){
        if(!cin){
            cout << m_error + "Bitte einen Buchstaben eingeben:" << endl;
            cin.clear();
            cin.ignore();
            cin >> korrekte_eingabe;
        }else if(cin){
            return korrekte_eingabe;
        }
    }
}

int get_int_input(){
    int korrekte_eingabe = 0;
    cin >> korrekte_eingabe;
    while(true){
        if(!cin){
            cout << m_error + "Bitte eine Zahl eingeben:" << endl;
            cin.clear();
            cin.ignore();
            cin >> korrekte_eingabe;
        }else if(cin){
            return korrekte_eingabe;
        }
    }
}

int main(){
    cout << comment + "Lieber Leser, geben Sie Ihren Namen ein:" << endl;
    string autor_name = get_input();
    cout << comment + "Moin " + autor_name << endl;
    cout << comment + "Gib den Namen des Adressaten des Briefs ein" << endl;
    string leser_name = get_input();
    cout << letter + "Hallo " + leser_name + "\nAlles klar bei dir? Wie steht's? Lass mal wieder was machen!" << endl;
    cout << comment + "Erinnerst du dich an: " << endl;
    string freund_name = get_input();
    cout << letter + "Hast du " + freund_name + " in letzter Zeit gesehen?" << endl;
    char freund_geschlecht = '0';
    cout << comment + "Gib das Geschlecht von " + freund_name + " ein (m/w)" << endl;
    freund_geschlecht = get_char_input();
    while(!(freund_geschlecht == 'm' || freund_geschlecht == 'w')){
        cout << comment + "Bitte im Format (m/w) angeben" <<endl;   
        freund_geschlecht = get_char_input(); 
    }
    if(freund_geschlecht == 'm'){
        cout << letter +"Wenn du " + freund_name +" siehst, sag ihm bitte, er soll mich anrufen." <<endl;
    }else if(freund_geschlecht == 'w'){
        cout << letter +"Wenn du " + freund_name +" siehst, sag ihr bitte, sie soll mich anrufen." <<endl;
    }

    cout << comment + "Wie alt ist der/die Empfänger*in nochmal?" << endl;
    int alter = get_int_input();

    if( alter < 0 || alter > 110){
        cout << m_error;
        simple_error("Das kann nicht sein!"); 
    }

    if(alter <= 12){
        int geburtstagsalter = alter+1;
        cout << letter + "Nächstes Jahr wirst du "; 
        cout << geburtstagsalter;
        cout << " Jahre alt!" << endl;
    }else if (alter == 17){
        cout << letter + "Nächstes Jahr darfst du wählen!" << endl;
    }else if (alter > 70){
        cout << letter + "Ich hoffe dir bekommt die Rente!" << endl;
    }

    cout << letter + "Viele Grüße," << endl << endl;
    cout << letter + autor_name << endl;
    cout << "\033[39mBye" << endl;
    return 0;
}