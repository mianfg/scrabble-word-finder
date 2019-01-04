# Scrabble Word Finder
> Programa para buscar la mejor palabra de un set de Letras que se encuentre en un cierto Diccionario

Este programa es la práctica final de la asignatura **Estructura de Datos** del **Doble Grado en Ingeniería Informática y Matemáticas** de la **Universidad de Granada**, curso 2018/2019. Ha sido desarrollada por los siguientes alumnos:

* Miguel Ángel Fernández Gutiérrez ([@mianfg](https://github.com/mianfg))
* Juan Manuel Mateos Pérez ([@Trajano1999](https://github.com/Trajano1999))

---

> **DISCLAIMER**
>
> SCRABBLE® is a registered trademark. All intellectual property rights in and to the game are owned in the U.S.A and Canada by Hasbro Inc., and throughout the rest of the world by J.W. Spear & Sons Limited of Maidenhead, Berkshire, England, a subsidiary of Mattel Inc. Mattel and Spear are not affiliated with Hasbro. Words with Friends is a trademark of Zynga with Friends.
>
> This project is not affiliated with SCRABBLE®, Mattel Inc, Hasbro Inc, Zynga with Friends or Zynga Inc in any way. This project is for educational purposes only.

---

## Compilación y ejecución

[Descarga la última versión](https://github.com/mianfg/scrabble-word-finder/archive/v1.0.zip) de este proyecto o haz `clone`, luego cerciórate que tienes la siguiente estructura de archivos:

~~~
.
├── bin
├── data
│   ├── bolsa-en_EN.txt
│   ├── bolsa-es_ES.txt
│   ├── diccionario-en_EN.txt
│   └── diccionario-es_ES.txt
├── doc
│   ├── doxyfile
│   └── doxys
│       ├── ap1.md
│       └── ap2.md
├── include
│   ├── Diccionario.h
│   └── Letras.h
├── makefile
├── obj
├── output
├── src
│   ├── Diccionario.cpp
│   ├── Letras.cpp
│   └── scrabble.cpp
└── zip
~~~

Es **muy importante** que todas las carpetas estén creadas.

Luego, ejecuta la orden `make`. Dicha orden dará más instrucciones sobre cómo ejecutar la práctica. También te recomendamos hacer

~~~
make doxy
~~~

Y abrir el archivo `./doc/html/index.html` en un navegador web. En él verás toda la información de la práctica: estructuras de datos utilizadas, algoritmos...

> **NOTA:** debe tener Doxygen instalado.
