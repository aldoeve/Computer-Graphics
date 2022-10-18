scene.out: scene.cpp camera.cpp
	g++ -g -Wall -o scene scene.cpp camera.cpp -lglut -lGL -lGLU

clean:
	rm -f scene

save:
	git add --all
	git commit -m "."
	git push
