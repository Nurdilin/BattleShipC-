#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<ctime>
using namespace std;

/*~~~~~~~~~~~~~Simeiwseis~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 1. Kapoies sinarthseis opws oi constructors twn 
 *   ship,tug,submarine... topotheththikan meta thn
 *   dhlwsh ths klashs Grid giati ipirxan provlimata
 *   sto compile me to forward declaration.
 * 2. Otan trexoume to programma ama dwsoume th parametro tou megethous
 *   me arnhtiko prosimo tote energopoieitai to "cheat-debug mode" sto 
 *   opoio vlepoume ola ta ploia sto plegma. Ta rimoulka simvolizontai
 *   me T, ta ipovrixia me S kai ta aeroplanofora me A
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

class Gridpoint;
class Grid;

bool cheat=false;        //cheat mode on/off

//////////////////////////////////////////////////////////////
class Ship
{
     protected:          
          bool direction;      //0 orizontia ,1 katheta
          int length;          //1tug, 3sub ,5aircraft
          int x_plorh;         //ship x coordinate ploris
          int y_plorh;         //ship y coordinate ploris
          int dmg;             //posa simeia tou exoun xtipithei
          Grid *grid;          //deikths pros to grid        
     public:
          Ship(int,Grid*);
          virtual ~Ship(){};
 
          virtual void threaten()=0;         //to ploio apeileitai             
          virtual void sink()=0;             //to ploio vithistike
          virtual void score_update()=0;     //ananewsh tou scor
          void hit();                        //to ploio xtipithike
          
          int get_size(){ return length;}    
};

void Ship::hit()
{    
     dmg++;  //afskanouem ta xtipimata pou xei dextei
     if (dmg==length)    //an exoun xtipithei tosa simeia oso to mikos tou vithizetai
     {
          sink();
     }
}



/////////////////////////////////////////////////////////

class Tug: public Ship
{        
     public:
          Tug(Grid *p);
          ~Tug(){};
 
          void threaten();         //ylopoihsh ths pure virtual threaten gia thn tug
          void sink();             //ylopoihsh ths pure virtual sink gia thn tug
          void score_update();     //ylopoihsh ths pure virtual score_update gia thn tug          
};


/////////////////////////////////////////////////////////

class Submarine: public Ship 
{
     public:   
          Submarine(Grid *p);
          ~Submarine(){ };

          void threaten();
          void sink();             
          void score_update();        
};



/////////////////////////////////////////////////////////

class Aircraft_carrier: public Ship
{
     public:
          Aircraft_carrier(Grid *p);
          ~Aircraft_carrier(){};

          void threaten();  
          void sink();
          void score_update();
          
};


void Aircraft_carrier::threaten()       //h threaten gia thn aircraft den kanei tipota
{
     //tipota:P
}


///////////////////////////////////////////////////////////////

class Gridpoint
{          
          bool chosed;         //0 an dn exei epilegei, 1 an exei
          bool occupied;       //0 an dn einai katilimeno , 1 an einai
          bool hited;         //1 an exei ploio pou exei xtipitei alliws 0
          Ship *p2ship;       //deikths se ship 
     public:
          Gridpoint();
          ~Gridpoint();

          int is_chosed();     //elegxoume an exei epilegei to shmeio
          int is_occupied();   //elenxoume an einia katilimeno apo kapoio ploio
          int is_hited();     //elemxoume an se afto to simeio iparxei xtipimeno ploio

          void choose()  { chosed=true;}      //to simeio epilexthike apo ton paixth
          void occupy()  { occupied=true;}    //sto simeio bike ena ploio
          void unoccupy(){ occupied=false;}  //efige ena ploio apo to simeio
          void hit_gp()  { hited=true;}      //to simeio exei ena xtipimeno ploio

          void set_pointer_to_ship(Ship *p);
          Ship* get_pointer_to_ship(){ return p2ship;}

          int type(){ return p2ship->get_size();}
};

Gridpoint::Gridpoint()
{    
     chosed=false;       //arxika den exei epilegei,
     occupied=false;     //den exei ploio panw tou
     hited=false;        //oute xtipimeno ploio profanws
     p2ship=NULL;        //dn iparxei kapoio ploio sto opoio na deiksei
}

Gridpoint::~Gridpoint()
{    
     //cout<<"grid point deleted"<<endl;//4 debug
}

int Gridpoint::is_chosed()
{
     if (chosed==true)
     {
          return 1;
     }
     else
     {    
          return 0;
     }
}

int Gridpoint::is_occupied()
{
     if (occupied==true)
     {
          return 1;
     }
     else
     {    
          return 0;
     }
}

int Gridpoint::is_hited()
{
     if (hited==true)
     {
          return 1;
     }
     else
     {    
          return 0;
     }
}
     

void Gridpoint::set_pointer_to_ship(Ship *p) //anathetei ston p2ship enan deikth se ship
{
     p2ship=p;
}
//////////////////////////////////////////////////////////

class Grid
{         
          int Size;       //to megethos ths plevras tou plegmatos
          int K1;         //aircraft carriers
          int K2;         //submarines
          int K3;         //tugs
          int Sum;        //sinolikos arithmos ploiwn
          int sink_k1;    //sinolikos arithmos vithismenwn aircraft_carriers    
          int sink_k2;    //sinolikos arithmos vithismenwn submarines
          int sink_k3;    //sinolikos arithmos vithismenwn tugs
          int high_score; //to megisto scor pou prepei na petixei o xrhsths gia na kerdizei
          int score;      //to trexwn scor tou xrhsth
          Gridpoint **p;   
          Ship ** ship;       
     public:
          Grid(int N);
          ~Grid();
          
          void update(int, int); 
          void print();          //ektipwnei to plegma
          
          bool fits(Ship *,int, int, int, int);  //elenxei an xwraei ena ploio se kapoia thesh
          void place(Ship*,int, int, int, int);  //topothetei ena ploio se kapoia thesh
          void unplace(Ship *,int, int, int, int); //apomakrinei ena ploio apo kapoia thesh

          void score_up(int);      //afksanei to score tou xrhsth
          void print_score();      //ektipwnei to scor tou xrhsth
          void vithismena_skafh(int);

          int win();               //elenxei an o paikths exei kerdisei kai epistrefei 1 h 0
          void lost();            //minimata gia game over

          int get_grid_size(){return Size;}  //accessor gia to megethos tou plegmatos
};
          

Grid::Grid(int N)             //o constructor tou grid. Dexetai san parametro to megethos tou
{
     int i=0;

     K1=(int)(0.02*N*N);      //arxikopoihseis
     K2=(int)(0.03*N*N);  
     K3=(int)(0.06*N*N);       
     Sum=K1+K2+K3;
     high_score=K1*3+K2*5+K3*1;         //to maximum score pou borei na piasei o xrhsths
     Size=N;
     sink_k1=0;       
     sink_k2=0;    
     sink_k3=0;  
     
     p=new (nothrow) Gridpoint*[Size];         //dhmiourgia tou plegmatos
     if(p==NULL){ exit(1);}
     for(i=0;i<Size;i++)                        //enas disdiastatos pinakas
     {                                          //typou Gridpoint
          p[i]= new (nothrow) Gridpoint[Size];
          if (p[i]==NULL){exit(1);}
     }


     ship= new (nothrow) Ship*[Sum];         //dhmiourgia pinaka deiktwn pros adeikimena ship  
     if(ship==NULL){ exit(1);}

     for(i=0;i<K1;i++)
     {
         ship[i]=new (nothrow) Aircraft_carrier(this); //dhmiorgoume K1 aeroplanofora
         if (ship[i]==NULL){exit(1);}
     }
     for(i=K1;i<K1+K2;i++)
     {
          ship[i]=new (nothrow) Submarine(this);       //dhmiourgoume K2 upovrixia
          if (ship[i]==NULL){exit(1);}
     }
     for(i=K1+K2;i<Sum;i++)
     {
          ship[i]=new (nothrow) Tug(this);               //dhmiourgoume K1 rimoulka
          if (ship[i]==NULL){exit(1);}
     }   
}

Grid::~Grid()       //o destructor ths grid
{
     int i=0;
     for(i=0;i<Size;i++)      //svinoume to plegma
     {
          delete[] p[i];          
     }
     delete[] p;
     

     for(i=0;i<Sum;i++)      //diagrafoume ta ploia
     {
          delete ship[i];          
     }
     delete[] ship;
}


void Grid::score_up(int s)    
{
     score=score+s;
}

void Grid::print_score()
{
     cout<<"You have "<<score<<" out of "<<high_score<<" points"<<endl;
} 

void Grid::vithismena_skafh(int j)//afksanei ana ena ta vithismena ploia ths kathgorias...
{
     if (j==1)           //...aircraft_carrier
          sink_k1++;     
     else if (j==2)      //...submarines
          sink_k2++;
     else if (j==3)     //...tugs
          sink_k3++;
}
bool Grid::fits(Ship *ship,int x,int y,int dir,int len)
{
      /* Elenxei an h thesh pou tou dinoume dn ksefevgei apo to plegma
       * kai den einai  katilimenh apo allo ploio  
       * kai den exei epilegthei apo to xrhsth.
       * Tote epistrefei true alliws false
       */
     int i;
     if( dir==0)              //an h katefthinsi einai orizontia
     {
          for(i=0;i<len;i++)
          {
               if (x+i>Size-1)   //to simeio ksefevgei apo to plegma
               {
                    return false;  
               }

               if( p[x+i][y].is_occupied()==true) //to simeio einai katilimeno
               {
                    return false;
               }     
          
               if( p[x+i][y].is_chosed()==true) //to simeio exei epilexthei
               {
                    return false;
               }                   
          }
     }
     else if( dir==1)         //an einai katheta, paromoioi elenxoi
     {
          for(i=0;i<len;i++)
          {
               if (y+i>Size-1)
               {
                    return false;  
               }
               if( p[x][y+i].is_occupied()==true) 
               {
                    return false;
               }     
          
               if( p[x][y+i].is_chosed()==true) 
               {
                    return false;
               }                   
          }
     }
     return true;   //ola kala gia thn topothethsh
}  



