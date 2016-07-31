/* Automato Finito Deterministico (AFD)
 * Autores: Orlando Estefano de Almeida
 *          Heloisa Dias
 *          Inayara Nakoshi Izumi
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

#define MAX 100
using namespace std;

class Automato
{
public:
    vector<int> Estados;
    vector<char> Simbolos;
    int Transicoes[MAX][MAX];
    int estados_finais[MAX];       // Estados finais
    vector<int>w; //Palavra
    int q0[MAX];              // Estado inicial
    int Qt_Estados_Finais; //Quantidade de estados finais
    int numE;  // Numero de estados

public:        // declaração as funções
    void MostrarEstados(int);
    void CriarAutomato(int, char, int);
    void menu();
    bool VerificarPalavra(int, int, int, int);
    void ConverterPalavra(string, char, int);
    bool Cria_Automato_De_Arquivo(int, char, int, int);
    int main();

};

void MostrarEstados(vector<int> v)
{
    cout << "\n\n Estados do AFD \n\n"; // mostra a quantidade de estados do automato
    for(int i=0; i<v.size(); i++)
    {
        cout << " " << i <<"  -->  q" << v[i] << endl;
    }
}

void CriarAutomato(vector<int> &E, vector<char> &S, int T[MAX][MAX])
{
    Automato *ob = new Automato;
    int numS;  // Numero de simbolos
    char c;

    // Gerando estados
    cout << "\n Quantidade de estados: ";
    cin >> ob->numE;
    for(int i=0; i<ob->numE; i++)
    {
        E.push_back(i);  // Adiciona na proxima posição do vetor
    }

    // Inserindo simbolos
    cout << "\n Quantidade de Simbolos: ";
    cin >> numS;
    cout << endl;
    for(int i=0; i<numS; i++)
    {
        cout << "\t Simbolo " << i+1 << " : ";
        cin >> c;
        S.push_back(c);
    }
    sort(S.begin(),S.end());  // Ordenando os simbolos

    // Inserindo a matriz de transição
    cout << "\n INSIRA TABLA DE Transicoes \n\n";
    for(int i=0; i<ob->numE; i++)
    {
        for(int j=0; j<numS; j++)
        {
            printf("Q%d --> %c", i, S[j]);
            cout <<"\tT["<<i<<"]["<<j<<"] : Q";
            cin >> T[i][j];
        }
    }

    // Mostrando matriz de transição
    cout << "\n\n MATRIZ DE TRANSICOES \n\n";
    for(int i=0; i<ob->numE; i++)
    {
        for(int j=0; j<numS; j++)
        {
            cout << "\t" << T[i][j] << "  ";
        }
        cout << endl;
    }
}

void menu()
{
    int i;
    // Borda superior da tabela do menu
    printf("    %c", 201);
    for(i=0; i<63; i++)
    {
        printf("%c", 205);
    }
    printf("%c\n", 187);

    // Conteudo do Menu e suas barras laterais
    printf("    %c                 AUTOMATO FINITO DETERMINISTICO                %c\n", 186, 186);
    printf("    %c                                                               %c\n", 186, 186);
    printf("    %c   <1> Criar automato                                          %c\n", 186, 186);
    printf("    %c   <2> Verificar palavra                                       %c\n", 186, 186);
    printf("    %c   <3> Criar Automato apartir de arquivo                       %c\n", 186, 186);
    printf("    %c   <4> Sair                                                    %c\n", 186, 186);
    printf("    %c                                                               %c\n", 186, 186);
    printf("    %c                                                               %c\n", 186, 186);

    // Borda inferior da tabela do menu
    printf("    %c", 200);
    for(i=0; i<63; i++)
    {
        printf("%c", 205);
    }
    printf("%c\n", 188);
    cout << "\t opcao desejada: ";
}

bool VerificarPalavra(vector<int> w, int T[MAX][MAX], int q0[MAX],int estados_finais[MAX]) // Verifica se é uma palavra aceita pelo Automato
{
    Automato *ob = new Automato;
    int q, s; // Estado e Simbolos
    q = q0[0];  // Estado inicial
    bool EstadoVerificacao = false;

    for(int i=0; i<w.size(); i++)
    {
        s = w[i];
        q = T[q][s]; // estado atual
    }

    for(int i=0; i<=ob->Qt_Estados_Finais; i++)
    {
        if(q==estados_finais[i])
        {
            EstadoVerificacao = true;
            break;
        }
    }
    return EstadoVerificacao;
}

void ConverterPalavra(string Palavra, vector<char>S, vector<int>&w)
{

    int i, k=0;

    while(w.size()!=Palavra.length())
    {
        for(i=0; i<S.size(); i++)
        {
            if(Palavra[k]==S[i])
            {
                w.push_back(i);
            }
        }
        k++;
    }
}

bool Cria_Automato_De_Arquivo(vector<int> &E, vector<char> &S, int T[MAX][MAX], int estados_finais[MAX], int q0[MAX])  // Le do arquivo
{
    Automato *ob = new Automato;
    int numS;  // Numero de simbolos

    char simb;

    // Gerando estados
    cout << "\n Quantidade de estados: ";
    cin >> ob->numE;
    for(int i=0; i<ob->numE; i++)
    {
        E.push_back(i);  // Adiciona na proxima posição do vetor
    }

    // Definindo quantidade de estados finais
    cout << "\n Quantos estados finais Tem ?: ";
    cin >> ob->Qt_Estados_Finais;

    // Inserindo simbolos
    cout << "\n Quantidade de Simbolos: ";
    cin >> numS;
    cout << endl;
    for(int i=0; i<numS; i++)
    {
        cout << "\t Simbolo " << i+1 << " : ";
        cin >> simb;
        S.push_back(simb);
    }
    sort(S.begin(),S.end());  // Ordenando os simbolos

    ifstream txtFile; // Cria variavel de arquivo
    txtFile.open("TESTE.txt"); // Abre arquivo para leitura em modo texto

    // Le primeira linha do arquivo
    char init,ex; // ex variavel para pegar o caractere Q de qo...q1...qx
    txtFile >> init; // Pega aprimeira Linha do arquivo e aloca o ultimo caractere na variavel
    int atoi (const char * init);// Converte valor de caractere para inteiro
    q0[0] = init-48; // Reduz 48 para se obter o valor real do numero (ASCII)
    cout << "\nestado inicial Retirado do arquivo: " << q0[0];  // Mostra o estado inicial

    //Lendo a segunda linha do arquivo
    char estf;
    for(int i=0; i<ob->Qt_Estados_Finais; i++)
    {
        txtFile >> estf;
            int atoi (const char * estf); // Converte valor de caractere para inteiro
            estados_finais[i]=(estf-48); // Reduz 48 para se obter o valor real do numero (ASCII)
    }
    /// printando estados finais
    for(int i=0; i<ob->Qt_Estados_Finais; i++)
    {
        cout << "\n estado(s) final(s): " << estados_finais[i];
    }

    // Inserindo a matriz de transição
    char valor;
    for(int i=0; i<ob->numE; i++)
    {
        for(int j=0; j<numS; j++)
        {
            txtFile >> ex >> ex >> valor; //Pegando o valor da transição
            int atoi (const char * valor); // Converte valor de caractere para inteiro
            T[i][j] = (valor-48); // Reduz 48 para se obter o valor real do numero (ASCII)
        }
    }

    // Mostrando matriz de transição
    cout << "\n\n MATRIZ DE TRANSICOES \n\n";
    for(int i=0; i<ob->numE; i++)
    {
        for(int j=0; j<numS; j++)
        {
            cout << "\t" << T[i][j] << "  ";
        }
        cout << endl;
    }
    return true;
}

/*                  Função Principal
--------------------------------------------------------------*/
int main()
{
    Automato *ob = new Automato;
    bool AutomatoCriado = false;  // NÃO TEM AUTOMATO CRIADO
    int op, Qt_Estados_Finais,estf;

    do
    {
        menu();  // Chama a função Menu
        cin>>op;  // Pede para ser digitada uma opção do menu

        switch(op) // escolhe uma opção do menu, caso não seja uma opção válida exibe uma mensagem
        {

        case 1: // Cria um Automato apartir de entradas do teclado
            // Limpando Valores dos atributos
            ob->Estados.clear();
            ob->Simbolos.clear();
            //ob->estados_finais.clear();

            CriarAutomato(ob->Estados, ob->Simbolos, ob->Transicoes);
            MostrarEstados(ob->Estados);

            cout << "\n Informe o estado inicial: ";
            cin >> ob->q0[0];

            cout << "\n Quantos estados finais Tem ?: ";
            cin >> ob->Qt_Estados_Finais;

            cout << endl;
            for(int i=0; i<ob->Qt_Estados_Finais; i++)
            {
                cout << "\t Numero do(s) estado(s) final(s): ";
                cin >> estf;
                ob->estados_finais[i]= estf;
            }

            AutomatoCriado = true;
            break;

        case 2: // Verifica uma palavra digitada pertence ao alfabeto conhecido pelo Automato

            if(AutomatoCriado)
            {
                string Palavra;
                ob->w.clear();
                bool EstadoVerificacao = false;
                cout << "\n Insira a Palavra: ";
                cin>> Palavra;

                ConverterPalavra(Palavra, ob->Simbolos, ob->w);

                EstadoVerificacao = VerificarPalavra(ob->w, ob->Transicoes, ob->q0, ob->estados_finais);

                if(EstadoVerificacao)
                {
                    cout << "\n\t Palavra aceita \n\n";
                }
                else
                {
                    cout << "\n\t Palavra nao aceita \n\n";
                }
            }
            else
            {
                cout << "\n Automato nao Criado..! \n";
            }

            break;

        case 3: // Cria Automato aprtir de um arquivo se o arquivo existir
            // Limpando Valores dos atributos
            ob->Estados.clear();
            ob->Simbolos.clear();
           AutomatoCriado = Cria_Automato_De_Arquivo(ob->Estados, ob->Simbolos, ob->Transicoes, ob->estados_finais, ob->q0);
           MostrarEstados(ob->Estados);
            break;

        case 4: // Sai do Programa
            exit(0);

        default:
            cout << "\n\tOpcao incorreta..!\n";
            break;
        }

        cout << "\n\n";
        system("pause");
        system("cls");

    }
    while(op!=4);
}
