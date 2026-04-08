# 1. Detecção do Sistema Operacional
ifeq ($(OS),Windows_NT)
    # Força o uso do CMD no Windows para evitar conflitos com sh.exe do Git Bash
    SHELL := cmd.exe
    RM = rmdir /s /q
    # No Windows, precisamos garantir que o caminho use backslashes para comandos do CMD
    FIX_PATH = $(subst /,\,$1)
    EXEC_EXT = .exe
    # Comando para criar diretório se não existir
    SAFE_MKDIR = if not exist $(subst /,\,$1) mkdir $(subst /,\,$1)
    RUN_CMD = $(subst /,\,$(TARGET))
else
    RM = rm -rf
    FIX_PATH = $1
    EXEC_EXT =
    SAFE_MKDIR = mkdir -p $1
    RUN_CMD = ./$(TARGET)
endif

# 2. Configurações
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

# Regra genérica para objetos
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@$(call SAFE_MKDIR, $(dir $@))
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@$(SAFE_MKDIR) $(OBJ_DIR)
	@$(SAFE_MKDIR) $(BIN_DIR)
	$(RM) $(OBJ_DIR)
	$(RM) $(BIN_DIR)

run: all
	$(RUN_CMD)

.PHONY: all clean run