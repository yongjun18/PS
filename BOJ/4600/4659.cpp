#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;

char str[25];

int isVowel(char c) {
	for (int i = 0; i < 5; i++) {
		if (c == "aeiou"[i]) {
			return 1;
		}
	}
	return 0;
}

int includesVowel() {
	for (int i = 0; str[i]; i++) {
		if (isVowel(str[i])) {
			return 1;
		}
	}
	return 0;
}

int notThreeConsec() {
	int vowel = 0;
	int conson = 0;

	for (int i = 0; str[i]; i++) {
		if (isVowel(str[i])) {
			vowel++;
			conson = 0;
		}
		else {
			vowel = 0;
			conson++;
		}
		if (vowel >= 3 || conson >= 3) {
			return 0;
		}
	}
	return 1;
}

int notTwoConsec() {
	for (int i = 1; str[i]; i++) {
		if (str[i - 1] == str[i]) {
			if (str[i] != 'e' && str[i] != 'o') {
				return 0;
			}
		}
	}
	return 1;
}

int main()
{
	while (true) {
		scanf("%s", str);
		if (strcmp(str, "end") == 0) {
			break;
		}

		if (includesVowel() && notThreeConsec() && notTwoConsec()) {
			printf("<%s> is acceptable.\n", str);
		}
		else {
			printf("<%s> is not acceptable.\n", str);
		}
	}
	return 0;
}
