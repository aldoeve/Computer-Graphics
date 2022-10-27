indoor.out: camera.cpp indoor.cpp objects.cpp
	g++ -g -Wall -o indoor camera.cpp indoor.cpp objects.cpp -lglut -lGL -lGLU
	./indoor

clean:
	rm -f indoor

save:
	@git add --all
	@git commit -m"."
	git push

reminder:
	@echo -e '\n zip should contain camera.cpp indoor.cpp objects.cpp makefile stb_image.h objects.h \n'
