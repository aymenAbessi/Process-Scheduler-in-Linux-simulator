#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <gtk/gtk.h>
#include "Fifo/fifo.h"
#include "rr/rr.h"
#include "srt/srt.h"
#include "multilevel/multilevel.h"
#include "metrics/metrics.h"
#include "priority/priority.h"
#include "sjf/sjf.h"
#include "lifo/lifo.h"
#include "multilevelWithDynamicPriority/multilevelWithDynamicPriority.h"


int unit = 35 ;
int finish = 0;
int NumberOfAlgoExcuted =0 ;
int nbOfAlgo = 8 ;
int ExecutedAlgo [8]= {0,0,0,0,0,0,0,0} ;
int arraySize ;
char selectedAlgo[20];


float RotTimeAverage =0 ;
float waitingTimeAverage =0 ;
float repsponeTimeAverage =0 ;
float cpuTimeAverage =0;



typedef struct {
    const char *name;
    GdkRGBA color;
} ProcessColor;

ProcessColor *processColors;


typedef struct {
    const char *name;
	float RotTimeAverage ;
	float waitingTimeAverage ;
	float repsponeTimeAverage  ;
	float cpuTimeAverage;
	
} AlgosDataToPolt;

AlgosDataToPolt *dataVisualisation ;

ProcessColor *processColors;


GdkRGBA getProcessColor(const char *processName, ProcessColor *colorMap, int mapSize) {
    GdkRGBA defaultColor = {0, 0, 0, 1}; 

    for (int i = 0; i < mapSize; ++i) {
        if (strcmp(processName, colorMap[i].name) == 0) {
			
            return colorMap[i].color;
        }
    }

    return defaultColor;
}






void copyProcessArray(process *source, process *destination, int size) {
    for (int i = 0; i < size; ++i) {
        strcpy(destination[i].name, source[i].name);
        destination[i].ta = source[i].ta;
        destination[i].te = source[i].te;
        destination[i].priority = source[i].priority;
    }
}


void freeList(listHistorics *head) {
    listHistorics *current = head;
    while (current != NULL) {
        listHistorics *temp = current;
        current = current->next;
        free(temp); 
    }
}

void freeListV2(listQueueState *head) {
    listQueueState *current = head;
    while (current != NULL) {
        listQueueState *temp = current;
        current = current->next;
        free(temp);
    }
}






