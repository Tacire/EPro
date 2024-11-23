#include "std_lib_inc.h"

/**
 * Liste an Ausnahmefällen zur unten definierten Regel. 
 * Zur Übersichtlichkeit in seperate Funktion gegliedert.
 */
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

/**
 * Erstellt Zahlenwort basierend auf Regel:
 * "*hundert*und*zig"
 * Ausnahmen in der Schreibweise von 10er-vielfachen sind hier abgefangen.
 * Ruft ausnahme(zahl) für sonstige Ausnahmen auf.
 */
string zahl_zu_wort(int zahl){
    string zahlen_wort = "";
    string einer[10] = {"","ein","zwei","drei","vier","fuenf","sechs","sieben","acht","neun"};

    int dritteStelle = zahl / 100;
    int zweiteStelle = (zahl % 100) / 10;
    int ersteStelle = zahl % 10;

    // Startet das Zahlenwort mit der 100er Zahl, mit der immer das Wort beginnt
    if(dritteStelle == 1){
        zahlen_wort += "hundert";
    }else if(dritteStelle > 1){
        zahlen_wort += einer[dritteStelle] + "hundert";
    }

    /** 
     *  Die Hunderterstelle ist geregelt, falls die 10er und 1er Stelle eine Ausnahme sind,
     *  wird diese dem String hinzugefügt. Ansonsten wird der String nach normaler Regel
     *  "weiterberechnet".
     */
    if(ausnahme(zahl % 100) != ""){
        zahlen_wort += ausnahme(zahl % 100);
    }else{
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
        }else if(zweiteStelle == 6){
            zahlen_wort += "sechzig";
        }else if(zweiteStelle == 7){
            zahlen_wort += "siebzig";
        }else if(zweiteStelle > 3){
            zahlen_wort += einer[zweiteStelle] + "zig";
        }
    }

    return zahlen_wort;

}

int main(){
    int zahl = 0;
    cin >> zahl;

    while(cin){
        if(zahl < 1 || zahl > 999){
            cout << "Zahl ausserhalb des gueltigen Bereichs. \n";
        }else{
            cout << zahl_zu_wort(zahl) << "\n";
        }
        cin >> zahl;
    }
    
    cout << "Eingabe beendet \n";
    return 0;
}