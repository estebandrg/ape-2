typedef struct Usuario {
    int nombre[40];
    int saldo;
    int id;
    struct Usuario* izq;
    struct Usuario* der;
} Usuario;