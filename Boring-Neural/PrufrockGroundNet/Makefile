# ============================================================
# Makefile for SoilNet (from-scratch C++ Neural Network)
# ============================================================

# ------------------------------------------------------------
# 1. Compiler and flags
# ------------------------------------------------------------
CXX      = g++                          # The C++ compiler we will use
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude  # Language standard + warnings + include path
# -std=c++17   → use modern C++
# -Wall -Wextra → turn on almost all warnings (very useful while learning)
# -Iinclude    → tell the compiler to look in the "include/" folder for headers

# OpenCV 5 flags
OPENCV_CFLAGS := $(shell pkg-config --cflags opencv5)
OPENCV_LIBS   := $(shell pkg-config --libs   opencv5)

CXXFLAGS += $(OPENCV_CFLAGS)
LDFLAGS   = $(OPENCV_LIBS)

# Optional: add optimization or debug flags
# For a release build you can change the line above to:
# CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -Iinclude
# For a debug build (with symbols for gdb/lldb):
# CXXFLAGS = -std=c++17 -g -Wall -Wextra -Iinclude

# ------------------------------------------------------------
# 2. Directories
# ------------------------------------------------------------
SRC_DIR   = src
BUILD_DIR = build
TARGET    = soilnet                 # Name of the final executable

# ------------------------------------------------------------
# 3. Source files and object files
# ------------------------------------------------------------
# List every .cpp file that needs to be compiled.
# (Headers that are header-only do NOT appear here.)
SRCS = \
    $(SRC_DIR)/Tensor.cpp \
    $(SRC_DIR)/DenseLayer.cpp \
    $(SRC_DIR)/Conv2DLayer.cpp \
    $(SRC_DIR)/MaxPool2DLayer.cpp \
    $(SRC_DIR)/FlattenLayer.cpp \
    $(SRC_DIR)/Activation.cpp \
    $(SRC_DIR)/Loss.cpp \
    $(SRC_DIR)/Optimizer.cpp \
    $(SRC_DIR)/Network.cpp \
    $(SRC_DIR)/Dataset.cpp \
    $(SRC_DIR)/Utils.cpp \
    $(SRC_DIR)/main.cpp

# Automatically turn every .cpp into a .o inside the build/ folder
# Example: src/Tensor.cpp  →  build/Tensor.o
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# ------------------------------------------------------------
# 4. Default target (what happens when you just type "make")
# ------------------------------------------------------------
all: $(TARGET)

# ------------------------------------------------------------
# 5. Linking step – turn all object files into the final program
# ------------------------------------------------------------
$(TARGET): $(OBJS)
	@echo "Linking $@"
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)
	@echo "Build finished → ./$(TARGET)"

# ------------------------------------------------------------
# 6. Compilation rule – how to turn a .cpp into a .o
# ------------------------------------------------------------
# This is a *pattern rule*. It says:
#   "For any file that looks like build/Something.o,
#    the corresponding source is src/Something.cpp"
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)          # create build/ folder if it doesn't exist
	@echo "Compiling $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ------------------------------------------------------------
# 7. Convenience targets
# ------------------------------------------------------------
run: $(TARGET)
	./$(TARGET)

clean:
	@echo "Cleaning..."
	rm -rf $(BUILD_DIR) $(TARGET)
	@echo "Done."

# "Phony" targets – these are not real files, just commands
.PHONY: all run clean