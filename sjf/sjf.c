#include "sjf.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<string.h>


int compareStructsV8(const void *a, const void *b) {
 
    return ((process*)a)->ta - ((process*)b)->ta;
}



void enqueueSgfReadyQueue(listSgf **l, process p) {

    if(p.te >0){
     
    listSgf *newNode = (listSgf *)malloc(sizeof(listSgf));
    
    if (newNode == NULL) {
      
        return;
    }
    newNode->val = p;
    newNode->next = NULL;

    
    if (*l == NULL || (*l)->val.te > p.te) {
        newNode->next = *l;
        *l = newNode;
        return;
    }

    
    listSgf *current = *l;
    while (current->next != NULL && current->next->val.te <= p.te) {
        current = current->next;
    }

  
    newNode->next = current->next;
    current->next = newNode;
    }
}



process dequeueSgfReadyQueue(listSgf **l) {
    process x = {0};
  
    if (*l != NULL) {
       
        listSgf *current = *l;
        x = current->val;
         printf("%s leave the ready queue\n",x.name);
        *l = (*l)->next; 
        free(current);
    }
    return x;
}

bool existInReadyQueue(listSgf **l, process p) {
    listSgf *current = *l;
    while (current != NULL) {
        if (strcmp(current->val.name, p.name) == 0) {
            return true;
        }
        current = current->next;
    }
    return false;
}





int compareStructsSgfReadyQueue(const void *a, const void *b) {
    return ((process*)a)->ta - ((process*)b)->ta;
}


void addNewCommingToQueueSgfReadyQueue(listSgf **l, process *processes , int time , int arraySize,process running,listHistorics ** h){

  for(int i =0 ; i <arraySize ; i++){
      if(processes[i].ta == time && processes[i].te>0 && !existInReadyQueue(l,processes[i]) && (strcmp(running.name, processes[i].name))){
        printf("%s enter the ready queue at %d\n",processes[i].name,time);
        enqueueSgfReadyQueue(l,processes[i]);

          historicsToDraw processEnterReadyQueue ;
                  strcpy(processEnterReadyQueue.nameP, processes[i].name); 
                 processEnterReadyQueue.readyQueueOrRunning = 0;
                  processEnterReadyQueue.enterOrExit = 0;
                  processEnterReadyQueue.time = time;
                 addToHistorics(h,processEnterReadyQueue);
      }
  }
}





listHistorics* sjfX (process * dummy,int nb){

  listHistorics* head=NULL;

    
    size_t arraySize = nb;
    qsort(dummy, arraySize, sizeof(process), compareStructsV8);

 
    listSgf *q = NULL;

    process current ;
    int time =0 ;
    
   int nbProcessFinished =0;
   while( nbProcessFinished<nb){
  
  addNewCommingToQueueSgfReadyQueue(&q,dummy,time,arraySize,current,&head);

   if(q!=NULL){
     current = dequeueSgfReadyQueue(&q);

     historicsToDraw processExitReadyQueue;
      strcpy(processExitReadyQueue.nameP,current.name);
       processExitReadyQueue.readyQueueOrRunning=0;
         processExitReadyQueue.enterOrExit=1;
         processExitReadyQueue.time=time;
     addToHistorics(&head,processExitReadyQueue);


      historicsToDraw processEnterExecution= {*current.name,1,0,time};
      strcpy(processEnterExecution.nameP,current.name);
      processEnterExecution.readyQueueOrRunning = 1 ;
      processEnterExecution.enterOrExit=0 ;
      processEnterExecution.time=time;
     addToHistorics(&head,processEnterExecution);


    
     for(int i=time;i<time+current.te;i++){
        addNewCommingToQueueSgfReadyQueue(&q,dummy,i,arraySize,current,&head);
        printf("time %d s: process %s running \n",i,current.name);
     
     }
 
     time+= current.te ;
     nbProcessFinished ++ ;
     historicsToDraw processFinish;
     strcpy(processFinish.nameP,current.name);
     processFinish.readyQueueOrRunning=1;
     processFinish.enterOrExit=2;
     processFinish.time=time;
     addToHistorics(&head,processFinish);
     printf("\n =================================== \nat time %d s: process %s end ! \n \n =================================== \n",time,current.name);
   
   }else{

    printf("\ntime %d s:waiting for process .........\n",time);
     time ++ ;
   }

  
   }

    return head;
}




