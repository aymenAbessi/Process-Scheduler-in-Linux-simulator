#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "multilevelWithDynamicPriority.h"
#include <string.h>

 

int compareStructsV10(const void *a, const void *b) {
  
    return ((process*)a)->ta - ((process*)b)->ta;
}

void swapV2(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}



int nbPriorityV2 (process * pTab,int size){
    int n=0;
    int arr [size];

    for(int i =0 ; i<size ; i++){
        arr[i]=pTab[i].priority ;
    }

  
   for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swapV2(&arr[j], &arr[j + 1]);
            }
        }
    }

    int context = arr[0];
    n++ ;
    for (int i =0 ; i <size ; i ++){
        if (arr[i]>context || arr[i]<context){
            n++ ;
            context= arr[i];
        }

    }
    return n ;

}


int getRankV2(process * processes , int priority,int size){

   


     int arr [size];

    for(int i =0 ; i<size ; i++){
        arr[i]=processes[i].priority ;
    }

  
   for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swapV2(&arr[j], &arr[j + 1]);
            }
        }
    }

    int context = arr[0];
    int rank =0 ;
  
     if(priority<=context){

            return rank;

            }else{
                rank ++ ;
            }

    for (int i =0 ; i <size ; i++){
          if (arr[i]>context || arr[i]<context){
            context= arr[i];
            if(priority<=context){

                return rank;

            }else{
                rank ++ ;
            }
        }
    }

    return rank ;
}



void addNewComingToQueueV2(queue q[],process *processes,int time,int arraySize,listHistorics ** h){

   

   for(int i =0 ; i < arraySize ; i++){
    if(processes[i].ta == time && !isProcessInQueue(&q[getRankV2(processes,processes[i].priority,arraySize)],processes[i].name)){
             int decideWhereWeEnqueTheProcess = getRankV2(processes,processes[i].priority,arraySize);

                printf("at %d :process %s with priority %d puted in queue number %d\n",time,processes[i].name,processes[i].priority,decideWhereWeEnqueTheProcess);
                   historicsToDraw processEnterReadyQueue ;
                  strcpy(processEnterReadyQueue.nameP, processes[i].name); 
                 processEnterReadyQueue.readyQueueOrRunning = 0;
                  processEnterReadyQueue.enterOrExit = 0;
                  processEnterReadyQueue.time = time;
                 addToHistorics(h,processEnterReadyQueue);
                enqueue(&q[decideWhereWeEnqueTheProcess],processes[i]);
    }
   
   }

}

bool multilevelDynamicPriorityQueueEmpty(queue q[], int arraySize){

        for(int i =0 ;i<arraySize ; i++){
            if(notEmpty(&q[i])){

                return false;
            }
                
        }
        return true;

}

int selectedQueueNumberV2(queue q[],int arraySize){
    for (int i = arraySize-1 ; i>=0 ; i--){
        if(notEmpty(&q[i]))
        return i ;
    }
    return 0 ;

}


bool switchToOtherQueueV2(queue q[],int arraySize,int currentQueue,int nbOfQueue){
  
    if(currentQueue<nbOfQueue-1){
        for(int i = currentQueue+1 ; i<nbOfQueue ; i++){
        if(notEmpty(&q[i])){
            return true ;
        }
    }
    }
    
  
    return false ;

}

bool shouldWeUseQuantumV2(queue *q){
    if(notEmpty(q))
  
    return notEmpty(q);
}



