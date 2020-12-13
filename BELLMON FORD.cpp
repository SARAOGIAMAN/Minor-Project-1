#include<stdio.h>
#include<string.h>

// states and states table
typedef struct state
{
	char stateName[100];
}stateName;

stateName graphStates[100];
int numberOfStates;

// edges and edges table
typedef struct edges
{
	char predecessor[100];
	char successor[100];
	int weight;
}edges;

edges relations[100];
int numberOfEdges;

// reducing table
typedef struct SCP
{
	char stateName[100];
	int reachCost;
	int infinity;
	char predecessor[100];
}SCP;
SCP reducingTable[100];


char help[100],help1[100],c;


void GetGraph()
{  

	int i,j,l,s;
	FILE *InputFile;
	InputFile = fopen("input_b.txt","r");
	// get graph states
	fgets(help,255,InputFile);
	j=0;
	s=0;
	char commas = ',';
	
	for(i=0 ; i< strlen(help); i++)
	{
		c = help[i];
		if(c != commas)
		{
			if(c != '\n')
			{
				graphStates[s].stateName[j] = c;
				j++;	
			}
		}
		else
		{
			j = 0;
			s++;	
		}
		
	}
	numberOfStates = s+1;
	printf("Graph States : ");
	for(i=0 ; i < numberOfStates ; i++)
	{
		printf("(%s)", graphStates[i].stateName);	
	}
	printf("\nthe initial state is : %s",graphStates[0].stateName);
	
	// get graph edges
	printf("\nGraph Edges :\n");
	j=0;
	numberOfEdges = 0;
	
	while(!feof(InputFile))
	{	 
		 fscanf(InputFile, "%s %s %d",relations[j].predecessor, relations[j].successor, &relations[j].weight);
		 j++;
    }
    numberOfEdges = j;
    
    for(i=0; i<numberOfEdges; i++)
    {
    	printf("%s | %s | %d\n",relations[i].predecessor, relations[i].successor, relations[i].weight);
    	
	}
	fclose(InputFile);
}
void initReducingTable()
{
	int i;
	strcpy(reducingTable[0].stateName, graphStates[0].stateName);
	reducingTable[0].infinity = 0;
	reducingTable[0].reachCost = 0;
	for(i=1; i<=numberOfStates; i++)
	{
		strcpy(reducingTable[i].stateName,graphStates[i].stateName);
		reducingTable[i].infinity = 1;		
	}
}
int ReachCostIsInfinity(char sName[])
{
	int i;
	int infinity = 0;
	for(i=0;i<numberOfStates;i++)
	{
		if(strcmp(sName, reducingTable[i].stateName) == 0)
		{
			if(reducingTable[i].infinity == 1)
			{
				infinity = 1;
			}
		}
	}
	return infinity;
}
		
	
int tryReduce(char pre[], char sec[],int w)
{
	int changed,i,preIndex, secIndex;
	int preCostIsInfinity, secCostIsInfinity;
	int preCurrentCost, secCurrentCost;
	changed = 0;
	for(i=0; i<numberOfStates; i++)
	{
		if(strcmp(pre,reducingTable[i].stateName)==0)
		{
			preIndex = i;
			if(reducingTable[i].infinity == 1)
			{
				preCostIsInfinity = 1;				
			}
			else
			{
				preCostIsInfinity = 0;
				preCurrentCost = reducingTable[i].reachCost;
			}
		}
		if(strcmp(sec,reducingTable[i].stateName)==0)
		{
			secIndex = i;
			if(reducingTable[i].infinity == 1)
			{
				secCostIsInfinity = 1;
			}
			else
			{
				secCostIsInfinity = 0;
				secCurrentCost = reducingTable[i].reachCost;
				
			}
		}
	}
	
	if(preCostIsInfinity == 0 && secCostIsInfinity == 1)
	{
		reducingTable[secIndex].reachCost = preCurrentCost + w;
		reducingTable[secIndex].infinity = 0;
		strcpy(reducingTable[secIndex].predecessor , pre);
		changed = 1;
    }
	if(preCostIsInfinity == 0 && secCostIsInfinity == 0)
	{
		if(secCurrentCost > (preCurrentCost + w))
		{
			reducingTable[secIndex].reachCost = preCurrentCost + w;
			strcpy(reducingTable[secIndex].predecessor , pre);
			changed = 1;
		}
	}
	
	return changed;
	
}
void reduce()
{
	int i,j;
	for(i=0; i<numberOfStates; i++)
	{
		for(j = 0; j<numberOfEdges ; j++)
		{
			if( strcmp(reducingTable[i].stateName, relations[j].predecessor) == 0)
			{
				tryReduce(reducingTable[i].stateName,relations[j].successor, relations[j].weight);
			}
		}
	}
}
void printCurrentReachCost(int iteration)
{
	int i;
	printf("\nCurrent reducing state after iteration %d : \n",(iteration+1));
	for(i=0;i<numberOfStates;i++)
	{
		printf("%s | %s", reducingTable[i].stateName,reducingTable[i].predecessor);
		if(reducingTable[i].infinity == 1)
		{
			printf(" | Infinity");
		}
		else
		{
			printf(" | %d",reducingTable[i].reachCost);
		}
		printf("\n");
	}
}

//int checkNegativeCycle
void shortestPath()
{
	int i,b,j,negativeCycleExist = 0;
	FILE  *OutputFile;
	OutputFile = fopen("output.txt","w");
	fputs("state | predecessor | reachCost\n",OutputFile);
	for(i=0;i<numberOfStates; i++)
	{
		if(reducingTable[i].infinity == 1)
		{
			fprintf(OutputFile, "%s | %s | infinity\n",reducingTable[i].stateName, reducingTable[i].predecessor);		
		}
		else
		{
			fprintf(OutputFile, "%s | %s | %d\n",reducingTable[i].stateName, reducingTable[i].predecessor,reducingTable[i].reachCost);
		}
	}
	
	//check if there is a negative cycle
	negativeCycleExist = 0;
	for(i=0;i<numberOfStates; i++)
	{
		for(j=0;j<numberOfEdges; j++)
		{
			if(strcmp(graphStates[i].stateName, relations[j].predecessor) == 0)
			{
				negativeCycleExist = tryReduce(graphStates[i].stateName, relations[j].successor, relations[j].weight);
			}
		}
	}
	
	if(negativeCycleExist == 1)
	{
		printf("\n Negative Cycle exists\n");
		fprintf(OutputFile, "A negative cycle exist\n");
	}
	else
	{
		printf("\n No Negative Cycle exists\n");
		fprintf(OutputFile, "No negative cycle exist\n");
	}
	fclose(OutputFile);
}


main()
{
	int i;
	printf("\t\tBellman Ford Algorithm\n");
	GetGraph();
	initReducingTable();
	for(i=0;i<numberOfStates;i++)
	{
		reduce();
		printCurrentReachCost(i);
	}
	shortestPath();
}




