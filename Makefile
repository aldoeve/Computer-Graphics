scene.out: scene.cpp camera.cpp
	g++ -g -Wall -o scene scene.cpp camera.cpp -lglut -lGL -lGLU
	./scene

clean:
	rm -f scene
