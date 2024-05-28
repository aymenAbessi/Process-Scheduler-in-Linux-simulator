#include "../historicsToDraw/historicsToDraw.h"
#include "../queue/queue.h"
#include <stdbool.h>


int compareStructsV10(const void *a, const void *b);
void swapV2(int *a, int *b) ;



int nbPriorityV2 (process * pTab,int size);


int getRankV2(process * processes , int priority,int size);



void addNewComingToQueueV2(queue q[],process *processes,int time,int arraySize,listHistorics ** h);
bool multilevelDynamicPriorityQueueEmpty(queue q[], int arraySize);

int selectedQueueNumberV2(queue q[],int arraySize);


bool switchToOtherQueueV2(queue q[],int arraySize,int currentQueue,int nbOfQueue);

bool shouldWeUseQuantumV2(queue *q);


listHistorics * multilevelDynamicPriorityX (process * processes,int arraySize,int quantum);