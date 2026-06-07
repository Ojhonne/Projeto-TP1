# 1. Detecção do Sistema Operacional
ifeq ($(OS),Windows_NT)
    # Comandos para Windows
    RM = rmdir /s /q
    # Define a função com $1 (precisa usar o comando 'call' na regra)
    SAFE_MKDIR = if not exist $(subst /,\,$1) mkdir $(subst /,\,$1)
    EXEC_EXT = .exe
    
    # Regra de compilação para criar a pasta do objeto no Windows
    define CREATE_DIR_WIN
        if not exist $(subst /,\,$(dir $@)) mkdir $(subst /,\,$(dir $@))
    endef
    
    # Adapta a string de execução para o Windows (ex: bin\scrum.exe)
    RUN_CMD = $(subst /,\,$(TARGET))
else
    # Comandos para Linux/Mac
    RM = rm -rf
    SAFE_MKDIR = mkdir -p $1
    EXEC_EXT =
    
    # Regra de compilação para criar a pasta do objeto no Linux
    define CREATE_DIR_LINUX
        mkdir -p $(dir $@)
    endef
    
    # Mantém o padrão do bash
    RUN_CMD = ./$(TARGET)
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
	$(call SAFE_MKDIR,$(BIN_DIR))
	$(CXX) $(OBJECTS) -o $(TARGET)

# Regra condicional para criar diretórios durante a compilação dos .o
ifeq ($(OS),Windows_NT)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CREATE_DIR_WIN)
	$(CXX) $(CXXFLAGS) -c $< -o $@
else
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CREATE_DIR_LINUX)
	$(CXX) $(CXXFLAGS) -c $< -o $@
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