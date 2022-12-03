#include <sched.h>
#include <stdio.h>

int main(){
    struct sched_param pr;
    int p = 0;
    p = sched_getscheduler(0);
    int k = sched_getparam(0, &pr);
    int r2 = sched_get_priority_max(p);
    int r3 = sched_get_priority_min(p);

    int r1 = pr.sched_priority;

    if(p==0){printf("Politica de planificacion: SCHED_OTHER\n");}
    if(p==1){printf("Politica de planificacion: SCHED_FIFO\n");}
    if(p==2){printf("Politica de planificacion: SCHED_RR\n");}

    printf("Prioridad del proceso: %i\n",r1);
    printf("Prioridad maxima: %i\n",r2);
    printf("Prioridad minima: %i\n",r3);
    return 0;
}