# 1. ОПРЕДЕЛЕНИЕ ОПЕРАЦИОННОЙ СИСТЕМЫ
ifeq ($(OS),Windows_NT)
    RM = del /Q /F
    EXE = .exe
    FIX_PATH = $(subst /,\,$1)
else
    RM = rm -rf
    EXE =
    FIX_PATH = $1
endif

# 2. ПЕРЕМЕННЫЕ ПРОЕКТА
CC = g++
CFLAGS = -Wall -std=c++17
TARGET = my_program$(EXE)

# Ищет ВСЕ файлы .cpp в текущей папке
SRCS = $(wildcard *.cpp)
# Создает список объектных файлов (.o) в текущей папке
OBJS = $(SRCS:.cpp=.o)

# 3. ОСНОВНЫЕ ЦЕЛИ
.PHONY: all clean

all: $(TARGET)

# Сборка программы из объектных файлов
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Компиляция каждого .cpp в .o
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка папки от временных файлов и программы
clean:
	$(RM) $(call FIX_PATH, $(TARGET))
	$(RM) $(call FIX_PATH, *.o)
