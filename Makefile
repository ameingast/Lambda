CC 				= gcc
ECHO			= echo
CFLAGS 		= -std=c99 -fnested-functions -Wall
LFLAGS  	= -ll
TARGET 		= lambda
SRC 			= main.c
OBJ 			= ${SRC:.c=.o}

test: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJ)
	@${ECHO} "[LINK]\t$(TARGET)"
	@${CC} ${CFLAGS} ${OBJ} -o $(TARGET) $(LFLAGS)
	@${STRIP} $(TARGET)

%.o: %.c
	@${ECHO} "[GCC]\t$<"
	@${CC} -c ${CFLAGS} -o $@ $<

clean:
		@rm -f $(TARGET) $(OBJ)