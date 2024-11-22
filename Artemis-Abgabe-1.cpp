#include "std_lib_inc.h"

string ausnahme(int zahl){
    switch(zahl){
        case 1:
            return "eins";
        case 11:
            return "elf";
        case 12:
            return "zwoelf";
        case 16:
            return "sechzehn";
        case 17:
            return "siebzehn";
        default:
            return "";
    }
}

string zahl_zu_wort(int zahl){
    string zahlen_wort = "";
    string einer[10] = {"","ein","zwei","drei","vier","fuenf","sechs","sieben","acht","neun"};

    int dritteStelle = zahl / 100;
    int zweiteStelle = (zahl % 100) / 10;
    int ersteStelle = zahl % 10;
    
    if(ausnahme(zahl) != ""){
        return ausnahme(zahl);
    }

    if(dritteStelle == 1){
        zahlen_wort += "hundert";
    }else if(dritteStelle > 1){
        zahlen_wort += einer[dritteStelle] + "hundert";
    }

    if(ersteStelle == 1){
        zahlen_wort += einer[ersteStelle];
    }else if(ersteStelle > 1){
        zahlen_wort += einer[ersteStelle] + "und";
    }

    if(zweiteStelle == 1){
        zahlen_wort += "zehn";
    }else if(zweiteStelle == 2){
        zahlen_wort += "zwanzig";
    }else if(zweiteStelle == 3){
        zahlen_wort += "dreissig";
    }else if(zweiteStelle == 7){
        zahlen_wort += "siebzig";
    }else if(zweiteStelle > 3){
        zahlen_wort += einer[zweiteStelle] + "zig";
    }

}

int main(){
    int zahl = 0;
    cin >> zahl;

    while(cin){
        if(zahl < 1 || zahl > 999){
            cout << "Zahl ausserhalb des gueltigen Bereichs. \n";
        }else{
            cout << zahl_zu_wort(zahl);
        }
        cin >> zahl;
    }
    
    cout << "Eingabe beendet \n";
    return 0;
}