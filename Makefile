indoor.out: objProject.cpp objReader.cpp
	g++ -g -Wall -o test2 objProject.cpp objReader.cpp -lglut -lGL -lGLU
	./test2

clean:
	rm -f test2

save:
	@git add --all
	@git commit -m"."
	git push
