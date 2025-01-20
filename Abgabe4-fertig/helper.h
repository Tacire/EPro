// Sammlung relevanter Methoden über das gesammte Projekt
// Aktuell werden hier custom Exceptions geammelt, die in jeder Klasse geworfen werden können

#ifndef HELPER_H
#define HELPER_H
#pragma once

// Exception fuer nicht erlaubte Bewegungen
class BadMovement {};

// Exception fuer unbekannte Eingaben
class UnknownInput {};

// Exception fuer eine falsche Labyrinth-Eingabe
class BadMaze {};

#endif