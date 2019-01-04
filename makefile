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
	$(info _____________________________________________________________________)
	$(info )
	$(info Los archivos han sido compilados)
	$(info Puede también usar las siguientes órdenes make:)
	$(info -- make doxy : genera la documentación doxygen)
	$(info .     Aquí encontrará toda la información relativa a esta práctica)
	$(info -- make test : ejecuta el test equivalente a:)
	$(info .     ./bin/scrabble ./data/diccionario-es_ES.txt)
	$(info .     ./data/bolsa-es_ES.txt ./output/diccionario-es_ES-output.txt)
	$(info -- make clean : limpia los binarios y la documentación)
	$(info -- make zip : crea el comprimido)
	$(info _____________________________________________________________________)
	$(info )

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

test:
	./bin/scrabble ./data/diccionario-es_ES.txt ./data/bolsa-es_ES.txt ./output/diccionario-es_ES-output.txt

clean:
	rm -f $(OBJ)/*
	rm -f $(BIN)/scrabble
	rm -f $(ZIP)/*
	rm -fR $(DOC)/html
	rm -fR $(DOC)/latex
	rm -f $(OUT)/*

zip: clean
	zip -r $(ZIP)/scrabble.zip *