#ifndef SYSTEMS_FIXTURE_WORKER_H
#define SYSTEMS_FIXTURE_WORKER_H
#include "AutoTest.h"
#include <fcntl.h>
#include <poll.h>

namespace systems_fixture {
// Linux UAPI36/37; these constants predate our host but are absent from the
// original CentOS6 compiler headers. No host header or SDK type is included.
enum { setChildSubreaper=36, getChildSubreaper=37 };
inline unsigned long long milliseconds(){
 struct timespec now;if(clock_gettime(CLOCK_MONOTONIC,&now))return 0;
 return static_cast<unsigned long long>(now.tv_sec)*1000+now.tv_nsec/1000000;
}
inline int isolated(int(*body)(const tlhybrid_host*),const tlhybrid_host*host){
 // A subreaper lets this process wait for grandchildren orphaned by an abnormal
 // worker. Restore the previous kernel setting; no SDK graph enters this parent.
 int previous=0;if(prctl(getChildSubreaper,&previous)||prctl(setChildSubreaper,1))return 1;
 int fd[2];if(pipe(fd)){prctl(setChildSubreaper,previous);return 1;}
 pid_t pid=fork();
 if(pid==0){
  close(fd[0]);if(setpgid(0,0))_exit(72);
  prctl(PR_SET_DUMPABLE,0,0,0,0);
  signal(SIGSEGV,autotest::crashed);signal(SIGBUS,autotest::crashed);signal(SIGFPE,autotest::crashed);
  signal(SIGILL,autotest::crashed);signal(SIGABRT,autotest::crashed);
  signal(SIGALRM,SIG_DFL);signal(SIGPROF,SIG_DFL);
  struct itimerval limit;std::memset(&limit,0,sizeof(limit));limit.it_value.tv_sec=60;
  if(setitimer(ITIMER_REAL,&limit,NULL))_exit(73);
  // Per-invocation CPU/wall limits are still set by the unchanged inner runChild.
  int failures=body(host);
  if(!autotest::writeExact(fd[1],&failures,sizeof(failures)))_exit(autotest::kReportWriteFailure);
  close(fd[1]);_exit(0);
 }
 close(fd[1]);
 if(pid<0){close(fd[0]);prctl(setChildSubreaper,previous);return 1;}
 bool bad=false,timedOut=false,reaped=false;int status=0;size_t count=0;
 unsigned char report[sizeof(int)+1];
 // The child performs the same setpgid before creating any descendants.
 if(setpgid(pid,pid)&&errno!=EACCES&&errno!=ESRCH)bad=true;
 int flags=fcntl(fd[0],F_GETFL);if(flags<0||fcntl(fd[0],F_SETFL,flags|O_NONBLOCK)<0)bad=true;
 unsigned long long start=milliseconds();if(!start)bad=true;
 while(!bad){
  if(count<sizeof(report)){
   ssize_t got=read(fd[0],report+count,sizeof(report)-count);
   if(got>0)count+=got;
   else if(got<0&&errno!=EAGAIN&&errno!=EWOULDBLOCK&&errno!=EINTR){bad=true;break;}
  }
  if(count>sizeof(int)){bad=true;break;}
  pid_t waited=waitpid(pid,&status,WNOHANG);
  if(waited==pid){reaped=true;break;}
  if(waited<0&&errno!=EINTR){bad=true;break;}
  unsigned long long now=milliseconds();
  if(!now||now-start>=60000){bad=true;timedOut=true;break;}
  struct pollfd event={fd[0],POLLIN,0};
  if(poll(&event,1,100)<0&&errno!=EINTR){bad=true;break;}
 }
 // Never accept printed coverage as success after an abnormal worker. Kill the
 // entire private group, then reap the worker and every adopted descendant.
 if(kill(-pid,SIGKILL)&&errno!=ESRCH)bad=true;
 if(!reaped){
  kill(pid,SIGKILL);pid_t waited;
  do{waited=waitpid(pid,&status,0);}while(waited<0&&errno==EINTR);
  if(waited!=pid)bad=true;else reaped=true;
 }
 unsigned descendants=0;
 for(;;){int childStatus;pid_t child=waitpid(-pid,&childStatus,0);
  if(child>0){++descendants;continue;}
  if(child<0&&errno==EINTR)continue;
  if(child<0&&errno!=ECHILD)bad=true;
  break;
 }
 // Drain any final report bytes after the worker exited and all writers died.
 if(flags>=0){while(count<sizeof(report)){
  ssize_t got=read(fd[0],report+count,sizeof(report)-count);
  if(got>0){count+=got;continue;}
  if(got<0&&errno==EINTR)continue;
  if(got<0&&errno!=EAGAIN&&errno!=EWOULDBLOCK)bad=true;
  break;
 }}
 close(fd[0]);if(prctl(setChildSubreaper,previous))bad=true;
 if(bad||timedOut||!reaped||!WIFEXITED(status)||WEXITSTATUS(status)!=0||descendants||count!=sizeof(int)){
  host->log("    isolated fixture worker failed: status %d report %lu timeout %u reaped descendants %u\n",status,static_cast<unsigned long>(count),timedOut,descendants);
  return 1;
 }
 int failures;std::memcpy(&failures,report,sizeof(failures));return failures<0?1:failures;
}
}
#endif
