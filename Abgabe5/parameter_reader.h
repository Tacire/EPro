/*
 * Autor: Fritz Bökler (November 2023)
 *
 * Diese Header Datei enthält nur die Funktion
 * stringstream make_string_stream(int argc, char** args).
 *
 * Diese ermöglicht die Übergabe der Parameter einer main-Funktion
 * mit Kommandozeilenparametern
 * int main(int argc, char** argv)
 * direkt an einen stringstream, mit dem dann mithilfe des C++
 * Stream-Modells gearbeitet werden kann.
 *
 * Benutzung: Um mit den Kommandozeilen-Parametern zu arbeiten, einfach statt der
 * int main()
 * Funktion, die Funktion
 * int main(int argc, char** argv)
 * definieren und darin mit dem Aufruf
 * stringstream string_stream = make_string_stream(argc, argv);
 * einen stringstream string_stream erzeugen, der die Kommandozeilen-Parameter enthält.
 *
 * Die Parameter können dann mittels
 * string_stream >> var;
 * nacheinander in anderen Variablen unterschiedlicher Typen gespeichert werden.
 *
 */
#pragma once
#include <sstream>

inline std::stringstream make_string_stream(int argc, char** argv)
{
    std::stringstream string_stream;
    for(int i = 1; i < argc; ++i)
    {
        string_stream << argv[i] << ' ';
    }

    return string_stream;
}