#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

void gameOver();
void ShowScoreAndLife();
void bestScore();
void youWin();
int ctrl(int x,int y);

FILE *dosya;
int best=0, score=0,cc=430,i=0,enemyLife=0;
float c=415;
int ek=0,ek2=0,r=0,x,y;
bool isActive=false,isActive2=false,check=true,checkboss=true;
bool Left=true,Down=false,Up=false;
int a1=700,b1=100,a2=892,b2=166;
int q1,q2,w1,w2;
int k1,l1,k2,l2;
int p1,r1,p2,r2;
char scr[10],bst[10];

int randy(){
    int y;
    srand((unsigned)time(0));
    y = rand() %500 + 10;
    return y;
}
int randy1(){
    int y;
    srand((unsigned)time(0));
    y = rand() %250 + 70;
    return y;    
    } 
int randy2(){
    int y;
    srand((unsigned)time(0));
    y = rand() %330 + 50;
    return y;    
    }
int randy3(){
    int y;
    srand((unsigned)time(0));
    y = rand() %470 + 70;
    return y;    
    }
int randy4(){
    int y;
    srand((unsigned)time(0));
    y = rand() %540 + 50;
    return y;    
    } 
int randy5(){
    int y;
    srand((unsigned)time(0));
    y = rand() %150 + 50;
    return y;    
    } 
    
void smallEnemies(int x,int y)                                 
{
     readimagefile("tas.gif",x,y,x+50,y+56);
    
}

void enemyShooting(int a1,int b1,int a2,int b2 )            // Canavar ateþ fonkiyonu
{
         ek2+=20;
         isActive2=true;                     
                              k1=a1-35;
                              k2=a1-5;
                              l1=(b1+b2)/2-0;
                              l2=(b1+b2)/2-30;
                              k1-=ek2;
                              k2-=ek2;
                              if(k2<0){
                              isActive2=false;
                              ek2=0;
                              }
 }

void setBossPosition()                                         // Canavar Hareket Fonksiyonu
{
 
   if(Left){
              a1-=3;
              a2-=3;
              b1+=2;
              b2+=2;
              if(a1<=450){
                          Left=false;
                          Down=true;
                          }
              }
     if(Down){
              a1+=3;
              a2+=3;
              b1+=3;
              b2+=3;
              if(b2>=500){
                          Down=false;
                          Up=true;
                          }      
              }
     if(Up)
     {
      b1-=4;
      b2-=4;
      if(b1<=100){
                          Up=false;
                          Left=true;
                 } 
     }
}

void PlayerShooting(int x1,int x2,int y1,int y2)             // Player ateþ fonkiyonu
{
         ek+=40;
         isActive=true;                    
                              q1=x2;
                              q2=x2+15;
                              w1=(y1+y2)/2-3;
                              w2=(y1+y2)/2+3;
                              q1+=ek;
                              q2+=ek;
                              readimagefile("Mermi.jpg",q1,w1,q2,w2);
                              if(q2>900){
                              isActive=false;
                              ek=0;
                              }
}   

