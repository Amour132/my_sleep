#include <iostream>
#include <signal.h>
#include <unistd.h>
using namespace std;

void handler(int signo)
{

}

unsigned int Mysleep(unsigned int msecs)
 {
     struct sigaction newact,old;
     sigset_t newmask,oldmak,sussem;
     unsigned int unslept = 0;
     newact.sa_handler = handler;
     sigemptyset(&newact.sa_mask);
     newact.sa_flags = 0;
     sigaction(SIGALRM,&newact,&old);//注册信号处理函数

     sigemptyset(&newmask);
     sigaddset(&newmask,SIGALRM);
     sigprocmask(SIG_BLOCK,&newmask,&oldmak);

     alarm(msecs);//设置闹钟
     sussem = oldmak;
     sigdelset(&sussem,SIGALRM);
     sigsuspend(&sussem);
     unslept = alarm(0);//清除闹钟
     sigprocmask(SIG_BLOCK,&oldmak,NULL);
     sigaction(SIGALRM,&old,NULL);//恢复默认信号处理动作
     return unslept;
 }


int main()
{
  while(1)
  {
    cout << "wake up" << endl;
    Mysleep(2);
  }
  return 0;
}
