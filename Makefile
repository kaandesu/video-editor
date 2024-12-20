PROJECT_NAME = video_editor
BUILD_DIR = build

all: clean build run

build: clean
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake ..
	cd $(BUILD_DIR) && make

run: build
	./$(BUILD_DIR)/$(PROJECT_NAME)

clean:
	rm -rf $(BUILD_DIR)
