#ifndef __Letras_h__
#define __Letras_h__

#include <iostream>
#include <fstream>
#include <map>
#include <utility>
#include <string>
#include <cstdlib>
#include <locale>

/**
 * @class Letras
 * @brief TDA Letras (Bolsa de Letras)
 * 
 * Este tipo de dato está compuesto por un conjunto de letras. Por cada una de
 * las letras posibles se le asigna dos valores: puntuación y cantidad.
 * 
 * De este modo, la bolsa de letras puede identificarse como:
 * 
 * \f$\{\{letra_1, \{puntuacion_1, cantidad_1\}\},
 * \{\{letra_2, \{puntuacion_2, cantidad_2\}\},
 * ..., \{\{letra_n, \{puntuacion_n, cantidad_n\}\}\f$
 * 
 * Donde:
 *   - \f$letra_i\f$ es de tipo `char`
 *   - \f$puntuacion_i\f$ y \f$cantidad_i\f$ son de tipo entero
 * 
 * Restricciones:
 *   - \f$i \neq j \Rightarrow letra_i \neq letra_j\f$ (las letras son únicas,
 *     no hay repeticiones)
 *   - Cada letra tiene una única puntuación asociada
 * 
 * De este modo, el campo \f$cantidad_i\f$ especifica el número de veces que la
 * letra \f$letra_i\f$, con puntuación \f$puntuacion_i\f$, está en la bolsa de
 * letras.
 * 
 * @author Miguel Ángel Fernández Gutiérrez (<mianfg@correo.ugr.es>)
 * @author Juan Manuel Mateos Pérez (<jumape@correo.ugr.es>)
 * 
 * @date Desarrollado de diciembre del 2018 a enero del 2019
 */
class Letras {
private:
    /**
     * @brief Par de puntuación y cantidad \f$\{puntuacion, cantidad\}\f$
     */
    typedef std::pair<int, int> p_c;

    /**
     * @brief Conjunto de letras
     */
    std::map<char, p_c> bolsa;

public:
    /**
     * @class Letras::iterator
     * 
     * Iterador para la clase Letras
     * 
     * Este iterador devuelve, de forma secuencial y en orden, un puntero a cada
     * una de las claves (*keys*) del `map` donde se ha implementado la clase
     * Letras; de este modo, devuelve las letras que hay en la bolsa, pudiendo
     * hacer uso de las funciones getCantidad y getPuntuacion sobre el iterador
     */
    class iterator {
        std::map<char, p_c>::iterator it;

    public:
        /**
         * @brief Constructor por defecto
         */
        iterator() : it(0) {}

        /**
         * @brief Constructor por copia
         * @param it: Iterador a copiar
         */
        iterator(const std::map<char, p_c>::iterator &it) {
            this->it = it;
        }

        /**
         * @brief Acceso constante a la letra `char` asociada al iterador
         */
        const char &operator *() const {
            return it->first;
        }

        /**
         * @brief Sobrecarga del operador ++
         */
        iterator &operator++(int) {
            this->it++;
            return *this;
        }

        /**
         * @brief Sobrecarga del operador --
         */
        iterator &operator--(int) {
            this->it--;
            return *this;
        }

        /**
         * @brief Sobrecarga del operador ==
         * @param it: Iterador con respecto al que comprobar la igualdad
         * @return `true` si son iguales, `false` en caso contrario
         */
        bool operator==(const iterator &it) {
            return this->it == it.it;
        }

        /**
         * @brief Sobrecarga del operador !=
         * @param it: Iterador con respecto al que comprobar la no igualdad
         * @return `true` si no son iguales, `false` en caso contrario
         */
        bool operator!=(const iterator &it) {
            return this->it != it.it;
        }
    };

    /**
     * @brief Iterador a comienzo
     * @return Iterador al comienzo de la bolsa
     */
    iterator begin() {
        return iterator(bolsa.begin());
    }

    /**
     * @brief Iterador a final
     * @return Iterador a después del último elemento de la bolsa
     */
    iterator end() {
        return iterator(bolsa.end());
    }


    /**
     * @brief Constructor por defecto
     */
    Letras() : bolsa(std::map<char, p_c>()) {}

    /**
     * @brief Constructor por copia
     */
    Letras(const Letras &b) {
        bolsa = b.bolsa;
    }

    /**
     * @brief Construir bolsa de letras a partir de archivo
     * @param filename: Nombre del archivo donde se encuentra la bolsa de letras
     * 
     * Construye una bolsa de letras a partir de un archivo con el siguiente
     * formato:
     * 
     *     # SCRABBLE WORD FINDER v1.0 - BOLSA DE LETRAS
     *     letra_1[tabulador \t]puntuacion_1[tabulador \t]cantidad_1[salto de línea \n]
     *     letra_2[tabulador \t]puntuacion_2[tabulador \t]cantidad_2[salto de línea \n]
     *     ...
     *     letra_n[tabulador \t]puntuacion_n[tabulador \t]cantidad_n[salto de línea \n]
     * 
     * Se ignorarán todas las líneas comenzando por `#`
     */
    Letras(const std::string &filename);

