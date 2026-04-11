CC = cc
SRC = src/list.c src/dfa.c
MAIN = main.c

run:
	$(CC) $(MAIN) $(SRC)

