#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Configuratie {
private:
    char s;
    int i;
    string alpha;
    string beta;
public:
    Configuratie() {
    s = 'q';
    i = 1;
    alpha = "$";
    beta = "";}
    Configuratie(char s, int i, string alpha, string beta) {
        this->s = s;
        this->i = i;
        this->alpha = alpha;
        this->beta = beta;
    }
    char getS() {
        return s;
    }
    void setS(char s) {
        this->s = s;
    }
    int getI() {
        return i;
    }
    void setI(int i) {
        this->i = i;
    }
    string getAlpha() {
        return alpha;
    }
    void setAlpha(string alpha) {
        this->alpha = alpha;
    }
    string getBeta() {
        return beta;
    }
    void setBeta(string beta) {
        this->beta = beta;
    }

    friend ostream& operator<<(ostream& os, const Configuratie& cf);

};

ostream& operator<<(ostream& os, const Configuratie& cf)
{
    os<<'('<<cf.s<<','<<cf.i<<','<<cf.alpha<<','<<cf.beta<<")\n";
    return os;
}


class BottomUp {
private:
    vector<pair<int, pair<char, string>>> g;
    char S; //simbolul de start
    string w;
    ifstream fin;
    Configuratie config;
    int n;
public:
    BottomUp(string caleIntrare) {
        fin.open(caleIntrare);
        if(!fin.is_open()) {
            cout<<"Fisierul nu a putut fi deschis!";
        }

        string line;
        // citeste cuvantul de intrare
        getline(fin, line);
        w = "$" + line;
        n = w.size() - 1; // n = lungimea lui w fara $

        int it = 1;
        // citeste caracterul de start al gramaticii
        getline(fin, line);
        S = line[0];

        // citeste productiile gramaticii
        while(getline(fin, line)) {
            if(line != "") {
                char key;
                string word = "";
                unsigned idx = 0;

                // Ia primul simbol neterminal din stanga
                while(line[idx] != ' ' && idx != line.size()) {
                    ++idx;
                }
                // Daca nu s-a ajuns la final de linie cautand primul neterminal
                if(idx != line.size()) {
                    key = line[idx - 1]; // pentru ca line[idx] este spatiul pe care ne-am oprit
                    ++idx;               // mergem la urmatorul caracter de dupa spatiu

                    for (unsigned i = idx; i < line.size(); ++i) {
                        if (line[i] == ' ') {
                            g.push_back({it, {key, word}});
                            word = "";
                            ++it;
                        }
                        else {
                            word = word + line[i];
                        }
                    }
                    // adaugam si ce a ramas in word cand s-a terminat linia
                    if(word != "") {
                        g.push_back({it, {key, word}});
                        ++it;
                    }
                }
            }
        }
        /*for(int i = 0; i < g.size();i++) {
            cout<<g[i].first<<' ' <<g[i].second.first<<"->"<<g[i].second.second<<'\n';
        }*/
    }

    bool esteSufix(string s1, string s2)
    {
        int n1 = s1.length(), n2 = s2.length();
        if (n1 > n2)
          return false;
        for (int i=0; i<n1; i++)
           if (s1[n1 - i - 1] != s2[n2 - i - 1])
               return false;
        return true;
    }

    bool esteAcceptare() {
        return (config.getS() == 't');
    }

    void reducere(int i, int pozSuf) {
        // Caz 1
        stringstream ss;
        string index;
        string newAlpha = config.getAlpha().substr(0, pozSuf);
        newAlpha += g[i].second.first;
        config.setAlpha(newAlpha);
        // convert int to string
        ss<<g[i].first;
        ss>>index;
        string newBeta = index + config.getBeta();
        config.setBeta(newBeta);
    }

    void deplasare() {
        // Caz 2
        string newAlpha = config.getAlpha();
        newAlpha += w[config.getI()];
        string newBeta = "d" + config.getBeta();

        config.setI(config.getI() + 1);
        config.setAlpha(newAlpha);
        config.setBeta(newBeta);
    }

    void acceptare() {
        // caz 3
        config.setS('t');
    }

    void revenire() {
        // caz 4
        config.setS('r');
    }

    void caz5a(string newAlpha, int k) {
        config.setS('q');
        config.setAlpha(newAlpha);

        // convert k la string
        stringstream ss;
        string index;
        ss<<(k);
        ss>>index;
        // ia valoarea lui beta mai putin caracterul de pe prima pozitie; inainte adauga k
        string newBeta = index + config.getBeta().substr(1, config.getBeta().size() - 1);
        config.setBeta(newBeta);

    }

