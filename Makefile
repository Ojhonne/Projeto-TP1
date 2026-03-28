# 1. Detecção do Sistema Operacional
ifeq ($(OS),Windows_NT)
    # Comandos para Windows
    RM = rmdir /s /q
    MKDIR = mkdir
    FIX_PATH = $(subst /,\,$1)
    EXEC_EXT = .exe
    # Verifica se a pasta existe antes de criar (evita erro no Windows)
    SAFE_MKDIR = if not exist $(subst /,\,$1) mkdir $(subst /,\,$1)
else
    # Comandos para Linux/Mac
    RM = rm -rf
    MKDIR = mkdir -p
    FIX_PATH = $1
    EXEC_EXT =
    SAFE_MKDIR = mkdir -p $1
endif

# 2. Configurações de Compilação
CXX      := g++
CXXFLAGS := -Wall -std=c++17 -Iheaders
SRC_DIR  := source
OBJ_DIR  := obj
BIN_DIR  := bin
TARGET   := $(BIN_DIR)/scrum$(EXEC_EXT)

# 3. Arquivos
SOURCES  := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/**/*.cpp)
OBJECTS  := $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# 4. Regras
all: $(TARGET)

$(TARGET): $(OBJECTS)
	@$(call SAFE_MKDIR, $(BIN_DIR))
	$(CXX) $(OBJECTS) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if not exist $(subst /,\,$(dir $@)) mkdir $(subst /,\,$(dir $@))
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR) $(BIN_DIR)

# Regra para rodar o programa direto pelo make
run: all
	./$(TARGET)

.PHONY: all clean run