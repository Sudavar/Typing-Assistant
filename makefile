CC=g++
FLAG=-g3 -Wall
OPTFLAG=-O2
SOURCES=*.cpp *.c
EXECUTABLE=typing-assistant

all: final
debug: buildDeb run
final: buildOpt run
mem: buildDeb mem_check
gdb: buildDeb run_gdb

buildDeb:
	$(CC) $(FLAG) $(SOURCES) -o $(EXECUTABLE)

buildOpt:
	$(CC) $(OPTFLAG) $(SOURCES) -o $(EXECUTABLE)

run:
	./$(EXECUTABLE)

run_gdb:
	gdb ./$(EXECUTABLE)

mem_check:
	valgrind ./$(EXECUTABLE) --leak-check=full --show-reachable=yes --track-fds=yes

clean:
	rm $(EXECUTABLE)