void Grid::place(Ship *ship,int x,int y,int dir,int len)    //h topothethsh tou ploiou
{ 
     /* Ta simeia sta opoia tha bei to ploio
      * allazoun katastash se katilimena
      * kai kathe ena apo afta deixnei
      * sto ploio pou topothethtai epanw tou
      */

     int i;
     if( dir==0)              //an h katefthinsi einai orizontia
     {
          for(i=0;i<len;i++)
          {               
               p[x+i][y].occupy();             
               p[x+i][y].set_pointer_to_ship(ship);                  
          }
     }
     else if( dir==1)         //an einai katheta
     {
          for(i=0;i<len;i++)
          {               
               p[x][y+i].occupy();           
               p[x][y+i].set_pointer_to_ship(ship);            
          }
     }        
}

void Grid::unplace(Ship *ship, int x,int y,int dir,int len)
{
     /* H unplace xrhsimopoieitai otan apeileitai ena ploio
      * kai prepei na metakinithei se allh thesh. 
      * Allazei katastash se "mh katilimenh" sta simeia pou 
      * mexri twra vriskotan to ploio kai thetei tous deiktes
      * pros ta ploia aftwn twn gridpoints se NULL
      */
     int i;
     if( dir==0)              //an h katefthinsi einai orizontia
     {
          for(i=0;i<len;i++)
          {               
               p[x+i][y].unoccupy();                   
               p[x+i][y].set_pointer_to_ship(NULL);                  
          }
     }
     else if( dir==1)         //an einai katheta
     {
          for(i=0;i<len;i++)
          {               
               p[x][y+i].unoccupy();           
               p[x][y+i].set_pointer_to_ship(NULL);            
          }
     }        

}
void Grid::update(int co_x,int co_y)
{

     p[co_x][co_y].choose();  //thetoume tis sidetagmenes pleon san epilegmenes

     if(p[co_x][co_y].get_pointer_to_ship()!=NULL)        //elenxoume an iparxei ploio
     {
          p[co_x][co_y].get_pointer_to_ship()->hit();     //an nai to xtipame (hit())
          p[co_x][co_y].hit_gp();                         //to simeio exei ploio pou xtipithike
     }

     /*Stis epomenes if elenxoume an ta simeia pou apeilountai einai mesa 
      *sta oria tou  plegmatos kathws kai an iparxei ploio se afta ta
      *simeia wste na apeilithei. An isxioun kai oi 2 proipotheseis
      *to ploio pou vrisketai se aftes tis sidetagmenes ginetai threaten
      */

     if((co_x+1<Size-1)&&(p[co_x+1][co_y].get_pointer_to_ship()!=NULL))
     {    
          /* H get_pointer_to_ship einai enas accessor ths gridpoint pou 
           * epistrefei deikth sto ploio pou vrisketai panw sto gridpoint
           */
          p[co_x+1][co_y].get_pointer_to_ship()->threaten();   
     }

     if((co_x-1>=0)&&(p[co_x-1][co_y].get_pointer_to_ship()!=NULL))
     {
          p[co_x-1][co_y].get_pointer_to_ship()->threaten();
     }

     if((co_y+1<Size-1)&&(p[co_x][co_y+1].get_pointer_to_ship()!=NULL))
     {
          p[co_x][co_y+1].get_pointer_to_ship()->threaten();
     }

     if((co_y-1>=0) &&(p[co_x][co_y-1].get_pointer_to_ship()!=NULL))
     {
          p[co_x][co_y-1].get_pointer_to_ship()->threaten();
     }
}

