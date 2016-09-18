#include <iostream>
#include <semaphore.h>
#include <pthread.h>
using namespace std;

const int BUF_SIZE=1024;
sem_t mutex,slots,items;

void* Producer(void* p)
{
	while(1)
	{
		sem_wait(&slots);
		sem_wait(&mutex);
		cout<<"Producer Lock--- ";
		cout<<"producing";
		cout<<" ---Producer Unlock"<<endl;
		sem_post(&mutex);
		sem_post(&items);
	}
}
void *Consumer(void* p)
{
	while(1)
	{
		sem_wait(&items);
		sem_wait(&mutex);
		cout<<"Consumer Lock--- ";
		cout<<"Consuming";
		cout<<" ---Consumer Unlock"<<endl;
		sem_post(&mutex);
		sem_post(&slots);	
	}
}
int main()
{
	sem_init(&mutex,0,1);
	sem_init(&items,0,0);
	sem_init(&slots,0,BUF_SIZE);

	pthread_t pid[2];

	pthread_create(&pid[0],NULL,Consumer,NULL);
	pthread_create(&pid[1],NULL,Producer,NULL);

	for(int i=0;i<2;++i)
	{
		pthread_join(pid[i],NULL);
	}
	return 0;
}
