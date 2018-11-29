#include "storageLayer.h"

/**Storage global variable*/
clusterStoreMeta clusterStorage;

void initCluster(int numServer, int dps){
	/**
	* numServer: number of server in the cluster
	* dps: storage device per server
	*/	
	clusterStorage.numServer = numServer;
	for(int i = 0; i<numServer; i++){
		clusterStorage.server[i];
		initServer(&clusterStorage.server[i], i, dps);
		
	}
}

void initServer(serverMeta* server, int serverID, int numStorage){
	server->serverID = serverID;
	server->numStorage = numStorage;
	for(int i = 0; i<numStorage; i++){
		server->storageDevices[i];
		initDevice(&(server->storageDevices[i]), serverID, i);
	}
}


void initDevice(StorageDeviceMeta* sd, int serverID, int storageID){
	sd->serverID = serverID;
	sd->storageID = storageID;
	sd->deviceName ="./storage/server"+to_string(serverID)+"_storage"+to_string(storageID);
	int fd = open((char*)(sd->deviceName).c_str(), O_RDWR | O_CREAT | O_TRUNC);  
	if (fd ==-1) {
		cout<<"Error: Opern storage device error"<<endl;
		exit(0);
	}
	sd->sdDescriptor = make_pair(fd, 0);
	sd->offsetLocker = unique_lock<mutex>(sd->offsetMutex, defer_lock); 
}

void cleanDevice(){
	for(auto it1 = clusterStorage.server.begin(); it1!=clusterStorage.server.end(); it1++){

		for(auto it2 = it1->second.storageDevices.begin(); it2 != it1->second.storageDevices.end(); it2++){
			int err = close(it2->second.sdDescriptor.first); 
			if (err < 0){
				cout<<"File close error"<<endl;
			}
		}
	}
}


void printDevice(){
	cout<<"Number of servers: "<<clusterStorage.numServer<<endl;
	for(auto it1 = clusterStorage.server.begin(); it1!=clusterStorage.server.end(); it1++){
		cout<<"\tNumber of devices: "<<it1->second.numStorage<<endl;
		
		for(auto it2 = it1->second.storageDevices.begin(); it2 != it1->second.storageDevices.end(); it2++){
			cout<<"\t"<<it2->second.deviceName<<endl;
		}
	}
}


void writeRecords(int serverID, int storageID, char* in_val){
	//Append do not update old record, recordTable will handle that
	string val(in_val);
	//add \n if val do not have one
	int len = val.length();
	if(val[len-1] != '\n'){
		val = val+"\n";
	}
	
	//find the objID of the record
	int posStart = 0;
	int posEnd = val.find(" ");
	string objID = val.substr(posStart, posEnd-posStart);
	time_t ts = time(0);
	
	if(0){
		cout<<"ServerID: "<<serverID<<endl;
		cout<<"storageID: "<<storageID<<endl;
		cout<<"objID: "<<objID<<endl;
	}
	
	
	//Lock offset lock
	clusterStorage.server[serverID].storageDevices[storageID].offsetLocker.lock();
	
	
	//get the offset (tail) of the device
	int fd = (clusterStorage.server[serverID].storageDevices[storageID].sdDescriptor).first;
	long long offset = (clusterStorage.server[serverID].storageDevices[storageID].sdDescriptor).second;

	//test whether the record already exist, if not create record lock 
	if((clusterStorage.server[serverID].storageDevices[storageID].recordTable).find(objID) == (clusterStorage.server[serverID].storageDevices[storageID].recordTable).end()){
		clusterStorage.server[serverID].storageDevices[storageID].recordMutex[objID];
		clusterStorage.server[serverID].storageDevices[storageID].recordLocker.emplace(objID, unique_lock<mutex>(clusterStorage.server[serverID].storageDevices[storageID].recordMutex[objID], defer_lock));
	}
	
	//Lock record
	clusterStorage.server[serverID].storageDevices[storageID].recordLocker[objID].lock();
	
	//update the start of this record in record table
	clusterStorage.server[serverID].storageDevices[storageID].recordTable[objID][ts] = offset;
		
	//Write the record in the storage 
	int byte = pwrite (fd, (char*)val.c_str(), val.length(), offset);
	if(byte < 0){
		cout<<"Error: Write record to server"<<serverID<<"_storage"<<storageID<<"  fail"<<endl;
	}
	else{
		if(0){
			cout<<"Write: "<<byte<<" B data"<<endl;
		}
	}
	
	//update the offset of storage descriptor
	clusterStorage.server[serverID].storageDevices[storageID].sdDescriptor.second = (long long)offset+byte;
	
	//Unlock record
	clusterStorage.server[serverID].storageDevices[storageID].recordLocker[objID].unlock();
	//Unlock offset lock
	clusterStorage.server[serverID].storageDevices[storageID].offsetLocker.unlock();
	
	if(1){
		if(objID == "user4409142221109489457"){
			cout<<"After Write laster offset: "<<clusterStorage.server[serverID].storageDevices[storageID].sdDescriptor.second<<endl;
			string tmp = readLine(clusterStorage.server[serverID].storageDevices[storageID].sdDescriptor.first, clusterStorage.server[serverID].storageDevices[storageID].recordTable[objID][ts]);
			cout<<tmp<<endl;
		}
	}
	
	
	
	
}

// char* readRecords(int serverID, int storageID, char* in_objID){
void readRecords(int serverID, int storageID, char* in_objID, char** out_record){
	string objID(in_objID);
	//single read, singel write
	clusterStorage.server[serverID].storageDevices[storageID].recordLocker[objID].lock();
	auto iter = clusterStorage.server[serverID].storageDevices[storageID].recordTable[objID].end();
	iter--;
	int fd = (clusterStorage.server[serverID].storageDevices[storageID].sdDescriptor).first;
	long long offset = iter->second;
	string res = readLine(fd, offset);
	clusterStorage.server[serverID].storageDevices[storageID].recordLocker[objID].unlock();
	
	// char* out_record = (char*)res.c_str();
	// return out_record;
	
	res = res+'\0';
	int len = res.length();
	*out_record = (char*)malloc(len*sizeof(char));
	memcpy(*out_record, (char*)res.c_str(), len);
	

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
