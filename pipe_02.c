#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define BUFFER 256

int main(void) {
    int pai[2], filho[2];
    pid_t pid;

    /* pipe 1 */
    if(pipe(pai)<0) {
        perror("pipe") ;
        return -1 ;
    }
    /* pipe 2 */
    if(pipe(filho)<0) {
        perror("pipe") ;
        return -1 ;
    }

    /* processo filho. */
    pid = fork();

    if(pid == -1) {
        perror("fork") ;
        return -1 ;
    }

    if(pid > 0) {    /* Processo pai*/
        
        int soma = 0;

        close(pai[0]);
        close(filho[1]);

        for (int num = 1; num<=10; num++) {
			if (num%2 != 0) {
				soma += num;
			}
		}
		char str[BUFFER] = "A soma é :";
		printf("String do pai: '%s' %d\n", str, soma);
		write(filho[1], str, sizeof(str) + 1);
		exit(0);

    } else {

        int soma;
        for (int num = 1; num<=10; num++) {
			if (num%2 == 0) {
				soma += num;
			}
		}

		char str_recebida[BUFFER];

		close(filho[1]);

		read(pai[0], str_recebida, sizeof(str_recebida));
		("String do filho no pipe: '%s' %d\n", str_recebida, soma);
		exit(0);

    }

    return 0 ;
}
