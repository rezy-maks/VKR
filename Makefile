# Название исполняемого файла
TARGET = bin/main_program

# Директории
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
INCLUDE_DIR = include

# Файлы исходного кода
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Файлы объектных модулей
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Флаги компилятора
CXX = g++
CXXFLAGS = -fopenmp -Wall -Wextra -O2 -I$(INCLUDE_DIR)

# Флаги для создания динамических библиотек
SOFLAGS = -fPIC -shared -fopenmp

# Библиотеки
LIBS = -ldl -fopenmp

# Компиляция и линковка исполняемого файла
$(TARGET): $(OBJS) $(BIN_DIR)/libdata.so | $(BIN_DIR)
	$(CXX) -o $@ $(OBJS) $(LIBS)

# Компиляция объектных файлов
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Создание папки для объектных файлов (если еще не существует)
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Создание бинарной папки (если еще не существует)
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Создание динамической библиотеки
$(BIN_DIR)/libdata.so: $(BUILD_DIR)/my_data_structure.o | $(BIN_DIR)
	$(CXX) $(SOFLAGS) -o $@ $<

# Удаление скомпилированных файлов
clean:
	rm -f $(TARGET) $(OBJS) $(BIN_DIR)/libdata.so

# Компиляция динамических библиотек и основного файла
all: $(TARGET)

# Перекомпиляция проекта
rebuild: clean all

# Установка цели по умолчанию
.PHONY: all clean rebuild