    /**
     * @brief Función para insertar y modificar letras
     * 
     * Dependiendo de los parámetros, puede usarse esta función para:
     *   - Añadir nueva letra a la bolsa, en caso de que la letra no exista,
     *     o añadir una letra más a la bolsa, en caso de que ya exista
     *     
     *         insertarLetra(letra)
     * 
     *   - Añadir \f$n\f$ veces `letra` a la bolsa (puede usarse para añadir
     *     directamente \f$n\f$ veces la letra en caso de que no hubiera
     *     ninguna, o para añadir \f$n\f$ letras adicionales en caso de que ya
     *     se encontrase en la bolsa)
     * 
     *         insertarLetra(letra, n)
     * 
     * @param letra: Letra a insertar
     * @param cantidad: Cantidad de letras a insertar
     */
    void insertarLetra(char letra, int cantidad = 1);

    /**
     * @brief Asignar puntuación a letra
     * @param letra: Letra a asignar puntuación. Debe estar en la bolsa
     * @param puntuacion: Puntuación a asignar a `letra`
     */
    void asignarPuntuacion(char letra, int puntuacion);

    /**
     * @brief Función para eliminar letras
     * 
     * En caso de que no exista la letra que se quiere eliminar, el método no
     * hará nada. Si existen letras, pero la cantidad de letras a eliminar es
     * mayor que la cantidad de veces que se encuentra la letra en la bolsa, se
     * eliminarán todas las instancias de la letra en la bolsa.
     * 
     * @param letra: Letra a eliminar. Debe estar en la bolsa
     * @param cantidad: Número de veces que se quiere eliminar a `letra`
     */
    void eliminarLetra(char letra, int cantidad = 1);

    /**
     * @brief Genera un subconjunto de la bolsa de forma aleatoria
     * @param num_elementos: Número de letras del subconjunto
     */
    Letras randomSubset(int num_elementos) const;

    /**
     * @brief Devuelve la puntuación de cierta letra
     * 
     * Si la letra no se encuentra, devuelve el valor `0`.
     * 
     * @param letra: Letra de la que devolver la puntuación
     * @return La puntuación asignada a `letra`
     * 
     * @warning Esta clase permite asignar puntuaciones 0 a letras, así que
     * comprobar que esta función retorne 0 no es en general equivalente a que
     * la letra no se encuentre en la bolsa de letras. Para ello, use la función
     * @ref estaLetra(char letra).
     * 
     * @note Esta función **no es** ***case-sensitive***, para ello hace uso de
     * las funciones `toupper` y `tolower`, concretamente las funciones
     * definidas en `<locale>`.
     */
    int getPuntuacion(char letra) const;

    /**
     * @brief Devuelve la puntuación de una palabra
     * 
     * El cálculo de la puntuación se realiza mediante la suma de las
     * puntuaciones de cada una de las letras de la palabra.
     * 
     * @param: Palabra de la que devolver la puntuación
     * @return La puntuación asignada a `palabra`
     */
    int getPuntuacion(const std::string &palabra) const;

    /**
     * @brief Devuelve la cantidad de veces que está una letra en la bolsa
     * @param letra: Letra de la que devolver su cantidad
     * @return La cantidad de veces que está \a letra en la bolsa
     * 
     * @note Esta función **no es** ***case-sensitive***, para ello hace uso de
     * las funciones `toupper` y `tolower`, concretamente las funciones
     * definidas en `<locale>`.
     */
    int getCantidad(char letra) const;

    /**
     * @brief Devuelve el tamaño de la bolsa de letras
     * @return El número de letras que tiene la bolsa
     * 
     * Se considera el número de letras como la suma de todas las cantidades
     * asignadas a cada letra de la bolsa
     */
    int size() const;

    /**
     * @brief Comprueba si la bolsa está vacía
     * @return `true` si la bolsa está vacía, `false` en caso contrario
     */
    bool empty() const {
        return size() == 0;
    }

    /**
     * @brief Determina si la letra se encuentra en la bolsa
     * @param: Letra de la que se desea saber si se encuentra en la bolsa
     * @return `true` si `letra` está en la bolsa, `false` en caso contrario
     */
    bool estaLetra(char letra) const {
        return getCantidad(letra) > 0;
    }

    /**
     * @brief Determina si la palabra puede formarse a pratir de las letras de
     * la bolsa
     * @return `true` si puede formarse, `false` en caso contrario
     */
    bool estaPalabra(const std::string &palabra) const;

    /**
     * @brief Vacía la bolsa
     */
    void vaciar() {
        bolsa.clear();
    }

    /**
     * @brief Sobrecarga del operador de salida
     * @param out: Flujo de salida
     * @param bolsa: Bolsa que se escribirá
     * @return Referencia al flujo de salida
     * 
     * @see El formato de la salida coincide con el especificado en el
     * constructor a partir de archivo, @see Letras(const std::string &filename)
     */
    friend std::ostream& operator<<(std::ostream &in, const Letras &b);

    /**
     * @brief Sobrecarga del operador de entrada
     * @param in: Flujo de entrada
     * @param bolsa: Bolsa donde se leerán los datos
     * @return Referencia al flujo de entrada
     * 
     * El formato de la entrada debe coincidir con el formato de la salida
     * @see operator<<
     */
    friend std::istream& operator>>(std::istream &in, Letras &b);
};

#endif