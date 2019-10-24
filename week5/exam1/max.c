int max(int *arr, int n)
{
	int i, max;

	for(i=1, max=arr[0]; i < n; i++)
	{
		if(max < arr[i])
		{
			max = arr[i];
		}
	}	
	return max;
}
