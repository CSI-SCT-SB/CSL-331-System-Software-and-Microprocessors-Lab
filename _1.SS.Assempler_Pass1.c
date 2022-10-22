#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main()
{
	printf("\nPASS 1 OF A TWO PASS ASSEMBLER\n");
	printf("-----------------------------------\n");
	int locctr,start,length,flag=0,len,err=1,c=0;
	char opcode[10],label[10],operand[10],code[10],mnemonic[10],l[10];
	
	FILE *fp1,*fp2,*fp3,*fp4;
	fp1 = fopen("input.txt","r");
	fp2 = fopen("optab.txt","r");
	fp3 = fopen("symtab.txt","w+");
	fp4 = fopen("intermediate.txt","w");

	fscanf(fp1,"%s\t%s\t%s",label,opcode,operand);
	if(strcmp(opcode,"START")==0)
	{
		start = atoi(operand);
		locctr = start;
		fprintf(fp4,"\t%s\t%s\t%s\n",label,opcode,operand);
		fscanf(fp1,"%s\t%s\t%s",label,opcode,operand);
	}
	else
		locctr = 0;

	while(strcmp(opcode,"END")!=0)
	{
    flag = 0;
		fprintf(fp4,"%d\t",locctr);
		if(strcmp(label,"**")!=0)      //searching symtab for label
		{
			fseek(fp3,0,SEEK_SET);
			fscanf(fp3,"%s\n",l);
			
			while(!feof(fp3))
			{
				if(strcmp(label,l)==0)
				{
					break;
					err=0;				
				}
				//else
				fscanf(fp3,"%s\n",l);
			}
			fseek(fp3,0,SEEK_END);
			if(err==1)
				fprintf(fp3,"%s\t%d\n",label,locctr);
			//fprintf(fp3,"%s\t%d\n",label,locctr);
		}
		fscanf(fp2,"%s\t%s",code,mnemonic);
		while(strcmp(code,"END")!=0)
		{
			
			if(strcmp(code,opcode)==0)
			{
				locctr+=3;
				flag =1;
				break;
			}
			fscanf(fp2,"%s\t%s",code,mnemonic);
		}	
			if(strcmp(opcode,"WORD")==0)
			{
				flag=1;
				locctr+=3;
			}
			else if(strcmp(opcode,"RESW")==0)
			{
				flag=1;
				locctr+=(3*(atoi(operand)));
			}
			else if(strcmp(opcode,"RESB")==0)
			{
				flag=1;
				locctr+=(atoi(operand));
			}
			else if(strcmp(opcode,"BYTE")==0)
			{
				flag=1;
				len=strlen(operand)-2;
				locctr+=len;
			}
			
			else if(flag==0)
			{
				printf("\nERROR!..OPCODE '%s' NOT FOUND!\n",opcode);
				break;
			}
			
		
		fprintf(fp4,"\t%s\t%s\t%s\n",label,opcode,operand);
		fscanf(fp1,"%s\t%s\t%s",label,opcode,operand);		
		
	}
	fprintf(fp4,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
	length = locctr- start;
	printf("\nLength of the program is %d\n",length);

	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
}

// INPUT.txt
// **  START  2000
// **  LDA  FIVE
// **  STA  ALPHA
// **  LDCH  CHARZ
// **  STCH  C1
// ALPHA  RESW  2
// FIVE  WORD  5
// CHARZ  BYTE  C'Z'
// C1  RESB  1
// BETA  MULL  K
// *  END  *

// OPTAB.txt
// START  *
// LDA  03
// STA  0f
// LDCH  53
// STCH  57
// END  *
