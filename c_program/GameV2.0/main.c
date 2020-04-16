#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>
#include<unistd.h>
#include<stdbool.h>

bool s_Finished=false;

//player01 is Using Binary search Method to guess the number.
void* player01(void *arg) {
	int minNum = 1;
	int maxNum = 100;
	int *Num = (int*) arg;
	int turns = 1;
	int pguess;
	while (!s_Finished) {
		usleep(1000);
		int guess = maxNum + minNum - 1;
		pguess = (int) ceil(guess / 2.0); //possible guess by dividing the maximum range by 2
		printf("Guess by Player-01 = %d in %d turns \n", pguess, turns);

		if (pguess < *Num)
			minNum = pguess + 1;
		else if (pguess > *Num)
			maxNum = pguess - 1;
		else if (pguess == *Num) {
		   s_Finished=true;
			printf("Congratulation! PLAYER-01 WON the GAME!:)");
			break;
		}

		turns++;
	}

	return NULL;

}

//Here Player02 is Using Liner Search Method to Guess the Number
void* player02(void *arg) {
	int *Num1 = (int*) arg;
	int i = 1;
	while (!s_Finished) {
		usleep(1000);
		if (i != *Num1)
			printf("Guess by Player-02 = %d in %d turns \n ", i, i);

		else if (i == *Num1) {
		    s_Finished=true;
			printf("Guess by Player-02 = %d in %d turns \n ", i, i);
			printf("Congratulation! PLAYER-02 WON the GAME!:)");
			break;
		}
		i++;
	}

	return NULL;
}

//Here Player03 Using Random Number to Guess the Number.
void* player03(void *arg) {
	int *Num2 = (int*) arg;
	int turns = 1;
	int random_x;
	srand(time(NULL));

	while (!s_Finished) {
		usleep(1000);
		random_x = rand() % 100;
		printf("Guess by Player-03 = %d in %d turns \n ", random_x, turns);
		if (random_x == *Num2) {
		    s_Finished=true;
			printf("Congratulation! PLAYER-03 WON the GAME!:)");
			break;
		}
		turns++;
	}

	return NULL;
}

int main() {
	int UsrNum;

	printf(
			"*********************************************************************** \n");
	printf(
			"**                    Welcome To Guessing Game                       ** \n");
	printf(
			"*********************************************************************** \n \n");
	printf("PLEASE, Enter any NUMBER between 1 to 100 : - ");
	scanf("%d", &UsrNum);

	//pthread for Binary Search
	pthread_t mythread;
	//second pthread to Linear Search Method
	pthread_t secondthread;
	//third thread to Jump search Method

	pthread_t thirdthread;
	if (pthread_create(&mythread, NULL, player01, &UsrNum) != 0) {
		printf("Failed to create the thread\n");
		return 1;
	}
	if (pthread_create(&secondthread, NULL, player02, &UsrNum) != 0) {
		printf("Failed to create the thread\n");
		return 1;
	}
	if (pthread_create(&thirdthread, NULL, player03, &UsrNum) != 0) {
		printf("Failed to create the thread\n");
		return 1;
	}

	pthread_join(mythread, NULL);
	pthread_join(secondthread, NULL);
	pthread_join(thirdthread, NULL);

	return 0;
}
