# 1. Detecção do Sistema Operacional
ifeq ($(OS),Windows_NT)
    # Comandos para Windows
    RM = rmdir /s /q
    SAFE_MKDIR = if not exist $(subst /,\,$1) mkdir $(subst /,\,$1)
    EXEC_EXT = .exe
    
    # Biblioteca de interface para Windows (MinGW)
    LDLIBS = -lpdcurses
    
    define CREATE_DIR_WIN
        if not exist $(subst /,\,$(dir $@)) mkdir $(subst /,\,$(dir $@))
    endef
    
    RUN_CMD = $(subst /,\,$(TARGET))
else
    # Comandos para Linux/Mac
    RM = rm -rf
    SAFE_MKDIR = mkdir -p $1
    EXEC_EXT =
    
    # ADIÇÃO: -lpthread e -ldl para o SQLite no Linux
    LDLIBS = -lncurses -ltinfo -lpthread -ldl 
    
    define CREATE_DIR_LINUX
        mkdir -p $(dir $@)
    endef
    
    RUN_CMD = ./$(TARGET)
endif

# 2. Configurações de Compilação
CXX      := g++
CC       := gcc # ADIÇÃO: Compilador para arquivos C (SQLite)
CXXFLAGS := -Wall -std=c++17 -Iheaders
CFLAGS   := -Wall -Iheaders # ADIÇÃO: Flags para o compilador C
SRC_DIR  := source
OBJ_DIR  := obj
BIN_DIR  := bin
TARGET   := $(BIN_DIR)/scrum$(EXEC_EXT)

# 3. Arquivos
SOURCES_CPP := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/**/*.cpp)
SOURCES_C := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/**/*.c)

# ADIÇÃO: Concatena os objetos gerados a partir do .cpp e do .c
OBJECTS     := $(SOURCES_CPP:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o) \
               $(SOURCES_C:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# 4. Regras
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(call SAFE_MKDIR,$(BIN_DIR))
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDLIBS)

# --- REGRAS DE COMPILAÇÃO ---
ifeq ($(OS),Windows_NT)
# Regra para C++
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CREATE_DIR_WIN)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ADIÇÃO: Regra para C (SQLite) no Windows
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CREATE_DIR_WIN)
	$(CC) $(CFLAGS) -c $< -o $@
else
# Regra para C++
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CREATE_DIR_LINUX)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ADIÇÃO: Regra para C (SQLite) no Linux
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CREATE_DIR_LINUX)
	$(CC) $(CFLAGS) -c $< -o $@
endif

# O traço (-) no início faz o Make ignorar erros caso a pasta já não exista
clean:
ifeq ($(OS),Windows_NT)
	-$(RM) $(subst /,\,$(OBJ_DIR)) $(subst /,\,$(BIN_DIR))
else
	-$(RM) $(OBJ_DIR) $(BIN_DIR)
endif

# Regra para rodar o programa direto pelo make
run: all
	$(RUN_CMD)

.PHONY: all clean run