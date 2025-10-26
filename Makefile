LIBS := -lraylib -lraygui
INCLUDE := -Isrc -Ilib/raygui
CFLAGS := -std=c23 -O3 -Wall -Wextra -Wpedantic
CXXFLAGS := -std=c++23 -O3 -Wall -Wextra -Wpedantic

setup:
	@echo "Running setup script"
	@mkdir -p dist
	@mkdir -p dist/lib
	@gcc $(CFLAGS) -c lib/raygui/raygui.c -o dist/lib/raygui.o
	@ar rcs dist/lib/libraygui.a dist/lib/raygui.o
	@echo "Done!"

clean:
	@echo "Running clean script"
	@rm -r dist
	@echo "Done!"

build:
	@echo "Running build script"
	@g++ $(CXXFLAGS) $(INCLUDE) src/main.cpp -Ldist/lib $(LIBS) -o dist/out
	@cp -r assets dist/assets
	@echo "Done!"

run:
	@echo "Running project"
	@dist/out
	@echo "Done!"

format:
	@echo "Formatting project"
	@clang-format -i $(shell find src/** -type f)
	@echo "Done!"

buildRun: build run

.PHONY: setup clean build run buildRun format
