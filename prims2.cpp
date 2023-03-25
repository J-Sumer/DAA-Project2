class Solution {
public:
      int dist(vector<vector<int> >& points, int i,int j){
        int x1,x2,y1,y2;
        x1 = points[i][0];
        x2 = points[j][0];
        y1 = points[i][1];
        y2 = points[j][1];
        return abs(x1-x2) + abs(y1-y2);   
    }
	
    int prim(vector <vector <int> > &E, int n, vector<vector<int>>& edges){
        int c = 0;
        vector <int> w(n,INT_MAX);
        vector <bool> V(n,false);
        w[0]=0;
        int i,j;
        priority_queue <pair<int,int>, vector <pair<int,int> >, greater <pair<int,int> > > pq;
        for(i=0;i<n;i++){
            pq.push(make_pair(w[i],i));
        }
        int v,e,u;
        int weight = 0;
        while(!pq.empty()){
            v = pq.top().second;
            pq.pop();
            if(!V[v]){
                weight+=w[v];
                V[v]=true;
                for(i=0;i<E[v].size();i++){
                    e = E[v][i];
                    u = edges[e][1];
                    if(u == v){
                        u = edges[e][2];
                    }
                    if(!V[u] && w[u]>edges[e][0]){
                        w[u]=edges[e][0];
                        pq.push(make_pair(w[u],u));
                    }
                }
            }
        }  
       return weight;
    }
    int minCostConnectPoints(vector<vector<int> >& points) {
        vector <vector <int> > edges;
        vector <vector<int> > E;
        E.clear();
        int n = points.size();
        E.resize(n,vector <int> (0));
        int i,j,u,v;
        for(i=0;i<n;i++){
            for(j=i+1;j<n;j++){
                vector <int> a(3);
                a[0] = dist(points,i,j);
                a[1]=i;
                a[2]=j;
                edges.push_back(a);
            }
        }
        for(i=0;i<edges.size();i++){
            u = edges[i][1];
            v = edges[i][2];
            E[u].push_back(i);
            E[v].push_back(i);
            
        }
        return prim(E,points.size(),edges);   
    }
};