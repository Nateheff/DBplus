CC=g++
BINARY=bin
CFLAGS=-lws2_32


OBJECTS=main_server.o run.o Parser/Construct.o Nodes/Node.o Lexer/scanner.o Disk_Space/FSM.o Commands/create_db.o Commands/create_table.o Catalog/Syst_Attr.o Catalog/Syst_Index.o Catalog/Syst_Rel.o Commands/select.o B+_Tree.o Commands/insert.o Commands/drop.o Commands/update.o Commands/delete.o Socket/Socket.o Lexer/list.o

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

%.o:%.cpp
	$(CC) -c -o $@ $^

# OBJECTS_API=main_server.o run.o Parser/Construct.o Nodes/Node.o Lexer/scanner.o Disk_Space/FSM.o Commands/create_db.o Commands/create_table.o Catalog/Syst_Attr.o Catalog/Syst_Index.o Catalog/Syst_Rel.o Commands/select.o B+_Tree.o Commands/insert.o Commands/drop.o Commands/update.o Commands/delete.o Socket/Server.o