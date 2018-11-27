#include "traceLoader.h"


map<string, vector<ycsbRecord>> opTable; //key: objID, value: record


void loadRecord(string filename){
	
	FILE *fTrace = fopen((char*)filename.c_str(), "r");
	char tmpLine[MAX_LINE_SIZE]; 
	
	while(!feof(fTrace)){
		fgets(tmpLine, MAX_LINE_SIZE, fTrace);
		if(tmpLine[0] == '"' || tmpLine[0] == '*' || tmpLine[0] == '['){
			continue;
		}
			
		string tmpString(tmpLine);
		
		ycsbRecord tmp = parseRecord(tmpString);
		if(opTable.find(tmp.objID) == opTable.end()){
			vector<ycsbRecord> opSet;
			opSet.push_back(tmp);
			opTable[tmp.objID] = opSet;
		}
		else{
			opTable[tmp.objID].push_back(tmp);
		}

	}
	
	fclose(fTrace);
}

ycsbRecord parseRecord(string r){
	ycsbRecord tmp;
	int strLen = r.length();
	// cout<<"Length: "<<strLen<<endl;
	int posStart = 0;
	int posEnd = r.find(" ");
	string op = r.substr(0, posEnd-posStart);
	tmp.op = op;
	// cout<<op<<endl;
		
	posStart = posEnd+1;
	posEnd = r.find(" ", posStart);
	string tableName = r.substr(posStart, posEnd-posStart);
	tmp.tableName = tableName;
	// cout<<tableName<<endl;
		
	posStart = posEnd+1;
	posEnd = r.find(" ", posStart);
	string objID = r.substr(posStart, posEnd-posStart);
	tmp.objID = objID;
	// cout<<objID<<endl;
	if(op == "READ"){
		tmp.isRead = TRUE;
		posEnd = r.find("all", posEnd);
		if(posEnd < 0){
			cout<<"Not read all fields"<<endl;
			exit(0);
		}
	}
	else{
		tmp.isRead = FALSE;
		posStart = posEnd+1;
		posEnd = r.find("field", posEnd);
		while(1){
			int posEnd2 = r.find("=", posEnd+1);
			string field = r.substr(posEnd, posEnd2-posEnd);
			// cout<<field<<endl;
			
			posStart = posEnd2+1;
			posEnd = r.find("field", posStart);
			// cout<<posEnd<<endl;
			if(posEnd > 0){
				string content = r.substr(posStart, posEnd-posStart);
				tmp.content[field] = content;
				// cout<<content<<endl<<endl;
			}
			else{
				string content = r.substr(posStart, strLen-posStart-2);
				tmp.content[field] = content;
				// cout<<content<<endl<<endl;
				break;
			}
			
		}
	}
	return tmp;
}

void printTable(){
	int count = 0;
	for(auto t : opTable){
		count++;
		cout<<"objID: "<<t.first<<endl;
		cout<<"Record "<<count<<": "<<endl;
		int opCount = 0;
		for(auto opr : t.second){
			opCount++;
			cout<<"\top number: "<<opCount<<": "<<endl;
			cout<<"\t\top: "<<opr.op<<endl;
			cout<<"\t\ttable: "<<opr.tableName<<endl;
			for(auto r: opr.content){
				cout<<"\t\t"<<r.first<<": "<<r.second<<endl;
			}
		}
	}
}

