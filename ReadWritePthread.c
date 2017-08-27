//creating read/write Pthreads example 

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

#define NUM_READ_THREADS   5
#define NUM_WRITE_THREADS 5

int shared_variable=15;
int count=0;
int num;

//intializing Pthreads
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t rea = PTHREAD_COND_INITIALIZER;
pthread_cond_t writ = PTHREAD_COND_INITIALIZER;

void *writePhase (void *writearg);
void *readPhase (void *readarg);

int main(int argc, char*argv[]){
	time_t t;
	
	srand((unsigned) time(&t));
	
	num=(rand()%10);
	
	pthread_t rthread[NUM_READ_THREADS];
	pthread_t wthread[NUM_WRITE_THREADS];
	int i,j;
	int rThreadid[NUM_READ_THREADS];
	int wThreadid[NUM_WRITE_THREADS];
	
	
	for(i=0;i<NUM_READ_THREADS;i++){
		rThreadid[i]=i;
		pthread_create(&rthread[i],NULL,readPhase,&rThreadid[i]);
	}
	
	for(j=0;j<NUM_WRITE_THREADS;j++){
		wThreadid[j]=j;
		pthread_create(&wthread[j],NULL,writePhase,&wThreadid[j]);
	}
	for(i=0;i<NUM_READ_THREADS;i++){
		pthread_join(rthread[i],NULL);
	}

	for(i=0;i<NUM_WRITE_THREADS;i++){
		pthread_join(wthread[i],NULL);
	}
	
	return 0;
	//exit(1);

}

void *writePhase (void *writearg)
{
	sleep(num);
	
	while(count>0){
		pthread_cond_wait(&writ,&m);
	}
	printf("came till here\n");
	if(count==5){
		
		pthread_mutex_lock(&m);
		shared_variable+=1;
		printf("value written:%d\n",shared_variable);
		printf("Remaining Reads:%d\n",(5-count));
		pthread_mutex_unlock(&m);
		pthread_cond_signal(&rea);
		
		
	}
	
	return 0;
}
void *readPhase (void *readarg)
{
	sleep(num);
	while(count>4){
		pthread_cond_wait(&rea,&m);
	}
	
	pthread_mutex_lock(&m);
	
	while(count>=0 && count<5){ 
		printf("Remaining Reads:%d\n",abs(5-(count+1)));
		if(count<NUM_READ_THREADS){
			count=count+1;
		}
	}
	pthread_mutex_unlock(&m);
	
	if(count==5){
		pthread_cond_signal(&writ);
		
	}
	
	return 0;	
}


