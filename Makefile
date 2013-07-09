CXXFLAGS = -pedantic -Wall -Wextra -std=c++98 -O -Wabi -Weffc++ -Wctor-dtor-privacy -Wold-style-cast -Woverloaded-virtual -Wno-pmf-conversions -Wsign-promo `pkg-config --cflags sdl`

LIBS = `pkg-config --libs sdl`

main: main.o graphics.o functional.o sprite.o gamedriver.o
	g++ ${CXXFLAGS} main.o graphics.o functional.o sprite.o gamedriver.o -o main -Wl,${LIBS}

main.o: main.cpp main.h graphics.h

graphics.o: graphics.cpp graphics.h sprite.h

functional.o: functional.cpp functional.h

sprite.o: sprite.cpp sprite.h functional.h graphics.h

gamedriver.o: gamedriver.cpp gamedriver.h functional.h graphics.h

clean:
	rm *.o main
