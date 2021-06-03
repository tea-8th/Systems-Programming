#include<stdio.h>
#include<stdlib.h>
#include<string.h>
extern answers[3][100];
void file_open()
{
	FILE* fd;
	fd = fopen("demo.txt", "r");

	char buf[1024];
	long ipos, epos;
	char s[1024];
	int i = 0;
	int flag = 0;

	char temp1[1024];

	printf("Enter number:");
	scanf("%s", &s);
	//printf("%s\n",&s);
	char check = ' ';
	while (feof(fd) == 0)
	{

		ipos = epos = ftell(fd);
		//printf("%ld\n",pos);
		char c = fgetc(fd);
		while (c != ' ' && c != '\n' && i < 1024)
		{
			if (c != s[i])
			{
				epos = ipos;
				flag = 1;
				i = 0;
				break;
			}
			else
			{
				c = fgetc(fd);
				i++;
				epos++;
			}
		}
		if (flag == 0)
		{
			//fseek(fd, 0, SEEK_CUR);
			break;
		}
		else
		{
			flag = 0;
			fgets(buf, 1024, fd);
			//printf("%s\n", buf);
		}
	}
	fgets(temp1, 1024, fd);
	//printf("%s\n", temp1);

	char(*ptemp2)[100];
	ptemp2 = answers;
	char* p;
	char* q;
	p = temp1;
	q = temp1 + strlen(temp1);
	int j = 0;

	while (p <= q)
	{
		if (*p == ' ')
		{
			*(*(ptemp2)+j) = '\0';
			j = 0;
			ptemp2++;
		}
		else
		{
			*(*(ptemp2)+j) = *p;
			//(*ptemp2)++;
			j++;
		}
		p++;
	}
	//printf("%s",&answers[2]);

}
