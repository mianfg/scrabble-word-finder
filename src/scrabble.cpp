#include <iostream>
#include <chrono>

#include "Diccionario.h"
#include "Letras.h"  // no es necesario

using namespace std;

/*! \mainpage
 *
 * # Práctica final de Estructura de Datos
 * ## 2º DGIIM UGR, curso 2018/2019
 * 
 * ### Alumnos
 * - Miguel Ángel Fernández Gutiérrez (<mianfg@correo.ugr.es>)
 * - Juan Manuel Mateos Pérez (<jumape@correo.ugr.es>)
 * 
 * 
 * 
 * -------
 * 
 * Más información sobre esta práctica en la documentación y en los apartados
 * del menú:
 * 
 * 1. **Implementación de la práctica**: explica las decisiones que hemos tomado
 * de cara a la implementación de las clases.
 * 2. **Ejecución de pruebas**: explica los ficheros de prueba disponibles en
 * esta práctica, las órdenes de ejecución `make`, etc.
 */

/**
 * @brief Función para imprimir cabecera
 */
void header() {
    cout << "\n          _____                _     _     _      \n"
         << "         / ____|              | |   | |   | |     \n"
         << "        | (___   ___ _ __ __ _| |__ | |__ | | ___ \n"
         << "         \\___ \\ / __| '__/ _` | '_ \\| '_ \\| |/ _ \\\n"
         << "         ____) | (__| | | (_| | |_) | |_) | |  __/\n"
         << "        |_____/ \\___|_|  \\__,_|_.__/|_.__/|_|\\___|\n"
         << "                                           \n"
         << "\n                  SCRABBLE WORD FINDER\n\n"
         << "Práctica final - Estructuras de Datos 2º DGIIM 18/19, UGR\n\n"
         << "_________________________________________________________\n\n"
         << "  Alumnos:\tMiguel Ángel Fernández Gutiérrez\n"
         << "\t\tJuan Manuel Mateos Pérez\n"
         << "_________________________________________________________\n\n\n";
}

/**
 * @brief Función para imprimir error en argumentos
 */
void errorArgumentos() {
    cout << "ERROR en parámetros. Debe llamar este programa como:\n"
         << "\t./scrabble [fichero_diccionario] [fichero_letras]"
         << " [salida_diccionario]\n"
         << "En el que:\n"
         << "\t[fichero_diccionario]\n"
         << "\t\tes la ruta al fichero que contiene el diccionario\n"
         << "\t\tque se usará para la prueba\n"
         << "\t[fichero_letras]\n"
         << "\t\tes la ruta al fichero que contiene la bolsa de letras\n"
         << "\t\tque se usará para la prueba\n"
         << "\tNOTA: ambos ficheros deberán tener el formato especificado\n"
         << "\ten las clases \"Diccionario\" y \"Letras\", respectivamente.\n\n\n";
}

void juego(const Diccionario &dict, const Letras &letras) {
    // contador de tiempos
    chrono::steady_clock::time_point inicio, fin;

    //  _______________________________________________________________________
    // |                                                                       |
    // |  Construcción de subbolsa aleatoria ("mano")                          |
    // |_______________________________________________________________________|

    int num_letras;
    cout << "¿Cuántas letras desea que tenga su mano? -> ";
    cin >> num_letras;
    Letras mano = letras.randomSubset(num_letras);

    cout << "¡Genial! En su mano tiene las siguientes letras:\n\n"
         << "[Letra] [Pts.]  [Ctd.]\n"
         << mano << "\n";

    //  _______________________________________________________________________
    // |                                                                       |
    // |  Criterio de priorización: puntuación o longitud                      |
    // |_______________________________________________________________________|

    bool criterio; char entrada;
    cout << "¿Qué criterio desea usar para priorizar las palabras?" << endl
         << "\tp: Puntuación" << endl
         << "\tl: Longitud" << endl << endl
         << "Inserte el código del criterio que desee usar -> ";
    cin >> entrada;

    cout << endl;
    if ( entrada == 'p' )
        criterio = true;
    else if ( entrada == 'l' )
        criterio = false;
    else {
        cout << "Ha insertado un caracter no válido, usando criterio"
             << " puntuación..." << endl;
        criterio = true;
    }

    //  _______________________________________________________________________
    // |                                                                       |
    // |  Introducir una palabra                                               |
    // |_______________________________________________________________________|

    string palabra_introducida;
    bool intento_correcto = true;
    cout << "Introduzca la mejor palabra que haya encontrado: ";
    cin >> palabra_introducida;

    if ( mano.estaPalabra(palabra_introducida) )
        if ( dict.estaPalabra(palabra_introducida) )
            if ( criterio )
                cout << "\nLa palabra \"" << palabra_introducida
                    << "\" tiene una puntuación de "
                    << mano.getPuntuacion(palabra_introducida) << " puntos\n\n";
            else
                cout << "\nLa palabra \"" << palabra_introducida
                     << "\" tiene una longitud de "
                     << palabra_introducida.size() << " letras\n\n";
        else {
            cout << "\nLa palabra \"" << palabra_introducida
                 << "\" no se encuentra en su diccionario\n\n";
            intento_correcto = false;
        }
    else {
        cout << "\nLa palabra \"" << palabra_introducida << "\""
             << " no puede formarse a partir de las letras proporcionadas\n\n";
        intento_correcto = false;
    }

    //  _______________________________________________________________________
    // |                                                                       |
    // |  Búsqueda de las mejores palabras                                     |
    // |_______________________________________________________________________|

    // contaremos cuánto tiempo tarda el ordenador en buscar las palabras
    inicio = chrono::steady_clock::now();
    set<string> palabras = dict.mejorPalabra(mano, criterio);
    fin = chrono::steady_clock::now();

    if ( !palabras.empty() ) {        
        if ( palabras.size() > 1 )
            cout << "Las mejores palabras ";
        else
            cout << "La mejor palabra ";
        
        if ( criterio )
            cout << "por puntuación";
        else
            cout << "por longitud";
        
        if ( palabras.size() > 1 )
            cout << " que se pueden formar con su mano\n"
                 << "son las siguientes palabras:\n";
        else
            cout << " que se puede formar con su mano\nes la palabra:\n";

        for ( auto it = palabras.begin(); it != palabras.end(); ++it )
            cout << '\t' << (*it) << '\n';
    
        if ( palabras.size() > 1 )
            cout << "Todas ellas tienen ";
        else
            cout << "Esta palabra tiene ";
        
        if ( criterio )
            cout << mano.getPuntuacion(*(palabras.begin())) << " puntos\n";
        else
            cout << palabras.begin()->size() << " letras\n";

        if ( intento_correcto ) {
            cout << endl;
            if ( criterio )
                if ( mano.getPuntuacion(palabra_introducida)
                      == mano.getPuntuacion(*(palabras.begin())) )
                    cout << "¡Lo has conseguido! ¡Has encontrado una palabra"
                         << " tan buena como la mejor posible!\n";
                else
                    cout << "¡Casi encuentras la mejor palabra!\n";
            else
                if ( palabra_introducida.size() == palabras.begin()->size() )
                    cout << "¡Lo has conseguido! ¡Has encontrado una palabra"
                         << " tan buena como la mejor posible!\n";
                else
                    cout << "¡Casi encuentras la mejor palabra!\n";
        }
    }

    cout << "[t] Tiempo usado: "
         << chrono::duration_cast<chrono::nanoseconds>(fin - inicio).count()
                / 1000000000.0
         << " segundos\n";
}

