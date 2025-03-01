#include<stdio.h>

void subsets(int arr[],int current[],int c_size,int index,int c_sum,int target,int n,int best[],int* best_n,int* max_prod){
	if(c_sum==target){
		int prod=1;
		for(int i=0;i<c_size;i++){
			prod*=current[i];
		}
		if(prod>*max_prod){
			*max_prod= prod;
			*best_n = c_size;
			for(int i=0;i<*best_n;i++){
				best[i]=current[i];
			}
		}
	}
	if(index>=n||c_sum>target)
		return;
	subsets(arr,current,c_size,index+1,c_sum,target,n,best,best_n,max_prod);
	current[c_size]=arr[index];
	subsets(arr,current,c_size+1,index+1,c_sum+arr[index],target,n,best,best_n,max_prod);
}
void maxsubarray(int arr[],int target, int n){
	int current[n],best[n];
	int best_n=0;
	int max_prod =0;
	subsets(arr,current,0,0,0,target,n,best,&best_n,&max_prod);	
	if(best_n==0){
		printf("No subset exists.");
	}
	else{
		printf("Subset with the maximum product is: \n");
		printf("\n");
		printf("{");
		for(int i=0;i<best_n;i++){
			printf("%d",best[i]);
			if(i!=best_n-1){
				printf(", ");
			}
		}
		printf("}\n");
	}
}


int main(){
	int n,target;
	printf("Enter the number of elements: ");
	scanf("%d",&n);
	int arr[n];
	printf("Enter the elements of the array: ");
	for(int i=0;i<n;i++){
		scanf("%d",&arr[i]);
	}
	printf("Enter the target sum: ");
	scanf("%d",&target);
	maxsubarray(arr,target,n);
	return 0;
}