void PlayerMovement(int  x1,int y1,int x2,int y2)
{
    bool shoot=false;
    int ek3=30;//hareket icin ek birim
    char tus;
    int xi=900;
    int yi= randy(); 
    p1=x1;
    r1=y1;
    p2=x2;
    r2=y2;
    
  while(1){ //sonsuzdöngü baþladý   
  
  readimagefile("arkaplan.jpg",0,0,900,600);
  ShowScoreAndLife(); 
  readimagefile("Player.gif",x1,y1,x2,y2);
  readimagefile("Boss.gif",a1,b1,a2,b2);
  readimagefile("Mermi.gif",k1,l1,k2,l2);
   
  score++;
  c+=0.1;
 
  if(c>=400)
  c-=0.1;
  
  smallEnemies(xi,yi);
  
  if(k1>x1 && k1<x2 && l2<y2 && l1>y1){                         // Canavar tarafýndan vurulunca
               
                 c-=15;
                 ek2=0;
         }
   if(cc>=520 && cc<=560){                                      //Canavar Öldüðünde  
       check=false;  // tuþlara basýlmasý engellendi
       a2=a1+40;
       b2=b1+200;
       readimagefile("Player2.gif",a1,b1,a2,b2);
       b1+=10;
       b2+=10;
       if(b2>=650){
       score+=10000;
       bestScore();
       youWin(); 
       }      
}
if(c>=270 && c<=320){             // Player Öldüðünde
       
       check=false;   //Tusa basýlmasý engellendi
       x2=x1+40;
       y2=y1+200;
       readimagefile("Player2.gif",x1,y1,x2,y2);
       y1+=10;
       y2+=10;
       bestScore();
       if(y2>=600)
       gameOver();
}
  
   xi-=15;
  
   setBossPosition();
   
   if(checkboss==true)
   enemyShooting(a1,b1,a2,b2);
   
   if(xi<x2 && xi>x1 && yi<y2 && yi>y1-25 ){    // Gök taþý ile Playerýn Çarpýþmasý
  
                  c-=10;; 
                  r++;
                  if(r==1)
                  yi=randy1();
                  else if(r==2)
                  yi=randy4();
                  else if(r==3)
                  yi=randy3();
                  else if(r==4)
                  {
                       yi=randy2();
                       r=0;
                  }                           
                  xi=900;
                  score-=500;
                  }
              if(xi<=0){
                          yi=randy5();
                          xi=900;
                      } 
   
   if(kbhit() && check==true)// Tusalara basýlmasý 
   {
    tus= getch();
    if(tus==27) exit(0);
    else 
    {   
                   if(tus==72 && y1>50)//yukarý tus
                   {
                    y1-=ek3; 
                    y2-=ek3;
                        
                    if(y1<=20)
                    {
                    y1+=ek3; 
                    y2+=ek3;
                    }
                    }
                    else if(tus==80 && y1<500)//aþagý tus
                    {
                    
                    y1+=ek3; 
                    y2+=ek3; 
                    
                    if(y2>=570)
                    {
                    y1-=ek3; 
                    y2-=ek3;
                    }
                    }
                    else if(tus==32){ // Ateþ edildi
                        
                         PlayerShooting(x1,x2,y1,y2);
                    }
      }
}                
 if(isActive==true){
 
     PlayerShooting(x1,x2,y1,y2); 
     if(q2+20>xi && w1<yi+50 && w2>yi-24){ //Player Gök taþýný vurunca
                                               score+=500;
                                               xi=900;
                                                r++;
                  if(r==1)
                  yi=randy1();
                  else if(r==2)
                  yi=randy4();
                  else if(r==3)
                  yi=randy3();
                  else if(r==4)
                  {
                       yi=randy2();
                       r=0;
                       }
                                               ek=0;
                                               isActive=false;
                                               
                                               }
     
     if(q2+20>a1 && w1<b1+100 && w2>b1-44){ // Player Canavarý Vurunca
                 cc+=1;
                 score+=1000;//anlamak içinde iþimiz bitince sil
                 ek=0;
                 isActive=false;
                 }
         }
    }
}

void MenuInput()
{
    int x1=50,y1=50,x2=150,y2=84;
    PlaySound("menüses.wav",NULL,SND_ASYNC);
    readimagefile("Menü.jpg",0,0,900,600);
    readimagefile("bir.jpg",640,250,900,260);
    readimagefile("pg.gif",720,230,900,270);
    readimagefile("iki.jpg",640,300,900,310);
    readimagefile("hs.gif",720,280,900,322);
    readimagefile("üç.jpg",640,350,900,360);
    readimagefile("c.gif",720,330,900,374);
    readimagefile("dört.jpg",640,400,900,410);
    readimagefile("qg.gif",720,380,900,422);
    readimagefile("credits.gif",720,330,900,375);
    while(1)//oyun basla butonu
      {
         while(ismouseclick(WM_LBUTTONDOWN))
      {

        getmouseclick(WM_LBUTTONDOWN,x,y);
    
           if(x>720 && x<900 && y>230 && y<270)//play game
           {    
            cleardevice();
   	        PlaySound("arkases.wav",NULL,SND_ASYNC);
            PlayerMovement(x1,y1,x2,y2);
           } 
           if(x>720 && x<900 && y>280 && y<322)//high score
           {
            cleardevice();
            readimagefile("high.jpg",0,0,900,600);
            bestScore();
            sprintf(bst,"%d",best);
            setcolor(14);
            settextstyle(10,0,3);
            outtextxy(145,137,bst);
            outtextxy(250,550,"Press any key for return Menu..");
            getch();
            MenuInput();
           
           } 
           if(x>720 && x<900 && y>330 && y<374){ // credits
                    
                     readimagefile("creditss.jpg",0,0,900,600);
                     setcolor(14);
                     setbkcolor(BLUE);
                     settextstyle(10,0,3);
                     outtextxy(250,550,"Press any key for return Menu..");
                     getch();
                     MenuInput();
                     
                    }                 
           if(x>720  &&  x<900  && y>380  && y<422 ){ // quit game
                    
                    exit(1);
                    }                     
     }
}
}

