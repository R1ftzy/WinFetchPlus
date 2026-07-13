winfetch: src/main.c \
          src/sysinfo.c \
          src/hardware.c \
          src/memory.c \
          src/battery.c \
          src/gpu.c \
          src/display.c \
          src/config.c \
          src/renderer.c \
          src/math3d.c \
          src/demo.c \
          src/demos/cube.c \
          
	mkdir -p bin
	gcc $^ -o bin/$@ -ladvapi32 -lpowrprof -lm