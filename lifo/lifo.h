#include "../queue/queue.h"
#include "../historicsToDraw/historicsToDraw.h"



listHistorics* lifoX (process * dummy,int nb);
void  addNewCommingToQueueLifo(queue *q,process *process,int time,int arraySize,listHistorics ** l);
int compareStructsV9(const void *a, const void *b);