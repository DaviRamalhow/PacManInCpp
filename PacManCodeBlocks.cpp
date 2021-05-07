#include <iostream>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <cstdlib>
#include <time.h>
#include <string>
#include <fstream>
#include <sstream>
#include <time.h>

using namespace std;
time_t inicio, fim;
int backcolor=0;
int dir = 0;
int x=39,y=22;
int anteriorpx,anteriorpy;
char tecla;
int pts = 0;
string nome;
int vidas = 3;
string linha;
fstream arq1;
ofstream arqSave;
ifstream arqLoad;
bool pastilha;
bool SaveConfir = false;
bool SaveOpen = false;
char Resposta;
int Fase =1;
bool Fase2;
bool Fase3;
void gotoxy( int x, int y ){
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE) ;
    COORD position = { x, y } ;

    SetConsoleCursorPosition( hStdout, position ) ;
}//função setinhas.|______


char mapa[50][100] = {//MAPA NÉ|__
"-------------------------------------------------------------",
"------------------A___________________B-A___________________B",
"------------------|...................|-|...................|",
"------------------|.A_____B.A_______B.|-|.A_______B.A_____B.|",
" -----------------|.|-----|.|-------|.|-|.|-------|.|-----|.|",
"------------------|.D_____p.D_______p.D_p.D_______p.D_____p.|",
"------------------|.........................................|",
"------------------|.A_____B.A_B.A_____________B.A_B.A_____B.|",
"------------------|.D_____p.|-|.D____B---A____p.|-|.D_____p.|",
"------------------|.........|-|......|---|......|-|.........|",
"------------------D_______B.|-D____B.|---|.A____p-|.A_______p",
"--------------------------|.|-A____p.D___p.D____B-|.|--------",
"--------------------------|.|-|.................|-|.|--------",
"--------------------------|.D_p.A______-______B.D_p.|--------",
"--------------------------|.....|------*------|.....|--------",
"--------------------------|.A_B.D_____________p.A_B.|--------",
"--------------------------|.|-|.................|-|.|--------",
"--------------------------|.|-|.A_____________B.|-|.|--------",
"------------------A_______p.D_p.D____B---A____p.D_p.D_______B",
"------------------|..................|---|..................|",
"------------------|.A_____B.A______B.|---|.A______B.A_____B.|",
"------------------|.D___B-|.D______p.D___p.D______p.|-A___p.|",
"------------------|.....|-|.........................|-|.....|",
"------------------D___B.|-|.A_B.A_____________B.A_B.|-|.A___p",
"------------------A___p.D_p.|-|.D____B---A____p.|-|.D_p.D___B",
"------------------|.........|-|......|---|......|-|.........|",
"------------------|.A_______p-D____B.|---|.A____p-D_______B.|",
"------------------|.D______________p.D___p.D______________p.|",
"------------------|.........................................|",
"------------------D_________________________________________p",
};
int color [7]= { //É A COR
      0x009,
      0x00E,
      0x00C,
      0x002,
      0x00B,
      0x005,
      0x00F

     };
void setCColor( int color = 0)//ENFIA COR
{
        static HANDLE hConsole;

        hConsole = GetStdHandle( STD_OUTPUT_HANDLE );

        SetConsoleTextAttribute( hConsole, color | (backcolor * 0x10 + 0x100) );
}
void pintar_mapa()//PINTA O MAPA
{
     for(int i = 0 ; i < 78 ; i++){
         for(int j = 0 ; j < 30 ; j++){
               gotoxy(i,j);
//DA COR E FORMA PARA TODO O MAPA
               if(mapa[j][i] == ' ') {mapa[j][i] = '.';}
               if(mapa[j][i] == '_') {setCColor(color[0]);printf("%c",205);}
               if(mapa[j][i] == '.') {setCColor(color[1]); printf("%c",250);}
               else if(mapa[j][i] == '|') {setCColor(color[0]);printf("%c",186);}
               else if(mapa[j][i] == 'A') {setCColor(color[0]);printf("%c",201);}
               else if(mapa[j][i] == 'B') {setCColor(color[0]);printf("%c",187);}
               else if(mapa[j][i] == 'p') {setCColor(color[0]);printf("%c",188);}
               else if(mapa[j][i] == 'D') {setCColor(color[0]);printf("%c",200);}
         }
     }
}
void pacman(int x , int y){

     gotoxy(x,y); printf("%c",2);//Imprime o fantasma na tela
}

