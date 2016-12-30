#include <stdio.h>
#include <stdlib.h>

typedef struct item_struct{
	int value;
	int weight;
} item;

item* deleteThis (item* itemsGiven, item* newItems, int index, int numItems){
	//printf("delete this numItems = %d\n", numItems);
	for(int i = 0; i < index; i++){
		newItems[i] = itemsGiven[i];
	}
	for(int i = index; i < numItems; i++){
		newItems[i] = itemsGiven[i+1];
	}
	return newItems;
}

int perm(item* items, int capacity, int numItems){
	int bestValue = 0;
	for(int i = 0; i < numItems; i++){
		if(capacity >= items[i].weight){
			item* newItems = (item*) malloc((numItems - 1)  * sizeof(item*));
			newItems = deleteThis(items, newItems, i, numItems);
			int value = perm(newItems, capacity - items[i].weight, numItems - 1);
			//free(newItems);
			if(value + items[i].value > bestValue){
				bestValue = value + items[i].value;
				//printf("max value = %d\n",bestValue);
			}
		}
	}
	return bestValue;
}

void getInput(){
	int bagSize = 0;
	int numItems = 0;

	printf("Enter the maximum amount of weight that your bag can hold: ");
	scanf("%d", &bagSize);
	printf("Enter the number of items that are in the jewelry store: ");
	scanf("%d", &numItems);
	
	item* itemInput = (item*) malloc(numItems * sizeof(item*));
	item a;

	printf("Enter your items, one per line (value weight): \n");
	for(int i = 0; i < numItems; i++){
		if(i == 0){
			scanf("%d %d", &a.value, &a.weight);
		}		
		else {
			scanf(" %d %d", &a.value, &a.weight);
		}
		itemInput[i] = a;
	}
	int maxTheft = perm(itemInput, bagSize, numItems);
	printf("They most profitable heist will net you $%d in total.\n", maxTheft);
	free(itemInput);
}


int main(){

	getInput();

	return 0;
}