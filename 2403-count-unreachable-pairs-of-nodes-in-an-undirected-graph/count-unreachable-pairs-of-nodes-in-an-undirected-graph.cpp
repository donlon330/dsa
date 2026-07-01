class Solution {
public:
    vector<int>parent;
    vector<int>rank;
    int find(int x){
        if(x==parent[x]){
            return x;
        }
        return parent[x]=find(parent[x]);
    }
    void Union(int x, int y){
        int x_parent=find(x);
        int y_parent=find(y);
        if(x_parent== y_parent){
            return;
        }
        if(rank[x_parent]>rank[y_parent]){
            parent[y_parent]=x_parent;
        }
        else if(rank[x_parent]<rank[y_parent]){
            parent[x_parent]=y_parent;
        }
        else{
            parent[x_parent]=y_parent;
            rank[y_parent]++;
        }
    }
    long long countPairs(int n, vector<vector<int>>& edges) {
        parent.resize(n);
        rank.resize(n);
        int count=0;
        for(int i=0;i<n;i++){
            parent[i]=i;
        }
        //componets bnaye
        for(auto it:edges){
            int first=it[0];
            int second=it[1];
            Union(first,second);
        }
        //map for storing "parent componet"-->size
        unordered_map<int,int>mp;
        for(int i=0;i<n;i++){
            int baap=find(i);
            mp[baap]++;
        }
        //resylt formm map
        long long ans=0;
        int remaining_nodes=n;
        for(auto it:mp){
            int baap=it.first;
            long long size=it.second;
            ans+=(size)*(remaining_nodes-size);
            remaining_nodes-=size;
        }
        return ans;

    }
};