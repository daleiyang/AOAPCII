//本题作者是刘禹  --编者注
#include <stdio.h> 
#include <string.h> 

#include <iostream> 
#include <sstream> 

#include <string> 
#include <vector> 
#include <set> 
#include <map> 
#include <utility> 
#include <algorithm> 

using namespace std; 

typedef string KEY; 
typedef set<pair<int, int> > TARGET; 
typedef pair<KEY, TARGET> ENTRY; 

string strtolower(string str) 
{ 
        for (int i = 0; i < str.length(); i++) 
        { 
                str[i] = tolower(str[i]); 
        } 
        return str; 
} 

void inline dump_line(const vector<string>& doc, int line) 
{ 
        if (line < doc.size()) 
        { 
                printf("%s", doc[line].data()); 
        } 
} 

void inline dump_document(const vector<string>& doc) 
{ 
        for (int i = 0; i < doc.size(); i++) 
        { 
                dump_line(doc, i); 
        } 
} 

bool operator < (const pair<int, int>& a, const pair<int, int>& b) 
{ 
        if (a.first == b.first) 
        { 
                return (a.second < b.second); 
        } 
        else 
        { 
                return (a.first < b.first); 
        } 
} 

void inline dump_query(vector<pair<int, int> >& items, const vector<vector<string> >& docs) 
{ 
        if (items.size() == 0) 
        { 
                printf("Sorry, I found nothing.\n"); 
        } 

        sort(items.begin(), items.end()); 

        int i; 
        int lastdoc = 0; 
        for (i = 0; i < items.size(); i++) 
        { 
                if (items[i].first > lastdoc) 
                { 
                        lastdoc = items[i].first; 
                        if (i > 0) 
                        { 
                                printf("----------\n"); 
                        } 
                } 
                if (i > 0) 
                { 
                        if (items[i] == items[i - 1]) 
                        { 
                                continue; 
                        } 
                } 
                dump_line(docs[items[i].first], items[i].second); 
        } 
} 

void inline dump_query_not(vector<pair<int, int> >& items, const vector<vector<string> >& docs) 
{ 
        if (items.size() == 0) 
        { 
                printf("Sorry, I found nothing.\n"); 
        } 

        sort(items.begin(), items.end()); 

        int i; 
        int lastdoc = 0; 
        for (i = 0; i < items.size(); i++) 
        { 
                if (items[i].first > lastdoc) 
                { 
                        lastdoc = items[i].first; 
                        if (i > 0) 
                        { 
                                printf("----------\n"); 
                        } 
                } 
                if (i > 0) 
                { 
                        if (items[i] == items[i - 1]) 
                        { 
                                continue; 
                        } 
                } 
                dump_document(docs[items[i].first]); 
        } 
} 


void inline tokenize(map<KEY, TARGET>& index, int idoc, const vector<string>& doc) 
{ 
        char buff[100]; 
        char idx = 0; 
        char ch; 

        int i, j; 
        for (i = 0; i < doc.size(); i++) 
        { 
                for (j = 0; j < doc[i].length(); j++) 
                { 
                        if (isalpha(ch = doc[i][j])) 
                        { 
                                buff[idx++] = ch; 
                        } 
                        else 
                        { 
                                if (idx > 0) 
                                { 
                                        buff[idx++] = '\0'; 
                                        string word(buff); 
                                        index[strtolower(word)].insert(pair<int, int>(idoc, i)); 
                                } 
                                idx = 0; 
                        } 
                } 
        } 
} 

int main(void) 
{ 
#ifndef ONLINE_JUDGE 
        freopen("web.in", "r", stdin); 
        freopen("web.out", "w", stdout); 
#endif 
        vector<vector<string> > document; 
        map<KEY, TARGET> index; 

        char buff[1000]; 
         
        int N = 0; 
        scanf("%d\n", &N); 

        document = vector<vector<string> >(N); 

        int idx = 0; 
        while (gets(buff) != NULL) 
        { 
                if (strncmp(buff, "**********", 10) == 0) 
                { 
                        // tokenize the document 
                        tokenize(index, idx, document[idx]); 
                        // switch to next document 
                        idx += 1; 
                        // if all document are loaded, break; 
                        if (idx >= N) break; 
                } 
                else 
                { 
                        // store the document line by line 
                        document[idx].push_back(string(buff)); 
                        document[idx].back() += "\n"; 
                } 
        } 

        int M = 0; 
        scanf("%d\n", &M); 
         
        int i, j; 
        char a[100], b[100], c[100]; 
        string op; 
         
        TARGET tgt; 
        vector<pair<int, int> > tmp, tmp2; 

        set<pair<int, int> >::iterator it; 

        int * maska = new int[N]; 
        int * maskb = new int[N]; 
         
        for (idx = 0; idx < M; idx++) 
        { 
                gets(buff); 
                switch (sscanf(buff, "%s %s %s\n", a, b, c)) 
                { 
                case 1: // simple 
                        tgt = index[strtolower(string(a))]; 
                        for (it = tgt.begin(), i = 0; it != tgt.end(); it++) 
                        { 
                                tmp.push_back((*it)); 
                        } 
                        // dump query result 
                        dump_query(tmp, document); 
                        break; 
                case 2: // NOT 
                        tgt = index[strtolower(string(b))]; 
                        i = 0; 
                        for (it = tgt.begin(); it != tgt.end(); it++) 
                        { 
                                while (i < (*it).first) 
                                { 
                                        tmp.push_back(pair<int, int>(i++, 0)); 
                                } 
                                i = (*it).first + 1; 
                        } 
                        while (i < N) 
                        { 
                                tmp.push_back(pair<int, int>(i++, 0)); 
                        } 
                        // dump query result 
                        dump_query_not(tmp, document); 
                        break; 
                case 3: // AND, OR 
                        op = strtolower(string(b)); 
                        if (op == "and") 
                        { 
                                memset(maska, 0, N * sizeof(int)); 
                                memset(maskb, 0, N * sizeof(int)); 

                                tgt = index[strtolower(string(a))]; 
                                for (it = tgt.begin(); it != tgt.end(); it++) 
                                { 
                                        tmp.push_back(*it); 
                                        maska[(*it).first]++; 
                                } 
                                tgt.clear(); 

                                tgt = index[strtolower(string(c))]; 
                                for (it = tgt.begin(); it != tgt.end(); it++) 
                                { 
                                        tmp.push_back(*it); 
                                        maskb[(*it).first]++; 
                                } 
                                tgt.clear(); 
                                // filter 
                                for (i = 0; i < tmp.size(); i++) 
                                { 
                                        if ((maska[tmp[i].first] > 0) && (maskb[tmp[i].first] > 0)) 
                                        { 
                                                tmp2.push_back(tmp[i]); 
                                        } 
                                } 
                                // dump query result 
                                dump_query(tmp2, document); 
                        } 
                        else // OR 
                        { 
                                tgt = index[strtolower(string(a))]; 
                                for (it = tgt.begin(); it != tgt.end(); it++) 
                                { 
                                        tmp.push_back(*it); 
                                } 
                                tgt.clear(); 

                                tgt = index[strtolower(string(c))]; 
                                for (it = tgt.begin(); it != tgt.end(); it++) 
                                { 
                                        tmp.push_back(*it); 
                                } 
                                tgt.clear(); 
                                // dump query result 
                                dump_query(tmp, document); 
                        } 
                        break; 
                } // switch 

                printf("==========\n"); 

                tgt.clear(); 
                tmp.clear(); 
                tmp2.clear(); 

        } // for 

        delete [] maska; 
        delete [] maskb; 

        return 0; 
} 
