#include<stdio.h>
#include<string.h>

//No of Vertices declared Globally
int VerticesN;

//Structure string which containes array of names
struct string
{
    char name[100];
};

//Unvisited, Visited Array and starting Vertex
string unvisited[100], visited[100], startV;
int unvisitedN = 0, visitedN = 0;

// A B 6
struct edge
{
    string v1;
    string v2;
    int weight;
};

// Array of edges A B 6 , A D 7 ...
edge edges[100];
int EdgesN = 0;

struct minPath
{
    string Vertex;
    string Previous;
    int dist;
};
//Array of new Paths
minPath minPaths[100];


void getInput()
{
    FILE *input;
    input = fopen("input.txt","r");
    fscanf(input, "%s", startV.name);
    while(!feof(input))
    {
        fscanf(input, "%s %s %d", edges[EdgesN].v1.name, edges[EdgesN].v2.name, &edges[EdgesN].weight);
        EdgesN++;
    }
    fclose(input);
}

void printGraph()
{
    printf("\n\n----------OUR GRAPH----------");
    printf("\nStarting Vertex is: %s", startV.name);
    printf("\nOur Edges: ");
    for(int i=0;i<EdgesN; i++)
    {
        printf("\n%s %s %d", edges[i].v1.name, edges[i].v2.name, edges[i].weight);
    }
    printf("\n\n-----------------------------");
}

int added(char name[])
{
    for(int i=0;i<unvisitedN;i++)
    {
        if(strcmp(name, unvisited[i].name)==0)
        {
            return 1;
        }
    }
    return 0;
}

void getUnvisitedVertices()
{
    for(int i=0;i<EdgesN;i++)
    {
        if(!added(edges[i].v1.name))
        {
            strcpy(unvisited[unvisitedN].name, edges[i].v1.name);
            unvisitedN++;
        }
        if(!added(edges[i].v2.name))
        {
            strcpy(unvisited[unvisitedN].name, edges[i].v2.name);
            unvisitedN++;
        }
    }
}

void printVisit()
{
    printf("\nUnvisited: ");
    for(int i=0;i<unvisitedN;i++)
    {
        printf(" %s",unvisited[i].name);
    }
    printf("\nVisited: ");
    for(int i=0;i<visitedN;i++)
    {
        printf(" %s",visited[i].name);
    }
}

void initializeMinPathTable()
{
    int initialDist = 1;
    for(int i=0; i<EdgesN;i++)
    {
        initialDist = initialDist + edges[i].weight;
    }
    for(int i=0;i<VerticesN;i++)
    {
        strcpy(minPaths[i].Vertex.name, unvisited[i].name);
        strcpy(minPaths[i].Previous.name, "NULL");
        if(strcmp(minPaths[i].Vertex.name, startV.name)==0)
        {
            minPaths[i].dist = 0;
        }
        else
        {
            minPaths[i].dist = initialDist;
        }
    }
}

void printMinPathTable()
{
    printf("\n\nMin Path Now: ");
    for(int i=0;i<VerticesN;i++)
    {
        printf("\n%s %d %s",minPaths[i].Vertex.name, minPaths[i].dist, minPaths[i].Previous.name);
    }
}

edgeWeight(char s1[], char s2[])
{
    for(int i=0;i<EdgesN;i++)	
    {
        if(strcmp(edges[i].v1.name,s1)==0 && strcmp(edges[i].v2.name, s2)==0)
        {
            return edges[i].weight;
        }
        if(strcmp(edges[i].v2.name, s1)==0 && strcmp(edges[i].v1.name, s2)==0)
        {
            return edges[i].weight;
        }
    }
}

int unvisitedIndexInPath(char s[])
{
    for(int i=0;i<VerticesN;i++)
    {
        if(strcmp(s, minPaths[i].Vertex.name)==0)
        {
            return i;
        }
    }
}

