#!/bin/bash

# bear -- \
# 	gcc src/*.c -I include -Wall -Wextra -o game \
# 		-lraylib -lGL -lm -lpthread -ldl -lrt -lX11

if [ $1 -eq 1 ]; then
	bear -- \
		gcc src/*.c src/map/*.c src/entities/*.c -I include -Wall -Wextra -ggdb3 -fsanitize=address,undefined -o bin/game \
			-lraylib -lGL -lm -lpthread -ldl -lrt -lX11
else
	bear -- \
		gcc src/*.c src/map/*.c src/entities/*.c -I include -Wall -Wextra -fsanitize=address,undefined -o bin/game \
			-lraylib -lGL -lm -lpthread -ldl -lrt -lX11
fi
