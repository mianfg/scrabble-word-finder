#ifndef __Diccionario_h__
#define __Diccionario_h__

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <locale>

#include "Letras.h"

/**
 * @brief Nodo de la clase Diccionario
 * 
 * @author Miguel Ángel Fernández Gutiérrez (<mianfg@correo.ugr.es>)
 * @author Juan Manuel Mateos Pérez (<jumape@correo.ugr.es>)
 * 
 * @date Desarrollado de diciembre del 2018 a enero del 2019
 */
class DicNodo {
    /**
     * @brief Forma palabra
     * 
     * Es `true` si la sucesión de chars de los arcos hasta llegar a él acaba en
     * una palabra del diccionario, `false` en caso contrario
     */
    bool es_palabra;

    /**
     * @brief Arcos del grafo
     * 
     * Cada arco tiene como etiqueta un `char` y apunta a otro `DicNodo`
     */
    std::map<char, DicNodo*> arcos;

    /**
     * @brief Constructor por defecto
     */
    DicNodo() : es_palabra(false) {}

    friend class Diccionario;
};

/**
 * @brief TDA Diccionario
 * 
 * Esta clase incluye la funcionalidad necesaria para almacenar un Diccionario
 * en un \a trie, y acceder a sus elementos, así como encontrar las palabras
 * óptimas para el uso conjunto con la clase Letras
 * 
 * Un *diccionario* es un conjunto de *palabras*. La estructura de *trie*
 * es una optimización en memoria de un diccionario cualquiera, aprovechando
 * la repetición de prefijos en las palabras. Además, es más óptimo en búsqueda,
 * especialmente si se conocen por adelantado las letras disponibles.
 * 
 * @author Miguel Ángel Fernández Gutiérrez (<mianfg@correo.ugr.es>)
 * @author Juan Manuel Mateos Pérez (<jumape@correo.ugr.es>)
 * 
 * @date Desarrollado de diciembre del 2018 a enero del 2019
 */
class Diccionario {
    /**
     * @brief Puntero a nodo raíz
     */
    DicNodo* raiz;

    /**
     * @brief Número de palabras
     */
    unsigned int num_palabras;

public:
    /**
     * @brief Constructor por defecto
     */
    Diccionario() : raiz(new DicNodo), num_palabras(0) {}

    /**
     * @brief Construir diccionario a partir de archivo
     * @param filename: Nombre del archivo donde se encuentra el
     *                  diccionario
     * 
     * Construye un diccionario con todas las palabras del archivo,
     * con el siguiente formato:
     * 
     *     # SCRABBLE WORD FINDER v1.0 - DICCIONARIO
     *     palabra_1[salto de línea \n]
     *     palabra_2[salto de línea \n]
     *     ...
     *     palabra_n[salto de línea \n]
     * 
     * Se ignorarán todas las líneas comenzando por `#`
     */
    Diccionario(const std::string &filename);

    /**
     * @brief Insertar palabra
     * @param palabra: Palabra a insertar como `std::string`
     * 
     * @see Si se quiere pasar como C-string, usar
     *      insertar(const char* palabra, int tam)
     */
    void insertar(const std::string &palabra);

    /**
     * @brief Insertar palabra
     * @param palabra: Palabra a insertar como C-string
     * @param tam: Tamaño de la palabra a insertar
     * 
     * @see Si se quiere pasar como `std::string`, usar
     *      insertar(const std::string &palabra)
     */
    void insertar(const char* palabra, int tam) {
        insertar(std::string(palabra, tam));
    }

    /**
     * @brief Comprobar si se encuentra una palabra
     * @param palabra: Palabra a comprobar
     * @return `true` si la palabra está en el diccionario,
     *         `false` en caso contrario
     * 
     * @see Si se quiere pasar como `std::string`, usar
     *      estaPalabra(const std::string &palabra)
     */
    bool estaPalabra(const std::string &palabra) const;

    /**
     * @brief Comprobar si se encuentra una palabra
     * @param palabra: Palabra a comprobar
     * @tam: Tamaño de la palabra a comprobar
     * @return `true` si la palabra está en el diccionario,
     *         `false` en caso contrario
     *
     * @see Si se quiere pasar como `std::string`, usar
     *      estaPalabra(const std::string &palabra)
     */
    bool estaPalabra(const char* palabra, int tam) const {
        return estaPalabra(std::string(palabra, tam));
    }

