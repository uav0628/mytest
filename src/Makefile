# MakeFile
mymain: main.o func.o debug.o network.o pipe.o #ターゲット: 依存ファイル
	g++ -Wall -o mymain main.o func.o debug.o network.o pipe.o -lpthread #実行コマンド

main.o: main.cpp func.h debug.h
	g++ -Wall -c main.cpp #実行コマンド

func.o: func.cpp func.h debug.h
	g++ -Wall -c func.cpp #実行コマンド

debug.o: debug.cpp debug.h
	g++ -Wall -c debug.cpp #実行コマンド

network.o: network.cpp network.h
	g++ -Wall -c network.cpp #実行コマンド

pipe.o: pipe.cpp pipe.h
	g++ -Wall -c pipe.cpp #実行コマンド

clean:
	rm -f *.o mymain
