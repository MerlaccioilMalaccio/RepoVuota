#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>


//ciao

#define BUFFER_SIZE 1024
int main()
{
    int fd[2];
    int p;
    char buffer[BUFFER_SIZE];
    if(pipe(fd)==-1)//creazione pipe
    {
        printf("\n Errore nella creazione della pipe");
        exit(-1);
    }

    p=fork();
    if(p>0)//padre
    {
        printf("\n Sono il padre: il mio PID=%d. Mio figlio ha PID=%d",getpid(),p);
        close(fd[0]);//padre deve scrivere nella pipe quindi chiude in lettura(uscita della pipe)
        const char* messaggio="Buona fortuna";
        if(write(fd[1],messaggio, strlen(messaggio))==-1)
        {
            printf("\n Errore di scrittura nella pipe")
            exit(-1);
        }
        close(fd[1]);
        wait();
    }
    else//figlio
    {
        printf("\n Sono il figlio: il mio PID=%d. Mio padre ha PID=%d",getpid(),getppid());
        close(fd[0]);//figlio deve leggere dalla pipe quindi chiude in scrittura(input pipe)
        if(read(fd[0],buffer,BUFFER_SIZE)==-1)
        {
            printf("\n Errore di lettura nella pipe")
            exit(-1);
        }
        else
        {
            buffer[n]='\0';
            printf("Messaggio ricevuto: %s\n",buffer);
            close(fd[0]);
        }
    }
    return 0;
}