    /**
     * @brief Devuelve el tamaño del diccionario
     * @return El número de palabras que tiene el diccionario
     */
    int size() const {
        return num_palabras;
    }

    /**
     * @brief Comprueba si el diccionario está vacío
     * @return `true` si el diccionario está vacío,
     *         `false` en caso contrario
     */
    bool empty() const {
        return raiz == 0;
    }

    /**
     * @brief Limpia el Diccionario, esto es, elimina las
     * palabras que hay en él
     */
    void clear();

    /**
     * @brief Reconstruye diccionario a letras: sobrecarga de operador de salida
     * @param out: Flujo de salida
     * @param dict: Diccionario que se quiere mostrar
     * @return Referencia a flujo de salida
     * 
     * Construye un diccionario legible a partir de un objeto de la clase
     * Diccionario, en estructura \a trie, hacia el formato legible por
     * el constructor.
     * 
     * @see El formato del operador de salida está especificado en el
     *      contructor Diccionario(const std::string &filename)
     */
    friend std::ostream& operator<<(std::ostream &out, const Diccionario &dict) {
        std::string str;
        dict.mostrarArcos(out, dict.raiz, str, 0);

        return out;
    }

    /**
     * @brief Lectura de un diccionario: sobrecarga del operador de entrada 
     * @param in: Flujo de entrada
     * @param dic: Diccionario que se quiere leer
     * @return Referencia a flujo de entrada
     */
    friend std::istream& operator>>(std::istream& in, Diccionario& dic);

    /**
     * @brief Busca la mejor palabra del diccionario que puede formarse desde
     * una cierta bolsa de letras
     * @param bolsa: Bolsa de letras disponibles para construir la palabra
     * @param criterio: Criterio de comparación para encontrar la mejor letra:
     *           - Si es `true`, se usa el **criterio por puntuación**
     *             (se busca la palabra con mayor puntuación)
     *           - Si es `false`, se usa el **criterio por longitud**
     *             (se busca la palabra con mayor longitud)
     * 
     * @note Es posible que haya varias palabras que coincidan con el criterio,
     * en cuyo caso se devolverá una de ellas (la primera que se encuentre).
     * Si no existe ninguna palabra, se devolverá el string vacío `""`
     */
    std::set<std::string> mejorPalabra(const Letras &bolsa,
                                       bool criterio = true) const {
        std::set<std::string> mejores_palabras;
        // insertamos una palabra con la que comparar (la palabra vacía)
        mejores_palabras.insert("");
        std::string mejor_palabra_prov;
        mejorPalabra_aux(mejores_palabras, raiz, mejor_palabra_prov,
                         0, bolsa, bolsa, criterio);
        
        return mejores_palabras;
    }

private:
    /**
     * @brief Cambiar cierta posición de un string, sin `out_of_range`
     * @param str: String a modificar
     * @param loc: Posición a modificar
     * @param c: Caracter a añadir
     * 
     * Esta es una función que realiza lo mismo que el `at()` de `std::string`,
     * pero sin la excepción `out_of_range`, es decir, permite hacer
     * 
     *     str[loc] = c   // incluso cuando loc >= str.size() (para un loc cualquiera)
     * 
     * En caso de que `loc > str.size()`, se colocará el caracter `_` desde
     * `str[str.size() - 1]` hasta `str[loc - 1]`
     * 
     * Esta función puede ser usada para hacer, directamente:
     * 
     *     str[str.size()] = c
     * 
     * en lugar del rutinario
     * 
     *     str.push_back(c)
     * 
     * lo cual tiene una gran utilidad a la hora de asignar `char`s al `string`
     * en una posición determinada sin tener que preocuparse de si disponemos
     * del tamaño suficiente.
     * 
     * @see Esta función se usa fuertemente en @ref mostrarArcos()
     */
    friend void stringAssign(std::string &str, unsigned int loc, const char &c);

