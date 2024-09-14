#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 2147483000

typedef struct {
	double saldo;
	float deposito;
	float saque;
} Transacao;

void* deposito(void* transacao) {
	Transacao* transac = (Transacao*) transacao;
	for (unsigned int i = 0; i < N; i++) {
		transac->saldo += transac->deposito;
	}
}

void* saque(void* transacao) {
	Transacao* transac = (Transacao*) transacao;
	for (unsigned int i = 0; i < N; i++) {
		transac->saldo -= transac->saque;
	}
}

int main() {
	pthread_t threadDeposito;
	pthread_t threadSaque;

	Transacao transacao;
	transacao.saldo = 1000.0;
	transacao.deposito = 5.0;
	transacao.saque = 2.0;

	pthread_create(&threadDeposito, NULL, deposito, (void*) &transacao);
	pthread_create(&threadSaque, NULL, saque, (void*) &transacao);

	if (pthread_join(threadDeposito, NULL) != 0) {
		perror("Error while joining threadDeposito!");
		exit(3);
	}

	if (pthread_join(threadSaque, NULL) != 0){
		perror("Error while joining threadSaque!");
		exit(3);
	}

	printf("|===========| Programa Fase 1 |===========|\n");
	printf("-> Quantidade de operações = 2147483000\n");
	printf("-> Valor esperado: R$ 6442450000.00\n");
	printf("-> Saldo obtido: R$ %.2lf\n\n", transacao.saldo);

	return 0;
}