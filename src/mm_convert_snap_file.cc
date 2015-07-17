#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <map>
#include <vector>
#include <assert.h>
#include <string.h>
#include <sys/time.h>
#include <fstream>
#include "mmio.h"

using namespace std;
typedef int node_t;
typedef int edge_t;

vector< pair<node_t, node_t> > parse_adjacency_file(char* filename){
  ifstream adjFile(filename);
  vector< pair<node_t, node_t> > adjVector;
  pair<node_t, node_t> temp;
  int source, sink;
  while( adjFile >> source >> sink)
  {
    temp.first = (node_t) source;
    temp.second = (node_t) sink;
    adjVector.push_back(temp);
  }
  return adjVector;
}

node_t max_node(std::vector<pair<node_t, node_t> > list){
  node_t mNode = 0;
  for(std::vector< pair<node_t, node_t> >::iterator it = list.begin(); it!= list.end(); ++it)
  {
    if((*it).first > mNode)
    {
      mNode = (*it).first;
    }
    if((*it).second > mNode)
    {
      mNode = (*it).first;
    }
  }
  return mNode;
}

int main(int argc, char** argv) {
  //super hacky: assume the first input is the source, the second is the output
  struct timeval T1, T2;
  
  char* inFile = argv[1];
  char* outFile = argv[2];
  FILE *ofp;
  if ((ofp = fopen(outFile, "w")) == NULL) {
    printf("Error: output file is invalid\n");
    exit(1);
  }
  printf("Converting: %s -> %s\n", inFile, outFile);
  //get the adjacency lists from the snap file
  gettimeofday(&T1, NULL);
  vector< pair<node_t, node_t> > adj = parse_adjacency_file(inFile);
  gettimeofday(&T2, NULL);
  printf("File reading time (ms) = %lf\n", ((T2.tv_sec) - (T1.tv_sec)) * 1000 + (T2.tv_usec - T1.tv_usec) * 0.001);

  node_t N = max_node(adj)+1; //node count
  edge_t M = adj.size(); //edge count

  printf("Found %i Nodes, %i Edges\n", N, M);

  MM_typecode matcode;
  mm_initialize_typecode(&matcode);
  mm_set_matrix(&matcode);
  mm_set_coordinate(&matcode);
  mm_set_real(&matcode);

  mm_write_banner(ofp, matcode); 
  mm_write_mtx_crd_size(ofp, N, N, M);
  for(unsigned int i = 0; i<M; i++){
    fprintf(ofp, "%d %d 1.0\n", adj[i].first, adj[i].second);
  }

  fclose(ofp);
  return 0;
}