gboolean draw_callback(GtkWidget *widget, cairo_t *cr, gpointer data) {
	
    listHistorics *processes =((TwoInOne *)data)->list;
	listQueueState *readyQueue =((TwoInOne *)data)->queueList;

	
	int marge=50 ;
	
	

    gint width, height;
    gtk_widget_get_size_request(widget, &width, &height);

	

	
    cairo_set_font_size(cr, 15);
    gdk_cairo_set_source_rgba(cr, &(GdkRGBA){0, 0, 0, 1});

   
    cairo_move_to(cr, marge, 140);
	cairo_show_text(cr, "0"); 
	cairo_move_to(cr, marge, 120);
    cairo_line_to(cr, (unit*finish)+marge, 120); 
    cairo_stroke(cr);



    
    listHistorics *current = processes;
    while (current != NULL) {
        historicsToDraw process = current->val;
       
        
     
        if (process.readyQueueOrRunning == 1 && process.enterOrExit == 0) {
         
            gint rectStart = process.time; 
            gint rectWidth =0;

		

			  listHistorics *search =current;
   				 while(search!=NULL){
        			if(strcmp(search->val.nameP, current->val.nameP) == 0 && ( (search->val.enterOrExit==1  && search->val.readyQueueOrRunning == 1)|| (search->val.enterOrExit==2  && search->val.readyQueueOrRunning == 1))){
              			rectWidth =( search->val.time - current->val.time) * unit   ;
						break;
        			}
					search = search->next;
    			}
			
			
			 gdk_cairo_set_source_rgba(cr, &(GdkRGBA){0, 0, 0, 1}); 
			
			cairo_move_to(cr, (process.time*unit)+50, 140);
			char labelStart[10];
  			sprintf(labelStart, "%d", process.time);
    		cairo_show_text(cr, labelStart); 


			cairo_move_to(cr, (search->val.time*unit)+50, 140);
			char labelEnd[10];
  			sprintf(labelEnd, "%d", search->val.time);
    		cairo_show_text(cr, labelEnd); 

 		


          
	 	 	GdkRGBA color = getProcessColor(process.nameP,processColors,arraySize);
            gdk_cairo_set_source_rgba(cr,&color); 

          
            cairo_rectangle(cr, (process.time*unit)+50, 50,rectWidth, 50); 
            cairo_fill(cr);

		
			gdk_cairo_set_source_rgba(cr, &(GdkRGBA){1, 1, 1, 1}); 
   		    cairo_move_to(cr, (process.time*unit)+50+ 5, 80); 
    		cairo_show_text(cr, current->val.nameP);
		
        }

       
        current = current->next;
    }


	

		
	listQueueState *temp = readyQueue ;
	 gdk_cairo_set_source_rgba(cr, &(GdkRGBA){0, 0, 0, 1}); 
	
	while(temp != NULL){
		
			if(strcmp(temp->val.namesOfProcessess,"")){


	char inputString[40] ;
	strcpy(inputString,temp->val.namesOfProcessess);
				
    char *token;
    char *tokensArray[temp->val.nb]; 
    
    int index = 0;

    token = strtok(inputString,","); 


    while (token != NULL && index < temp->val.nb) {
        tokensArray[index++] = token;
        token = strtok(NULL, ",");
    }

   
    for (int i = 0; i < index; i++) {
			cairo_move_to(cr, (temp->val.time*unit)+50, 180+20*i);
    		cairo_show_text(cr,tokensArray[i]); 
    }


			cairo_move_to(cr, (temp->val.time*unit)+50, 140);
			char labelStart[10];
  			sprintf(labelStart, "%d", temp->val.time);
    		cairo_show_text(cr, labelStart); 

		
		
	}
			
		

		temp=temp->next ;

	}
	

			
			cairo_set_font_size(cr, 30);
			gdk_cairo_set_source_rgba(cr, &(GdkRGBA){0, 0, 0, 1}); 
   		    cairo_move_to(cr, 100, 350); 
			
    		cairo_show_text(cr, selectedAlgo);
			cairo_move_to(cr, 100, 380);

		

PangoLayout *layoutHeader = pango_cairo_create_layout(cr);
pango_layout_set_text(layoutHeader, "============= Metrics 📊 ===========", -1);

PangoFontDescription *font_desc_header = pango_font_description_from_string("Sans Bold 18");
pango_layout_set_font_description(layoutHeader, font_desc_header);
pango_font_description_free(font_desc_header);

cairo_set_source_rgb(cr, 0, 0, 0); 
pango_cairo_show_layout(cr, layoutHeader); 
g_object_unref(layoutHeader);

cairo_move_to(cr, 100, 420);

PangoLayout *layoutMetrics = pango_cairo_create_layout(cr);
char text[200];





snprintf(text, sizeof(text), "Rotation Time: %.2f \xF0\x9F\x94\x83\nWaiting Time: %.2f \xF0\x9F\x95\x92\nResponse Time: %.2f \xE2\x8F\xB1\nCPU Time: %.2f \xF0\x9F\x96\xA5",
         RotTimeAverage, waitingTimeAverage, repsponeTimeAverage, cpuTimeAverage);

pango_layout_set_text(layoutMetrics, text, -1);

PangoFontDescription *font_desc_metrics = pango_font_description_from_string("Sans Bold 18");
pango_layout_set_font_description(layoutMetrics, font_desc_metrics);
pango_font_description_free(font_desc_metrics);

cairo_set_source_rgb(cr, 0, 0, 0); 
pango_cairo_show_layout(cr, layoutMetrics); 
g_object_unref(layoutMetrics);




			





    return FALSE;
}


