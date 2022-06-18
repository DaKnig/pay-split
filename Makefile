CFLAGS += `pkg-config --cflags --libs gtk4` -export-dynamic -O0 -g -Werror
main: main.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf main *.o

memtest: main
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all \
	         --suppressions=/usr/share/glib-2.0/valgrind/glib.supp   \
	         --suppressions=/usr/share/gtk-4.0/valgrind/gtk.supp     \
	         ./main
