#include "cpu.h"

cpu::cpu(int n):iterTimes(n){}
cpu::cpu(){iterTimes=100000;}
inline void* myThread(void* args){return NULL;}

double cpu::getReadOH(){
	double total=0;
	uint64_t start,end;
	for (int i=0;i<iterTimes;++i){
		//preempt_disable();
		start = rdtsc();
		end = rdtscp();
		//preempt_enable();
		total += (end-start);
	}
	return total*1.0/iterTimes;
}

double cpu::getLoopOH(){
	uint64_t start,end;
	start = rdtsc();
	for (int i=0;i<iterTimes;++i){
	}
	end = rdtsc();
	return (end-start)*1.0/iterTimes;
}

inline void fun0() {return;}
inline void fun1(int a1) {return;}
inline void fun2(int a1,int a2) {return;}
inline void fun3(int a1,int a2,int a3) {return;}
inline void fun4(int a1,int a2,int a3,int a4) {return;}
inline void fun5(int a1,int a2,int a3,int a4,int a5) {return;}
inline void fun6(int a1,int a2,int a3,int a4,int a5,int a6) {return;}
inline void fun7(int a1,int a2,int a3,int a4,int a5,int a6,int a7) {return;}


vector<double> cpu::getProcCallOH(){
	double total=0;
	uint64_t start,end;
	vector<double> res;
	rdtsc();
	rdtscp();

	for (int i=0;i<iterTimes;++i){
		start = rdtsc();
		fun0();
		end = rdtscp();
		total += (end-start);
	}
	res.push_back(total*1.0/iterTimes);

	total=0;
	for (int i=0;i<iterTimes;++i){
		start = rdtsc();
		fun1(0);
		end = rdtscp();
		total += (end-start);
	}
	res.push_back(total*1.0/iterTimes);

	total=0;
	for (int i=0;i<iterTimes;++i){
		start = rdtsc();
		fun2(0,0);
		end = rdtscp();
		total += (end-start);
	}
	res.push_back(total*1.0/iterTimes);

	total=0;
	for (int i=0;i<iterTimes;++i){
		start = rdtsc();
		fun3(0,0,0);
		end = rdtscp();
		total += (end-start);
	}
	res.push_back(total*1.0/iterTimes);

	total=0;
	for (int i=0;i<iterTimes;++i){
		start = rdtsc();
		fun4(0,0,0,0);
		end = rdtscp();
		total += (end-start);
	}
	res.push_back(total*1.0/iterTimes);

	total=0;
	for (int i=0;i<iterTimes;++i){
		start = rdtsc();
		fun5(0,0,0,0,0);
		end = rdtscp();
		total += (end-start);
	}
	res.push_back(total*1.0/iterTimes);

	total=0;
	for (int i=0;i<iterTimes;++i){
		start = rdtsc();
		fun6(0,0,0,0,0,0);
		end = rdtscp();
		total += (end-start);
	}
	res.push_back(total*1.0/iterTimes);

	total=0;
	for (int i=0;i<iterTimes;++i){
		start = rdtsc();
		fun7(0,0,0,0,0,0,0);
		end = rdtscp();
		total += (end-start);
	}
	res.push_back(total*1.0/iterTimes);
	return res;

}

double cpu::getSysCallOH(){
	double total=0;
	uint64_t start,end;
	rdtsc();
	rdtscp();
	for (int i=0;i<iterTimes;++i){
		start = rdtsc();
		getpid();
		end = rdtscp();
		//cout << end-start<<endl;
		total += (end-start);
	}
	return total*1.0/iterTimes;
}

double cpu::getFreq(){
	int dur = 10;
	double total=0;
	uint64_t start,end;
	rdtsc();
	rdtscp();
	for (int i=0;i<1;++i){
		start = rdtsc();
		sleep(dur);
		end = rdtscp();
		total += (end-start);
	}
	return total*1.0/dur;
}

double cpu::getProcessCreationOH(){
	uint64_t start,end;
	long long total=0;
	rdtsc();
	rdtscp();
	for (int i=0;i<iterTimes;++i){
		start = rdtsc();
		pid_t pid = fork();
		if (pid < 0)
		   cout << "error" <<endl;
		else if (pid == 0){
			exit(0);
		}
		else{
			wait(NULL);
			end = rdtscp();
			total += (end-start);
		}
	}
	
	//cout << total << endl;
	return total*1.0/iterTimes;
}

double cpu::getThreadCreationOH(){
	uint64_t start,end;
	long long total = 0;
	rdtsc();
	rdtscp();
	for (int i=0;i<iterTimes;++i){
		pthread_t th;
		start = rdtsc();
		int err = pthread_create(&th, NULL, myThread, NULL); 
		end = rdtscp();
		pthread_join(th,NULL);
		total+=(end-start);
	}
	
	return total*1.0/iterTimes;
}

double cpu::getProcessCtxSwitchOH(){
	return 0;
}