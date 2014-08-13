#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#define MAXLINE 4096
#define SA struct socketaddr
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char **argv)
{
  int listenfd,connfd;
  struct sockaddr_in servaddr;
  char buff[MAXLINE];
  time_t ticks;
  //int res ,length;

  
  if((listenfd = socket(AF_INET,SOCK_STREAM,0))<0)
      printf("socket error");
  bzero(&servaddr,sizeof(servaddr));//bzero将整个结构体清零
  servaddr.sin_family = AF_INET;//将地址族设置为AF_INET
  servaddr.sin_addr.s_addr =htonl(INADDR_ANY);
  servaddr.sin_port = htons(9999);

  if((bind(listenfd,(SA *) &servaddr,sizeof(servaddr)))<0)
      printf("bind error");
  listen(listenfd,50);
  for(;;)
  {
    if((connfd = accept(listenfd,(struct sockaddr *)NULL,NULL))<0)
      printf("accept error");
    //获取当前系统时间
    ticks = time(NULL);
    //ctime将整数值转换成直观可读的时间格式
    snprintf(buff,sizeof(buff),"%.24s\r\n",ctime(&ticks));
    //write函数将把结果字符串写给客户
    puts(ctime(&ticks));
    printf("%d\n",strlen(buff));
    // length = strlen(buff);
    write(connfd,buff,strlen(buff));

    //终止连接，TCP的四次挥手
    close(connfd);
  }

  exit(0);
}
