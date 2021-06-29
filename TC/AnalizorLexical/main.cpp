#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>
#define CUVANTCHEIE 1000
#define Q_ERR_LEX   -1
#define Q_EOF       -2
using namespace std;


class Token {
    int tip;
    int valoare;
public:
    Token(int tip, int valoare) {
        this->tip = tip;
        this->valoare = valoare;
    }
    int getTip() {
        return tip;
    }
    int getValoare() {
        return valoare;
    }
};

class AnalizorLexical {
private:
    vector<string> valoriToken;
    vector<string> cuvinteCheie{"auto", "break", "case", "char", "const", "continue", "default", "do",
                                "double", "else", "enum", "extern", "float", "for", "goto", "if", "inline",
                                "int", "long", "register", "restrict", "return", "short", "signed", "sizeof",
                                "static", "struct", "switch", "typedef", "union", "unsigned", "void",
                                "volatile", "while", "_Alignas", "_Alignof", "_Atomic", "_Bool", "_Complex",
                                "_Generic", "_Imaginary", "_Noreturn", "_Static_assert", "_Thread_local"};
    int q0;
    vector<char> Q{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                   'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                   '_', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                   '.', '+', '-', ',', ';', '{', '}', '[', ']', '(', ')', '"', '/', '*', '=', '&', '|', '^', '<', '>', '!', '~', '%', '#', '?', ':', '$', '@', ' ', '\\', '\''};
    vector<int> F{1, 3, 4, 6, 9, 10, 11, 12, 13, 14, 15, 18, 19,
                  21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
                  36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
                  51, 52, 53, 54, 55, 56, 57, 58, 60, 63, 64}; // vector ce contine starile finale
    map<pair<int, char>, int> T; // vector de tranzitii
    map<int, string> stariNume{{CUVANTCHEIE, "cuvant cheie"}, {1, "identificator"}, {3, "literal string"},
                                {4, "constanta intreaga"}, {6, "constanta flotanta"}, {9, "constanta flotanta"},
                                {10, "constanta flotanta"}, {11, "operator +"}, {12, "constanta intreaga"}, {13, "constanta binara"},
                                {14, "constanta hexa"}, {15, "constanta octala"}, {18, "literal caracter"}, {19, "operator ."},
                                {21, "operator ..."}, {22, "operator -"}, {23, "operator ++"}, {24, "operator +="}, {25, "operator --"},
                                {26, "operator -="}, {27, "operator ->"}, {28, "operator <"}, {29, "operator <<"}, {30, "operator <<="},
                                {31, "operator <="}, {32, "operator >"}, {33, "operator >>"}, {34, "operator >>="}, {35, "operator >="},
                                {36, "operator |"}, {37, "operator ||"}, {38, "operator |="}, {39, "operator &"}, {40, "operator &&"},
                                {41, "operator &="}, {42, "operator *"}, {43, "operator *="}, {44, "operator ="}, {45, "operator =="},
                                {46, "operator %"}, {47, "operator %="}, {48, "operator !"}, {49, "operator !="}, {50, "operator ^"},
                                {51, "operator ^="}, {52, "operator ~"}, {53, "operator :"}, {54, "operator ;"}, {55, "operator paranteza"},
                                {56, "operator acolada"}, {57, "operator /"}, {58, "operator /="}, {60, "comentariu pe o singura linie"},
                                {63, "comentariu pe mai multe linii"}, {64, "separator , "}};

    int pozitieCurenta;
    ifstream fisier;
public:
    AnalizorLexical(string caleF) {
        q0 = 0;
        pozitieCurenta = 0;
        fisier.open(caleF);
        if(!fisier.is_open()) {
            cout<<"Fisierul nu a putut fi deschis!";
        }
        // construim tranzitiile
        // Formare cuvant cheie sau identificator
        // q0 - q1 cu a-z, A-Z, _
        for(char c = 'a'; c <= 'z'; ++c) {
            T.insert({{0, c}, 1});
        }
        for(char c = 'A'; c <= 'Z'; ++c) {
            T.insert({{0, c}, 1});
        }
        T.insert({{0, '_'}, 1});

        // q1 - q1 cu a-z, A-Z, 0-9, _
        for(char c = 'a'; c <= 'z'; ++c) {
            T.insert({{1, c}, 1});
        }
        for(char c = 'A'; c <= 'Z'; ++c) {
            T.insert({{1, c}, 1});
        }
        for(char c = '0'; c <= '9'; ++c) {
            T.insert({{1, c}, 1});
        }
        T.insert({{1, '_'}, 1});

        //Formare literal string
        T.insert({{0, '"'}, 2});
        int qSize = Q.size();
        for (int i = 0; i < qSize; ++i) {
            if(Q[i] != '"' && Q[i] !='\\')
                T.insert({{2, Q[i]}, 2});
        }
        T.insert({{2, '\t'}, 2});
        T.insert({{2, '"'}, 3});
        //Stare de blocaj daca se trece la rand nou in interiorul stringului sau daca dupa " urmeaza alte
        T.insert({{2, '\n'}, 102});
        T.insert({{2, '\r'}, 102});
        T.insert({{2, '\f'}, 102});
        T.insert({{2, '\v'}, 102});
        T.insert({{2, '\r\n'}, 102});

        T.insert({{2, '\\'}, 80});

        T.insert({{80, '\n'}, 2});
        T.insert({{80, '\r'}, 2});
        T.insert({{80, '\f'}, 2});
        T.insert({{80, '\v'}, 2});
        T.insert({{80, '\t'}, 2});
        T.insert({{80, '\r\n'}, 2});

        /*for (int i = 0; i < qSize; ++i) {
                T.insert({{2, Q[i]}, 2});
        }*/
        //Formare constante
        //1, 2,....9, 100, 1242...
        for(char c = '1'; c <= '9'; ++c) {
            T.insert({{0, c}, 4});
        }
        for(char c = '0'; c <= '9'; ++c) {
            T.insert({{4, c}, 4});
        }
        //stare blocanta; daca gasim semne de punctuatie
        vector<char> semnPct{'@', '#', '$', '_', '[', ']'};
        int sPSize = semnPct.size();
        for(int i = 0; i < sPSize; ++i) {
            T.insert({{4, semnPct[i]}, 102});
        }
        for(char c = 'a'; c <='z'; ++c) {
            if(c != 'e' && c != 'f' && c != 'l')
                T.insert({{4, c}, 102});
        }
        for(char c = 'A'; c <='Z'; ++c) {
            if(c != 'E' && c != 'F' && c != 'L')
                T.insert({{4, c}, 102});
        }

        //constanta flotanta: 1.43, 214.09842
        T.insert({{4, '.'}, 5});
        T.insert({{0, '.'}, 19});
        for(char c = '0'; c <= '9'; ++c) {
            T.insert({{5, c}, 6});
            T.insert({{6, c}, 6});
            T.insert({{19, c}, 6});
        }
        //stare blocanta
        for(int i = 0; i < sPSize; ++i) {
            T.insert({{6, semnPct[i]}, 102});
        }
        for(char c = 'a'; c <='z'; ++c) {
            if(c != 'e' && c != 'f' && c != 'l')
                T.insert({{6, c}, 102});
        }
        for(char c = 'A'; c <='Z'; ++c) {
            if(c != 'E' && c != 'F' && c != 'L')
                T.insert({{6, c}, 102});
        }
        //constanta ce contine E, e
        T.insert({{6, 'e'}, 7});
        T.insert({{6, 'E'}, 7});
        T.insert({{4, 'e'}, 7});
        T.insert({{4, 'E'}, 7});
        T.insert({{7, '+'}, 8});
        T.insert({{7, '-'}, 8});
        for(char c = '0'; c <= '9'; ++c) {
            T.insert({{8, c}, 9});
            T.insert({{9, c}, 9});
            T.insert({{7, c}, 9});
        }
        //constanta ce contine F, f, L, l
        //123F
        T.insert({{4, 'f'}, 10});
        T.insert({{4, 'F'}, 10});
        T.insert({{4, 'l'}, 10});
        T.insert({{4, 'L'}, 10});
        //12.34F
        T.insert({{6, 'f'}, 10});
        T.insert({{6, 'F'}, 10});
        T.insert({{6, 'l'}, 10});
        T.insert({{6, 'L'}, 10});
        //12.34e-3F
        T.insert({{9, 'f'}, 10});
        T.insert({{9, 'F'}, 10});
        T.insert({{9, 'l'}, 10});
        T.insert({{9, 'L'}, 10});
        //constana cu +,- in fata; -11.3, +32.124e-43
        T.insert({{0, '+'}, 11});
        T.insert({{0, '-'}, 22});
        for(char c = '1'; c <= '9'; ++c) {
            T.insert({{11, c}, 4});
            T.insert({{22, c}, 4});
        }

        //stare blocanta
        for(int i = 0; i < sPSize; ++i) {
            T.insert({{9, semnPct[i]}, 102});
        }
        for(char c = 'a'; c <='z'; ++c) {
            if(c != 'e' && c != 'f' && c != 'l')
                T.insert({{9, c}, 102});
        }
        for(char c = 'A'; c <='Z'; ++c) {
            if(c != 'E' && c != 'F' && c != 'L')
                T.insert({{9, c}, 102});
        }

        //stare blocanta
        for(int i = 0; i < sPSize; ++i) {
            T.insert({{10, semnPct[i]}, 102});
        }
        for(char c = 'a'; c <='z'; ++c) {
            if(c != 'e' && c != 'f' && c != 'l')
                T.insert({{10, c}, 102});
        }
        for(char c = 'A'; c <='Z'; ++c) {
            if(c != 'E' && c != 'F' && c != 'L')
                T.insert({{10, c}, 102});
        }

        //stare blocanta
        for(int i = 0; i < sPSize; ++i) {
            T.insert({{12, semnPct[i]}, 102});
        }
        for(char c = 'a'; c <='z'; ++c) {
            if(c != 'e' && c != 'f' && c != 'l')
                T.insert({{12, c}, 102});
        }
        for(char c = 'A'; c <='Z'; ++c) {
            if(c != 'E' && c != 'F' && c != 'L')
                T.insert({{12, c}, 102});
        }

        //constante ce incep cu 0; constanta 0, binare, hexa, octale
        T.insert({{0, '0'}, 12});
        //contante binare
        T.insert({{12, 'b'}, 13});
        T.insert({{12, 'B'}, 13});
        T.insert({{13, '0'}, 13});
        T.insert({{13, '1'}, 13});

        //stare blocanta
        for(int i = 0; i < sPSize; ++i) {
            T.insert({{13, semnPct[i]}, 103});
        }
        for(char c = 'a'; c <='z'; ++c) {
                T.insert({{13, c}, 103});
        }
        for(char c = 'A'; c <='Z'; ++c) {
                T.insert({{13, c}, 103});
        }
        for(char c = '2'; c <='9'; ++c) {
                T.insert({{13, c}, 103});
        }

        //constante hexa
        T.insert({{12, 'x'}, 14});
        T.insert({{12, 'X'}, 14});
        for(char c = 'a'; c <= 'f'; ++c) {
            T.insert({{14, c}, 14});
        }
        for(char c = 'A'; c <= 'F'; ++c) {
            T.insert({{14, c}, 14});
        }
        for(char c = '0'; c <= '9'; ++c) {
            T.insert({{14, c}, 14});
        }

        //stare blocanta
        for(int i = 0; i < sPSize; ++i) {
            T.insert({{14, semnPct[i]}, 104});
        }
        for(char c = 'g'; c <='z'; ++c) {
                T.insert({{14, c}, 104});
        }
        for(char c = 'G'; c <='Z'; ++c) {
                T.insert({{14, c}, 104});
        }
        //constante octale
        for(char c = '0'; c <= '7'; ++c) {
            T.insert({{12, c}, 15});
            T.insert({{15, c}, 15});
        }

        //stare blocanta
        for(int i = 0; i < sPSize; ++i) {
            T.insert({{15, semnPct[i]}, 105});
        }
        for(char c = 'a'; c <='z'; ++c) {
                T.insert({{15, c}, 105});
        }
        for(char c = 'A'; c <='Z'; ++c) {
                T.insert({{15, c}, 105});
        }
        for(char c = '8'; c <='9'; ++c) {
                T.insert({{15, c}, 105});
        }


        //literal caracter
        T.insert({{0, '\''}, 16});
        for (int i = 0; i < qSize; ++i) {
            if(Q[i] != '\'')
                T.insert({{16, Q[i]}, 17});
        }
        T.insert({{17, '\''}, 18});

        //operator ...
        T.insert({{19, '.'}, 20});
        T.insert({{20, '.'}, 21});

        //operatori cu +
        T.insert({{11, '+'}, 23});
        T.insert({{11, '='}, 24});

        //operatori cu -
        T.insert({{22, '-'}, 25});
        T.insert({{22, '='}, 26});
        T.insert({{22, '>'}, 27});

        //operatori cu <
        T.insert({{0, '<'}, 28});
        T.insert({{28, '<'}, 29});
        T.insert({{29, '='}, 30});
        T.insert({{28, '='}, 31});

        //operatori cu >
        T.insert({{0, '>'}, 32});
        T.insert({{32, '>'}, 33});
        T.insert({{32, '='}, 35});
        T.insert({{33, '='}, 34});

        //operatori cu |
        T.insert({{0, '|'}, 36});
        T.insert({{36, '|'}, 37});
        T.insert({{36, '='}, 38});

        //operatori cu &
        T.insert({{0, '&'}, 39});
        T.insert({{39, '&'}, 40});
        T.insert({{39, '='}, 41});

        //operatori cu *
        T.insert({{0, '*'}, 42});
        T.insert({{42, '='}, 43});

        //operatori cu =
        T.insert({{0, '='}, 44});
        T.insert({{44, '='}, 45});

        //operatori cu %
        T.insert({{0, '%'}, 46});
        T.insert({{46, '='}, 47});

        //operatori cu !
        T.insert({{0, '!'}, 48});
        T.insert({{48, '='}, 49});

        //operatori cu ^
        T.insert({{0, '^'}, 50});
        T.insert({{50, '='}, 51});

        //operator ~
        T.insert({{0, '~'}, 52});

        //operator :
        T.insert({{0, ':'}, 53});

        //operator ;
        T.insert({{0, ';'}, 54});

        //operator [],()
        T.insert({{0, '['}, 55});
        T.insert({{0, ']'}, 55});
        T.insert({{0, '('}, 55});
        T.insert({{0, ')'}, 55});

        //operator { }
        T.insert({{0, '{'}, 56});
        T.insert({{0, '}'}, 56});

        //operatori /, /=, si comentarii
        T.insert({{0, '/'}, 57});
        T.insert({{57, '='}, 58});
        T.insert({{57, '/'}, 59});
        for (int i = 0; i < qSize; ++i) {
            T.insert({{59, Q[i]}, 59});
        }
        T.insert({{59, '\n'}, 60}); //comentariu pe o singura linie
        T.insert({{59, '\f'}, 60});
        T.insert({{59, '\r'}, 60});
        T.insert({{59, '\r\n'}, 60});
        T.insert({{57, '*'}, 61});
        for (int i = 0; i < qSize; ++i) {
            if(Q[i] != '*')
                T.insert({{61, Q[i]}, 61});
        }
        T.insert({{61, '\n'}, 61});
        T.insert({{61, ' '}, 61});
        T.insert({{61, '\t'}, 61});
        T.insert({{61, '\v'}, 61});
        T.insert({{61, '\f'}, 61});
        T.insert({{61, '\r'}, 61});
        T.insert({{61, '\r\n'}, 61});
        T.insert({{61, '*'}, 62});
        T.insert({{62, '*'}, 62});
        for (int i = 0; i < qSize; ++i) {
            if(Q[i] != '*' &&  Q[i] != '/')
                T.insert({{62, Q[i]}, 61});
        }
        T.insert({{62, '\n'}, 61});
        T.insert({{62, ' '}, 61});
        T.insert({{62, '\t'}, 61});
        T.insert({{62, '\v'}, 61});
        T.insert({{62, '\f'}, 61});
        T.insert({{62, '\r'}, 61});
        T.insert({{62, '\r\n'}, 61});
        T.insert({{62, '/'}, 63});


        //separator ,
        T.insert({{0, ','}, 64});


        //sarim peste spatii, \n, \t
        T.insert({{0, ' '}, 0});
        T.insert({{0, '\n'}, 0});
        T.insert({{0, '\t'}, 0});
        T.insert({{0, '\v'}, 0});
        T.insert({{0, '\f'}, 0});
        T.insert({{0, '\r'}, 0});
        T.insert({{0, '\r\n'}, 0});

    }
    char citesteCaracter() {
        char c;
        fisier.get(c);
        return c;
    }

    void incrementPozitieCurenta() {
        pozitieCurenta++;
    }

    string iaNumeStareFinala(int stare) {
        return (stariNume.find(stare))->second;
    }

    string iaValoareToken(int pos) {
        return valoriToken[pos];
    }

    string iaCuvantCheie(int pos) {
        return cuvinteCheie[pos];
    }

    bool esteStareFinala(int q) {
        // verifica daca q este stare finala si returneaza true daca este, false in caz contrar
        if(find(F.begin(), F.end(), q) != F.end())
            return true;
        return false;
    }

    bool finalFisier() {
        return fisier.eof();
    }

    int esteCuvantCheie(string s) {
        // verifica daca s este cuvant cheie; daca da, ii returneaza pozitia; altfel returneaza -1
        int cSize = cuvinteCheie.size();
        for(int i = 0; i < cSize; ++i) {
            if(s.compare(cuvinteCheie[i]) == 0)
                return i;
        }
        return -1;
    }

    bool esteComentariu(int q) {
        return (q == 60 || q == 63);
    }
    int adaugaValoareToken(string s) {
        int vSize = valoriToken.size();
        for(int i = 0; i < vSize; ++i) {
            if(s.compare(valoriToken[i]) == 0)
                return i;
        }
        // string-ul nu a fost gasit, il adaugam la final si returnam pozitia
        valoriToken.push_back(s);
        return vSize;
    }

    Token getToken(char& c) {
        int q = q0;
        string token;
        map<pair<int, char>, int>::iterator it;
        it = T.find({q, c});
        while(it != T.end()){
            if(finalFisier())
                break;
            cout<<"carcat:"<<(int)c<<'-';
            cout<<"starea:"<<q<<'\n';
            // ignoram spatiile dinaintea unui token
            if(!(q == q0 && isspace(c)))
                token += c;
            q = it->second;
            fisier.get(c);
            pozitieCurenta++;
            it = T.find({q, c});

        }
        //cout<<token;
        if(esteStareFinala(q)) {
            if(esteComentariu(q)) {
                    return getToken(c);
            }
            else {
                int pCuvCheie = esteCuvantCheie(token);
                if(q == 1 && pCuvCheie != -1) {
                    return Token(CUVANTCHEIE, pCuvCheie);
                }
                else {
                    int pos = adaugaValoareToken(token);
                    return Token(q, pos);
                }
            }

        }
        else if(!finalFisier()) {
            cout<<"Token:"<<token<<" q="<<q;
            return Token(Q_ERR_LEX, c);
        }
        else {
            return Token(Q_EOF, -1);
        }
    }
};
int main()
{
    AnalizorLexical analizor("test1.in");
    ofstream out("rezultat.out");
    char c;
    bool stop = 0;
    if(!analizor.finalFisier()) {
        analizor.incrementPozitieCurenta();
        c = analizor.citesteCaracter();
        while(!analizor.finalFisier() && !stop) {
            Token t = analizor.getToken(c);
            int tip = t.getTip();
            switch(tip) {
              case CUVANTCHEIE:
                cout<<analizor.iaNumeStareFinala(tip)<<" cu valoarea "<<analizor.iaCuvantCheie(t.getValoare())<<'\n';
                break;
              case Q_ERR_LEX:
                stop = 1;
                cout<<"Eroare lexicala la pozitia "<<t.getValoare()<<'\n';
                break;
              case Q_EOF:
                break;
              default:
                    cout<<analizor.iaNumeStareFinala(t.getTip())<<" cu valoarea "<<analizor.iaValoareToken(t.getValoare())<<'\n';
            }
        }
    }

    return 0;
}
