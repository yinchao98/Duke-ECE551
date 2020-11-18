test: test.cpp category.h rand_story.h rand_story.cpp 
	g++ -o test -ggdb3 -Wall -Werror -pedantic -std=gnu++98 test.cpp category.h rand_story.h rand_story.cpp
