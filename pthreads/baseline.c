#include <stdio.h>
#include <pthread.h>

#define N 2147483000

typedef struct {
	double saldo;
	float deposito;
	float saque;
} Transacao;

double deposito(Transacao* transacao) {
	for (unsigned int i = 0; i < N; i++) {
		transacao->saldo += transacao->deposito;
	}
	return transacao->saldo;
}

double saque(Transacao* transacao){
	for (unsigned int i = 0; i < N; i++) {
		transacao->saldo -= transacao->saque;
	}
	return transacao->saldo;
}

int main() {
	Transacao transacao;
	transacao.saldo = 1000.0;
	transacao.deposito = 5.0;
	transacao.saque = 2.0;

	transacao.saldo = deposito(&transacao);
	transacao.saldo = saque(&transacao);

	printf("|===========| Programa Base |===========|\n");
	printf("-> Quantidade de operações = 2147483000\n");
	printf("-> Valor esperado: R$ 6442450000.00\n");
	printf("-> Saldo obtido: R$ %.2lf\n\n", transacao.saldo);
    
	return 0;
}