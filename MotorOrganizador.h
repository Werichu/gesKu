#ifndef MOTORORGANIZADOR_H_INCLUDED
#define MOTORORGANIZADOR_H_INCLUDED
#include <iostream>
#include <filesystem>
#include <fstream>
#include "Funciones.h"

namespace fs = std::filesystem; // para usar "fs como clave de acceso a la biblioteca
using std::cout, std::endl; // usar la biblioteca estandar

/*
    Este objeto se encarga de manejar los archivos y utiliza las rutas digitadas por el usuario para la operacion
*/

class Gestor{
    std::string rutaOrigen;
    std::string rutaDestino;

public:
    //metodos setters
    void fijaRutaOrigen(std::string origen){
        rutaOrigen = origen;
    }

    void fijaRutaDestino(std::string destino){
        rutaDestino = destino;
    }

    //metodos getters
    // en esta ocasion no habra, se decidio usar el acceso directo de los atributos del objeto


    void copiarArchivos(){
    /*
        Esta funcion se encarga del copiado de archivos de un diractorio a otro
            Variables auxiliares:
                string RutaOrigen: <acceso directo a los atributos privados del objeto>
                string RutaOrigen: <acceso directo a los atributos privados del objeto>
                const fs::path& origen <estas variables tranforman las cadenas digitadas por el usuario a rutas o "caminos" de ficheros>
                const fs::path& destino <estas variables tranforman las cadenas digitadas por el usuario a rutas o "caminos" de ficheros>
    */

        // utilizamos la direccion de memoria de las rutas digitadas por el usuario
        const fs::path& origen = rutaOrigen;
        const fs::path& destino = rutaDestino;

        try{
            fs::create_directories(destino); // en caso de que no exista el destino este se creara automaticamente
            fs::copy(origen,destino, fs::copy_options::recursive); // si ambas rutas existen el programa continuara exitosamente
            cout<<"Se ha copiedo exitosamente de: "<<origen<<" a "<<destino<<std::endl;
        }catch(const fs::filesystem_error& e){// en caso de que no se capturara el error y el programa terminara
            std::cerr<<"error en copiar: "<<e.what()<<std::endl;
            }
    }

    void MoverArchivos(){
    /*
        Esta funcion s eencarga de mover archivos, en si copea lo que tiene un directorio o archivo a otro, se elimina
        y se vuelve a crear el directorio de origen, funciona de manera similar al copeado solo con ese agregado
            Variables auxiliares:
                string RutaOrigen: <acceso directo a los atributos privados del objeto>
                string RutaOrigen: <acceso directo a los atributos privados del objeto>
                const fs::path& origen <estas variables tranforman las cadenas digitadas por el usuario a rutas o "caminos" de ficheros>
                const fs::path& destino <estas variables tranforman las cadenas digitadas por el usuario a rutas o "caminos" de ficheros>

    */
        const fs::path& origen = rutaOrigen; // se crean las rutas digitadas por el usuario
        const fs::path& destino = rutaDestino;

        try{
            fs::create_directories(destino); // en caso de que no exista el destino este se creara automaticamente

            fs::copy(origen,destino, fs::copy_options::recursive); // si ambas rutas existen el programa continuara exitosamente
            // se copea tanto archivos como subdirectorios a la carpeta destino digitada por el usuario
            fs::remove_all(origen); // se eliminan todos los archivos dentro de la carpeta de origen
            fs::create_directories(origen); // la carpeta de origen se vuelve a crear con el mismo nombre que tenia anteriormente
            std::cout<<"Se ha movido exitosamente de: "<<origen<<" a "<<destino<<std::endl;
        }catch(const fs::filesystem_error& e){// en caso de que no se capturara el error y el programa terminara
            std::cerr<<"error en mover: "<<e.what()<<std::endl;
        }
    }
};
#endif // MOTORORGANIZADOR_H_INCLUDED
