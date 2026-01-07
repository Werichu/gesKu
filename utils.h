#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
#include <iostream>
#include <ctime>
#include <cstring>

enum {SALIR,FIJAR,COPIAR,MOVER,ACTIVIDAD};

std::string fechaActual(){
    time_t ahora = time(0);
    char* fecha = ctime(&ahora);

    return fecha;
}

#endif // UTILS_H_INCLUDED