int Grid::win()          //epistrefei 1 an kerdise o xrhsths
{
     
     if(score==high_score)
     {
          cout<<"You, Master of the Sea!"<<endl;
          cout<<"Your score is "<<score<<endl;
          cout<<"You have sunk "<<sink_k1<<" aircraft carriers"<<endl;
          cout<<"You have sunk "<<sink_k2<<" submarines"<<endl;
          cout<<"You have sunk "<<sink_k3<<" tugs"<<endl;
          return 1;
     }
     else
     {
          return 0;
     }
}

void Grid::lost()             //ektipwnei ta minimata gia to gameover
{
     cout<<"Game Over!"<<endl;
     cout<<"Your score is "<<score<<endl;
     cout<<"You have sunk "<<sink_k1<<" aircraft carriers"<<endl;
     cout<<"You have sunk "<<sink_k2<<" submarines"<<endl;
     cout<<"You have sunk "<<sink_k3<<" tugs"<<endl;
}

void Grid::print()       //ektipwnei to plegma
{
     int i=0, j=0;

     cout<<"\n\n"<<endl;
     print_score();
	cout<<"\t___";             //sxediash anw oriou
     for(i=0;i<Size;i++)
     {
          if ((i%2==0)&&(i!=0))    //ektipwnei stis steiles tous monous arithmous
          {
               cout<<"__";
               continue;
          }
          if (i<10)
		     cout<<i<<"_";     
          else 
               cout<<i;
     }

	cout<<"\n";

	for(i=0;i<Size;i++)
	{	
          cout<<"\t";
          cout << setfill ('0') << setw (2)<<i;   //arithmos grammhs
          cout<<"|";                              //aristero akro
		for(j=0;j<Size;j++)
		{
               if(p[i][j].is_hited()==1)          //to siemeio exei xtipithei
               {
                    cout<<"B|";
               }
		     else if (p[i][j].is_chosed()==1)   //to simeio exei epilegei
			{
                    cout<<"F|";
               }
			else if ((p[i][j].is_occupied()==1)&&(cheat==true))//mas deixnei ta ploia(cheat-debug)
               {    
                    if (p[i][j].type()==1)               
                         cout<<"T|";         //tug
                    else if (p[i][j].type()==3)
                         cout<<"S|";        //sub
                    else if (p[i][j].type()==5)
                         cout<<"A|";         //aircraft                             
               }
               else
               {
			     //cout<<"_|";//poio wraio gia to plegma alla th na kanoume:P
                    cout<<".|";
               }
		}
		cout<<"\n";
	}		
}
/////////////////////constructors/////////////////////////