int main(int argc, char* argv[]) {
    //  _______________________________________________________________________
    // |                                                                       |
    // |  Comprobaciones de argumentos                                         |
    // |_______________________________________________________________________|

    header();   // imprimir cabecera

    // comprobaciones en argumentos
    if ( argc != 4 ) {
        errorArgumentos();
        exit(EXIT_FAILURE);
    }

    //  _______________________________________________________________________
    // |                                                                       |
    // |  Construcción de diccionario y bolsa de letras proporcionados         |
    // |_______________________________________________________________________|

    // contador de tiempos
    chrono::steady_clock::time_point inicio, fin;

    // contaremos cuánto tiempo tarda el ordenador en cargar el diccionario y \
       la bolsa de letras
    inicio = chrono::steady_clock::now();
    Diccionario dict(argv[1]);
    Letras letras(argv[2]);
    fin = chrono::steady_clock::now();

    // comprobaciones en carga
    if ( !dict.empty() && !letras.empty() ) {
        cout << "Se ha importado satisfactoriamente:\n"
             << "  - el diccionario tiene " << dict.size() << " palabras\n"
             << "  - la bolsa de letras tiene " << letras.size() << " letras\n"
             << "[t] Tiempo usado: "
             << chrono::duration_cast<chrono::nanoseconds>(fin - inicio).count()
                    / 1000000000.0
             << " segundos\n";
    } else {
        cout << "Ha habido un error importando: alguno de los archivos\n"
             << "no contenía elementos que insertar.\n";
        exit(EXIT_FAILURE);
    }

    //  _______________________________________________________________________
    // |                                                                       |
    // |  Salida de diccionario a archivo, y de bolsa de letras a terminal     |
    // |                                                                       |
    // |    NOTA: hemos hecho que la salida sea a un archivo para que, en      |
    // |          caso de tener un diccionario grande (como los                |
    // |          proporcionados en los ficherso de prueba), no saturar        |
    // |          la salida de la terminal                                     |
    // |_______________________________________________________________________|

    cout << "\nSe está escribiendo el diccionario en el fichero:\n"
         << '\t' << argv[3] << "...\n";

    ofstream salida;
    salida.open(argv[3]);
    salida << "# SCRABBLE WORD FINDER v1.0 - DICCIONARIO\n"
           << "# Este diccionario ha sido generado como copia de "
           << argv[1] << "\n"
           << dict;
    salida.close();

    if ( salida )
        cout << "El diccionario ha sido escrito satisfactoriamente\n";
    else
        cout << "Ha habido un error escribiendo en el archivo\n"
             << "pero... ¡no pasa nada, continuemos!\n";

    // mostrar bolsa de letras
    cout << "\nA continuación se muestra la bolsa de letras:\n\n"
         << "[Letra] [Pts.]  [Ctd.]\n"
         << letras << "\n";

    //  _______________________________________________________________________
    // |                                                                       |
    // |  Frecuencia de letras en bolsa de letras (uso de iterador Letras)     |
    // |_______________________________________________________________________|

    cout << "\nDel mismo modo, se muestran las frecuencias de las letras:\n\n"
         << "[Letra] [FAbs.] [FRel.]\n";

    Letras::iterator it;

    for ( it = letras.begin(); it != letras.end(); it++ )
        cout << (*it) << '\t' << letras.getCantidad(*it)
             << '\t' << (double)letras.getCantidad(*it) / letras.size() << '\n';
    cout << endl;

    //  _______________________________________________________________________
    // |                                                                       |
    // |  Juego: interacción por parte de usuario                              |
    // |_______________________________________________________________________|

    bool continuar = true;
    char cont = 'S';
    while ( cont == 'S' || cont == 's' ) {
        juego(dict, letras);
        cout << "\n · ¿Quieres intentarlo de nuevo? (S/n) -> ";
        cin >> cont;
        cout << endl;
    }

    cout << "¡Gracias por jugar! :)\n\n";
    
    // fin del programa (POSIX)
    exit(EXIT_SUCCESS);
}