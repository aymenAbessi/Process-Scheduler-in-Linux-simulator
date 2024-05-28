CC=gcc
CFLAGS=-Iqueue -IhistoricsToDraw -pthread -I/usr/include/gtk-3.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/harfbuzz -I/usr/include/pango-1.0 -I/usr/include/fribidi -I/usr/include/harfbuzz -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/uuid -I/usr/include/freetype2 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/libpng16 -I/usr/include/x86_64-linux-gnu -I/usr/include/libmount -I/usr/include/blkid -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -g
LIBS=`pkg-config --cflags --libs gtk+-3.0` -lm

all: 3AM
# 3AM come from (aimen angham anas and mouhib)

queue/queue.o: queue/queue.c
	$(CC) -c queue/queue.c -o queue/queue.o

historicsToDraw/historicsToDraw.o: historicsToDraw/historicsToDraw.c
	$(CC) -c historicsToDraw/historicsToDraw.c -o historicsToDraw/historicsToDraw.o

sjf/sjf.o: sjf/sjf.c queue/queue.h historicsToDraw/historicsToDraw.h
	$(CC) -c sjf/sjf.c -o sjf/sjf.o $(CFLAGS)

lifo/lifo.o: lifo/lifo.c queue/queue.h historicsToDraw/historicsToDraw.h
	$(CC) -c lifo/lifo.c -o lifo/lifo.o $(CFLAGS)

multilevelWithDynamicPriority/multilevelWithDynamicPriority.o: multilevelWithDynamicPriority/multilevelWithDynamicPriority.c queue/queue.h historicsToDraw/historicsToDraw.h
	$(CC) -c multilevelWithDynamicPriority/multilevelWithDynamicPriority.c -o multilevelWithDynamicPriority/multilevelWithDynamicPriority.o $(CFLAGS)


rr/rr.o: rr/rr.c queue/queue.h historicsToDraw/historicsToDraw.h
	$(CC) -c rr/rr.c -o rr/rr.o $(CFLAGS)

multilevel/multilevel.o: multilevel/multilevel.c queue/queue.h historicsToDraw/historicsToDraw.h
	$(CC) -c multilevel/multilevel.c -o multilevel/multilevel.o $(CFLAGS)

srt/srt.o: srt/srt.c queue/queue.h historicsToDraw/historicsToDraw.h
	$(CC) -c srt/srt.c -o srt/srt.o $(CFLAGS)

priority/priority.o: priority/priority.c queue/queue.h historicsToDraw/historicsToDraw.h
	$(CC) -c priority/priority.c -o priority/priority.o $(CFLAGS)

Fifo/fifo.o: Fifo/fifo.c queue/queue.h historicsToDraw/historicsToDraw.h
	$(CC) -c Fifo/fifo.c -o Fifo/fifo.o $(CFLAGS)

metrics/metrics.o: metrics/metrics.c historicsToDraw/historicsToDraw.h
	$(CC) -c metrics/metrics.c -o metrics/metrics.o $(CFLAGS)


3AM: main.o queue/queue.o historicsToDraw/historicsToDraw.o multilevel/multilevel.o priority/priority.o lifo/lifo.o multilevelWithDynamicPriority/multilevelWithDynamicPriority.o srt/srt.o sjf/sjf.o rr/rr.o Fifo/fifo.o metrics/metrics.o
	$(CC) -g main.o queue/queue.o historicsToDraw/historicsToDraw.o priority/priority.o multilevel/multilevel.o rr/rr.o srt/srt.o lifo/lifo.o multilevelWithDynamicPriority/multilevelWithDynamicPriority.o sjf/sjf.o Fifo/fifo.o metrics/metrics.o -o 3AM $(LIBS)

main.o: main.c queue/queue.h historicsToDraw/historicsToDraw.h srt/srt.h lifo/lifo.h sjf/sjf.h multilevelWithDynamicPriority/multilevelWithDynamicPriority.h Fifo/fifo.h metrics/metrics.h
	$(CC) -c main.c -o main.o $(CFLAGS)


run: 3AM
	./3AM

# Rule to run the compiled program with valgrind for debugging
debug: 3AM
	valgrind --leak-check=full ./3AM

# Clean command to remove generated files
clean:
	rm -f main.o queue/queue.o historicsToDraw/historicsToDraw.o multilevel/multilevel.o priority/priority.o lifo/lifo.o multilevelWithDynamicPriority/multilevelWithDynamicPriority.o srt/srt.o sjf/sjf.o rr/rr.o Fifo/fifo.o metrics/metrics.o 3AM
