#include <iostream>
#include <time.h>
#include <vector>
#include <unistd.h>  
#include <sys/types.h>  
#include <stdio.h>  
#include <stdlib.h>
#include <pthread.h>   
#include <x86intrin.h>

using namespace std;
/*
static inline uint64_t rdtsc(){
    unsigned int lo,hi;
    __asm__ __volatile__ ("cpuid");
    __asm__ __volatile__ ("rdtsc");

    __asm__ __volatile__ ("mov %%edx, %0\n\t"
 "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
"%rax", "%rbx", "%rcx", "%rdx");
    return ((uint64_t)hi << 32) | lo;
}*/

static inline uint64_t rdtsc(){
	unsigned int cycles_high, cycles_low;
	asm volatile ("CPUID\n\t"
		"RDTSC\n\t"
		"mov %%edx, %0\n\t"
		"mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::"%rax", "%rbx", "%rcx", "%rdx");
	return ((uint64_t)cycles_high << 32) | cycles_low;
}

/*
static inline uint64_t rdtscp(){
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtscp" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}*/

static inline uint64_t rdtscp(){
	unsigned int cycles_high1, cycles_low1;
	asm volatile("RDTSCP\n\t"
		"mov %%edx, %0\n\t"
		"mov %%eax, %1\n\t"
		"CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
		"%rax", "%rbx", "%rcx", "%rdx");
	return ((uint64_t)cycles_high1 << 32) | cycles_low1;
}

void* myThread(void* args){return NULL;}

void read_from_pipe (int file){
	FILE *stream;
	int c;
	stream = fdopen (file, "r");
	//while ((c = fgetc (stream)) != EOF)
		//putchar (c);
	fclose (stream);
 }

 void write_to_pipe (int file)
 {
	FILE *stream;
	stream = fdopen (file, "w");
	//fprintf (stream, "hello, world!\n");
	//fprintf (stream, "goodbye, world!\n");
	fclose (stream);
 }


int main(){

	rdtsc();
	rdtscp();

	// measure CPU frequency
	/*
	uint64_t start,end;
	int dur = 1;
	start = rdtsc();
	sleep (dur);
	end = rdtscp();
	cout << end-start << endl;*/
	
	// measure process creation overhead
	/*
	uint64_t start,end;
	start = __rdtsc();
	pid_t pid = fork();
	if (pid < 0)
	   cout << "error" <<endl;
	else if (pid == 0)
		exit(0);
	else{
		
		wait(NULL);
		end = __rdtsc();
		//cout << pid << endl;
		cout << end-start << endl;
	}
	*/
	

	// measure sys call overhead
	/*
	uint64_t start,end;
	for (int i=0;i<10;++i){
		pid_t pid = fork();
		if (pid < 0)
		   cout << "error" <<endl;
		else if (pid == 0){
			start = rdtsc();
			getpid();
			end = rdtscp();
			int id = getpid();
			cout << "child("<<id<<"): "<<end-start << endl;
			exit(0);
		}
		else{
			wait(NULL);
			start = rdtsc();
			getpid();
			end = rdtscp();
			int id = getpid();
			cout << "parent("<<id<<"): "<<end-start << endl;
		}
	}*/

	// measure thread creation overhead
	/*
	uint64_t start,end;
	long long total;
	for (int i=0;i<100;++i){
		pthread_t th;
		start = rdtsc();
		pthread_create(&th, NULL, myThread, NULL); 
		end = rdtsc();
		pthread_join(th, NULL); 
		cout << end-start<<endl;
	}
	*/

	// measure context switch between processes
	
	uint64_t start,end;
	pid_t pid;
	int myPipe[2];
	//cout << pipe(myPipe)<<endl;
	if (pipe(myPipe)){
		cout << "error" << endl;
		return 0;
	}

	pid=fork();
	if (pid < 0)
	   cout << "error" <<endl;
	else if (pid == 0){
		close (myPipe[1]);
        read_from_pipe (myPipe[0]);
        //read(myPipe[0]);
		exit(0);
	}
	else{
		//wait(NULL);
		close (myPipe[0]);
        write_to_pipe (myPipe[1]);
        //write(myPipe[1]);
		wait(NULL);
	}


	return 0;
}