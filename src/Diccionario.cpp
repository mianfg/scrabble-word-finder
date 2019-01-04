#include "Diccionario.h"

/* __________________________________ */
/*|                                  |*/
/*|        Clase Diccionario         |*/
/*|__________________________________|*/

Diccionario::Diccionario(const std::string &filename) {
    // la función operator>> vacía el diccionario, \
       creamos algo que eliminar
    raiz = new DicNodo;

    std::ifstream archivo(filename);
    archivo >> (*this);
    archivo.close();
}

void Diccionario::insertar(const std::string &palabra) {
    DicNodo* itera = raiz;

    for ( unsigned int i = 0; i < palabra.size(); i++ ) {
        if ( itera->arcos.count(palabra[i]) == 0 ) {
            // la letra no se encuentra
            DicNodo* new_nodo = new DicNodo;
            itera->arcos.insert(std::pair<char, DicNodo*>(palabra[i], new_nodo));
        }

        itera = itera->arcos[palabra[i]];
    }
    // hemos llegado al final
    itera->es_palabra = true;

    num_palabras++;
}

bool Diccionario::estaPalabra(const std::string &palabra) const {
    DicNodo* itera = raiz;
    bool esta = true;

    for ( unsigned int i = 0; i < palabra.size() && esta; i++ ) {
        if ( itera->arcos.count(palabra[i]) == 0 )
            esta = false;
        if ( esta )
            itera = itera->arcos[palabra[i]];
    }

    return esta;
}

void Diccionario::clear() {
    if ( !empty() ) {
        raiz->arcos.clear();
        num_palabras = 0;
    }
}

std::istream& operator>>(std::istream &in, Diccionario& dic){
    std::string palabra_leida;

    // vacío
    dic.clear();
    
    // inserto las palabras leidas en el diccionario
    while ( getline(in, palabra_leida) )
        if ( palabra_leida[0] != '#' )
            dic.insertar(palabra_leida);

    return in;
}

void stringAssign(std::string &str, unsigned int loc, const char &c) {
    if ( loc < str.size() )
        str[loc] = c;
    else {
        for ( int i = str.size(); i < loc; i++ )
            str.push_back('_');
        str.push_back(c);
    }
}

void Diccionario::mostrarArcos(std::ostream &out, DicNodo *nodo,
                               std::string str, int nivel) const {
    std::map<char, DicNodo*>::const_iterator it;
    
    // comprobamos si el nodo que se ha pasado acaba en palabra
    if ( nodo->es_palabra == true )
        out << str << '\n';

    // iteramos sobre los arcos que cuelgan de nodo    
    for ( it = nodo->arcos.begin(); it != nodo->arcos.end(); ++it ) {
        // asignamos el char al string
        stringAssign(str, nivel, it->first);   // str[nivel] = it->first;
        // función recursiva
        mostrarArcos(out, it->second, str, nivel+1);
    }
}

int comparador(const std::string &palabra_1, const std::string &palabra_2,
                const Letras &bolsa, bool criterio) {
    if ( criterio )
        if ( bolsa.getPuntuacion(palabra_1) > bolsa.getPuntuacion(palabra_2) )
            return 1;
        else if ( bolsa.getPuntuacion(palabra_1) < bolsa.getPuntuacion(palabra_2) )
            return -1;
        else
            return 0;
    else
        if ( palabra_1.size() > palabra_2.size() )
            return 1;
        else if ( palabra_1.size() < palabra_2.size() )
            return -1;
        else
            return 0;
}

void Diccionario::mejorPalabra_aux(std::set<std::string> &mejores_palabras, DicNodo *nodo,
                                   std::string str, int nivel, const Letras &bolsa,
                                   Letras bolsa_temp, bool criterio) const {
    std::map<char, DicNodo*>::const_iterator it;

    if ( nodo->es_palabra == true ) {
        int comp = comparador(str, *(mejores_palabras.begin()), bolsa, criterio);
        if ( comp == 1 ) {
            // se trata de una palabra mejor de todas las que había, \
               vaciamos el set e insertamos ésta
            mejores_palabras.clear();
            mejores_palabras.insert(str);
        } else if ( comp == 0 )
            // se trata de una palabra con puntuación/longitud igual a la \
               mejor, la insertamos en el set
            mejores_palabras.insert(str);
    }
    
    for ( it = nodo->arcos.begin(); it != nodo->arcos.end(); ++it )
        if ( bolsa_temp.estaLetra(it->first) ) {
            stringAssign(str, nivel, std::toupper(it->first, std::locale()));
            Letras bolsa_new(bolsa_temp);
            bolsa_new.eliminarLetra(it->first);

            mejorPalabra_aux(mejores_palabras, it->second, str,
                             nivel+1, bolsa, bolsa_new, criterio);
        }
}