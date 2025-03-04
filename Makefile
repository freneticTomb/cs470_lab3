#define the c compiler to user
CC=gcc

#define any compile-time flag
CFLAGS=-Wall -g

# Define target executables
TARGETS = sjf rr

all: $(TARGETS)

# Build SJF executable
sjf: SFJ_initial.c
	$(CC) $(CFLAGS) -o sjf SFJ_initial.c

# Build RR executable
rr: RR_inital.c
	$(CC) $(CFLAGS) -o rr RR_inital.c


