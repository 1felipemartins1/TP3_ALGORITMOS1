# Nome do executável
EXEC = tp2

# Compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -Wall -Wextra -Wpedantic -Wformat-security -Wconversion -Werror -std=c++17

# Arquivos do projeto
SRC = main.cpp network.cpp
OBJ = $(SRC:.cpp=.o)

# Regra principal
all: $(EXEC)

# Regra para gerar o executável
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regra para compilar arquivos fonte em objetos
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza dos arquivos gerados
clean:
	rm -f $(OBJ) $(EXEC)
