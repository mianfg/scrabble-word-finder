# 2 - Ejecución de pruebas

El `Makefile` implementado en esta práctica contiene la funcionalidad necesaria para compilar todos los contenidos de la práctica, además de órdenes para poder ejecutar la prueba:

| Orden `make` | Uso |
| --- | --- |
| `make` | Compila todos los archivos |
| `make doxy` | Genera la documentación Doxygen |
| `make test` | Ejecuta el test (ver abajo) |
| `make clean` | Limpia los binarios y esta documentación Doxygen |
| `make zip` | Crea archivo comprimido |

## El test de esta práctica: `scrabble.cpp`

Todas las pruebas que se constatan en el guion de prácticas se realizan de forma simultánea en este ejecutable, que tiene las siguientes partes:

1. Construcción de diccionario y bolsa de letras
2. Salida de diccionario a archivo, y de bolsa de letras por pantalla
3. Salida de frecuencia de letras por pantalla
4. Bucle de juego
   1. Generar subbolsa aleatoria a partir de la bolsa proporcionada
   2. Preguntar criterio de priorización: puntuación o longitud
   3. Introducir palabra
   4. Calcular las mejores palabras por el criterio
   5. Comprobar si se ha introducido una palabra tan buena como la mejor
   6. Reiniciar bucle

### Medición de tiempos y uso de memoria

El programa de prueba `scrabble.cpp` hace uso de la librería `<chrono>` para contar los tiempos:

* de construcción de los objetos `Letras` y `Diccionario` a partir de los archivos pasados como argumento.
* de búsqueda de la mejor palabra.

## Más ficheros de prueba

Esta práctica tiene los siguientes ficheros de prueba en la carpeta `data`:

| Archivo | Descripción |
| --- | --- |
| `bolsa-es_ES.txt` | Bolsa de letras con el conjunto de letras oficial de Scrabble para el idioma español (`es_ES`) |
| `bolsa-en_EN.txt` | Bolsa de letras con el conjunto de letras oficial de Scrabble para el idioma inglés (`en_EN`) |
| `diccionario-es_ES.txt` | Palabras del diccionario de la RAE para el idioma español (`es_ES`). Contiene **80383 palabras** |
| `diccionario-en_EN.txt` | Palabras del diccionario Oxford Dictionary para el idioma inglés (`en_EN`). Contiene **466544 palabras** e **incluye caracteres especiales** |

Puede ejecutar el programa `scrabble` con los siguientes argumentos:

~~~
./bin/scrabble [fichero_diccionario] [fichero_letras] [salida_diccionario]
~~~

En el que:

* `[fichero_diccionario]` es la ruta del fichero que contiene el diccionario.
* `[fichero_letras]` es la ruta al fichero que contiene la bolsa de letras.
* `[salida_diccionario]` es la ruta al fichero donde se escribirá el diccionario proporcionado.

Con las siguientes consideraciones:

* Es muy importante que tanto `[fichero_diccionario]` como `[fichero_letras]` tengan el formato especificado en las clases `Diccionario` y `Letras`, respectivamente. Además, las rutas deben ser válidas.
* Si `[salida_diccionario]` no existe, se creará, pero al menos debe existir la carpeta donde está contenido.