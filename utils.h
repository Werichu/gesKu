#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
#include <iostream>
#include <ctime>

enum {SALIR,FIJAR,COPIAR,MOVER,ACTIVIDAD};

void fechaActual(){
    std::string fecha;
    time_t tiempoAhora;
    tiempoAhora = time(NULL);
    ctime(&tiempoAhora);
}

#endif // UTILS_H_INCLUDED
