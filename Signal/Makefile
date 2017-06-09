.PHONY:all
all:Signal Kill_Sig Alarm_Sig Block_Sig Pend_Sig RePend_Sig

Signal:Signal.c
	gcc -o $@ $^
Kill_Sig:Kill_Sig.c
	gcc -o $@ $^
Alarm_Sig:Alarm_Sig.c
	gcc -o $@ $^
Block_Sig:Block_Sig.c
	gcc -o $@ $^
Pend_Sig:Pend_Sig.c
	gcc -o $@ $^
RePend_Sig:RePend_Sig.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm -rf Signal Kill_Sig Alarm_Sig Block_Sig Pend_Sig RePend_Sig
