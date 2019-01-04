# Makefile para SCRABBLE WORD FINDER
# Práctica final ED, 2º DGIIM 2018/2019, UGR
# Alumnos: Miguel Ángel Fernández Gutiérrez
#          Juan Manuel Mateos Pérez

INC = include
BIN = bin
SRC = src
OBJ = obj
ZIP = zip
DOC = doc
OUT = output

all: $(BIN)/scrabble
	@echo "_____________________________________________________________________\n"
	@echo "make all: Los archivos han sido compilados\n"
	@echo "Puede también usar las siguientes órdenes make:"
	@echo " - make doxy : genera la documentación doxygen"
	@echo "      Aquí encontrará toda la información relativa a esta práctica"
	@echo " - make test : ejecuta el test equivalente a:"
	@echo "      ./bin/scrabble ./data/diccionario-es_ES.txt"
	@echo "      ./data/bolsa-es_ES.txt ./output/diccionario-es_ES-output.txt"
	@echo " - make clean : limpia los binarios y la documentación"
	@echo " - make zip : crea el comprimido"
	@echo "_____________________________________________________________________\n"

$(BIN)/scrabble: $(OBJ)/scrabble.o $(OBJ)/Diccionario.o $(OBJ)/Letras.o
	g++ -o $(BIN)/scrabble $(OBJ)/scrabble.o $(OBJ)/Diccionario.o $(OBJ)/Letras.o

$(OBJ)/scrabble.o: $(SRC)/scrabble.cpp $(INC)/*.h
	g++ -o $(OBJ)/scrabble.o -c $(SRC)/scrabble.cpp -I$(INC)

$(OBJ)/Diccionario.o: $(SRC)/Diccionario.cpp $(INC)/Diccionario.h $(OBJ)/Letras.o
	g++ -o $(OBJ)/Diccionario.o -c $(SRC)/Diccionario.cpp -I$(INC)

$(OBJ)/Letras.o: $(SRC)/Letras.cpp $(INC)/Letras.h
	g++ -o $(OBJ)/Letras.o -c $(SRC)/Letras.cpp -I$(INC)

doxy:
	doxygen doc/doxyfile
	@echo "_____________________________________________________________________\n"
	@echo "make test: Se ha generado la documentación. Vaya a:"
	@echo "              ./doc/html/index.html"
	@echo "_____________________________________________________________________\n"

test:
	./bin/scrabble ./data/diccionario-es_ES.txt ./data/bolsa-es_ES.txt ./output/diccionario-es_ES-output.txt

clean:
	rm -f $(OBJ)/*
	rm -f $(BIN)/scrabble
	rm -f $(ZIP)/*
	rm -fR $(DOC)/html
	rm -fR $(DOC)/latex
	rm -f $(OUT)/*
	@echo "_____________________________________________________________________\n"
	@echo "make clean: Limpiados todos los binarios y la documentación"
	@echo "_____________________________________________________________________\n"

zip: clean
	zip -r $(ZIP)/scrabble.zip *
	@echo "_____________________________________________________________________\n"
	@echo "make zip: Se ha comprimido el archivo en:"
	@echo "             ./zip/scrabble.zip"
	@echo "_____________________________________________________________________\n"
