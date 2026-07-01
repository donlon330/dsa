class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int n=s.size();

        // Noting down the first and last occ
        map<char,pair<int,int>>mpp;
        for(int i=0;i<n;i++){
            if(mpp.count(s[i])) mpp[s[i]].second=i;
            else mpp[s[i]]={i,i};
        }

        //Building the graph
        map<char,set<char>>adj;
        for(auto it:mpp){
            char node=it.first;
            int f=it.second.first,l=it.second.second;

            for(int i=f+1;i<l;i++){
                if(s[i]!=node) adj[node].insert(s[i]);
            }
        }

        //use of this var to store the SCC later
        // Im too lazy to write TWO Dfs so im reusing the same one but with a flag
        string temp="";

        //Applying Kosaraju
        vector<bool>vis(26,false);
        stack<char>st;
        for(auto it:mpp){
            char node=it.first;
            if(!vis[node-'a']){
                vis[node-'a']=true;
                dfs(node,adj,st,vis,true,temp);
            }
        }

        //reversing the edges
        fill(vis.begin(),vis.end(),false);
        map<char,set<char>>rev;
        for(auto it:adj){
            char node=it.first;
            for(char c:adj[node]){
                rev[c].insert(node);
            }
        }

        //Second pass of DFS
        vector<string>components;
        while(!st.empty()){
            char node=st.top();
            st.pop();
            if(!vis[node-'a']){
                if(!temp.empty()){
                    components.push_back(temp);
                    temp.clear();
                }
                vis[node-'a']=true;
                dfs(node,rev,st,vis,false,temp);
            }
        }
        if(!temp.empty()) components.push_back(temp);


        //Checking outdegree and adding it to the answer
        vector<string>ans;
        for(string t:components){
            bool ok=true;
            for(char c:t){
                for(char nei:adj[c]){
                    if(t.find(nei)==string::npos){
                        ok=false;
                        break;
                    }
                }
                if(!ok) break;
            }
            if(ok){
                int mini=INT_MAX,maxi=INT_MIN;
                for(char c:t){
                    mini=min(mini, mpp[c].first);
                    maxi=max(maxi, mpp[c].second);
                }
                ans.push_back(s.substr(mini, (maxi-mini+1)));
            }
        }
        return ans;
    }
    void dfs(char node, map<char,set<char>>&adj, stack<char>&st, vector<bool>&vis, bool first, string &temp){
        for(char c:adj[node]){
            if(!vis[c-'a']){
                vis[c-'a']=true;
                dfs(c,adj,st,vis,first,temp);
            }
        }
        if(first) st.push(node);
        else temp.push_back(node);
    }
};