#include "../queue/queue.h"
#include "../historicsToDraw/historicsToDraw.h"


typedef struct listSgf
{
  process val ;
  struct listSgf *next ;
} listSgf ;





bool existInReadyQueue(listSgf **l, process p) ;
void enqueueSgfReadyQueue(listSgf **l, process p) ;
process dequeueSgfReadyQueue(listSgf **l);
void addNewCommingToQueueSgfReadyQueue(listSgf **l, process *processes , int time , int arraySize,process running,listHistorics ** h);
listHistorics* sjfX (process * dummy,int nb) ;