Ship::Ship(int x,Grid* gr)
{
     length=x;
     dmg=0;
     grid=gr;                           //to ploio deixnei sto Grid     
     direction=rand()%2;                //orizetai tixaia h katefthinsi, 0 orizontia 1 katheta
     x_plorh=rand()%(gr->get_grid_size());  //dhmiourgountai tixaies sidetagmenes gia th plwrh
     y_plorh=rand()%(gr->get_grid_size());

     while(gr->fits(this,x_plorh,y_plorh,direction,x)==0)//elenxos an borei na topotheththei to ploio
     {
          x_plorh=rand()%(gr->get_grid_size());//dhmiourgountai nees tixaies sid/menes gia th plwrh
          y_plorh=rand()%(gr->get_grid_size()); 
          direction=rand()%2;                
     }

     gr->place(this,x_plorh,y_plorh,direction,x);//topothethsh tou ploiou sto grid
}

Tug::Tug(Grid *gr):Ship(1,gr)  
{
     /*O constructor tou tug. Pairnei san orisma enan deikth 
      * pros to Grid kai kalei me xrhsh initializer list ton
      * constructor tou ship opou tou pernaei to megethos tou
      * dhladh 1 kai ton deikth pros to plegma
      */       
}


Submarine::Submarine(Grid *gr):Ship(3,gr)//pernaei to megethos tou 3
{
}

Aircraft_carrier::Aircraft_carrier(Grid *gr):Ship(5,gr)//pernaei to megethos tou 5
{
}
////////////////////sinarthseis twn tug,submarine,aircraft carrier//////

void Tug::score_update()
{
     grid->score_up(1);            //afksanei to scor tou paixth kata 1
}

void Aircraft_carrier::score_update()
{
     grid->score_up(3);           //afksanei to scor tou paixth kata 3
}

