# Компилятор и инструменты
CXX := g++
AR := ar

# Флаги
CXXFLAGS := -std=c++17 -fPIC 
LDFLAGS := -framework Accelerate
FORMAT := clang-format

# Директории
SRC_DIR := src
BUILD_DIR := build
TEST_DIR := tests
INCLUDE_DIR := include

# Цели
TEST_TARGET := libML_test
LIB_TARGET := libML.a

# Исходники
INCLUDE_FILES := $(wildcard $(INCLUDE_DIR)/core.hpp) \
                 $(wildcard $(INCLUDE_DIR)/models/IModel.hpp) \
                 $(wildcard $(INCLUDE_DIR)/models/AClassifier.hpp) \
                 $(wildcard $(INCLUDE_DIR)/models/neighbors/*.hpp) \
                 $(wildcard $(INCLUDE_DIR)/metrics/classification.hpp) \
                 $(wildcard $(INCLUDE_DIR)/metrics/distance.hpp)

SOURCE_FILES := $(wildcard $(SRC_DIR)/models/AClassifier.cpp) \
                $(wildcard $(SRC_DIR)/models/neighbors/*.cpp) \
                $(wildcard $(SRC_DIR)/metrics/distance/*.cpp) \
				$(wildcard $(SRC_DIR)/metrics/classification/*.cpp)

TEST_FILES := $(wildcard $(TEST_DIR)/*.cpp)

# Объектные файлы
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCE_FILES))

# Цветной вывод
YELLOW := \033[1;33m
RESET := \033[0m

.PHONY: all lib test format check_style clean

all: format lib

$(BUILD_DIR):
	@mkdir -p $@

# Построение библиотеки
lib: $(BUILD_DIR) $(LIB_TARGET)

$(LIB_TARGET): $(OBJ_FILES)
	@echo "$(YELLOW)[AR]$@$(RESET)"
	@$(AR) rcs $@ $^

# Построение объектных файлов
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)[CXX]$<$(RESET)"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Построение и запуск тестов
test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(LIB_TARGET) $(TEST_FILES)
	@echo "$(YELLOW)[LINK]$@$(RESET)"
	@$(CXX) $(CXXFLAGS) $(TEST_FILES) -L. -lML $(LDFLAGS) -o $@

# Проверка и форматирование
check_style:
	@echo "$(YELLOW)[CHECK FORMAT]$(RESET)"
	@$(FORMAT) -n $(SOURCE_FILES) $(TEST_FILES) $(INCLUDE_FILES)

format:
	@echo "$(YELLOW)[FORMAT]$(RESET)"
	@$(FORMAT) -i $(SOURCE_FILES) $(TEST_FILES) $(INCLUDE_FILES)

# Очистка
clean:
	@echo "$(YELLOW)[CLEAN]$(RESET)"
	@rm -rf $(BUILD_DIR) $(TEST_TARGET) $(LIB_TARGET)
