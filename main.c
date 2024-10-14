#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef enum {
    NO_ERROR,
    EMPTY_INPUT,
    BUFFER_OVERFLOW,
    DIVISION_BY_ZERO,
    NEGATIVE_SQUARE_ROOT,
    NEGATIVE_LOGARITHM,
} ErrorType;

typedef enum {
    NUMBER,
    PLUS,
    UMINUS,
    BMINUS,
    MULTIPLY,
    DIVIDE,
    POWER,
    SIN,
    COS,
    TAN,
    SQRT,
    LOG,
    LN,
    pi,
    e,
    PARENTHESIS_OPEN,
    PARENTHESIS_CLOSE
} TokenType;

typedef struct token {
    TokenType type;
    float* value;
    struct token* next;
} Token;

typedef Token* TokenList;

Token* createToken(TokenType type, float* value) {
    Token* token = (Token*) malloc(sizeof(Token));
    token->type = type;
    token->value = value;
    token->next = NULL;
    return token;
}

void addToken(TokenList* tokens, Token* token) {
    if (*tokens == NULL) {
        token->next = NULL;
        *tokens = token;
    } else {
        Token* current = *tokens;
        while (current->next != NULL) {
            current = current->next;
        }
        token->next = NULL;
        current->next = token;
    }
}