void Submarine::score_update()
{
     grid->score_up(5);           //afksanei to scor tou paixth kata 5
}
////////////////////threaten twn tug,submarine/////////////////////////
void Tug::threaten()
{
     int dir;
     int x,y;
     if(dmg==0)         //an to tug DEN exei xtipithei(vuliaksei) dokimazei na metakinithei
     {                  //h diadiakasia einai paromoia me thn arxikh tou topothethsh
        dir=rand()%2;                
        x=rand()%grid->get_grid_size();    
        y=rand()%grid->get_grid_size();

        while(grid->fits(this,x,y,dir,length)==0)  
        {   
            dir=rand()%2;               
            x=rand()%grid->get_grid_size();        
            y=rand()%grid->get_grid_size();
         }
         /* Otan vrethei nea katallhlh thesh tote to apomakrinoume apo
          * th trexwn thesh tou kai to topothetoume sth kainourgia. Sth
          * sinexeia enimeronoume tis aparaithtes metavlhtes
          */ 

         grid->unplace(this, x_plorh,y_plorh,direction,length);  
         
         grid->place(this,x,y,dir,length);

         x_plorh=x;     
         y_plorh=y;     
         direction=dir;        
      }    
}


void Submarine::threaten()
{
     /* An to ipovrixio DEN exei xtipithei dokimazei na metakinithei.
      * H diadikasia einai paromoia me thn threaten tou tug me thn diafora
      * oti tha dokimasei mono mia thesh gia na metekinithei ,opote an afth 
      * den einai epitrepth tha parameinei sth thesh tou
      */
     int dir;
     int x,y;
     if(dmg==0)         
     {
        dir=rand()%2;              
        x=rand()%grid->get_grid_size();        
        y=rand()%grid->get_grid_size();
        if(grid->fits(this,x,y,dir,length)==1) //mia efkaireia mono 
        {
            grid->unplace(this, x_plorh,y_plorh,direction,length);  

            grid->place(this,x,y,dir,length);

            x_plorh=x;     
            y_plorh=y;     
            direction=dir;
        }
     }
}
///////////////////////////////sink////////////////////////////
void Tug::sink()         
{
     score_update();                    //kalei th score_update
     grid->vithismena_skafh(3);         //enhmerwnei ton metrhth vithismenwn tug                
     cout<<"You just got a small boat!"<<endl; 
}

void Submarine::sink()
{
     score_update();
     grid->vithismena_skafh(2);
     cout<<"You just got a submarine!"<<endl;
}

void Aircraft_carrier::sink()
{ 
     score_update();
     grid->vithismena_skafh(1);
     cout<<"You just got a large ship!"<<endl;
}


///////////////////////////////////////////////////////////////
int main(int argc,char *argv[])
{    
     if(argc!=2)     //an exoun dothei lathos orismata
     {
          cout<<"use: navmaxia [N] "<<endl;
          return -1;
     }

     srand(time(NULL));     

     int N=atoi(argv[1]);

     if(N<0)       //cheat mode , ama dwsoume to N pou theloume alla arnthiko
     {             //tote boroume na paiksoume kai na vlepoume tis theseis twn ploiwn
          N=-N;
          cheat=true;
     }

     if (N<5)  //katw apo 5 dn emfanizontai ploia sto grid
     {
          cout<<"There are no ships. The grid is too small!"<<endl;
          return -1;
     }

     int K= (int)(0.75*N*N);  //arithmos vhmatwn
     
     int x,y;                   //coordinates to strike
     Grid* Battlefield;         //deikths pros Grid
     Battlefield =new Grid(N);  //dhmiourgia tou Grid
     Battlefield->print();      //prwth ektipwsh

     
     while (K--)    
     {
          cout<<"Give the coordinates to strike!"<<endl;         //dinoume tis sintetagmenes
          cin>>x;
          cin>>y;
          while((x>=N)||(y>=N))                   //elenxos an vriskontai mesa sta epitrepta oria
          {
               cout<<"Invalid coordinates. Try again!"<<endl;
               cin>>x;
               cin>>y;
          }
          cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"<<endl;//illuion katharismou othonis
          cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"<<endl;
          cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"<<endl;
         

          Battlefield->update(x,y);

          if (Battlefield->win()==1)    //ama o paikths kerdise
          {
               delete Battlefield;
               return 0;  
          }
          Battlefield->print();         //ektipwsh tou plegmatos meta to update
     }

     Battlefield->lost();     //an stis K prospatheis dn exeis kerdisei o piakths tote game over
     
     delete Battlefield;
     return 0;     
}


