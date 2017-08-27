//create PThread 
#include<stdio.h>
#include<pthread.h>
#define NumTHREADS 2

//create a function that is to be executed by the thread

void *hello (void *arg){ 
	int *j= (int*)arg;
	int num =*j;
	printf("Thread Number:%d\n",num); //assigning thread numbers
	printf("Hello World\n");
	return 0;
}
int main(){
	
	int i;
	int ThreadId[NumTHREADS];
	//declare thread
	pthread_t thread[NumTHREADS];
	//create thread
	for(i=0;i<NumTHREADS;i++){
		ThreadId[i]=i;
		pthread_create(&thread[i],NULL,hello,&ThreadId[i]); 

//pthread_create(thread,attribute,function or routine, arg to the							                          routine);	
	//if ThreadId is not given and i is directly used then there occur data race condition where when one threads reads i other thread modifies 	i which results in wrong thread number. so to avoid the thread id is stored in a temp variable so it doesnt change.	
												
	}
	//join thread after executing the routine
	for(i=0;i<NumTHREADS;i++){
		pthread_join(thread[i],NULL); //pthread_join(thread,void *status(status to be returned from the routine. here NULL))
	}
	return 0;


}
	

