int sum(int *arr, int n)
{
	int i, sum;

	for(i=0, sum=0; i < n; i++)
	{
		sum += arr[i];
	}	
	return sum;
}