listHistorics* multilevelDynamicPriorityX(process * processes,int arraySize,int q){
  
    listHistorics* head=NULL;
    int nbOfQueue = nbPriorityV2 (processes,arraySize);

    queue multilevelQueue [nbOfQueue];

  
    int selectedQueue ; 
    int time =0; 
   
     

      qsort(processes,arraySize, sizeof(process), compareStructsV10);

  



     for (int i = 0; i < nbOfQueue; ++i) {

        init_queue(&multilevelQueue[i]);
     }

   process current ={"  ",-1,-1,-1};
     
        int moveToQuantum= false ;

        int finishedProcess = 0 ;
    
    while(finishedProcess<arraySize){
        
       
      
        addNewComingToQueueV2(multilevelQueue,processes,time,arraySize,&head);

     printf("\n\n\n\n");
        printAllQueueContents(multilevelQueue,nbOfQueue);
           printf("\n\n\n\n");
   
            
        if(!multilevelDynamicPriorityQueueEmpty(multilevelQueue,nbOfQueue)){

            selectedQueue = selectedQueueNumberV2(multilevelQueue,nbOfQueue);
              printf("at time %d the selected queue is %d\n",time,selectedQueue);
            if(!moveToQuantum){
                   current = dequeue(&multilevelQueue[selectedQueue]);
                  printf("at time %d : %s get out of queue %d and run\n",time,current.name,selectedQueue);

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
            }

               
            bool workWithQuantum = shouldWeUseQuantumV2(&multilevelQueue[selectedQueue]) ;
                
            

              int quantum = q ;

                

            while (!switchToOtherQueueV2(multilevelQueue,nbOfQueue,selectedQueue,nbOfQueue) && quantum>0 && current.te>0){
                      printf("at %d : %s (%d) run \n",time,current.name,current.te);
                      current.te = current.te -1 ;
                      time ++ ;
                      if(workWithQuantum){
                        moveToQuantum = true;
                        quantum -- ;
                      }
                    addNewComingToQueueV2(multilevelQueue,processes,time,arraySize,&head);
                    if(shouldWeUseQuantumV2(&multilevelQueue[selectedQueue])&& !moveToQuantum){
                        moveToQuantum = true ;
                        printf("move to quantum mode ");
                        break;
                    }
                   
            }
            if(current.te==0){
                finishedProcess ++ ;
                printf("at %d : %s end \n",time,current.name);
                moveToQuantum = false;

                  historicsToDraw processFinish;
               strcpy(processFinish.nameP,current.name);
               processFinish.readyQueueOrRunning=1;
               processFinish.enterOrExit=2;
               processFinish.time=time;
               addToHistorics(&head,processFinish);

            }else{
               
                    bool added= false ;
                     if(switchToOtherQueueV2(multilevelQueue,nbOfQueue,selectedQueue,nbOfQueue)){
                           added = true ;
                    printf(" switch to other queue  \n\n");
                           moveToQuantum = false;
                            printf("at %d : %s back to ready queue \n",time,current.name);

                        if(selectedQueue==0)
                enqueue(&multilevelQueue[selectedQueue],current);
                            else{
                                current.priority-=1 ;
                                enqueue(&multilevelQueue[selectedQueue-1],current);
                            }
                        

                   historicsToDraw processExitExcution ;
                  strcpy(processExitExcution.nameP, current.name); 
                  processExitExcution.readyQueueOrRunning = 1;
                  processExitExcution.enterOrExit = 1;
                  processExitExcution.time = time;
                  addToHistorics(&head,processExitExcution);

                  historicsToDraw processEnterReadyQueue ;
                  strcpy(processEnterReadyQueue.nameP, current.name); 
                  processEnterReadyQueue.readyQueueOrRunning = 0;
                  processEnterReadyQueue.enterOrExit = 0;
                  processEnterReadyQueue.time = time;
                  addToHistorics(&head,processEnterReadyQueue);
                 }

                if( quantum == 0){

                 
                if(!added){
                    printf("at %d : %s back to ready queue \n",time,current.name);

                        if(selectedQueue==0)
                enqueue(&multilevelQueue[selectedQueue],current);
                            else{
                                current.priority-=1 ;
                                enqueue(&multilevelQueue[selectedQueue-1],current);
                            }
                

                   historicsToDraw processExitExcution ;
                  strcpy(processExitExcution.nameP, current.name); 
                  processExitExcution.readyQueueOrRunning = 1;
                  processExitExcution.enterOrExit = 1;
                  processExitExcution.time = time;
                  addToHistorics(&head,processExitExcution);

                  historicsToDraw processEnterReadyQueue ;
                  strcpy(processEnterReadyQueue.nameP, current.name); 
                  processEnterReadyQueue.readyQueueOrRunning = 0;
                  processEnterReadyQueue.enterOrExit = 0;
                  processEnterReadyQueue.time = time;
                  addToHistorics(&head,processEnterReadyQueue);
                }
                if(!switchToOtherQueueV2(multilevelQueue,nbOfQueue,selectedQueue,nbOfQueue) && ! added){
                       current=dequeue(&multilevelQueue[selectedQueue]);
                          printf("at time %d : %s get out of queue %d and run\n",time,current.name,selectedQueue);

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
                }
             
            
                }
                    
             

            
             
            }
        
        }
        else{
              printf("at time %d all queue are empty\n",time);
      
                 time ++ ;
        }
        
       
    }


     



    
    
    
   

    return head;
}

