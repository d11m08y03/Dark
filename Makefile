output: temp/main.o temp/Entity.o temp/Level.o temp/Mouse.o temp/Particles.o temp/RenderWindow.o temp/Sound.o temp/Scenarios.o
	g++ temp/main.o temp/Entity.o temp/Level.o temp/Mouse.o temp/Particles.o temp/RenderWindow.o temp/Sound.o temp/Scenarios.o -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o bin/output

temp/main.o: src/main.cpp
	g++ -c src/main.cpp -m64 -g -Wall -I include && mv main.o temp/

temp/Entity.o: src/Entity.cpp
	g++ -c src/Entity.cpp -m64 -g -Wall -I include && mv Entity.o temp/

temp/Level.o: src/Level.cpp
	g++ -c src/Level.cpp -m64 -g -Wall -I include && mv Level.o temp/

temp/Mouse.o: src/Mouse.cpp
	g++ -c src/Mouse.cpp -m64 -g -Wall -I include && mv Mouse.o temp/

temp/Particles.o: src/Particles.cpp
	g++ -c src/Particles.cpp -m64 -g -Wall -I include && mv Particles.o temp/

temp/RenderWindow.o: src/RenderWindow.cpp
	g++ -c src/RenderWindow.cpp -m64 -g -Wall -I include && mv RenderWindow.o temp/

temp/Sound.o: src/Sound.cpp
	g++ -c src/Sound.cpp -m64 -g -Wall -I include && mv Sound.o temp/

temp/Scenarios.o: src/Scenarios.cpp
	g++ -c src/Scenarios.cpp -m64 -g -Wall -I include && mv Scenarios.o temp/

run:
	./bin/output

clean:
	rm temp/*.o 