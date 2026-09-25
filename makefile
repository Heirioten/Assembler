assembler: assembler.o symbolTree.o parser.o linkedList.o aInstructions.o cInstructions.o
	gcc -g -o assembler assembler.o symbolTree.o parser.o linkedList.o aInstructions.o cInstructions.o

assembler.o: assembler.c
	gcc -g -c assembler.c

testing: testing.o symbolTree.o parser.o linkedList.o aInstructions.o cInstructions.o
	gcc -g -o testing testing.o symbolTree.o parser.o linkedList.o aInstructions.o cInstructions.o

testing.o: testing.c
	gcc -g -c testing.c

symbolTree.o: Symbol_Tree/symbolTree.c
	gcc -g -c Symbol_Tree/symbolTree.c

linkedList.o: Linked_List/linkedList.c
	gcc -g -c Linked_List/linkedList.c

parser.o: Parser/parser.c
	gcc -g -c Parser/parser.c

aInstructions.o: Instruction_Sets/A_Instructions/aInstructions.c
	gcc -g -c Instruction_Sets/A_Instructions/aInstructions.c

cInstructions.o: Instruction_Sets/C_Instructions/cInstructions.c
	gcc -g -c Instruction_Sets/C_Instructions/cInstructions.c

clean:
	rm -f testing assembler *.o