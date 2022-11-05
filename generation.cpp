#include <iostream>
#include <ctime>
//za korištenje funkcije time moramo imati ovu biblioteku. 

#define MAP_W 100
#define MAP_H 60
//definisanje samu visinu i širinu mape

using namespace std;

int alive=1;
int dead=0;

int map[MAP_H][MAP_W];
//2D niz (array) 

int seed = time(NULL);
//stavljanje seed kao time nam omogućava da svaki put kad pokrenemo program generacija bude jedinstvena. Seed je jednak vremenu ili trenutku u kojem se pokrene program. 

int aliveProb=58;
//postutak "alive" ispisa tj. koliko će biti šanse da se jedinice ispišu(u ovom slučaju #)
int generacije=10;


void gen(){
srand(seed);
for(int h=0; h<MAP_H;h++){
    for(int w=0; w<MAP_W;w++){
        map[h][w]=alive;
        if(rand()% 100 > aliveProb) map[h][w]=dead;
    }
}
}
//sama funkcija za generaciju


void spasiIMG(string filename){
FILE*pgmimg;
string ext=".pgm";
pgmimg=fopen((filename+ext).c_str(),"wb");
fprintf(pgmimg, "P2\n");
fprintf(pgmimg, "%d %d\n", MAP_W, MAP_H);
fprintf(pgmimg, "255\n");
for (int h = 0; h < MAP_H; h++) {
  for (int w = 0; w < MAP_W; w++) {
   fprintf(pgmimg, "%d ", (!map[h][w])*255);
  }
  fprintf(pgmimg, "\n");
 }
 fclose(pgmimg);
}
//funkcija za spašavanje završene generacije u više files


int blizu(int x, int y){
    int broj=0;
    for(int h=y-1; h<2 + y;h++){
    for(int w=x-1; w<2 + x;w++){
        if(!(w==x&&h==y)){
            broj+=map[h][w];
        } 
    }
}
    return broj;
}
//funkcija za "skeniranje" ili provjeravanje za isti value pored sebe

void display(int sx, int sy, int width, int height){
    for(int h=sy; h<sy+height;h++){
    for(int w=sx; w<sx+width;w++){
        if(map[h][w]){
            cout<<"#";
        } else {
            cout<<".";
        }
        
    }
    cout<<endl;
}
}
//funkcija za ispis generacije


void display(){
    display(0,0,MAP_W,MAP_H);
}
//ovdje sam samo dodijelio value parametrima

int main(){
gen();
cout<<"Generacija#0"<<endl;

display();
spasiIMG("gen0");


for(int gen1=0; gen1<generacije;gen1++){
for(int h=0; h<MAP_H;h++){
    for(int w=0; w<MAP_W;w++){
        int broj = blizu(w,h);
        if(map[h][w] == dead && broj >= 6) map[h][w]=alive;
        if(map[h][w] == alive && broj <= 3) map[h][w]=dead;
        
    }
} // for petlja za kalkulisanje da li object treba biti ispisan kao alive ili dead (# ili . ) pomoću funkcije blizu 
cout<<"Generation #"<<gen1+1<<":"<<endl;
display();
spasiIMG("gen" + to_string((gen1+1)));
}
return 0;
}