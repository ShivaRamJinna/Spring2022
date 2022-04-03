#include<stdio.h>
int main(int argc, char const *argv[])
{
	//Initializing the Variables 
	int NumberofElements, TempHigh, keyElement;
	//input for Number of elements
	scanf("%d",&NumberofElements);
	int Unsorted_Array[NumberofElements];
	printf("Enter %d Elements.\n", NumberofElements);

	
	// Caputring Input Elements
	for(int i=0;i<NumberofElements;i++)
	{
		scanf("%d", &Unsorted_Array[i]);
	}



	// Insertion Sort //
	for (int i = 1; i < NumberofElements; i++)
	{
		TempHigh=Unsorted_Array[i];
		keyElement=i-1;
		while((TempHigh<Unsorted_Array[keyElement])&&(keyElement>=0)) 
		{
			Unsorted_Array[keyElement+1]=Unsorted_Array[keyElement];
			keyElement-=1;
		}
		Unsorted_Array[keyElement+1]=TempHigh;

	}

	//Printing Sorted Array
	printf("Sorted Array: ");
    for(int i=0;i<NumberofElements;i++)
    {
    	printf(" %d",Unsorted_Array[i]);
	}
	return 0;
}