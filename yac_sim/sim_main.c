#include "../structDef.h"
#include "yac.h"


void UserMain(int argc, char *argv[]){
	
	//always generate same random sequence
	srand (1);
	
	int i = 0;
	
	if(argc!=3){
		printf("argument not correct, please enter the path of configure file\n");
		return;
	}
	
	int numServer = atoi(argv[1]);
	int numDevPerServer = DEV_PER_SERVER;
	char* loadTracePath = argv[2];
	
	printf("Number of servers: %d\n", numServer);
	printf("trace path: %s\n", loadTracePath);

	
	//1. Initialize the cluster
	initCluster(numServer, numDevPerServer);
	
	if(DEBUG){
		printDevice();
	}
	
	//2. Initial cluster manager
	cmInput cmIn;
	for (i=0; i < NUM_CLUSTER_MANAGER; i++){
		//Initial process
		ClusterManag[i] = NewProcess("ClusterManag",clusterManag,0);		
		cmIn.numServer = numServer;
		cmIn.traceName = loadTracePath;
		cmIn.cmID = i;
		ActivitySetArg(ClusterManag[i], &cmIn, sizeof(cmIn));
		ActivitySchedTime(ClusterManag[i],0.00000,INDEPENDENT);
	}
	
	//3. Initial servers
	psInput psIn[MAX_NUM_SERVER];
	for(i = 0; i<MAX_NUM_SERVER; i++){
		
		//Initial queue
		makePhyMsgQueue(i);
		sem_PhyMQFull[i] = NewSemaphore("sem_PhyMQFull", QUEUE_CAP);
		sem_PhyMQAtomic[i] = NewSemaphore("sem_PhyMQAtomic", 1);
		sem_WakePhyServer[i] = NewSemaphore("sem_WakePhyServer", 0);
		
		//initial process
		PhyServer[i] = NewProcess("PhyServer",phyServer,0);		
		psIn[i].psID = i;
		ActivitySetArg(PhyServer[i], &psIn[i], sizeof(psIn[i]));
		ActivitySchedTime(PhyServer[i],0.00000,INDEPENDENT);
	}
	
	//4. Initial statistics
	initialStatistic();
	
	//5. Start simiulation
	printf("\n******************************Start Simulation*******************************************\n");
	DriverRun(SIMULATION_TIME); // Maximum time of the simulation (in cycles).	
	printf("\n********************************Simulation Finish****************************************\n");
	printStatistic();
	printf("\n*****************************************************************************************\n");
	
	cleanDevice();

}