CXX      := g++
CXXFLAGS += -g -O0 -std=c++17 -Wall -Wextra -Wno-attributes -Wno-unused-parameter -DLIBTEST
LDFLAGS  += 
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects/
APP_DIR  := $(BUILD)/bin/
TARGET   := simtest
INCLUDE  += -I.
SRC      := $(wildcard ./*.cpp)

OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)%.o)

all: build simtest

$(OBJ_DIR)%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $(APP_DIR)$(TARGET) $(OBJECTS) $(LDFLAGS)

.PHONY: all build clean simtest

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

simtest: $(APP_DIR)$(TARGET)

install: install_bin

install_bin: $(APP_DIR)$(TARGET)
	install -d $(PREFIX)/bin/
	install -m 775 $(APP_DIR)$(TARGET) $(PREFIX)/bin/

clean:
	-@rm -rvf $(OBJ_DIR)*
	-@rm -rvf $(APP_DIR)*
