#include "Letras.h"

/* __________________________________ */
/*|                                  |*/
/*|           Clase Letras           |*/
/*|__________________________________|*/

Letras::Letras(const std::string &filename) {
    std::ifstream archivo(filename);

    archivo >> (*this);
}

void Letras::insertarLetra(char letra, int cantidad) {
    using namespace std;

    std::map<char, p_c>::iterator it;

    if ( estaLetra(letra) ) {
        for ( it = bolsa.begin(); it != bolsa.end(); ++it )
            if ( it->first == letra )
                it->second.second += cantidad;
    } else
        bolsa.insert(std::pair<char, p_c>(letra, p_c(0, cantidad)));

}

void Letras::asignarPuntuacion(char letra, int puntuacion) {        
    std::map<char, p_c>::iterator it;

    if( estaLetra(letra) )
        for ( it = bolsa.begin(); it != bolsa.end(); ++it )
            if ( it->first == letra )
                it->second.first = puntuacion;
}

void Letras::eliminarLetra(char letra, int cantidad) {
    // no case-sensitive
    if ( bolsa.count(letra) > 0 )
        letra = letra;
    else if ( bolsa.count(std::toupper(letra, std::locale())) > 0 )
        letra = std::toupper(letra, std::locale());
    else if ( bolsa.count(std::tolower(letra, std::locale())) > 0 )
        letra = std::tolower(letra, std::locale());
    else
        // la letra no se encuentra, no se hará nada \
           (nunca añadiremos '\0' a la bolsa de letras)
        letra = '\0';
     
    if ( estaLetra(letra) )
        insertarLetra(letra, cantidad*(-1));

    if ( bolsa.at(letra).second <= 0 )
        bolsa.erase(letra);
}

Letras Letras::randomSubset(int num_elementos) const {
    std::map<char, p_c>::const_iterator it;
    std::string todo, letras_generadas;
    Letras res;
    int contador;

    for ( it = bolsa.begin(); it != bolsa.end(); ++it ) {
        contador = 0;
        while ( contador != it->second.second ) {
            todo.push_back(it->first);
            contador++;
        }
    }
    
    // generación aleatoria
    srand(time(NULL));
    for ( int i=0; i<num_elementos; ++i )
        letras_generadas.push_back(todo[rand() % todo.size()]);
    
    for ( int i=0; i < letras_generadas.size(); ++i ) {
        res.insertarLetra(letras_generadas[i]);
        res.asignarPuntuacion(letras_generadas[i], bolsa.at(letras_generadas[i]).first);
    }
    
    return res;
}

int Letras::getPuntuacion(char letra) const {
    if ( bolsa.count(letra) > 0 )
        return bolsa.at(letra).first;
    else if ( bolsa.count(std::toupper(letra, std::locale())) > 0 )
        return bolsa.at(std::toupper(letra, std::locale())).first;
    else if ( bolsa.count(std::tolower(letra, std::locale())) > 0 )
        return bolsa.at(std::tolower(letra, std::locale())).first;
    else
        return 0;
}

int Letras::getPuntuacion(const std::string &palabra) const {
    int puntuacion = 0;
    for ( int i = 0; i < palabra.size(); i++ )
        puntuacion += getPuntuacion(palabra[i]);

    return puntuacion;
}

int Letras::getCantidad(char letra) const {
    if ( bolsa.count(letra) > 0 )
        return bolsa.at(letra).second;
    else if ( bolsa.count(std::toupper(letra, std::locale())) > 0 )
        return bolsa.at(std::toupper(letra, std::locale())).second;
    else if ( bolsa.count(std::tolower(letra, std::locale())) > 0 )
        return bolsa.at(std::tolower(letra, std::locale())).second;
    else
        return 0;
}

int Letras::size() const {
    int tam = 0;
    std::map<char, p_c>::const_iterator it;

    for ( it = bolsa.begin(); it != bolsa.end(); ++it )
        tam += it->second.second;
    
    return tam;
}

bool Letras::estaPalabra(const std::string &palabra) const {
    Letras letras_aux(*this);

    for ( int i = 0; i < palabra.size(); i++ ) {
        if ( !letras_aux.estaLetra(palabra[i]) )
            return false;
        
        letras_aux.eliminarLetra(palabra[i]);
    }

    return true;
}

std::ostream& operator<<(std::ostream &out, const Letras &b) {
    typedef std::pair<int, int> p_c;

    std::map<char, p_c>::const_iterator it;

    for ( it = b.bolsa.begin(); it != b.bolsa.end(); ++it )
        out << it->first << '\t'
            << it->second.first << '\t'
            << it->second.second << '\n';

    return out;
}

std::istream& operator>>(std::istream &in, Letras &b) {
    typedef std::pair<int, int> p_c;

    b.bolsa.clear();

    char l;
    int primero, segundo;
    std::string trash;

    while( in >> l ) {
        in.putback(l);
        if ( l != '#') {
            in >> l >> primero >> segundo;
            b.bolsa.insert(std::pair<char, p_c>(l, p_c(primero, segundo)));
        } else
            // ignorar línea de comentario
            getline(in, trash);
    }
    
    return in;
}