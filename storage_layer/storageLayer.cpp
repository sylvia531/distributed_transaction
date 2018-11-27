#include "storageLayer.h"

map<int, map<int, pair<int, long long>>> storageDevice; //k1: server, k2: device id, v: (file descriptor, last offset) 
map<string, map<time_t,  long long>> recordTable; //k1: objID, k2: timestamp, v: record offset
void initDevice(int numServer, int dps){
	/**
	* numServer: number of server in the cluster
	* dps: storage device per server
	*/
	for(int i = 0; i<numServer; i++){
		map<int, pair<int, long long>> sdDescriptor;
		for(int j = 0; j<dps; j++){
			string dname = "./storage/server"+to_string(i)+"_storage"+to_string(j);
			int fd = open((char*)dname.c_str(), O_RDWR | O_CREAT | O_TRUNC);  
			if (fd ==-1) {
				cout<<"Error: Opern storage device error"<<endl;
				exit(0);
			}
			// cout<<fd<<endl;
			sdDescriptor[j] = make_pair(fd, 0);
		}
		storageDevice[i] = sdDescriptor;
	}
}

void cleanDevice(){
	for(auto sd : storageDevice){
		for(auto dname : sd.second){
			int err = close(dname.second.first); 
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
			string tmpName = "\t./storage/server"+to_string(sd.first)+"_storage"+to_string(dname.first);
			cout<<tmpName<<endl;
		}
	}
}

void writeRecords(int serverID, int storageID, string val){
	
	int len = val.length();
	if(val[len-1] != '\n'){
		val = val+"\n";
	}
	int fd = storageDevice[serverID][storageID].first;
	long long offset = storageDevice[serverID][storageID].second;
	
	int posStart = 0;
	int posEnd = val.find(" ");
	string objID = val.substr(posStart, posEnd-posStart);
	time_t ts = time(0);
	
	if(0){
		cout<<"ServerID: "<<serverID<<endl;
		cout<<"storageID: "<<storageID<<endl;
		cout<<"objID: "<<objID<<endl;
		cout<<"Write: "<<fd<<endl;
	}
	
	
	if(objID == "user2408371864701034737"){
		cout<<"Write: "<<fd<<endl;
	}

	recordTable[objID][ts] = offset;
	
	
	int err = write(fd, (char*)val.c_str(), val.length()); 
	int byte = pwrite (fd, (char*)val.c_str(), val.length(), offset);
	if(err < 0){
		cout<<"Error: Write record to server"<<serverID<<"_storage"<<storageID<<"  fail"<<endl;
	}
	else{
		if(0){
			cout<<"Write: "<<byte<<" B data"<<endl;
		}
	}
	
	storageDevice[serverID][storageID].second = (long long)offset+byte;
	
	if(objID == "user2408371864701034737"){
		cout<<"After Write laster offset: "<<storageDevice[serverID][storageID].second<<endl;
		string tmp = readLine(storageDevice[serverID][storageID].first, recordTable[objID][ts]);
		cout<<tmp<<endl;
	}
	
	
	
	
}

string readRecords(int serverID, int storageID, string objID){
	auto iter = recordTable[objID].end();
	iter--;
	int fd = storageDevice[serverID][storageID].first;
	long long offset = iter->second;
	
	return readLine(fd, offset);
}

string readLine(int fd, long long offset){
	char c;
	string res;
	int byte;
	while(byte = pread(fd, &c, 1, offset) == 1) {
		res.push_back(c);
		if(c == '\n' || c == 0x0){
			break;
		}
		offset = offset+byte;
	}
	
	return res;
}



