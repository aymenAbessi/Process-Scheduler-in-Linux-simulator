#include "metrics.h"
#include<stdlib.h>
#include <string.h>
#include <stdio.h>


void setResponseTime(metrics *m,process p) {

 

    m->responseTime = m->firstResponse-p.ta;
}

void setRotingTime(metrics *m,process p) {

    m->rotingsTime = m->finishedTime-p.ta;
}

void setWatingTime(metrics *m){
    m->waitingTime = m->finishedTime - m->rotingsTime ;
}

void setFinishedTime(listHistorics *l,metrics *m,process p){
     listHistorics *current = l;  
  


    while (current != NULL) {
      

        if(strcmp(p.name,current->val.nameP)==0){
              if (current->val.readyQueueOrRunning == 1 && current->val.enterOrExit== 2) {
                m->finishedTime= current->val.time ; 
             
                break ;
        } 

        }
      
         current = current->next;
      

}

}

void setFirstResponseTime(listHistorics *l,metrics *m,process p){

        listHistorics *current = l;
        int firstExcutionTime;

    while (current != NULL) {
      
       
                  if(strcmp(p.name,current->val.nameP)==0){
                         if (current->val.readyQueueOrRunning == 1 && current->val.enterOrExit== 0) {
                              m->firstResponse= current->val.time ; 
                           
                      break ;

                        }
               
                 }
              
            
           current = current->next;

        } 

}

void fillTable(listHistorics *head, metrics *metricsTable,process * dummyp,int arraySize){
  

      for(int i=0; i<arraySize;i++){
        strcpy(metricsTable[i].name,dummyp[i].name);
        setFinishedTime(head,&metricsTable[i],dummyp[i]);
      
       setFirstResponseTime(head,&metricsTable[i],dummyp[i]);
         setResponseTime(&metricsTable[i],dummyp[i]);
        setRotingTime(&metricsTable[i],dummyp[i]);
        setWatingTime(&metricsTable[i]);
      }

       for (int i=0;i<arraySize;i++){
        printf("%s , finished time :%d  , first response time : %d , roting time : %d , waiting time : %d , response time : %d\n",metricsTable[i].name,metricsTable[i].finishedTime,metricsTable[i].firstResponse,metricsTable[i].rotingsTime,metricsTable[i].waitingTime,metricsTable[i].responseTime);
      }

}