void pts_pacman(int x, int y){
     gotoxy(x,y); cout<<" ";
     if(mapa[y][x] == '.'){ mapa[y][x] = ' '; pts ++;}//Soma os pontos né...
}
        class fantasma{
//Caracteristicas basicas do Fantasma
      int fdir;
      int fx, fy;
      int col;
public:
//Prototipando todas as funções
      fantasma(int x , int y , int color);
      void imprimir_fantasma() const;
      void pts_fantasma() const;
      void mover_fantasma();
      void encontrar_pacman();
      void apagar_fantasma() const;;
};
fantasma::fantasma(int x , int y, int color){
//Propriedades do Fantasma
      fx = x;
      fy = y;
      col = color;
      fdir =0;
}
void fantasma::imprimir_fantasma() const{
//Imprime o Fantasma na tela kkkk
     setCColor(color[col]);
     gotoxy(fx,fy);printf("%c",5);
}
void fantasma::apagar_fantasma() const{

//Apaga o Fantasma kkkkk
     gotoxy(fx,fy);cout<<" ";
}
void fantasma::pts_fantasma() const{

     gotoxy(fx,fy); printf(" ");
}
void fantasma::encontrar_pacman(){
     if(y == fy && x == fx || (fdir == 0 && dir == 1 || fdir == 1 && dir == 0
     ||fdir == 2 && dir == 3 || fdir == 3 && dir == 2 )&&(fy == anteriorpy && fx == anteriorpx)){
//if (pastilhas == true ){ }
      x = 39;
      y = 22;
      dir = 4;
      vidas--;
     }
}
void fantasma::mover_fantasma(){

     apagar_fantasma();
     encontrar_pacman();
     int bolx=fx,boly=fy;

     if(mapa[fy][fx] == '*'){
             fdir = 0;//Entrada do Covil Fantasma
}
//Ele anda em todas as direções que não forem mapa, se colocar do jeito mais fácil ele não funciona!
//Não faça para ele andar nos espaços!

     if(fdir == 2){
          if(mapa[fy][fx+1] != '_' && mapa[fy][fx+1] != 'A' && mapa[fy][fx+1] != '|' &&
          mapa[fy][fx+1] != 'B' && mapa[fy][fx+1] != 'p' && mapa[fy][fx+1] != 'D'){fx++;}
          else fdir = rand()%4;
     }//Direita
     if(fdir == 3){
          if(mapa[fy][fx-1] != '_' && mapa[fy][fx-1] != 'A' && mapa[fy][fx-1] != '|' &&
          mapa[fy][fx-1] != 'B' && mapa[fy][fx-1] != 'p' && mapa[fy][fx-1] != 'D'){fx--;}
          else fdir = rand()%4;
     }//Esquerda
     if(fdir == 0){
          if(mapa[fy-1][fx] != '_' && mapa[fy-1][fx] != 'A' && mapa[fy-1][fx] != '|' &&
          mapa[fy-1][fx] != 'B' && mapa[fy-1][fx] != 'p' && mapa[fy-1][fx] != 'D'){fy--;}
          else fdir = rand()%4;
     }//Cima
     if(fdir == 1){
          if(mapa[fy+1][fx] != '_' && mapa[fy+1][fx] != 'A' && mapa[fy+1][fx] != '|' &&
      mapa[fy+1][fx] != 'B' && mapa[fy+1][fx] != 'p' && mapa[fy+1][fx] != 'D'){fy++;}
          else fdir = rand()%4;
     }//Baixo

     if(mapa[boly][bolx] == '.') {setCColor(color[1]); gotoxy(bolx,boly);printf("%c",250);} //Colisão bolinha x fantasma


//if(fx <= 17) fx = 61;
//else if(fx >= 62) fx = 18;
     imprimir_fantasma();
}

//void pegar_pastilha::pacman(){
//if (mapa[fy-1][fx] == 'o'){
//    inicio = time(NULL);
//    pastilha = true;
//
//fim = time(NULL);
//
//if(difftime(fim,inicio) >= 5){
//    pastilha = false;
//
//}//IF DIFFTIME
//while (pastilha == true){
//    if ((x == fx) && (y == fy)){
//
//
//     if(difftime(fim,inicio) >= 6){
//
//
//    }
//}
//}//if PRINCIPAL

