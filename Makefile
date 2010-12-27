CC 				= gcc
ECHO			= echo
CFLAGS 		= -std=c99 -fnested-functions -Wall
LFLAGS  	= -ll
TARGET 		= lambda
SRC 			= main.c
OBJ 			= ${SRC:.c=.o}

test: strip
	@${ECHO} "[TEST]\t$(TARGET)"
	@./$(TARGET)

strip: $(TARGET)
	@${ECHO} "[STRIP]\t$(TARGET)"
	@${STRIP} $(TARGET)

$(TARGET): $(OBJ)
	@${ECHO} "[LINK]\t$(TARGET)"
	@${CC} ${CFLAGS} ${OBJ} -o $(TARGET) $(LFLAGS)

%.o: %.c
	@${ECHO} "[CC]\t$<"
	@${CC} -c ${CFLAGS} -o $@ $<

clean:
		@rm -f $(TARGET) $(OBJ)