int on_button_clicked(GtkWidget *widget, gpointer data) {
  
	
    FILE *dataFile = fopen("dataVisualisation.txt", "w");
    if (dataFile == NULL) {
        printf("Error opening data file.\n");
        return 1;
    }

   
    for (size_t i = 0; i <nbOfAlgo; ++i) {
		if(ExecutedAlgo[i])
        fprintf(dataFile, "%s %f %f %f %f\n", dataVisualisation[i].name, dataVisualisation[i].RotTimeAverage, dataVisualisation[i].waitingTimeAverage, dataVisualisation[i].repsponeTimeAverage, dataVisualisation[i].cpuTimeAverage);
    }

    fclose(dataFile);

   
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");

    if (gnuplotPipe) {
        fprintf(gnuplotPipe, "set terminal x11 title 'Line Chart'\n");
        fprintf(gnuplotPipe, "set style data lines\n");  


        fprintf(gnuplotPipe, "set xlabel 'Algorithm'\n");
        fprintf(gnuplotPipe, "set ylabel 'Metric Value'\n");

        fprintf(gnuplotPipe, "set title 'Metrics Comparison'\n");

        fprintf(gnuplotPipe, "plot 'dataVisualisation.txt' using 2:xtic(1) title 'RotTimeAverage' with lines lw 2, \
                                '' using 3 title 'waitingTimeAverage' with lines lw 2, \
                                '' using 4 title 'responseTimeAverage' with lines lw 2, \
                                '' using 5 title 'cpuTimeAverage' with lines lw 2\n");


        fflush(gnuplotPipe);
        pclose(gnuplotPipe);
    } else {
        printf("Error opening GNUplot.\n");
    }

	
    FILE *gnuplotPipe1 = popen("gnuplot -persistent", "w");

    if (gnuplotPipe1) {
        fprintf(gnuplotPipe1, "set terminal x11 title 'Bar Chart'\n");
        fprintf(gnuplotPipe1, "set style data histograms\n");
        fprintf(gnuplotPipe1, "set style fill solid\n"); 
        fprintf(gnuplotPipe1, "set boxwidth 0.5 relative\n");
        fprintf(gnuplotPipe1, "set xlabel 'Algorithm'\n");
        fprintf(gnuplotPipe1, "set ylabel 'Metric Value'\n");
        fprintf(gnuplotPipe1, "set title 'Metrics Comparison - Chart 1'\n");
        fprintf(gnuplotPipe1, "set xtic rotate by -45\n");
        fprintf(gnuplotPipe1, "plot 'dataVisualisation.txt' using 2:xtic(1) title 'RotTimeAverage' lc rgb '#1f77b4', \
                                '' using 3 title 'waitingTimeAverage' lc rgb '#ff7f0e', \
                                '' using 4 title 'responseTimeAverage' lc rgb '#2ca02c', \
                                '' using 5 title 'cpuTimeAverage' lc rgb '#d62728'\n"); 

        fflush(gnuplotPipe1);
        pclose(gnuplotPipe1);
    } else {
        printf("Error opening GNUplot for Chart 1.\n");
    }



}

