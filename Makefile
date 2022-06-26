TARGET = termPacman
CXX = g++
CXX_FLAGS = -std=c++14 -Wall -pedantic
BUILD_DIR = build

.PHONY: all
all: compile doc

.PHONY: compile
compile: $(TARGET)

.PHONY: run
run: $(TARGET)
	./$(TARGET)

$(TARGET): $(BUILD_DIR)/main.o $(BUILD_DIR)/CApplication.o $(BUILD_DIR)/CSession.o $(BUILD_DIR)/CMap.o $(BUILD_DIR)/CDifficulty.o $(BUILD_DIR)/CEasy.o $(BUILD_DIR)/CNormal.o $(BUILD_DIR)/CHard.o $(BUILD_DIR)/CMoving.o $(BUILD_DIR)/CPacman.o $(BUILD_DIR)/CGhost.o $(BUILD_DIR)/CRedGhost.o $(BUILD_DIR)/CPinkGhost.o $(BUILD_DIR)/CBlueGhost.o $(BUILD_DIR)/COrangeGhost.o $(BUILD_DIR)/CVeryEasy.o
	$(CXX) $(CXX_FLAGS) $^ -o $@

$(BUILD_DIR)/%.o: src/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXX_FLAGS) $< -c -o $@

.PHONY: doc
doc: src/CApplication.h src/CBlueGhost.h src/CDifficulty.h src/CEasy.h src/CGhost.h src/CHard.h src/CMap.h src/CMoving.h src/CNormal.h src/COrangeGhost.h src/CPacman.h src/CPinkGhost.h src/CRedGhost.h src/CSession.h
	doxygen Doxyfile

.PHONY: clean
clean: 
	rm -rf $(TARGET) $(BUILD_DIR)/ doc/ 2>/dev/null

#dependencies
$(BUILD_DIR)/CApplication.o: src/CApplication.cpp src/CApplication.h src/CSession.h src/CDifficulty.h src/CMap.h src/CMoving.h src/CPacman.h src/CGhost.h src/CRedGhost.h src/CPinkGhost.h src/CBlueGhost.h src/COrangeGhost.h src/CEasy.h src/CNormal.h src/CHard.h src/CVeryEasy.h
$(BUILD_DIR)/CBlueGhost.o: src/CBlueGhost.cpp src/CBlueGhost.h src/CMoving.h src/CMap.h src/CGhost.h src/CDifficulty.h
$(BUILD_DIR)/CDifficulty.o: src/CDifficulty.cpp src/CDifficulty.h src/CMap.h
$(BUILD_DIR)/CEasy.o: src/CEasy.cpp src/CEasy.h src/CDifficulty.h src/CMap.h
$(BUILD_DIR)/CGhost.o: src/CGhost.cpp src/CGhost.h src/CMoving.h src/CMap.h src/CDifficulty.h
$(BUILD_DIR)/CHard.o: src/CHard.cpp src/CHard.h src/CDifficulty.h src/CMap.h
$(BUILD_DIR)/CMap.o: src/CMap.cpp src/CMap.h
$(BUILD_DIR)/CMoving.o: src/CMoving.cpp src/CMoving.h src/CMap.h
$(BUILD_DIR)/CNormal.o: src/CNormal.cpp src/CNormal.h src/CDifficulty.h src/CMap.h
$(BUILD_DIR)/COrangeGhost.o: src/COrangeGhost.cpp src/COrangeGhost.h src/CMoving.h src/CMap.h src/CGhost.h src/CDifficulty.h
$(BUILD_DIR)/CPacman.o: src/CPacman.cpp src/CPacman.h src/CMoving.h src/CMap.h
$(BUILD_DIR)/CPinkGhost.o: src/CPinkGhost.cpp src/CPinkGhost.h src/CMoving.h src/CMap.h src/CGhost.h src/CDifficulty.h
$(BUILD_DIR)/CRedGhost.o: src/CRedGhost.cpp src/CRedGhost.h src/CMoving.h src/CMap.h src/CGhost.h src/CDifficulty.h
$(BUILD_DIR)/CSession.o: src/CSession.cpp src/CSession.h src/CDifficulty.h src/CMap.h src/CMoving.h src/CPacman.h src/CGhost.h src/CRedGhost.h src/CPinkGhost.h src/CBlueGhost.h src/COrangeGhost.h
$(BUILD_DIR)/main.o: src/main.cpp src/CApplication.h src/CSession.h src/CDifficulty.h src/CMap.h src/CMoving.h src/CPacman.h src/CGhost.h src/CRedGhost.h src/CPinkGhost.h src/CBlueGhost.h src/COrangeGhost.h src/CEasy.h src/CNormal.h src/CHard.h src/CVeryEasy.h
$(BUILD_DIR)/CVeryEasy.o: src/CVeryEasy.cpp src/CVeryEasy.h src/CDifficulty.h src/CMap.h

