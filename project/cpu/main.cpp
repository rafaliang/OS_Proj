#include "cpu.h"

int main(){
	class cpu myCpu(1000);
	//cout << myCpu.getReadOH()<<endl;
	//cout << myCpu.getLoopOH()<<endl;
	//cout << myCpu.getSysCallOH()<<endl;
	vector<double> res = myCpu.getProcCallOH();
	for (auto it:res)
		cout << it<<endl;
	//cout << myCpu.getProcessCreationOH()<<endl;
	//cout << myCpu.getThreadCreationOH()<<endl;
	//cout << myCpu.getFreq()<<endl;
	return 0;
}