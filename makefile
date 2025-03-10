# Define object files and target
OBJ_FILES = main.o common.o create_database.o display_output.o save_database.o search.o search_file.o update_database.o
TARGET = inverted.exe

# Build the executable
$(TARGET): $(OBJ_FILES)
	gcc -o $(TARGET) $(OBJ_FILES)
	
main.o: main.c
	gcc -c main.c

# Compile common.o
common.o: common.c
	gcc -c common.c

# Compile create_database.o
create_database.o: create_database.c
	gcc -c create_database.c

# Compile create_database.o
display_output.o: display_output.c
	gcc -c display_output.c

# Compile save_database.o
save_database.o: save_database.c
	gcc -c save_database.c

# Compile search.o
search.o: search.c
	gcc -c search.c

# Compile search_file.o
search_file.o: search_file.c
	gcc -c search_file.c

# Compile update_database.o
update_database.o: update_database.c
	gcc -c update_database.c

# Clean up object files and executable
clean:
	rm -f $(OBJ_FILES) $(TARGET)