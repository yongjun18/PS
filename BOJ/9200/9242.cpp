#include <bits/stdc++.h>
using namespace std;

char digit[20][20] = {
	"**** ** ** ****",
	"  *  *  *  *  *",
	"***  *****  ***",
	"***  ****  ****",
	"* ** ****  *  *",
	"****  ***  ****",
	"****  **** ****",
	"***  *  *  *  *",
	"**** ***** ****",
	"**** ****  ****"
};

char str[5][45];

int get_digit(int x){
	for(int k=0; k<=9; k++){
		int tmp, ok;
		
		ok = 1;
		tmp = 0;
		for(int i=0; i<5; i++){
			for(int j=0; j<3; j++){
				if(digit[k][tmp] != str[i][j+x]){
					ok = 0;
					break;
				}
				tmp++;
			}
		}
		if(ok) return k;
	}
	return -1;
}

int main() {
	int ok;
	int num;
	
	for(int i=0; i<5; i++){
		fgets(str[i], 40, stdin);
	}
	
	ok = 1;
	num = 0;
	for(int i=0; true; i+=4){
		if(str[0][i] != '*' && str[0][i] != ' ') break;
		
		int res = get_digit(i);
		if(res == -1){
			ok = 0;
			break;
		}
		num *= 10;
		num += res;
	}
	
	if(ok == 0 || num % 6 != 0){
		printf("BOOM!!\n");
	}
	else printf("BEER!!\n");
	
	return 0;
}