void dijkstra(char vName[])
{
    printf("\n\n\n\t\t... reducing from %s ....\n\n",vName);
    string vName_unvisited_neighbors[100];
    int N = 0;
    for(int i=0;i<EdgesN;i++)
    {
        if(strcmp(edges[i].v1.name, vName)==0)
        {
            strcpy(vName_unvisited_neighbors[N].name,edges[i].v2.name);
            N++;
        }
        if(strcmp(edges[i].v2.name, vName)==0)
        {
            strcpy(vName_unvisited_neighbors[N].name,edges[i].v1.name);
            N++;
        }
    }
	
	//Now we remove vName neighbors that aren't in the unvisited array  
    string help[100];
    int x=0, isUnvisited;
    for(int i=0;i<N;i++)
    {
        isUnvisited = 0;
        for(int j=0;j<unvisitedN;j++)
        {
            if(strcmp(vName_unvisited_neighbors[i].name,unvisited[j].name)==0)
            {
                isUnvisited = 1;
            }
        }
        if(isUnvisited == 1)
        {
            strcpy(help[x].name, vName_unvisited_neighbors[i].name);
            x++;
        }
    }
    N = x;
    for(int i=0;i<N;i++)
    {
        strcpy(vName_unvisited_neighbors[i].name, help[i].name);
    }

    printf("\nUnvisited Neighbors of '%s' are: ",vName);
    for(int i=0;i<N;i++)
    {
        printf(" %s",vName_unvisited_neighbors[i].name);
    }
	
	//now we replace the distances	of vName unvisited neighbors
	// we get the distance of vname
    int vNameDist;
    for(int i=0;i<VerticesN;i++)
    {
        if(strcmp(vName,minPaths[i].Vertex.name)==0)
        {
            vNameDist = minPaths[i].dist;
        }
    }
	
	//Now we update the distance and previous vertex of vName if we can..
    int weight, distPlusWeight;
    for(int i=0;i<N;i++)
    {
        weight = edgeWeight(vName, vName_unvisited_neighbors[i].name);
        distPlusWeight = weight + vNameDist;
        for(int j=0;j<VerticesN;j++)
        {
            if(strcmp(vName_unvisited_neighbors[i].name,minPaths[j].Vertex.name)==0)
            {
                if(minPaths[j].dist > distPlusWeight)
                {
                    minPaths[j].dist = distPlusWeight;
                    strcpy(minPaths[j].Previous.name, vName);
                }
            }
        }
    }

    printMinPathTable();

    strcpy(visited[visitedN].name, vName);
    visitedN++;
    string help1[100];
    int x1=0;
    for(int i=0;i<unvisitedN;i++)
    {
        if(strcmp(vName, unvisited[i].name)!=0)
        {
            strcpy(help1[x1].name, unvisited[i].name);
            x1++;
        }
    }
    unvisitedN = x1;
    for(int i=0;i<unvisitedN;i++)
    {
        strcpy(unvisited[i].name, help1[i].name);
    }
    printVisit();

    if(unvisitedN > 0)
    {
        int index, i2, min;
        index = unvisitedIndexInPath(unvisited[0].name);
        min = minPaths[index].dist;
        for(int i=0;i<unvisitedN;i++)
        {
            i2 = unvisitedIndexInPath(unvisited[i].name);
            if(min > minPaths[i2].dist)
            {
                index = i2;
                min = minPaths[index].dist;
            }
        }

        dijkstra(minPaths[index].Vertex.name);
    }
}

void output()
{
	FILE *out;
	out = fopen("out1.txt","w");
	fprintf(out, "Starting Vertex: %s", startV.name);
	for(int i=0; i<VerticesN; i++)
	{
		fprintf(out, "\n%s %d %s",minPaths[i].Vertex.name, minPaths[i].dist, minPaths[i].Previous.name);
	}
	fclose(out);
}

main()
{
    getInput();
    printGraph();
    getUnvisitedVertices();
    VerticesN = unvisitedN;
    printVisit();
    initializeMinPathTable();
    printMinPathTable();
    dijkstra(startV.name);
    output();
}