void SaveGame (){


    arqSave.open("save.txt");
    arqSave << x << endl;
    arqSave << y << endl;
    //arqSave << A.(fx,fy) <<endl;
    //arqSave << B.(fx,fy) <<endl;
    //arqSave << C.(fx,fy) <<endl;
    //arqSave << D.(fx,fy) <<endl;

    arqSave << pts << endl;
    for(int i=0;i<50;i++){
        for(int j=0;j<100;j++){
            arqSave << mapa[i][j];
            Sleep(100);
}
        arqSave << endl;
}
    arqSave << Fase << endl;
    arqSave.close();

}//Para salvar na vertical coloca o i em baixo e o j em cima.

int main(){
    cout<<"Vc tem um jogo salvo?"<<endl;
    cout<<"[S|N]";
    if (Resposta == 's'){
arqLoad.open("save.txt");
    arqLoad >> x;
    arqLoad >> y;
    arqLoad >> pts;
    arqLoad.getline(mapa[0], 101); // Para ler o endl do final da linha dos pontos;
    for(int i=0;i<50;i++){
            arqLoad.getline(mapa[i], 101);
            Sleep(100);
        //arqLoad << endl; //se der problema eh aqui
    }
    arqLoad >> Fase;
    arqLoad.close();
    cout << endl << endl<< endl;
    cout << x << endl;
    cout << y << endl;
    cout << pts << endl;

//    for(int i=0;i<50;i++){
//        for(int j=0;j<100;j++){
//            cout << mapa[i][j];
//            Sleep(100);
//        }
//        cout << endl;
//    }
    cout << Fase << endl;

    }

gotoxy( x, y );
//DECLARAÇÃO DOS FANTASMAS
   fantasma A(41,14,2);//1, VERMELHO
   fantasma B(42,14,3);//2, VERDE
   //fantasma C(40,14,4);//3, AZUL
   //fantasma D(39,14,6);//4, ROXO OU BRANCO, ODEIO ESSE TOM DE ROXO
   pintar_mapa();


while(Fase == 1){


      pts_pacman(x,y);
      anteriorpx = x; anteriorpy = y;

      pacman(x,y);
      Sleep(35);
      pts_pacman(x,y);

      B.encontrar_pacman(); // MATA PACMAN B
      //C.encontrar_pacman(); //DECLARAR FASE 2
      //D.encontrar_pacman(); //DECLARAR FASE 3
      A.encontrar_pacman();//MATA PAC MAN A

      anteriorpx = x; anteriorpy = y;

      pacman(x,y);
      Sleep(35);

gotoxy( x, y ); cout << " ";//APAGA O TRECHO DO PAC MAN

      A.mover_fantasma();// MOVE A
      B.mover_fantasma(); //MOVE B
      //C.mover_fantasma(); //DECLARAR FASE 2
      //D.mover_fantasma(); //DECLARAR FASE 3

        if ( GetAsyncKeyState( VK_UP ) ){
if( mapa[y-1][x] == '.' ){ mapa[y-1][x] = ' '; y--;  pts++; }//CIMA
else if( mapa[y-1][x] == ' ' ) y--;
}
if ( GetAsyncKeyState( VK_DOWN ) ){
if( mapa[y+1][x] == '.' ){ mapa[y+1][x] = ' '; y++;  pts++; }//BAIXO
else if( mapa[y+1][x] == ' ' ) y++;

}
if ( GetAsyncKeyState( VK_LEFT ) ){
if( mapa[y][x-1] == '.' ){ mapa[y][x-1] = ' '; x--;  pts++;  }//ESQUERDA
else if( mapa[y][x-1] == ' ' ) x--;
}
if ( GetAsyncKeyState( VK_RIGHT ) ){
if( mapa[y][x+1] == '.' ){mapa[y][x+1] = ' '; x++;   pts++; }//DIREITA
else if( mapa[y][x+1] == ' ' ) x++;
//else if( mapa[y][x+1] == 'o' ){pegar_pastilha();}
}
gotoxy( x,y );printf("%c",2);

gotoxy( 100, 50 );
gotoxy( 66, 2 ); cout << pts;
Sleep( 35 );

if(vidas <= 0){//MORRE

system("cls");
cout<<" VC PERDEU, SEUS PONTOS FORAM: "<<pts;
cout<<endl<<"digite seu nome: ";
cin>>nome;
arq1.open("Highscore.txt", ios::app);//ABRE O ARQUIVO, APP PARA ADICIONAR EM BAIXO
    if(arq1.is_open()){
        for(int i = 0;i<1;i++){//DELIMITA PARA UM NOME SÓ
            arq1 << nome<< " - " << pts << endl;
}
    arq1.close();//FECHA O ARQUIVO
}//if ARQUIVO
Fase = 0;
system ("cls");
cout<<"Vc deseja jogar novamente?[s/N]"<<endl;
cin>> Resposta;
if(Resposta == 's'){
system ("cls");
Fase = 1;
pintar_mapa();
vidas = 3;

}//if resposta
    arq1.open("Highscore.txt", ios:: in);
    if( arq1.is_open()){
        while(getline(arq1, linha)){
    cout<<endl<<linha;
        }
    }
break;
}//if VIDAS

if(pts == 385){//GANHA
system("Cls");
cout<<"-FASE 2-";
Sleep(2000);
Fase ++;
}//if points 385
}//While 1

//for(int i = 0; i < 100; i++) {
//     for(int j = 0; j < 50; j++) {
//          if(mapa[j][i] == ' '){
//            mapa[j][i] = '.';
//        }
//     }
//}
        fantasma C(40,14,4);//3, AZUL
        cout<<"Deseja salvar o Jogo??";
        cin>>Resposta;
        if(Resposta == 's'){
            SaveGame();
        }

        system("cls");
        pintar_mapa();
        x = 39;
        y = 22;
        vidas +=1;


while( Fase ==  2){

      pts_pacman(x,y);
      anteriorpx = x; anteriorpy = y;

      pacman(x,y);
      Sleep(25);
      pts_pacman(x,y);

      B.encontrar_pacman();//MATA PACMAN B
      C.encontrar_pacman();// MATA PACMAN C
      //D.encontrar_pacman(); // DECLARAR NA FASE 3
      A.encontrar_pacman(); // MATAR PACMAN A

      anteriorpx = x; anteriorpy = y;

      pacman(x,y);
      Sleep(28);

gotoxy( x, y ); cout << " ";//APAGA O TRECHO DO PAC MAN

      A.mover_fantasma();//MOVIMENTA A
      B.mover_fantasma();//MOVIMENTA B
      C.mover_fantasma();//MOVIMENTA C
      //D.mover_fantasma();

        if ( GetAsyncKeyState( VK_UP ) ){
if( mapa[y-1][x] == '.' ){ mapa[y-1][x] = ' '; y--;  pts++; }//CIMA
else if( mapa[y-1][x] == ' ' ) y--;
}
if ( GetAsyncKeyState( VK_DOWN ) ){
if( mapa[y+1][x] == '.' ){ mapa[y+1][x] = ' '; y++;  pts++; }//BAIXO
else if( mapa[y+1][x] == ' ' ) y++;
}
if ( GetAsyncKeyState( VK_LEFT ) ){
if( mapa[y][x-1] == '.' ){ mapa[y][x-1] = ' '; x--;  pts++;  }//ESQUERDA
else if( mapa[y][x-1] == ' ' ) x--;
}
if ( GetAsyncKeyState( VK_RIGHT ) ){
if( mapa[y][x+1] == '.' ){mapa[y][x+1] = ' '; x++;   pts++; }//DIREITA
else if( mapa[y][x+1] == ' ' ) x++;
//else if( mapa[y][x+1] == 'o' ){pegar_pastilha();}
}
gotoxy( x,y );printf("%c",2);

        gotoxy( 100, 50 );
gotoxy( 66, 2 ); cout << pts;
Sleep( 28 );

if(pts == 770){//GANHA
system("Cls");
cout<<"-FASE 3-";
Sleep(2000);
Fase++;
}//if points 762

if(vidas <= 0){//MORRE

    system("cls");
cout<<" VC PERDEU, SEUS PONTOS FORAM: "<<pts;
cout<<endl<<"digite seu nome: ";
cin>>nome;
arq1.open("Highscore.txt", ios::app);//ABRE O ARQUIVO, APP PARA ADICIONAR EM BAIXO
    if(arq1.is_open()){
        for(int i = 0;i<1;i++){//DELIMITA PARA UM NOME SÓ
            arq1 << nome<< " - " << pts << endl;
}
        arq1.close();//FECHA O ARQUIVO
}//if ARQUIVO
Fase = 0;
system ("cls");
cout<<"Vc deseja jogar novamente?[s|n]"<<endl;
cin>> Resposta;
if(Resposta == 's'){
system ("cls");
Fase = 1;
pintar_mapa();
vidas = 3;


}//if resposta
    arq1.open("Highscore.txt", ios:: in);
    if( arq1.is_open()){
        while(getline(arq1, linha)){
    cout<<endl<<linha;
        }
    }
    break;
}//if VIDAS
}//While 2
        for(int i = 0; i < 100; i++) {
     for(int j = 0; j < 50; j++) {
          if(mapa[j][i] == ' '){
            mapa[j][i] = '.';
        }
     }
}
        fantasma D(39,14,6);//4, ROXO OU BRANCO, ODEIO ESSE TOM DE ROXO
        system("cls");
        pintar_mapa();
        x = 39;
        y = 22;
        vidas +=1;
cout<<"Deseja salvar o Jogo??";
cin>>Resposta;
if(Resposta == 's'){
SaveGame();
        }
while( Fase == 3){


      pts_pacman(x,y);
      anteriorpx = x; anteriorpy = y;

      pacman(x,y);
      Sleep(21);
      pts_pacman(x,y);

      B.encontrar_pacman();//MATA PACMAN B
      C.encontrar_pacman();// MATA PACMAN C
      D.encontrar_pacman(); // DECLARAR NA FASE 3
      A.encontrar_pacman(); // MATAR PACMAN A

      anteriorpx = x; anteriorpy = y;

      pacman(x,y);
      Sleep(21);


gotoxy( x, y ); cout << " ";//APAGA O TRECHO DO PAC MAN

      A.mover_fantasma();//MOVIMENTA A
      B.mover_fantasma();//MOVIMENTA B
      C.mover_fantasma();//MOVIMENTA C
      D.mover_fantasma();//MOVIMENTA D

        if ( GetAsyncKeyState( VK_UP ) ){
if( mapa[y-1][x] == '.' ){ mapa[y-1][x] = ' '; y--;  pts++; }//CIMA
else if( mapa[y-1][x] == ' ' ) y--;
}
if ( GetAsyncKeyState( VK_DOWN ) ){
if( mapa[y+1][x] == '.' ){ mapa[y+1][x] = ' '; y++;  pts++; }//BAIXO
else if( mapa[y+1][x] == ' ' ) y++;
}
if ( GetAsyncKeyState( VK_LEFT ) ){
if( mapa[y][x-1] == '.' ){ mapa[y][x-1] = ' '; x--;  pts++;  }//ESQUERDA
else if( mapa[y][x-1] == ' ' ) x--;
}
if ( GetAsyncKeyState( VK_RIGHT ) ){
if( mapa[y][x+1] == '.' ){mapa[y][x+1] = ' '; x++;   pts++; }//DIREITA
else if( mapa[y][x+1] == ' ' ) x++;
//else if( mapa[y][x+1] == 'o' ){pegar_pastilha();}
}
gotoxy( x,y );printf("%c",2);

        gotoxy( 100, 50 );
gotoxy( 66, 2 ); cout << pts;
Sleep( 21 );

if(pts == 1155){//GANHA

    system("cls");

    cout<<"Parabens vc Ganhou, seus pontos foram: "<< pts ;
cout<<endl<<"digite seu nome: ";
cin>>nome;
arq1.open("Highscore.txt", ios::app);//ABRE O ARQUIVO!
    if(arq1.is_open()){
      for(int i = 0;i<1;i++){
        arq1 << nome<< " - " << pts << endl;

}
    arq1.close();
}
cout<<"Vc deseja salvar seu progresso? [S/N]";
cin>>Resposta;
SaveGame();
Fase = 0;
break;
}//if points 1143

if(vidas <= 0){//MORRE

    system("cls");
cout<<" VC PERDEU, SEUS PONTOS FORAM: "<<pts;
cout<<endl<<"digite seu nome: ";
cin>>nome;
arq1.open("Highscore.txt", ios::app);//ABRE O ARQUIVO, APP PARA ADICIONAR EM BAIXO
    if(arq1.is_open()){
        for(int i = 0;i<1;i++){//DELIMITA PARA UM NOME SÓ
            arq1 << nome<< " - " << pts << endl;
}
        arq1.close();//FECHA O ARQUIVO
}//if ARQUIVO

    arq1.close();//FECHA O ARQUIVO
}//if ARQUIVO




Fase = 0;
system ("cls");

if(Resposta == 's'){



system ("cls");
Fase = 1;
pintar_mapa();
vidas = 3;

}//if resposta
    arq1.open("Highscore.txt", ios:: in);
    if( arq1.is_open()){
        while(getline(arq1, linha)){
    cout<<endl<<linha;
        }
    }
    break;
}//if VIDAS
//While 3
return 0;
}