void freeTokens(TokenList* tokens) {
    Token* current = *tokens;
    while (current != NULL) {
        Token* next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
    *tokens = NULL;
}

void showTokens(TokenList tokens) {
    Token* current = tokens;
    while (current != NULL) {
        switch (current->type) {
            case NUMBER:
                printf("NUMBER : %f\n", *current->value);
            break;
            case PLUS:
                printf("PLUS\n");
            break;
            case UMINUS:
                printf("UMINUS\n");
            break;
            case BMINUS:
                printf("BMINUS\n");
            break;
            case MULTIPLY:
                printf("MULTIPLY\n");
            break;
            case DIVIDE:
                printf("DIVIDE\n");
            break;
            case POWER:
                printf("POWER\n");
            break;
            case SIN:
                printf("SIN\n");
            break;
            case COS:
                printf("COS\n");
            break;
            case TAN:
                printf("TAN\n");
            break;
            case SQRT:
                printf("SQRT\n");
            break;
            case LOG:
                printf("LOG\n");
            break;
            case LN:
                printf("LN\n");
            break;
            case pi:
                printf("PI\n");
            break;
            case e:
                printf("E\n");
            break;
            case PARENTHESIS_OPEN:
                printf("PARENTHESIS_OPEN\n");
            break;
            case PARENTHESIS_CLOSE:
                printf("PARENTHESIS_CLOSE\n");
            break;
        }
        current = current->next;
    }
}

Token* popToken(TokenList* tokens) {
    Token* current = *tokens;
    Token* previous = NULL;

    while (current->next != NULL) {
        previous = current;
        current = current->next;
    }

    if (previous != NULL) {
        previous->next = NULL;
    } else {
        *tokens = NULL;
    }

    current->next = NULL;
    return current;
}

Token* getLast(TokenList tokens) {
    Token* current = tokens;
    while (current->next != NULL) {
        current = current->next;
    }
    return current;
}

void showPostfix(TokenList postfix) {
    Token* current = postfix;
    while (current != NULL) {
        switch (current->type) {
            case NUMBER:
                printf("%f ", *(current->value));
            break;
            case PLUS:
                printf("+ ");
            break;
            case UMINUS:
                printf("- ");
            break;
            case BMINUS:
                printf("- ");
            break;
            case MULTIPLY:
                printf("* ");
            break;
            case DIVIDE:
                printf("/ ");
            break;
            case POWER:
                printf("^ ");
            break;
            case SIN:
                printf("sin ");
            break;
            case COS:
                printf("cos ");
            break;
            case TAN:
                printf("tan ");
            break;
            case SQRT:
                printf("sqrt ");
            break;
            case LOG:
                printf("log ");
            break;
            case LN:
                printf("ln ");
            break;
            case pi:
                printf("pi ");
            break;
            case e:
                printf("e ");
            break;
            case PARENTHESIS_OPEN:
                printf("( ");
            break;
            case PARENTHESIS_CLOSE:
                printf(") ");
            break;
            
        }
        current = current->next;
    }
    printf("\n");

}

ErrorType tokenize(char* input, TokenList* tokens) {
    if (input == NULL || strcmp(input, "") == 0) {
        return EMPTY_INPUT;
    }

    char buffer[64];
    bool isLastNumber = false;

    for (int i = 0; input[i] != '\0'; i++) {
        switch (input[i]) {

            // OPERATORS
            case '+':
                addToken(tokens, createToken(PLUS, NULL));
                isLastNumber = false;
            break;
            break;
            case '-':
                if (isLastNumber) {
                    addToken(tokens, createToken(BMINUS, NULL));
                    isLastNumber = false;
                } else {
                    addToken(tokens, createToken(UMINUS, NULL));
                    isLastNumber = false;
                }
            break;
            case '*':
                addToken(tokens, createToken(MULTIPLY, NULL));
                isLastNumber = false;
            break;
            case '/':
                addToken(tokens, createToken(DIVIDE, NULL));
                isLastNumber = false;
            break;
            case '^':
                addToken(tokens, createToken(POWER, NULL));
                isLastNumber = false;
            break;

            // FUNCTIONS

            case 's':
                if (input[i+1] == 'i' && input[i+2] == 'n') {
                    addToken(tokens, createToken(SIN, NULL));
                    isLastNumber = false;
                    i += 2;
                } else if (input[i+1] == 'q' && input[i+2] == 'r' && input[i+3] == 't') {
                    addToken(tokens, createToken(SQRT, NULL));
                    isLastNumber = false;
                    i += 3;
                }
            break;
            case 'c':
                if (input[i+1] == 'o' && input[i+2] == 's') {
                    addToken(tokens, createToken(COS, NULL));
                    isLastNumber = false;
                    i += 2;
                }
            break;
            case 't':
                if (input[i+1] == 'a' && input[i+2] == 'n') {
                    addToken(tokens, createToken(TAN, NULL));
                    isLastNumber = false;
                    i += 2;
                }
            break;
            case 'l':
                if (input[i+1] == 'o' && input[i+2] == 'g') {
                    addToken(tokens, createToken(LOG, NULL));
                    isLastNumber = false;
                    i += 2;
                } else if (input[i+1] == 'n') {
                    addToken(tokens, createToken(LN, NULL));
                    isLastNumber = false;
                    i += 1;
                }
            break;

            // CONSTANTS

            case 'p':
                if (input[i+1] == 'i') {
                    addToken(tokens, createToken(pi, NULL));
                    isLastNumber = false;
                    i += 1;
                }
            break;
            case 'e':
                addToken(tokens, createToken(e, NULL));
                isLastNumber = false;
            break;

            // PARENTHESIS

            case '(':
            case '[':
                addToken(tokens, createToken(PARENTHESIS_OPEN, NULL));
                isLastNumber = false;
            break;
            case ')':
            case ']':
                addToken(tokens, createToken(PARENTHESIS_CLOSE, NULL));
                isLastNumber = false;
            break;


            // NUMBERS

            default:

                if (input[i] >= '0' && input[i] <= '9' || input[i] == '.' || input[i] == ',') {
                    int j = 0;
                    
                    while (input[i] >= '0' && input[i] <= '9'|| input[i] == '.' || input[i] == ',') {
                        buffer[j] = input[i];
                        if (input[i] == ',') {
                            buffer[j] = '.';
                        }
                        j++;
                        i++;

                        if (j >= 64) {
                            return BUFFER_OVERFLOW;
                        }
                    }
                    i--;
                    buffer[j] = '\0';

                    float* value = (float*) malloc(sizeof(float));
                    *value = atof(buffer);
                    addToken(tokens, createToken(NUMBER, value));
                    isLastNumber = true;
                }


            break;
        }
    }

    return NO_ERROR;

}

int getPrecedence(TokenType type) {
    switch (type) {
        case PARENTHESIS_OPEN:
        case PARENTHESIS_CLOSE:
            return 0;
        break;
        case PLUS:
        case UMINUS:
        case BMINUS:
            return 1;
        break;
        case MULTIPLY:
        case DIVIDE:
            return 2;
        break;
        case POWER:
            return 3;
        break;
        case SIN:
        case COS:
        case TAN:
        case SQRT:
        case LOG:
        case LN:
            return 4;
        break;

        // USELESS
        case pi:
        case e:
        case NUMBER:
            return 5;
        break;
    }
}

ErrorType toPostfix(TokenList tokens, TokenList* postfix) {

    TokenList stack = NULL;
    bool isLastOperator = false;
    TokenType lastOperator = NUMBER;

    while (tokens != NULL) {
        Token* current = tokens;
        tokens = tokens->next;

        switch (current->type) {
            case NUMBER:
                float* value = malloc(sizeof(float));
                *value = *current->value;
                addToken(postfix, createToken(current->type, value));
            break;
            case pi:
            case e:
                addToken(postfix, createToken(current->type, NULL));
                isLastOperator = false;
            break;
            case PLUS:
            case UMINUS:
            case BMINUS:
            case MULTIPLY:
            case DIVIDE:
            case POWER:
            case SIN:
            case COS:
            case TAN:
            case SQRT:
            case LOG:
            case LN:
                if (isLastOperator && (getPrecedence(current->type) <= getPrecedence(getLast(stack)->type))) {
                    addToken(postfix, popToken(&stack));
                }
                addToken(&stack, createToken(current->type, NULL));
                lastOperator = current->type;
                isLastOperator = true;
            break;
            case PARENTHESIS_OPEN:
                addToken(&stack, createToken(current->type, NULL));
                lastOperator = current->type;
                isLastOperator = false;
            break;
            case PARENTHESIS_CLOSE:
                while (stack != NULL && (getLast(stack)->type != PARENTHESIS_OPEN)) {
                    addToken(postfix, popToken(&stack));
                }
                if (stack != NULL) {
                    popToken(&stack);
                }
                lastOperator = current->type;
                isLastOperator = false;
            break;
        }

    }

    while (stack != NULL) {
        Token *current = popToken(&stack);
        if (current->type != PARENTHESIS_OPEN) {
            addToken(postfix, current);
        }
    }

    freeTokens(&stack);

    
    return NO_ERROR;
}

ErrorType evaluate(TokenList postfix, float* result) {
    TokenList stack = NULL;

    Token *current = postfix;

    while (current != NULL) {
        switch (current->type) {
            case NUMBER:
                addToken(&stack, createToken(current->type, current->value));
            break;
            case pi:
                float* pi = malloc(sizeof(float));
                *pi = 3.14159265359;
                addToken(&stack, createToken(NUMBER, pi));
            break;
            case e:
                float* e = malloc(sizeof(float));
                *e = 2.71828182846;
                addToken(&stack, createToken(NUMBER, e));
            break;
            case PLUS:
                float* plus = malloc(sizeof(float));
                *plus = *popToken(&stack)->value + *popToken(&stack)->value;
                addToken(&stack, createToken(NUMBER, plus));
            break;
            case UMINUS:
                float* uminus = malloc(sizeof(float));
                *uminus = - *popToken(&stack)->value;
                addToken(&stack, createToken(NUMBER, uminus));
            break;
            case BMINUS:
                float* bminus = malloc(sizeof(float));
                float a = *popToken(&stack)->value;
                float b = *popToken(&stack)->value;
                *bminus = b - a;
                addToken(&stack, createToken(NUMBER, bminus));
            break;
            case MULTIPLY:
                float* multiply = malloc(sizeof(float));
                *multiply = *popToken(&stack)->value * *popToken(&stack)->value;
                addToken(&stack, createToken(NUMBER, multiply));
            break;
            case DIVIDE:
                float* divide = malloc(sizeof(float));
                
                float c = *popToken(&stack)->value;
                float d = *popToken(&stack)->value;
                if (c == 0) {
                    return DIVISION_BY_ZERO;
                }
                *divide = d / c;
                addToken(&stack, createToken(NUMBER, divide));
            break;
            case POWER:
                float* power = malloc(sizeof(float));
                float ex = *popToken(&stack)->value;
                float f = *popToken(&stack)->value;
                *power = pow(f, ex);
                addToken(&stack, createToken(NUMBER, power));
            break;
            case SIN:
                float* sinv = malloc(sizeof(float));
                *sinv = sin(*popToken(&stack)->value);
                addToken(&stack, createToken(NUMBER, sinv));
            break;
            case COS:
                float* cosv = malloc(sizeof(float));
                *cosv = cos(*popToken(&stack)->value);
                addToken(&stack, createToken(NUMBER, cosv));
            break;
            case TAN:
                float* tanv = malloc(sizeof(float));
                *tanv = tan(*popToken(&stack)->value);
                addToken(&stack, createToken(NUMBER, tanv));
            break;
            case SQRT:
                float* sqrtv = malloc(sizeof(float));
                float tSqrtv = *popToken(&stack)->value;
                if (tSqrtv < 0) {
                    return NEGATIVE_SQUARE_ROOT;
                }
                *sqrtv = sqrt(tSqrtv);
                addToken(&stack, createToken(NUMBER, sqrtv));
            break;
            case LOG:
                float* logv = malloc(sizeof(float));
                float tLogv = *popToken(&stack)->value;
                if (tLogv < 0) {
                    return NEGATIVE_LOGARITHM;
                }
                *logv = log10(tLogv);
                addToken(&stack, createToken(NUMBER, logv));
            break;
            case LN:
                float* ln = malloc(sizeof(float));
                float tLn = *popToken(&stack)->value;
                if (tLn < 0) {
                    return NEGATIVE_LOGARITHM;
                }
                *ln = log(tLn);
                addToken(&stack, createToken(NUMBER, ln));
            break;
        }
        
        
        current = current->next;
    }

    *result = *popToken(&stack)->value;

    freeTokens(&stack);

    return NO_ERROR;
    
}

void handleErrors(ErrorType error) {
    switch (error) {
        case EMPTY_INPUT:
            printf("Error : Empty input\n");
        break;
        case BUFFER_OVERFLOW:
            printf("Error : Buffer overflow\n");
        break;
    }
}

void clear() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");   
    #endif
}

