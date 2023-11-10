CC=g++
BINARY=bin

OBJECTS=main.o run.o Parser/Construct.o Nodes/Node.o Lexer/scanner.o Disk_Space/FSM.o Commands/create_db.o Commands/create_table.o Catalog/Syst_Attr.o Catalog/Syst_Index.o Catalog/Syst_Rel.o Commands/select.o B+_Tree.o Commands/insert.o

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^

%.o:%.cpp
	$(CC) -c -o $@ $^