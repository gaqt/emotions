setup:
	@mkdir -p dist

build:
	@g++ src/main.cpp -lraylib -O3 -o dist/out

run:
	@dist/out

buildRun: build run
