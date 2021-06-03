#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include<sys/wait.h>
#include <unistd.h>
#include <signal.h>

//#include "myheader.h"

const int N = 256;
const int READ = 0;
const int WRITE = 1;

char* questions[3] = {"What's your name?", "What's your favourite color?", "Who is your best friend?"};
char answers[3][100];

void (*oldhandler)();
void signal_handler()
{
	printf("\nYour program exited\n");
	exit(0);
}

int main()
{
	int fd1[2], fd2[2];
	int stat;
	
	int pipestat1 = pipe(fd1);

	if (pipestat1 == -1)
	{
		printf("Pipe 1 Creation failed\n");
		return 1;
	}

	int pipestat2 = pipe(fd2);

	if (pipestat2 == -1)
	{
		printf("Pipe 2 Creation failed\n");
		return 1;
	}
	file_open();
	int pid = fork();

	if (pid != 0)
	{

		close(fd1[READ]);
		close(fd2[WRITE]);

		while (1)
		{	int que = -1;
			while (que < 0 || que > 3)
			{
				printf("Enter the Question number between 0 to 3 : \n");
				scanf("%d", &que);
				if (que < 0 || que > 3 )
					printf("Please Enter a valid Question number between 0 to 3(if 3 press ctrl+c to exit) : \n");

			}
			if (que == 3) {
				//printf("Press ctrl+C to exit");
				kill(pid,SIGINT);
				oldhandler=signal(SIGINT,signal_handler);
				pause();
			}

			printf("The question you asked is : %s\n", questions[que]);
			write(fd1[WRITE], questions[que], strlen(questions[que]) + 1);

			

			char msg[N];

			int bytesRead = read(fd2[READ], &msg, N);
			printf("The answer to your question is : %s\n", &msg);


		}

		wait(&stat);
		if (WIFEXITED(stat)) {
			printf("Exit status: %d\n", WEXITSTATUS(stat));
		}
		close(fd1[WRITE]);
		close(fd2[READ]);
	}
	else
	{
		close(fd1[WRITE]);
		close(fd2[READ]);

		while (1)
		{
			char message[N];

			int bytesRead = read(fd1[READ], message, N);

			int cnt;
			for (int i = 0; i < 4; i++)
			{
				if (strcmp(message, questions[i]) == 0)
				{
					cnt = i;
					break;
				}
			}

			if (cnt == 3)
			{
				close(fd1[READ]);
				close(fd2[WRITE]);
				break;
			}
			else {
				write(fd2[WRITE], answers[cnt], strlen(answers[cnt]) + 1);
			}
		}
		close(fd1[READ]);
		close(fd2[WRITE]);
		exit(0);


	}
	return 0;
}
