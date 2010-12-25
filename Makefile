CC 				= gcc
ECHO			= echo
CFLAGS 		= -std=c99 -fnested-functions -Wall
LFLAGS  	= -ll
TARGET 		= lambda
SRC 			= main.c
OBJ 			= ${SRC:.c=.o}

$(TARGET): $(OBJ)
	@${ECHO} "[LINK]\t$(TARGET)"
	@${CC} ${CFLAGS} ${OBJ} -o $(TARGET) $(LFLAGS)
	@${STRIP} $(TARGET)

%.o: %.c
	@${ECHO} "[GCC]\t$<"
	@${CC} -c ${CFLAGS} -o $@ $<

test:
	./$(TARGET)

clean:
		@rm -f $(TARGET) $(OBJ)