int main() {
    
    clear();
    printf("Welcome to this simple calculator, type 'h' to get more information or 'q' to quit\n");

    bool running = true;
    
    while (running) {
        printf("> ");

        char input[2048];
        fgets(input, 2048, stdin);

        if (strcmp(input, "q\n") == 0) {
            running = false;
            break;
        }
        if (strcmp(input, "h\n") == 0) {
            printf("This simple calculator can handle the following operations : +, -, /, *, ^\n");
            printf("You can also use the following functions : sin, cos, tan, sqrt, log, ln and constants : pi, e\n");
            printf("Don't forget to use parenthesis ( either '()' or '[]' )\n");
            printf("This calculator follow the PEMDAS order of operation\n");
            printf("To evaluate you can juste type 'enter'\n");
            continue;
        }
        if (strcmp(input, "c\n") == 0) {
            clear();
            continue;
        }


        // Tokenize the input

        TokenList tokens = NULL;
        ErrorType error = tokenize(input, &tokens);
        // showPostfix(tokens);

        if (error) {
            handleErrors(error);
            return 1;
        }


        // Convert to postfix

        TokenList postfix = NULL;
        error = toPostfix(tokens, &postfix);
        freeTokens(&tokens);

        
        if (error) {
            handleErrors(error);
            return 1;
        }


        // printf("Postfix : \n");

        // showPostfix(postfix);


        // Evaluate the postfix

        float result = 0;

        evaluate(postfix, &result);

        printf("> %f\n", result);

        freeTokens(&postfix);



    }



    return 0;
}