#include<limits.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
 

struct string
{

    char name[100];
};

string store[100];

int pp;

typedef struct{
    string sourceVertex;
    int sv;
    int dv;
    string destVertex;
    int edgeWeight;
}edge;

 

typedef struct{
    int vertices;
    int edges;
    edge* edgeMatrix;
}graph;

 

graph loadGraph(char* fileName){
    FILE* fp = fopen(fileName,"r");
    graph G;
    int i;
    fscanf(fp,"%d%d",&G.vertices,&G.edges);
    G.edgeMatrix = (edge*)malloc(G.edges*sizeof(edge));

    for(i=0;i<G.edges;i++){

        fscanf(fp,"%d %s %d %s %d",&G.edgeMatrix[i].sv,G.edgeMatrix[i].sourceVertex.name,&G.edgeMatrix[i].dv,G.edgeMatrix[i].destVertex.name,&G.edgeMatrix[i].edgeWeight);

        strcpy(store[G.edgeMatrix[i].sv].name,G.edgeMatrix[i].sourceVertex.name);

        strcpy(store[G.edgeMatrix[i].dv].name,G.edgeMatrix[i].destVertex.name);

    }

 

    fclose(fp);

   /* FILE* up = fopen(fileName,"r");

    int ek=0;

    fscanf(up,"%d%d",&ek,&ek);

     for(i=0;i<ek;i++){

        fscanf(up,"%d %s %d %s %d",&pp,store[pp].name,&pp,store[pp].name,&pp);

    }

    fclose(up);

*/

    return G;

}

 

void floydWarshall(graph g){

    int processWeights[g.vertices][g.vertices], processedVertices[g.vertices][g.vertices];

    int i,j,k;

 

    for(i=0;i<g.vertices;i++)

        for(j=0;j<g.vertices;j++){

            processWeights[i][j] = SHRT_MAX;

            processedVertices[i][j] = (i!=j)?j+1:0;

        }

 

    for(i=0;i<g.edges;i++)

        processWeights[g.edgeMatrix[i].sv-1][g.edgeMatrix[i].dv-1] = g.edgeMatrix[i].edgeWeight;

 

    for(i=0;i<g.vertices;i++)

        for(j=0;j<g.vertices;j++)

            for(k=0;k<g.vertices;k++){

                if(processWeights[j][i] + processWeights[i][k] < processWeights[j][k]){

                    processWeights[j][k] = processWeights[j][i] + processWeights[i][k];

                    processedVertices[j][k] = processedVertices[j][i];

                }

            }

 

    printf("\t\tpair\t\t\t    dist\t\t\t   path");

    for(i=0;i<g.vertices;i++)

        for(j=0;j<g.vertices;j++){

            if(i!=j){

                printf("\n%s -> %s %3d %s",store[i+1].name,store[j+1].name,processWeights[i][j],store[i+1].name);

                k = i+1;

                do{

                    k = processedVertices[k-1][j];

                    printf("->%s",store[k].name);

                }while(k!=j+1);

            }

        }

}

int main(){

    floydWarshall(loadGraph("input_f.txt"));

    return 0;}
