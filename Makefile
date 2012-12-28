CC = gcc

CFLAGS = -Wno-unused-parameter `pkg-config gtk+-3.0 webkitgtk-3.0 libnotify --cflags`

LDFLAGS = `pkg-config gtk+-3.0 webkitgtk-3.0 libnotify --libs`

SRCS = pengap.c main.c

OBJS = $(SRCS:.c=.o)

MAIN = pengap

all: pengap.js.h $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $(MAIN)

pengap.js.h:
	xxd -i pengap.js > pengap.js.h

.cpp.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f pengap.js.h $(OBJS) $(MAIN)
