# 1 - Implementación de la práctica

## Clases utilizadas

Para la implementación de esta práctica, hemos optado por usar dos clases:

* `Letras`: implementa el TDA *bolsa de letras*, que consiste en un conjunto de letras con sus puntuaciones asociadas (permitiendo también tener control de la cantidad de veces que se repite cada letra). Permite extraer subconjuntos de él.
* `Diccionario`: implementa el TDA *diccionario*, que tiene las estructuras necesarias para agilizar la búsqueda de la mejor palabra posible a partir de cierta bolsa de letras.

## La clase `Letras`

Puedes consultar toda la información sobre Letras en este mismo Doxygen.

\subsection 1-2-1 Estructuras de datos utilizadas

Para esta clase hemos utilizado la siguiente estructura de la STL:

~~~ c++
std::map<char, std::pair<int, int> >
~~~

Debido a que, con ella, podíamos implementar toda la funcionalidad de letra y bolsa de letras, usando una única clase. Además, así logramos que sea eficiente en memoria usando contenedores STL. Por otra parte, el uso de `map` nos permite mostrar los caracteres de forma ordenada.

## La clase `Diccionario`

Puedes consultar toda la información sobre Diccionario y DicNodo en este mismo Doxygen.

### Estructuras de datos utilizadas

Para la implementación del diccionario hemos usado un [*trie*](https://en.wikipedia.org/wiki/Trie) o *árbol de prefijos*, una estructura frecuentemente utilizada en diversos problemas relacionados con diccionarios, autocorrección, etc. Esto es así porque permite una búsqueda muy rápida.

Normalmente estas estructuras suelen ser poco eficientes en memoria, pero nosotros hemos intentado evitar eso mediante el uso nuevamente de un `map`, que actuará como arcos que cuelgan de un `bool`, siendo esta nuestra estructura de nodo, `DicNodo`.

De este modo, se crean únicamente tantos arcos como sean necesarios.

### Algunas alternativas interesantes

En la investigación para la realización de esta práctica, encontramos una alternativa interesante a esta estructura, llamada **DAWG** (*Direct Acyclic Word Graph*) o **MA-FSA** (*Minimal Acyclic Finite-State Automata*).

La virtud de esta estructura es que, además de de hacer que no se repitan prefijos (como un *trie*), hace lo mismo para los sufijos.

Esta estructura es mucho más eficiente en memoria, a coste de ser algo más lenta de construir. Normalmente, se construye un *trie* y se usan algoritmos para generar el *DAWG* a partir de él, lo cual es poco útil. Sin embargo, tras investigar conseguimos llegar a ideas de cómo implementarlo de forma directa, sin un *trie* intermedio. Conseguimos implementarla para diccionarios ordenados alfabéticamente (gracias en parte a [este artículo](http://stevehanov.ca/blog/index.php?id=115)), pero no tuvimos tiempo de conseguir que funcionase completamente, por lo que nos decantamos por el *trie*, una estructura algo más sencilla.

Sin embargo, dejamos las referencias aquí, porque se trata de una estructura de datos muy interesante:

* "Incremental Construction of Minimal Acyclic Finite-State Automata", J. Daciuk, B. W. Watson, S. Mihov, R. E. Watson.: http://www.aclweb.org/anthology/J00-1002.pdf
* http://pages.pathcom.com/~vadco/dawg.html
* http://www.wutka.com/dawg.html
* "Compressing dictionaries with a DAWG", Steve Hanov: http://stevehanov.ca/blog/index.php?id=115
* https://gist.github.com/smhanov/94230b422c2100ae4218