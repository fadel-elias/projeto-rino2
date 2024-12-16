all: 
	g++ -I SDLsrc/include -L SDLsrc/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2