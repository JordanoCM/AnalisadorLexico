#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

// Enumeração para os diferentes tipos de tokens que o analisador pode identificar
enum TokenType {
    NUM,     // Número
    VAR,     // Variável
    ABRPAR,  // Parêntese aberto '('
    FECPAR,  // Parêntese fechado ')'
    ABRCOL,  // Colchete aberto '['
    FECCOL,  // Colchete fechado ']'
    ABRCH,   // Chave aberta '{'
    FECCH,   // Chave fechada '}'
    SOM,     // Operador de soma '+'
    DIF,     // Operador de subtração '-'
    DIV,     // Operador de divisão '/'
    MUL,     // Operador de multiplicação '*'
    INVALID  // Caractere inválido
};

// Classe para representar um token identificado
class Token {
public:
    TokenType type;  // Tipo do token
    std::string value;  // Valor do token (múltiplos caracteres possíveis)

    // Construtor da classe Token
    Token(TokenType type, const std::string& value) : type(type), value(value) {}

    // Função para imprimir o tipo do token
    void printToken() {
        switch (type) {
            case NUM:
                std::cout << "NUM" << std::endl;
                break;
            case VAR:
                std::cout << "VAR" << std::endl;
                break;
            case ABRPAR:
                std::cout << "ABRPAR" << std::endl;
                break;
            case FECPAR:
                std::cout << "FECPAR" << std::endl;
                break;
            case ABRCOL:
                std::cout << "ABRCOL" << std::endl;
                break;
            case FECCOL:
                std::cout << "FECCOL" << std::endl;
                break;
            case ABRCH:
                std::cout << "ABRCH" << std::endl;
                break;
            case FECCH:
                std::cout << "FECCH" << std::endl;
                break;
            case SOM:
                std::cout << "SOM" << std::endl;
                break;
            case DIF:
                std::cout << "DIF" << std::endl;
                break;
            case DIV:
                std::cout << "DIV" << std::endl;
                break;
            case MUL:
                std::cout << "MUL" << std::endl;
                break;
            default:
                std::cout << "INVALID" << std::endl;
                break;
        }
    }
};

// Classe para o analisador léxico
class Lexer {
public:
    // Função para analisar a linha de entrada e identificar tokens
    bool analyze(const std::string& input) {
        std::string currentToken;  // Armazena o token atual em construção
        TokenType currentType = INVALID;  // Tipo do token atual
        bool hasError = false;  // Flag para verificar se houve um erro

        for (char c : input) {
            if (isdigit(c)) {  // Se o caractere é um dígito
                if (currentType == NUM) {  // Se o tipo atual é NUM, continua construindo o número
                    currentToken += c;
                } else {
                    if (!currentToken.empty()) {  // Se há um token atual, imprime-o
                        Token token(currentType, currentToken);
                        token.printToken();
                    }
                    currentToken = c;  // Inicia um novo token
                    currentType = NUM;  // Define o tipo do token como NUM
                }
            } else if (isalpha(c)) {  // Se o caractere é uma letra
                if (currentType == VAR) {  // Se o tipo atual é VAR, continua construindo a variável
                    currentToken += c;
                } else {
                    if (!currentToken.empty()) {  // Se há um token atual, imprime-o
                        Token token(currentType, currentToken);
                        token.printToken();
                    }
                    currentToken = c;  // Inicia um novo token
                    currentType = VAR;  // Define o tipo do token como VAR
                }
            } else if (isspace(c)) {  // Se o caractere é um espaço em branco, ignora-o
                continue;
            } else {  // Para outros caracteres
                if (currentType == NUM || currentType == VAR) {  // Se há um token atual de NUM ou VAR, imprime-o
                    Token token(currentType, currentToken);
                    token.printToken();
                    currentToken.clear();  // Limpa o token atual
                    currentType = INVALID;  // Define o tipo do token como INVALID
                }

                // Identifica o tipo do token para caracteres especiais
                switch (c) {
                    case '(':
                        currentType = ABRPAR;
                        break;
                    case ')':
                        currentType = FECPAR;
                        break;
                    case '[':
                        currentType = ABRCOL;
                        break;
                    case ']':
                        currentType = FECCOL;
                        break;
                    case '{':
                        currentType = ABRCH;
                        break;
                    case '}':
                        currentType = FECCH;
                        break;
                    case '+':
                        currentType = SOM;
                        break;
                    case '-':
                        currentType = DIF;
                        break;
                    case '*':
                        currentType = MUL;
                        break;
                    case '/':
                        currentType = DIV;
                        break;
                    default:
                        std::cerr << "Erro léxico: caractere inválido '" << c << "'" << std::endl;
                        return false;  // Retorna falso para indicar erro e interrompe a análise
                }

                if (!hasError) {
                    Token token(currentType, std::string(1, c));
                    token.printToken();
                    currentType = INVALID;  // Reseta o tipo de token para INVALID
                }
            }
        }

        // Imprime o último token se houver
        if (!currentToken.empty()) {
            Token token(currentType, currentToken);
            token.printToken();
        }

        return !hasError;  // Retorna verdadeiro se não houver erros
    }
};

int main() {
    Lexer lexer;  // Cria uma instância do analisador léxico
    std::ifstream file("entrada.txt");  // Abre o arquivo de entrada

    if (!file.is_open()) {  // Verifica se o arquivo foi aberto corretamente
        std::cerr << "Não foi possível abrir o arquivo." << std::endl;
        return 1;
    }

    bool success = true;  // Flag para verificar o sucesso da análise
    std::string line;
    while (std::getline(file, line)) {  // Lê o arquivo linha por linha
        if (!lexer.analyze(line)) {  // Analisa cada linha
            success = false;  // Define sucesso como falso se houver erro
            break;  // Interrompe a análise se houver erro léxico
        }
    }

    file.close();  // Fecha o arquivo

    if (success) {  // Imprime EOF apenas se a análise for bem-sucedida
        std::cout << "EOF" << std::endl;
    }

    return 0;
}
