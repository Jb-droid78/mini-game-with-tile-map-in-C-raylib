#!/bin/bash

if [ $1 == "run" ]; then 
	bear -- \
		gcc src/*.c src/map/*.c src/entities/*.c -I include -Wall -Wextra -fsanitize=address,undefined -o bin/game \
			-lraylib -lGL -lm -lpthread -ldl -lrt -lX11 && ./bin/game
elif [ $1 == "debug" ]; then
	bear -- \
		gcc src/*.c src/map/*.c src/entities/*.c -I include -Wall -Wextra -ggdb3 -fsanitize=address,undefined -o bin/game_debug \
		-lraylib -lGL -lm -lpthread -ldl -lrt -lX11
else
	echo "debug or run?"
fi	

# bear -- \
# 	gcc src/*.c src/map/*.c src/entities/*.c -I include -Wall -Wextra -ggdb3 -fsanitize=address,undefined -o bin/game \
# 		-lraylib -lGL -lm -lpthread -ldl -lrt -lX11
