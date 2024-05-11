/*
 * GeneralMath.c
 *
 *  Created on: Jan 28, 2024
 *      Author: user
 */



#include "main.h"

int binarySearch(float arr[], int leftIndex, int rightIndex, float valueToSearchFor)
{
	if (arr[leftIndex] < valueToSearchFor)
	{
		return -1;
	}
	if (arr[rightIndex] > valueToSearchFor)
	{
		return 999;
	}

	int previousM = 0;
    while (leftIndex <= rightIndex)
    {
        int m = leftIndex + (rightIndex - leftIndex) / 2;
        if (previousM == m)
        {
        	m = previousM + 1;
        }
        // Check if valueToSearchFor is present at mid
        if ( (arr[m -1] >= valueToSearchFor) && (arr[m] <= valueToSearchFor) )
        {
            return m;
        }

        // If valueToSearchFor greater, ignore left half
        if (arr[m] < valueToSearchFor)
        {
            rightIndex = m;
        }

        // If valueToSearchFor is smaller, ignore right half
        else if (arr[m - 1] > valueToSearchFor)
        {
            leftIndex = m - 1;
        }
        previousM = m;
    }

    // If we reach here, then element was not present

    return -1;
}
