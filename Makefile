indoor.out: conclusion.cpp objReader.cpp objects.cpp
	g++ -g -Wall -o conclusion conclusion.cpp objReader.cpp camera.cpp objects.cpp -lglut -lGL -lGLU
	./conclusion

clean:
	rm -f conclusion

save:
	@git add --all
	@git commit -m"."
	git push