    void caz5b(string newAlpha) {
        config.setAlpha(newAlpha);
        // elimin primul caracter din beta
        string newBeta = config.getBeta().substr(1, config.getBeta().size() - 1);
        config.setBeta(newBeta);
    }

    void caz5c(string newAlpha) {
        config.setS('q');

        char ai = w[config.getI()];
        newAlpha += ai;
        string newBeta = "d" + config.getBeta().substr(1, config.getBeta().size() - 1);

        config.setI(config.getI() + 1);
        config.setAlpha(newAlpha);
        config.setBeta(newBeta);
    }

    void caz5d() {
        config.setI(config.getI() - 1);
        // elimina ultimul caracter
        string newAlpha = config.getAlpha().substr(0, config.getAlpha().size() - 1);
        // elimina primul caracter
        string newBeta = config.getBeta().substr(1, config.getBeta().size() - 1);
        config.setAlpha(newAlpha);
        config.setBeta(newBeta);
    }

    void cazEroare() {
        config.setS('e');
    }

    string parsareBottomUp() {
        while(!esteAcceptare()) {
            cout<<config;
            if(config.getS() == 'q') {
                // verificam daca suntem in cazurile 1, 2 sau 4 (3 e verificat in while)
                int idxI = -1, idxSuf = -1;
                for(unsigned i = 0; i < g.size(); ++i)
                    if(esteSufix(g[i].second.second, config.getAlpha())) {
                        idxI = i;
                        idxSuf = config.getAlpha().size() - g[i].second.second.size();
                        break;
                    }

                if(idxI != -1) {
                    // suntem pe cazul 1
                    cout<<"Cazul 1\n";
                    reducere(idxI, idxSuf);
                }
                else if(config.getI() < n + 1){
                    // caz 2
                    cout<<"Cazul 2\n";
                    deplasare();
                }
                else {
                    string endAlpha = "$";
                    endAlpha += S;
                    if(config.getAlpha().compare(endAlpha) == 0) {
                        //caz 3
                        cout<<"Cazul 3\n";
                        acceptare();
                    }
                    else {
                        // caz 4
                        cout<<"Cazul 4\n";
                        revenire();
                    }
                }
            }
            else if (config.getS() == 'r') {
                if(config.getBeta() != "" && config.getBeta()[0] != 'd') {
                    // cazuri 5 a-c
                    int idxK = -1;
                    int j = (config.getBeta()[0] - '0') - 1; // indecsii sunt cu 1 in plus
                    // ultimul caracter e neterminal
                    unsigned sizeSubStr = config.getAlpha().size() - 1;
                    string alphaBeta = config.getAlpha().substr(0, sizeSubStr);
                    alphaBeta += g[j].second.second;
                    // parcurgem alte productii care s-ar potrivi in alphabeta
                    for(unsigned k = j + 1; k < g.size(); k++)
                        if(esteSufix(g[k].second.second, alphaBeta)) {
                            idxK = k;
                            break;
                    }

                    if(idxK != -1) {
                        // caz 5a
                        cout<<"Cazul 5a\n";

                        sizeSubStr = alphaBeta.size() - g[j].second.second.size();
                        string alphaPr = alphaBeta.substr(0, sizeSubStr);
                        alphaPr += g[idxK].second.first;
                        cout<<"j="<<j<<' '<<g[j].second.second<<' '<<g[idxK].second.second<<'\n';
                        cout<<idxK<<' '<<alphaBeta<<' ';
                        cout<<"\nSize substr: "<<sizeSubStr<<' '<<alphaPr<<'\n';
                        caz5a(alphaPr, idxK+1);
                    }
                    else if(config.getI() == (n + 1)) {
                        // caz 5b
                        cout<<"Cazul 5b\n";
                        caz5b(alphaBeta);
                    }
                    else {
                        // caz 5c
                        cout<<"Cazul 5c\n";
                        caz5c(alphaBeta);
                        cout<<config;
                    }
                }
                else if (config.getI() != 1) {
                    // caz 5d
                    cout<<"Cazul 5d\n";
                    caz5d();
                }
                else {
                    // caz 5e
                    cout<<"Cazul 5e\n";
                    cazEroare();
                    cout<<config;
                    return "ERROR";
                }

            }
        }
        // inlocuieste d cu '' in beta
        string beta = config.getBeta();
        string result;
        for(unsigned i = 0; i < beta.size(); i++) {
            if(beta[i] != 'd')
                result += beta[i];
        }
        return result;
    }


};
int main()
{
    BottomUp bottomUp("test.in");
    cout<<bottomUp.parsareBottomUp();
    return 0;
}