    /**
     * @brief Mostrar palabras desde arcos a partir de cierto nodo
     * @param out: Flujo de salida
     * @param nodo: Nodo a partir del cual se muestran los arcos
     * @param str: String que se pasa como acumulador de caracteres
     * 
     * Construye el diccionario a partir de un objeto, acumulando las letras de
     * los arcos y mostrándolas cuando formen una palabra.
     * 
     * @see Esta función se usa para la sobrecarga del operador de salida
     *      operator<<()
     * 
     * \par [Implementación alternativa con C-string]
     * A continuación, la implementación original de `mostrarArcos`, usando
     * C-string (el cual tendría limitaciones de tamaño) en lugar de strings.
     * Nótese cómo, para poder implementarlo con tamaño ilimitado con
     * `std::string`, hemos usado la función auxiliar @ref stringAssign()
     *
     *     void Diccionario::mostrarArcos(std::ostream &out, DicNodo *nodo, char str[], int nivel) const {
     *         std::map<char, DicNodo*>::const_iterator it;
     *         if ( nodo->es_palabra == true ) {
     *             str[nivel] = '\0';
     *             out << str << '\n';
     *         }
     * 
     *         for ( it = nodo->arcos.begin(); it != nodo->arcos.end(); ++it ) {
     *             str[nivel] = it->first;
     *             mostrarArcos(out, it->second, str, nivel+1);
     *         }
     *     }
     *
     * \par
     * Esto también cambiaría la implementación de la sobrecarga del operador de
     * salida, operator<<(), a la siguiente:
     * 
     *     friend std::ostream& operator<<(std::ostream &out, const Diccionario &dict) {
     *         char str[STRLIMIT];
     *         dict.mostrarArcos(out, dict.raiz, str, 0);
     * 
     *         return out;
     *     }
     * 
     * \par
     * Donde `STRLIMIT` es una constante o `#define` de la clase
     */
    void mostrarArcos(std::ostream &out, DicNodo *nodo, std::string str, int nivel) const;

    /**
     * @brief Comparador en función de criterio
     * @param palabra_1: Primera palabra
     * @param palabra_2: Segunda palabra
     * @param bolsa: Bolsa de letras con respecto a la que comparar
     * @param criterio: Criterio de comparación para encontrar la mejor letra:
     *           - Si es `true`, se usa el **criterio por puntuación**
     *             (se busca la palabra con mayor puntuación)
     *           - Si es `false`, se usa el **criterio por longitud**
     *             (se busca la palabra con mayor longitud)
     * @return Devuelve uno de los siguientes valores:
     *           - `1` si `palabra_1 > palabra_2`
     *           - `-1` si `palabra_1 < palabra_2`
     *           - `0` si `palabra_1 == palabra_2`
     */
    friend int comparador(const std::string &palabra_1, const std::string &palabra_2,
                           const Letras &bolsa, bool criterio);

    /**
     * @brief Función recursiva auxiliar para mejorPalabra()
     * 
     * Esta función recibe los siguientes parámetros y realiza lo que se
     * explica en cada uno de ellos. Es usado en @ref mejorPalabra()
     * 
     * @param mejores_palabras: Es el set de `std::string` que se devolverá,
     * en él se almacenarán todas las palabras que tengan mejor puntuación o
     * longitud (dependiendo de `criterio`). Es pasado por referencia para que
     * todas las llamadas recursivas a la función modifiquen un mismo `set`, que
     * será devuelto al llamar a la función mejorPalabra()
     * @param nodo: Es un puntero a nodo del diccionario, el que se usa para
     * iterar de forma recursiva sobre los nodos (de forma similar a como se
     * hace en mostrarArcos())
     * @param str: En cada llamada a esta función, se van almacenando los
     * `char`s de los arcos en este `string`, que es usado para comprobar si
     * se ha formado palabra (de forma similar a mostrarArcos())
     * @param nivel: Indica el lugar de `str` donde insertar el `char` asociado
     * al arco que se recorre (de forma similar a mostrarArcos())
     * @param bolsa: Bolsa original, contiene todas las puntuaciones y todas las
     * cantidades de letras permitidas
     * @param bolsa_temp: Bolsa usada en la función recursiva para comprobar la
     * disponibilidad de letras
     * @param criterio: Criterio de búsqueda (puntuación o longitud)
     */
    void mejorPalabra_aux(std::set<std::string> &mejores_palabras, DicNodo* nodo,
                          std::string str, int nivel, const Letras &bolsa,
                          Letras bolsa_temp, bool criterio) const;
};

#endif