int main(int argc, char *argv[]) {


	FILE *f;
	char buffer [100];
	

	process *pTab;

    dataVisualisation =  malloc(nbOfAlgo*sizeof(AlgosDataToPolt));
	

	

	int continueWithTheOldConfigFile;
	printf("1: continue with the existing config file \n2: generate new config file\n>> ");
	scanf("%d",&continueWithTheOldConfigFile) ; 
	while (continueWithTheOldConfigFile>2 || continueWithTheOldConfigFile<1){
		printf("1 :continue with the existing config file \n2: generate new config file\n>> ");
		scanf("%d",&continueWithTheOldConfigFile) ; 
	}


	if(continueWithTheOldConfigFile == 1){

	
	
	

	f=fopen("config.txt","r");

	if(f==NULL){
		printf("errors !");
		exit(1);
	}

	
	process tab[100];
	int i = 0;
	while(fgets(buffer,100,f)){
	
		if(buffer[0]=='#' || isspace(buffer[0])){
			continue;
		}
		
		
		char* token = strtok(buffer,",");
		strcpy(tab[i].name,token);
		
		token = strtok(NULL,",");
		tab[i].ta=atoi(token);
		
		token = strtok(NULL,",");
		tab[i].te=atoi(token);
		
		token = strtok(NULL,",");
		tab[i].priority=atoi(token);

		i++;
		
		
	}

		fclose(f);



		arraySize = i;
		pTab = tab ;

	}else if (continueWithTheOldConfigFile==2){
		
		
		printf("enter the number of processes: ");
		scanf("%d",&arraySize);
		pTab = malloc(arraySize*sizeof(process));

		int minTe ;
		int maxTe ;

		int minP;
		int maxP;
		
		int minTa ;
		int maxTa;
		
		printf("enter the minimual ta could a process have: ");
		scanf("%d",&minTa);
		printf("enter the maximual ta could a process have: ");
		scanf("%d",&maxTa);
		while(maxTa<minTa){
			printf("enter a number bigger than/equal to %d: ",minTa);
		scanf("%d",&maxTa);
		}
		
		printf("enter the minimual te could a process have: ");
		scanf("%d",&minTe);
		printf("enter the maximual te could a process have: ");
		scanf("%d",&maxTe);
		while(maxTe<minTe){
			printf("enter a number bigger than/equal to %d: ",minTe);
		scanf("%d",&maxTe);
		}
		
		printf("enter the minimual priority could a process have: ");
		scanf("%d",&minP);
		printf("enter the maximual priority could a process have: ");
		scanf("%d",&maxP);
		while(maxP<minP){
			printf("enter a number bigger than/equal to %d: ",minP);
		scanf("%d",&maxP);
		}

		f=fopen("config.txt","w+");
		fprintf(f,"%s","#processes\n");
		fprintf(f,"%s","# name, Arrival time , temp needed , priority\n");
		char name[12] ;
		for(int i = 1 ; i<=arraySize;i++){
			snprintf(name, 12, "p%d", i);;
			int randomP = rand() % (maxP - minP + 1) + minP;
			int randomTe = rand() % (maxTe - minTe + 1) + minTe;
			int randomTa = rand() % (maxTa - minTa + 1) + minTa;
		
			fprintf(f,"%s,%d,%d,%d\n",name,randomTa,randomTe,randomP);
		}


		fflush(f); 
		fseek(f, 0, SEEK_SET);


		int i =0;
		while(fgets(buffer,100,f)){
	
		if(buffer[0]=='#' || isspace(buffer[0])){
			continue;
		}
	
		char* token = strtok(buffer,",");
		strcpy(pTab[i].name,token);
		
		token = strtok(NULL,",");
		pTab[i].ta=atoi(token);
		
		token = strtok(NULL,",");
		pTab[i].te=atoi(token);
		
		token = strtok(NULL,",");
		pTab[i].priority=atoi(token);

		i++;
		
	}

		fclose(f);
	}








	int exit = 1;
	while(exit){

	metrics *metricsTable =malloc(sizeof(metrics)*arraySize);
    process copiedArray[arraySize];
    copyProcessArray(pTab, copiedArray, arraySize);
	listHistorics *l ;
	listQueueState *ql;
	TwoInOne *dataToDraw =malloc(sizeof(TwoInOne));
	dataToDraw->list = NULL; 
	dataToDraw->queueList = NULL; 
	int choice;
	int quantum ;
    printf("Choose a scheduling algorithm:\n");
    printf("1. FIFO\n");
    printf("2. SRT\n");
    printf("3. Round Robin\n");
    printf("4. Priority\n");
    printf("5. Multilevel\n");
	printf("6. SJF\n");
	printf("7. LIFO\n");
	printf("8. Multilevel with dynamic priority\n");
    printf("Enter your choice (1-8): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("You selected FIFO algorithm.\n");
			l=fifoX(pTab,arraySize);
			strcpy(selectedAlgo,"Fifo");
			ql=setWhoIsInTheQueue(l,arraySize,copiedArray);
			dataToDraw->list=l;
			dataToDraw->queueList=ql;
            break;
        case 2:
            printf("You selected SRT algorithm.\n");
			l=srtX(pTab,arraySize);
			strcpy(selectedAlgo,"SRT");
			ql=setWhoIsInTheQueue(l,arraySize,copiedArray);
			dataToDraw->list=l;
			dataToDraw->queueList=ql;
            break;
        case 3:
            printf("You selected Round Robin algorithm.\n");
			printf("enter the quantum: ");		
			scanf("%d",&quantum);
			l=roundRobinX(pTab,arraySize,quantum);
			strcpy(selectedAlgo,"RR");
			ql=setWhoIsInTheQueue(l,arraySize,copiedArray);
			dataToDraw->list=l;
			dataToDraw->queueList=ql;
            break;
        case 4:
            printf("You selected Priority algorithm.\n");
			strcpy(selectedAlgo,"Priority");
			l = priorityX(pTab,arraySize);
			ql=setWhoIsInTheQueue(l,arraySize,copiedArray);
			dataToDraw->list=l;
			dataToDraw->queueList=ql;
            break;
        case 5:
            printf("You selected Multilevel algorithm.\n");
			printf("enter the quantum : ");
			scanf("%d",&quantum);
			l=multilevelX(pTab,arraySize,quantum);
			strcpy(selectedAlgo,"Multilevel");
			ql=setWhoIsInTheQueue(l,arraySize,copiedArray);
			dataToDraw->list=l;
			dataToDraw->queueList=ql;
            break;
		 case 6:
            printf("You selected SJF algorithm.\n");
			l=sjfX(pTab,arraySize);
			strcpy(selectedAlgo,"SJF");
			ql=setWhoIsInTheQueue(l,arraySize,copiedArray);
			dataToDraw->list=l;
			dataToDraw->queueList=ql;
            break;
		 case 7:
            printf("You selected LIFO algorithm.\n");
			l=lifoX(pTab,arraySize);
			strcpy(selectedAlgo,"LIFO");
			ql=setWhoIsInTheQueue(l,arraySize,copiedArray);
			dataToDraw->list=l;
			dataToDraw->queueList=ql;
            break;
		case 8:
            printf("You selected Multilevel with dynamic priority algorithm.\n");
			printf("enter the quantum : ");
			scanf("%d",&quantum);
			l=multilevelDynamicPriorityX(pTab,arraySize,quantum);
			strcpy(selectedAlgo,"MultilevelV2");
			ql=setWhoIsInTheQueue(l,arraySize,copiedArray);
			dataToDraw->list=l;
			dataToDraw->queueList=ql;
            break;
        default:
            printf("Invalid choice. Default algorithms selected (FIFO) \n");
			l=fifoX(pTab,arraySize);
			strcpy(selectedAlgo,"Fifo");
			ql=setWhoIsInTheQueue(l,arraySize,copiedArray);
			dataToDraw->list=l;
			dataToDraw->queueList=ql;
            break;
    }
	


	if(NumberOfAlgoExcuted<nbOfAlgo && ExecutedAlgo[choice-1]==0)
		NumberOfAlgoExcuted++ ;

	ExecutedAlgo[choice-1]=1 ;



	
	
	copyProcessArray(copiedArray,pTab,arraySize);

	
	printList(l);
  
    fillTable(l,metricsTable,copiedArray,arraySize);

	

 	processColors = malloc(arraySize * sizeof(ProcessColor));

	cpuTimeAverage = 0;
	for (int i =0 ; i<arraySize;i++){
		cpuTimeAverage += pTab[i].te ;
		RotTimeAverage+=metricsTable[i].rotingsTime;
		waitingTimeAverage+=metricsTable[i].waitingTime;
		repsponeTimeAverage+=metricsTable[i].responseTime;
		if(metricsTable[i].finishedTime>finish)
			finish=metricsTable[i].finishedTime;


		
		processColors[i].name = pTab[i].name;
        processColors[i].color.red = (double)rand() / RAND_MAX;
        processColors[i].color.green = (double)rand() / RAND_MAX;
        processColors[i].color.blue = (double)rand() / RAND_MAX;
        processColors[i].color.alpha = 1.0;
			
	}


	
	RotTimeAverage/=arraySize;
	waitingTimeAverage/=arraySize;
	repsponeTimeAverage/=arraySize;
	cpuTimeAverage/=arraySize;
	



	if(strcmp(selectedAlgo,"Fifo")==0){
		AlgosDataToPolt algo ={"Fifo",RotTimeAverage,waitingTimeAverage,repsponeTimeAverage,cpuTimeAverage};
		dataVisualisation[0] = algo;
		printf("Algo :%s RotTimeAverage : %f secs, waitingTmeAverage: %f secs, cpuTime : %f secs, responseTime: %f secs\n",dataVisualisation[0].name,dataVisualisation[0].RotTimeAverage,dataVisualisation[0].waitingTimeAverage,dataVisualisation[0].cpuTimeAverage,dataVisualisation[0].repsponeTimeAverage);
	}else if(strcmp(selectedAlgo,"SRT")==0){
		AlgosDataToPolt algo ={"SRT",RotTimeAverage,waitingTimeAverage,repsponeTimeAverage,cpuTimeAverage};
		dataVisualisation[1] = algo;
		printf("Algo :%s RotTimeAverage : %f secs, waitingTmeAverage: %f secs, cpuTime : %f secs, responseTime: %f secs\n",dataVisualisation[1].name,dataVisualisation[1].RotTimeAverage,dataVisualisation[1].waitingTimeAverage,dataVisualisation[1].cpuTimeAverage,dataVisualisation[1].repsponeTimeAverage);
	}else if(strcmp(selectedAlgo,"RR")==0){
		AlgosDataToPolt algo ={"RR",RotTimeAverage,waitingTimeAverage,repsponeTimeAverage,cpuTimeAverage};
		dataVisualisation[2] = algo;
		printf("Algo :%s RotTimeAverage : %f secs, waitingTmeAverage: %f secs, cpuTime : %f secs, responseTime: %f secs\n",dataVisualisation[2].name,dataVisualisation[2].RotTimeAverage,dataVisualisation[2].waitingTimeAverage,dataVisualisation[2].cpuTimeAverage,dataVisualisation[2].repsponeTimeAverage);
	}else if(strcmp(selectedAlgo,"Priority")==0){
		AlgosDataToPolt algo ={"Priority",RotTimeAverage,waitingTimeAverage,repsponeTimeAverage,cpuTimeAverage};
		dataVisualisation[3] = algo;
		printf("Algo :%s RotTimeAverage : %f secs, waitingTmeAverage: %f secs, cpuTime : %f secs, responseTime: %f secs\n",dataVisualisation[3].name,dataVisualisation[3].RotTimeAverage,dataVisualisation[3].waitingTimeAverage,dataVisualisation[3].cpuTimeAverage,dataVisualisation[3].repsponeTimeAverage);
	}else if(strcmp(selectedAlgo,"Multilevel")==0){
		AlgosDataToPolt algo ={"Multilevel",RotTimeAverage,waitingTimeAverage,repsponeTimeAverage,cpuTimeAverage};
		dataVisualisation[4] = algo;
		printf("Algo :%s RotTimeAverage : %f secs, waitingTmeAverage: %f secs, cpuTime : %f secs, responseTime: %f secs\n",dataVisualisation[4].name,dataVisualisation[4].RotTimeAverage,dataVisualisation[4].waitingTimeAverage,dataVisualisation[4].cpuTimeAverage,dataVisualisation[4].repsponeTimeAverage);
	}else if(strcmp(selectedAlgo,"SJF")==0){
		AlgosDataToPolt algo ={"SJF",RotTimeAverage,waitingTimeAverage,repsponeTimeAverage,cpuTimeAverage};
		dataVisualisation[5] = algo;
		printf("Algo :%s RotTimeAverage : %f secs, waitingTmeAverage: %f secs, cpuTime : %f secs, responseTime: %f secs\n",dataVisualisation[5].name,dataVisualisation[5].RotTimeAverage,dataVisualisation[5].waitingTimeAverage,dataVisualisation[5].cpuTimeAverage,dataVisualisation[5].repsponeTimeAverage);
	}else if(strcmp(selectedAlgo,"LIFO")==0){
		AlgosDataToPolt algo ={"LIFO",RotTimeAverage,waitingTimeAverage,repsponeTimeAverage,cpuTimeAverage};
		dataVisualisation[6] = algo;
		printf("Algo :%s RotTimeAverage : %f secs, waitingTmeAverage: %f secs, cpuTime : %f secs, responseTime: %f secs\n",dataVisualisation[6].name,dataVisualisation[6].RotTimeAverage,dataVisualisation[6].waitingTimeAverage,dataVisualisation[6].cpuTimeAverage,dataVisualisation[6].repsponeTimeAverage);
	}else if(strcmp(selectedAlgo,"MultilevelV2")==0){
		AlgosDataToPolt algo ={"MultilevelV2",RotTimeAverage,waitingTimeAverage,repsponeTimeAverage,cpuTimeAverage};
		dataVisualisation[7] = algo;
		printf("Algo :%s RotTimeAverage : %f secs, waitingTmeAverage: %f secs, cpuTime : %f secs, responseTime: %f secs\n",dataVisualisation[7].name,dataVisualisation[7].RotTimeAverage,dataVisualisation[7].waitingTimeAverage,dataVisualisation[7].cpuTimeAverage,dataVisualisation[7].repsponeTimeAverage);
	}
	
	


	
   
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 1800, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

   
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

   
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_NEVER);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 0);

 
    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, 100 + (finish * unit), 600);
    gtk_container_add(GTK_CONTAINER(scrolled_window), drawing_area);
    g_signal_connect(drawing_area, "draw", G_CALLBACK(draw_callback),dataToDraw);

   
    GtkWidget *button = gtk_button_new_with_label("Compare Algos Metrics");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 10);

   
    gtk_widget_set_halign(button, GTK_ALIGN_CENTER);



if (NumberOfAlgoExcuted < 2) {
    gtk_widget_set_sensitive(button, FALSE); 
} else {
    gtk_widget_set_sensitive(button, TRUE); 
}


    gtk_widget_show_all(window);

    gtk_main();




	free(metricsTable);
	free(dataToDraw->list);
	free(dataToDraw->queueList);
	free(dataToDraw);
	


	printf("\n0-exit \n1- test other algorithms\n>>>");
	scanf("%d",&exit);
	}

	free(processColors);
	free(dataVisualisation);


if (continueWithTheOldConfigFile == 2) {
    free(pTab);
}

  printf("End of the project. Goodbye! \xe2\x99\xa5\n3AM Team\n");

return 0; 
}


