winfetch: src/main.c src/sysinfo.c src/hardware.c
	mkdir -p bin
	gcc $^ -o bin/$@ -ladvapi32