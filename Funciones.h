#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <iostream>
#include <filesystem>
#include <fstream>
#include <time.h>
#include "MotorOrganizador.h"
#include "utils.h"

using std::cout, std::cin, std::endl;
namespace fs = std::filesystem; // usamos "fs como clave"

//prototipos
bool fijaRutas();
void registroActividad();
Gestor g; //invocamos al objeto

void menuOpciones(){
        int opc; // para seleccionar las opciones del menu
    do{
        cout<<"---------- Gestor de archivos ----------\n";
        cout<<"[1] Fijar ruta"<<endl;
        cout<<"[2] Copiar archivos"<<endl;
        cout<<"[3] Mover archivos"<<endl;
        cout<<"[4] Ver registro de actividad"<<endl;
        cout<<"[0] Salir"<<endl;
        cout<<"Opcion: "; cin>>opc;
        cin.get();

        // menu de opciones
        switch(opc){
            case FIJAR: fijaRutas(); break;
            case COPIAR: g.copiarArchivos(); break;
            case MOVER: g.MoverArchivos(); break;
            case ACTIVIDAD: break;
            case SALIR: cout<<"Byteeeess!!!!"<<endl; break;
            default: cout<<"Opcion no valida"<<endl; break;
        }
    }while(opc != SALIR);
}

bool fijaRutas(){
    std::string origen, destino; //cadenas auxiliares para definir la ruta de los archivos

    // aqui el usuario digita la ruta de origen y destino donde movera/copeara archivos
    cout<<"Digita la ruta de origen: "<<endl;
    std::getline(cin,origen);
    cout<<"Digite la ruta de destino: "<<endl;
    std::getline(cin,destino);

    //se crean caminos para validad si son directorios existentes
    fs::path fO(origen);
    fs::path fD(destino);

    // compara si las rutas digitadas por el usuario existen
    if(!fs::is_directory(origen) || !fs::is_directory(destino)){
        cout<<"-> Error, No es o no existe el directorio\n\n";
        return false;
    } // caso contrario el programa prosigue y guarda las direcciones en el objeto

 /*   if(fs::is_directory(origen) == fs::is_directory(destino)){
        cout<<"-> Error, las rutas son identicas\n\n";
        return false;
    }// caso contrario el programa prosigue y guarda las direcciones en el objeto */

    g.fijaRutaOrigen(origen);
    g.fijaRutaDestino(destino);
    cout<<"-> Rutas fijadas"<<endl;

    return true;
}

void registroActividad(){
    std::string origen,destino; // variables auxiliares para almacenar rutas
    origen = g.fijaRutaOrigen();
    destino = g.fijaRutaDestino();

    std::ofstream miArchivo ("Movimientos.txt")
    miArchivo<<origen;
    miArchivo<<destino;
    miArchivo<<system_cl
}
#endif // FUNCIONES_H_INCLUDED
