
gcc -c queue/queue.c -o queue/queue.o


gcc -c historicsToDraw/historicsToDraw.c -o historicsToDraw/historicsToDraw.o -I queue/



gcc -c srt/srt.c -o srt/srt.o -I queue/ -I historicsToDraw/


gcc -c rr/rr.c -o rr/rr.o -I queue/ -I historicsToDraw/


gcc -c priority/priority.c -o priority/priority.0 -I queue/ -I historicsToDraw/

gcc -c sjf/sjf.c -o sjf/sjf.0 -I queue/ -I historicsToDraw/

gcc -c lifo/lifo.c -o lifo/lifo.0 -I queue/ -I historicsToDraw/

gcc -c multilevel/multilevel.c -o multilevel/multilevel.o -I queue/ -I historicsToDraw/

gcc -c multilevelWithDynamicPriority/multilevelWithDynamicPriority.c -o multilevelWithDynamicPriority/multilevelWithDynamicPriority.o -I queue/ -I historicsToDraw/

gcc -c Fifo/fifo.c -o Fifo/fifo.o -I queue/ -I historicsToDraw/ 


gcc -c metrics/metrics.c -o metrics/metrics.o  -I historicsToDraw/


gcc -g main.c queue/queue.c historicsToDraw/historicsToDraw.c metrics/metrics.c srt/srt.c Fifo/fifo.c lifo/lifo.c multilevelWithDynamicPriority/multilevelWithDynamicPriority.c priority/priority.c sjf/sjf.c rr/rr.c multilevel/multilevel.c -o 3AM `pkg-config --cflags --libs gtk+-3.0` -lm -I queue/ -I historicsToDraw/ -I metrics/ 

./3AM 
# 3AM come from (aimen angham anas and mouhib)

# for debugging :  valgrind --leak-check=full ./3AM

