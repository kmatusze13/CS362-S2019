CFLAGS= -Wall -fpic -coverage -lm -std=c99

default: tests.out

tests.out: randomtestcard1.c    randomtestcard2.c       randomtestadventurer.c
        echo "randomtestcard1.c:" >> tests.out
        gcc -o randomtestcard1  randomtestcard1.c $(CFLAGS)
        ./randomtestcard1 >> tests.out
        gcov bst.c >> tests.out
        echo "randomtestcard2.c:" >> tests.out
        gcc -o randomtestcard2  randomtestcard2.c $(CFLAGS)
        ./randomtestcard2 >> tests.out
        gcov bst.c >> tests.out
        echo "randomtestadventurer.c:" >> tests.out
        gcc -o randomtestadventurer.c  randomtestadventurer.c $(CFLAGS)
        ./randomtestadventurer >> tests.out
        gcov bst.c >> tests.out

clean:
        rm tests.out

cleanall: 
        rm tests.out randomtestcard1 randomtestcard2 randomtestadventurer  *.gcda *.gcno *.gcov
