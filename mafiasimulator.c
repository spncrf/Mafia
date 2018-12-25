/* This program calculates the likelihood that Town or Mafia will win given random conditions and no PRs */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int numMafia;
int numTown;
int total;
int iterations = 9000000;

int choose(int min, int max)
{
    int range, result, cutoff;
 
    if (min >= max)
        return min; // only one outcome possible, or invalid parameters
    range = max-min+1;
    cutoff = (RAND_MAX / range) * range;
 
    // Rejection method, to be statistically unbiased.
    do {
        result = rand();
    } while (result >= cutoff);
 
    return result % range + min;
}

void dayphase (){
	int lynch = choose(1, total);
	if (lynch <= numMafia){
		numMafia--;
	}
	else {
		numTown--;
	}
	return;
}

void nightphase(){
	numTown--;
	return;
}

int checkWinTown(){
	if (numMafia == 0){
		return 1;
	}
	return 0;
}

int checkWinMafia(){
	if (numTown <= numMafia){
		return 1;
	}
	return 0;
}

int beginGame(int Mafia, int Town) {
	numMafia = Mafia;
	numTown = Town;
	while (1){
		total = numMafia + numTown;
		dayphase();
		if(checkWinTown()==1)return 1;
		if(checkWinMafia()==1)return 0;
		nightphase();
		if(checkWinMafia()==1)return 0;
	}
}
		
int main () {
	int outcome;
	int MafiaTotal = 0;
	int TownTotal = 0;
	int Mafia, Town;
	srand(time(NULL));
	printf("How many Mafia members?\n");
	scanf("%d", &Mafia);
	printf("How many Town members?\n");
	scanf("%d", &Town);
	for(int i = 0; i < iterations; i++) {
		outcome = beginGame(Mafia, Town);
		if (outcome == 0){
			MafiaTotal++;
		}
		else {
			TownTotal++;
		}
	}
	double Townpercent = (double)TownTotal/((double)iterations/(100));
	double Mafiapercent = (double)MafiaTotal/((double)iterations/(100));
	printf("After %d iterations: \n", iterations); 
	printf("Town wins: %.2f%%\n", Townpercent);
	printf("Mafia wins: %.2f%%\n", Mafiapercent);
	return 0;
}
