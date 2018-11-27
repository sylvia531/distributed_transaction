#include "storageLayer.h"

map<int, map<int, pair<string, int>>> storageDevice; //k1: server, k2: device id, v: (filename, last descriptor) 
map<string, map<time_t, int>> recordTable; //k1: objID, k2: timestamp, v: file descriptor location
void initDevice(int numServer, int dps){
	/**
	* numServer: number of server in the cluster
	* dps: storage device per server
	*/
	for(int i = 0; i<numServer; i++){
		map<int, pair<string, int>> sdDescriptor;
		for(int j = 0; j<dps; j++){
			string dname = "./storage/server"+to_string(i)+"_storage"+to_string(j);
			int fd = open((char*)dname.c_str(), O_RDWR | O_CREAT | O_TRUNC);  
			if (fd ==-1) {
				cout<<"Error: Opern storage device error"<<endl;
				exit(0);
			}
			// cout<<fd<<endl;
			sdDescriptor[j] = make_pair(dname, fd);
		}
		storageDevice[i] = sdDescriptor;
	}
}

void cleanDevice(){
	for(auto sd : storageDevice){
		for(auto dname : sd.second){
			int err = close(dname.second.second); 
			if (err < 0){
				cout<<"File close error"<<endl;
			}
		}
	}
}

void printDevice(){
	for(auto sd : storageDevice){
		cout<<"Server: "<<sd.first<<endl;
		for(auto dname : sd.second){
			cout<<"\t"<<dname.second.first<<endl;
		}
	}
}

void writeRecords(int serverID, int storageID, string val){
	int len = val.length();
	if(val[len-1] != '\n'){
		val = val+"\n";
	}
	int fd = storageDevice[serverID][storageID].second;
	
	int posStart = 0;
	int posEnd = val.find(" ");
	string objID = val.substr(posStart, posEnd-posStart);
	time_t ts = time(0);

	recordTable[objID][ts] = fd;
	
	
	int err = write(fd, (char*)val.c_str(), val.length()); 
	if(err < 0){
		cout<<"Error: Write record to server"<<serverID<<"_storage"<<storageID<<"  fail"<<endl;
	}
	storageDevice[serverID][storageID].second = fd;
	
	
}

string readRecords(int serverID, int storageID, string objID){
	auto iter = recordTable[objID].end();
	iter--;
	int fd = iter->second;
	
	return readLine(fd);
}

string readLine(int fd){
	char c;
	string res;
	
	while (read(fd, &c, 1) == 1) {
		res.push_back(c);
		if(c == '\n' || c == 0x0){
			break;
		}
	}
	
	return res;
}



