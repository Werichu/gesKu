#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <iostream>
#include <filesystem>
#include <time.h>
#include "MotorOrganizador.h"
#include "utils.h"

using std::cout, std::cin, std::endl;
namespace fs = std::filesystem; // usamos "fs como clave"

//prototipos
bool fijaRutas();
void registroActividad(std::string, std::string);
void cargarArchivo();
void mostrarArchivo();
Gestor g; //invocamos al objeto

void menuOpciones(){
/*
    Esta funcion administra la funcionalidad de la aplicacion, a si misma, aqui son invocadas las funciones
    que hacen posible su correcta ejecucion
*/
        int opc; // para seleccionar las opciones del menu
        cargarArchivo();
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
            case ACTIVIDAD: mostrarArchivo(); break;
            case SALIR: cout<<"Byteeeess!!!!"<<endl; break;
            default: cout<<"Opcion no valida"<<endl; break;
        }
    }while(opc != SALIR);
}

bool fijaRutas(){
/*
    Esta funcion fija las rutas digitadas por el usuario hacia el objeto que administra la organiacion de los archivos
        Variables auxiliares:
            string origen:
            string destino: {estas variables almacenan las rutas digitadas por el usuario}
*/
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

    /*if(fs::is_directory(origen) == fs::is_directory(destino)){
        cout<<"-> Error, las rutas son identicas\n\n";
        return false;
    }// caso contrario el programa prosigue y guarda las direcciones en el objeto */

    //aqui se guardan las direcciones digitadas por el usuario y se pasan al objeto
    g.fijaRutaOrigen(origen);
    g.fijaRutaDestino(destino);
    registroActividad(origen,destino);
    cout<<"-> Rutas fijadas"<<endl;

    return true;
}

void registroActividad(std::string CopiaOrigen, std::string CopiaDestino){
/*
Esta funcion se encarga de guardar el registro de las rutas en un archivo
    Argumentos de la funcion:
        string CopiaOrigen, CopiaDestino: # Se reciben las copias de las rutas digitadas por el usuario las cuales posteriormente se aniadiran al archivo

    Variables auxiliares de la funcion:

        string fecha: # Variable que ayuda a almacenar la fecha actual del equipo almacenada recibe los datos de la funcion "fecha actual"
        almacenada en el archivo de cabezera "utils.h

        std:: ofstream miArchivo: # Acompaniada de "::std::ios::app" evita que lo escrito anteriormente en mi archivo se borre una vez se almacene la copia de una ruta
*/
    std::string fecha;

    // el retorno de la funcion "fecha actual" es almacenada en una variable
    fecha = fechaActual();

    // Se crea el objeto archivo acompaniado de "ios::app" para evitar el borrado de una escritura anterior
    std::ofstream miArchivo ("Movimientos.txt", std::ios::app);
    miArchivo<<CopiaOrigen<<endl;
    miArchivo<<CopiaDestino<<endl;
    miArchivo<<fecha<<endl;
    miArchivo<<"-------------------"<<endl;
    miArchivo.close();
}

void cargarArchivo(){
/*
    Esta funcion de encarga de cargar un archivo generado anteriormente con el nombre de "Movimientos.txt" la finalidad de esto es preservar movimientos
    anteriormente realizados fomentando asi la conciencia de las acciones de usuario


    Variables auxiliares:
        string linea: # cuando llegamos a esta iteracion "while(getline(miArchivo,linea))" el archivo se estara leyendo linea por linea hasta encontrar un salto de linea

        string contenido: # esta variable es acumulativa, va almacenando en contenido de la variable "linea" junto con un salto de linea para la correcta separacion de los datos
        gracias a esta variable podemos tener un orden al cargar el archivo

    Ejemplo de almacenamiento de las variables:
        linea = {rutaOrigen\nrutaDestino\nfecha\n"------"\n}

        contenido = {
            rutaOrigen\n
            rutaDestino\n
            fecha\n
            "---------------"\n
        }
*/
    // declaracion de variables y objeto archivo "si es que existe"
    std::string linea, contenido;
    std::ifstream miArchivo ("Movimientos.txt");

    // si el archivo no existe mostrara este mensaje
    if(!miArchivo){
        std::cerr<<"-> Error en cargar el archivo"<<endl;
        return;
    }

    // si existe entonces el bucle iniciara y se leera el contenido hasta que llegue a su fin
    if(miArchivo.is_open()){
        while(getline(miArchivo,linea)){
            contenido += linea + "\n";
        }

        cout<<"-> Archivo cargado"<<endl;
        miArchivo.close();
    }
}

void mostrarArchivo(){
/*
    Esta funcion muestra el contenido del archivo al usio en la consola evitando asi ir a la carpeta donde tenga la ubicacion del programa

    Variables auxiliares:
        string texto: #Esta funcion almacena toda la informacion del archivo al ser iterado nuevamente por un ciclo while hasta encontrar un salto de linea
*/
    // declaracion de variables auxiliares y objeto archivo
    std::string texto;
    std::ifstream miArchivo ("Movimientos.txt");

    // si mi archivo no existe mostrara ese mensaje de error
    if(!miArchivo){
        std::cerr<<"-> Error en cargar el archivo"<<endl;
        return;
    }

    // caso contrario si existe este se abrira y se empezara la iteracion hasta el fin delo mismo
    if(miArchivo.is_open()){
        while(getline(miArchivo,texto)){
            cout<<texto<<endl;
        }

        cout<<"-> Archivo cargado"<<endl;
        miArchivo.close();
    }
}
#endif // FUNCIONES_H_INCLUDED
