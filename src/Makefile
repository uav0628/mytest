# MakeFile
mymain: main.o func.o debug.o #ターゲット: 依存ファイル
	g++ -Wall -o mymain main.o func.o debug.o -lpthread #実行コマンド

main.o: main.cpp func.h debug.h
	g++ -Wall -c main.cpp #実行コマンド

func.o: func.cpp func.h debug.h
	g++ -Wall -c func.cpp #実行コマンド

debug.o: debug.cpp debug.h
	g++ -Wall -c debug.cpp #実行コマンド

clean:
	rm -f *.o mymain
