compile:
	g++ ./src/*.cpp -o build/output.exe -I ./include -L ./lib ./src/glad.c -lopengl32 -lglfw3 -lgdi32 -lassimp.dll

run:
	build/output.exe