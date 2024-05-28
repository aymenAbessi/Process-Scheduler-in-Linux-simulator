#include "../historicsToDraw/historicsToDraw.h"
#include "../queue/queue.h"
typedef struct metrics
{
  char name[10];
  int responseTime ;
  int finishedTime ; 
  int firstResponse ;
  int rotingsTime ; 
  int waitingTime ;
} metrics;

void setResponseTime(metrics *m,process p) ;
void setFinishedTime(listHistorics *l,metrics *m,process p);
void setResponseTime(metrics *m,process p);
void setRotingTime(metrics *m,process p) ;
void setWatingTime(metrics *m);

void fillTable(listHistorics *l , metrics *m,process * dummyp,int arraySize);