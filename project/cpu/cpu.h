#ifndef cpu_H
#define cpu_H

#include <iostream>
#include <time.h>
#include <vector>
#include <unistd.h>  
#include <sys/types.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <pthread.h> 
#include <x86intrin.h>
//#include <preempt.h>

using namespace std;

/*
static inline uint64_t rdtsc(){
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

static inline uint64_t rdtscp(){
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtscp" : "=a" (lo), "=d" (hi));
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

static inline uint64_t rdtscp(){
	unsigned int cycles_high1, cycles_low1;
	asm volatile("RDTSCP\n\t"
		"mov %%edx, %0\n\t"
		"mov %%eax, %1\n\t"
		"CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
		"%rax", "%rbx", "%rcx", "%rdx");
	return ((uint64_t)cycles_high1 << 32) | cycles_low1;
}

class cpu{
private:
	int iterTimes;
public:
	cpu(int n);
	cpu();

	double getReadOH();
	double getLoopOH();
	vector<double> getProcCallOH();
	double getSysCallOH();
	double getFreq();
	double getProcessCreationOH();
	double getThreadCreationOH();
	double getProcessCtxSwitchOH();
	double getThreadCtxSwitchOH();
};

#endif