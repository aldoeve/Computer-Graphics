scene.out: scene.cpp camera.cpp
	g++ -g -Wall -o scene.cpp camera.cpp -lglut -lGL -lGLU
