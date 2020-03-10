#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#define FIFO "fifo"

int main()
	{
		if (mkfifo(FIFO, 0644)<0)
				{
					perror("mkfifo error");
					return 1;
				}
		
				int fd = open(FIFO, O_RDONLY);
		if (fd < 0)
				{
				perror("open error");
				return 2;
			}
		
				char buf[1024];
			while (1)
			{
					ssize_t s = read(fd, buf, sizeof(buf)-1);
					if (s > 0)
						{
							buf[s] = 0;
							printf("proc_two: %s\n", buf);
					}
					else if (s == 0)
						{
							printf("proc_two quit, me too...");
							break;
						}
					else
						{
							break;
						}
				}
			close(fd);
			return 0;
		}
```
**clientPipe.c**

```c
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#define FIFO "fifo"
int main()
{
	     int fd = open(FIFO, O_WRONLY);
	    if (fd < 0)
		    {
		       perror("open error");
		        return 1;
		     }
	
		    char buf[1024];
	  while (1)
		    {
		        printf("eoch# ");
		         fflush(stdout);
		       ssize_t s = read(0, buf, sizeof(buf)-1);
		        if (s>0)
			        {
			             buf[s] = 0;
		            write(fd, buf, strlen(buf));
		      }
		    }
	     close(fd);
     return 0;
	 }
