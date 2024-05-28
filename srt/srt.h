#include "../queue/queue.h"
#include "../historicsToDraw/historicsToDraw.h"


typedef struct listP
{
  process val ;
  struct listP *next ;
} listP ;






void enqueueV2(listP **l, process p) ;
process dequeueV2(listP **l);
void addNewCommingToQueuev2(listP **l, process *processes , int time , int arraySize,process running,listHistorics ** h);
listHistorics*  srtX (process * dummy,int nb);
int compareStructs(const void *a, const void *b) ;