void gameOver(){
       PlaySound("lose.wav",NULL,SND_ASYNC);
       cleardevice();
       bestScore();
       
       cc=430;  // Can Tazeleme
       c=415;
      
      readimagefile("gameOver.jpg",0,0,900,600);
      sprintf(scr,"%d",score);
      setcolor(14);
      settextstyle(10,0,5);
      outtextxy(400,300,scr);
      bestScore();
      
      while(1)
      {
         while(ismouseclick(WM_LBUTTONDOWN))
      {

         getmouseclick(WM_LBUTTONDOWN,x,y);
           
           if(x>150 && x<290 && y>430 && y<470){ // Menuye git
                    score=0;
                    a1=700;
                    b1=100;
                    a2=892;
                    b2=166;
                    check=true;
                    MenuInput();
                    
                    }
           
           if(x>350 && x<560 && y>430 && y<470)// oyuna devam
           { 
            check=true;   
            PlaySound("arkases.wav",NULL,SND_ASYNC);
            score=0;
            PlayerMovement(p1,r1,p2,r2);
   	        } 
           
           if(x>660 && x<830 && y>430 && y<470)// quit game
           exit(1);
      }
    }                  
}
void ShowScoreAndLife(){
                 
                 sprintf(scr,"%d",score);
                 setbkcolor(BLACK);
                 setcolor(14);
                 settextstyle(10,0,2);
                 outtextxy(680,10,"SCORE : ");
                 outtextxy(800,10,scr);
                 setfillstyle(1,5);
                 bar(320,15,(int)c,35);
                 bar(cc,15,535,35);
                 rectangle(430,15,535,35);
                 rectangle(320,15,415,35);
}
                 
void youWin(){ 
      PlaySound("win.wav",NULL,SND_ASYNC);
      checkboss=false;// Tusa basýlmasý engellendi
      
      cc=430; // Can tazelendi
      c=415;
     
     cleardevice();
     readimagefile("youwin.jpg",0,0,900,600);
     sprintf(scr,"%d",score);
     setcolor(14);
     settextstyle(10,0,3);
     outtextxy(130,110,scr);
    
      while(1)
      {
         while(ismouseclick(WM_LBUTTONDOWN))
          {
          getmouseclick(WM_LBUTTONDOWN,x,y);
    
          if(x>280 && x<430 && y>105 && y<150){// Menuye git
            score=0;
            a1=700;
            b1=100;
            a2=892;
            b2=166;         
          checkboss=true;      // tuþlar aktif   
          MenuInput();         
                   
          }
    
           if(x>460 && x<640 && y>105 && y<150)// oyuna devam
           { 
            a1=700;
            b1=100;
            a2=892;
            b2=166;
            check=true;  // Tuslar aktif
            checkboss=true; 
            PlaySound("arkases.wav",NULL,SND_ASYNC);
            score=0;
            PlayerMovement(p1,r1,p2,r2);
   	        } 
           
           if(x>750 && x<870 && y>105 && y<150)// quit game
           exit(1);
      }
    }      
}                 

void bestScore(){
     
     dosya = fopen("puan.txt","a");
     
     if(dosya==NULL){
     outtextxy(400,400,"Teknik bir hata var..");
     }
     
     fprintf(dosya,"\n%d",score);
     fclose(dosya);     
     
     dosya =fopen("puan.txt","r");
    
     while(!feof(dosya)){
                    
                     fscanf(dosya,"%d",&score);
                    
                    if(score>=best)
                    best=score;   
                 }            
    fclose(dosya);
}

int main( )
{
	initwindow( 900 , 600 , "Game Of Team" );
	MenuInput();
       
    getch();
	return( 0 );
}
