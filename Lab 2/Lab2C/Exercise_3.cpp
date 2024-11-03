#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <vector>
#include <map>
#define fi first
#define se second
#define pii pair<int,int>
#define vii vector<pii>
#define pb push_back
#define mp make_pair
#define MAX_BUFF 255

using namespace std;

const char* fileNameIn = "input.txt";
const char* fileNameOut = "output.txt";

struct candidateInfo{
    float avergaeScore;
    float score1, score2;
    char name[MAX_BUFF];
    vector <int> opt;    
};

void init(const char* fileName, map<int, int>&mp, vector<candidateInfo*> &candidate, int &m){
    fstream f(fileName, ios::in);
    if (!f){
        cout << "Can't open file " << fileName << "\n";
        return;
    }
    f >> m;
    for (int i = 0; i < m; i++){
        int x, y;
        f >> x >> y;
        mp[x] = y;
    }

    char buff[MAX_BUFF];
    f.getline(buff, MAX_BUFF);
    while(f.getline(buff, MAX_BUFF)){
        if (strlen(buff) == 0) break;
        istringstream iss(buff);
        candidateInfo* newCandidate = new candidateInfo;
        iss.getline(newCandidate->name, MAX_BUFF, ',');

        iss.getline(buff, MAX_BUFF, ',');       
        newCandidate->score1 = atof(buff);

        iss.getline(buff, MAX_BUFF, ',');
        newCandidate->score2 = atof(buff);

        for (int i = 0; i < m; i++){
            iss.getline(buff, MAX_BUFF, ',');
            newCandidate->opt.pb(atoi(buff));
        }
        newCandidate->avergaeScore = (newCandidate->score1 + newCandidate->score2) / 2;
        newCandidate->avergaeScore = (int)(newCandidate->avergaeScore * 100) / 100.0;
        // cout << newCandidate->name << " " << newCandidate->avergaeScore << "\n";
        candidate.pb(newCandidate);
    }
    f.close();
}

bool isLowerThan(candidateInfo* a, candidateInfo* b){
    if (a->avergaeScore < b->avergaeScore)
        return true;
    else if (a->avergaeScore > b->avergaeScore)
        return false;
    else
        if (a->score1 < b->score1)
            return true;
        else if (a->score1 > b->score1)
            return false;
        else
            if (a->score2 < b->score2)
                return true;
            else if (a->score2 > b->score2)
                return false;
            else return true;
}

void selectionSort(vector<candidateInfo*> &candidate){
    int n = candidate.size();
    for (int i = 0; i < n - 1; i++){
        int maxID = i;
        for (int j = i + 1; j < n; j++){
            if (isLowerThan(candidate[maxID], candidate[j]))
                maxID = j;
        }
        if (maxID != i){
            candidateInfo* tmp = candidate[i];
            candidate[i] = candidate[maxID];
            candidate[maxID] = tmp;
        }
    }
}

void process(const char* fileName, vector<candidateInfo*> candidate, int m, map<int, int> mp){
    fstream f(fileName, ios::out);
    if (!f){
        cout << "Can't open file " << fileName << "\n";
        return;
    }
    selectionSort(candidate);
    map<int, vector<candidateInfo*>> result;
    vector<candidateInfo*> unsuccesful;

    bool flag = false;
    int id = 0;
    for(candidateInfo* c : candidate){
        // cout << ++id << ". " << c->name << " " << c->avergaeScore << "\n";
        flag = false;
        for (int i = 0; i < m; i++){
            int opt = c->opt[i];
            if (mp[opt] > 0){
                result[opt].pb(c);
                mp[opt]--;
                flag = true;
                break;
            }
        }
        if (!flag) unsuccesful.pb(c);
    }

    for (auto it = result.begin(); it != result.end(); it++){
        f << "Successful candidates for option " << it->fi << "\n";
        id = 0;
        for (candidateInfo* c : it->se){
            f << ++id << ". " << c->name << " " << c->avergaeScore << "\n";
        }
    }
    id = 0;
    f << "Unsuccessful candidates\n";
    for (candidateInfo* c : unsuccesful){
        f << ++id << ". " << c->name << " " << c->avergaeScore << "\n";
    }
    f.close();
}

void freeData(vector<candidateInfo*> &candidate){
    for (candidateInfo* c : candidate){
        delete c;
    }
}

int main(){
    map<int, int> mp;
    vector<candidateInfo*> candidate;
    int m;
    init(fileNameIn, mp, candidate, m);
    process(fileNameOut, candidate, m, mp);
    return 0;
}






