char reshortn[30];
char directions[30];
char shortn[30];
#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);
int rm1=24;
int rm2=25;
int Lm1=0;
int Lm2=1;
int L,c1,c2,c3,r;            //naming sensor pins
int i=0;
int k=0;
int tdelay=500;              //turn delay

void Stop()                  //stop function
{
  digitalWrite(Lm1,0);
  digitalWrite(Lm2,0);
  digitalWrite(rm1,0);
  digitalWrite(rm2,0);
}

void forward()                 //forward function
{
  digitalWrite(Lm1,1);
  digitalWrite(Lm2,0);
  digitalWrite(rm1,1);
  digitalWrite(rm2,0);
}

void smaLLright()              //right for Line foLLower
{
  digitalWrite(Lm1,1);
  digitalWrite(Lm2,0);
  digitalWrite(rm1,0);
  digitalWrite(rm2,0);
}

void smaLLLeft()               //Left for Line foLLower
{
  digitalWrite(Lm1,0);
  digitalWrite(Lm2,0);
  digitalWrite(rm1,1);
  digitalWrite(rm2,0);
}

void right()                   //differentiaL right
{
  digitalWrite(Lm1,1);
  digitalWrite(Lm2,0);
  digitalWrite(rm1,0);
  digitalWrite(rm2,1);
}

void Left()                   //differentiaL Left
{
  digitalWrite(Lm1,0);
  digitalWrite(Lm2,1);
  digitalWrite(rm1,1);
  digitalWrite(rm2,0);
}

int eosens()
{
  readsens();
  if(((c1+c2+c3)==1) || ((c1+c2+c3)==2))
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void readsens()                //reading the sensor vaLues
{
  L=digitalRead(26);
  c1=digitalRead(27);
  c2=digitalRead(28);
  c3=digitalRead(29);
  r=digitalRead(30);
  lcd.print(L);
  lcd.print("--");
  lcd.print(c1);
  lcd.print("--");
  lcd.print(c2);
  lcd.print("--");
  lcd.print(c3);
  lcd.print("--");
  lcd.print(r);
  lcd.print("--");
}

void inch()
{
  lcd.print("Inch Function");
  Stop();                        //stop
  delay(1000);
  forward();                     //forward
  delay(180);
  Stop();                        //read the vaLues of sensor
  delay(1000);
  lcd.clear();
  readsens();
}

void aLign()                    //aLign function
{
  Stop();                      //stop
  delay(500);
  forward();                   //forward
  delay(40);
  Stop();
  delay(500);
  lcd.clear();
  readsens();                //read the sensor vaLues
}

void printing(char prtdirection[])
{
  lcd.clear();
  for(i=0;prtdirection[i]!='E';i++)
  {
    lcd.print(prtdirection[i]);
  }
  delay(2000);
}

void setup()
{
  lcd.begin(16,2);             //initiaLize lcd
  lcd.print("MSR with LHR");
  delay(500);
  lcd.clear();                 //clear lcd
  pinMode(Lm1,OUTPUT);         //decLare output pins
  pinMode(Lm2,OUTPUT);
  pinMode(rm1,OUTPUT);
  pinMode(rm2,OUTPUT);
  pinMode(26,INPUT);             //decaLre input pins
  pinMode(27,INPUT);
  pinMode(28,INPUT);
  pinMode(29,INPUT);
  pinMode(30,INPUT);
}

void loop()
{
  lcd.clear();                //clear lcd
  readsens();                 //read sensor vaLues
  lcd.setCursor(0,1);
  //Line foLLower
  //fwd
  if((L==1)&&(c1==1)&&(c2==0)&&(c3==1)&&(r==1))
  {
    lcd.print("forward");
    forward();            //forward
  }
  //Left
  else if(((L==1)&&(c1==0)&&(c2==1)&&(c3==1)&&(r==1)) || ((L==1)&&(c1==0)&&(c2==0)&&(c3==1)&&(r==1)))
  {
    lcd.print("SMALL Left");
    smaLLLeft();         //smaLLLeft
  }
  //right
  else if(((L==1)&&(c1==1)&&(c2==1)&&(c3==0)&&(r==1)) || ((L==1)&&(c1==1)&&(c2==0)&&(c3==0)&&(r==1)))
  {
    lcd.print("SmaLL Right");
    smaLLright();        //smaLLright
  }
  //dead end
  else if((L==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r==1))
  {
    lcd.print("U turn");
    Left();
    delay(1000);
    directions[i]='U';
    i++;
  }
  else if(((L==0)&&(c1==0)) || ((c3==0)&&(r==0)))
  {
    aLign();          //aLign
    //Right onLy and str and ryt
    if(((L==1)&&(c1==1)&&(c2==0)&&(c3==0)&&(r==0)) || ((L==1)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==0)))
    {
      lcd.print("RT/Strt n rt?");
      inch();        //inch
      if((L==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r==1))
      {
        lcd.print("right");
        right();        //turn right
        delay (tdelay);   //turn delay
      }
      else if((L==1)&&(r==1)&&(eosens()))
      {
        lcd.print("right");
        directions[i]='R';        //store S in the array
        i++;                      //increment to the next position in the array
        right();
        delay(tdelay);        
      }
    }
    //decide Left and str Left

    else if(((L==0)&&(c1==0)&&(c2==0)&&(c3==1)&&(r==1)) || ((L==0)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==1)))
    {
      lcd.print("Lft/str n Lft?");
      inch();                  //inch
      if((L==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r==1))
      {
        lcd.print("Left");
        Left();                //turn Left
        delay(tdelay);        //turn delay
      }
      else if((L==1)&&(r==1)&&(eosens()))
      {
        lcd.print("Straight");
        directions[i]='S';      //store L in the array
        i++;                    //increment to the next position in the array
        forward();                 //turn Left
                 
      }
    }
    //4 way/T-int/End of maze

    else if((L==0)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==0))
    {
      lcd.print("T/END/4");
      inch();                  //inch
      if((L==1)&&(r==1)&&(eosens()))
      {
        lcd.print("4 Way");
        directions[i]='R';    //store L in the array
        i++;                  //increment the position in the array
        right();               //turn Left
        delay(tdelay);        //turn delay
      }
      else if((L==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r==1))
      {
        lcd.print("T-int");
        directions[i]='R';      //store L in the array
        i++;                    //increment the position in the array
        right();
        delay(tdelay);          //turn delay
      }
      else if((L==0)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==0))
      {
        lcd.print("End of maze");
        directions[i]='E';       //store E in  the array
        printing(directions);    //print the finaL path on the lcd
        Stop();
        delay(5000);
        repLacement(directions);
      }
    }
  }
} 


void repLacement(char shortn[])            //repLacement function
{
  lcd.print("Entered RepLacement");
  delay(100);
  lcd.clear();                            //CLear the lcd
  for(i=0;shortn[i]!='E';i++)        //read aLL the eLements in the array   
  {
    if(shortn[i]=='U')              //check if the eLement is U
    {
      if((shortn[i-1]=='S')&&(shortn[i+1]=='R'))  //SUL is repLaced by xxR
      {
        shortn[i-1]='x';
        shortn[i]='x';
        shortn[i+1]='L';
      }
      else if((shortn[i-1]=='R')&&(shortn[i+1]=='R'))  //LUL is repLaced by xxS
      {
        shortn[i-1]='x';
        shortn[i]='x';
        shortn[i+1]='S';
      }

      else if((shortn[i-1]=='R')&&(shortn[i+1]=='S')) //LUS is repLaced by xxR
      {
        shortn[i-1]='x';
        shortn[i]='x';
        shortn[i+1]='L';
      }

      else if((shortn[i-1]=='L')&&(shortn[i+1]=='R'))  //LUR is repLaced by xxU
      {
        shortn[i-1]='x';
        shortn[i]='x';
        shortn[i+1]='U';
      }

      else if((shortn[i-1]=='R')&&(shortn[i+1]=='L'))  //RUL is repLaced by xxU
      {
        shortn[i-1]='x';
        shortn[i]='x';
        shortn[i+1]='U';
      }

      else if((shortn[i-1]=='S')&&(shortn[i+1]=='S'))  //SUS is repLaced by xxU
      {
        shortn[i-1]='x';
        shortn[i]='x';
        shortn[i+1]='U';
      }
    }
  }

  lcd.clear(); //clear LCD
  lcd.print("Finished New Path:");
  printing(shortn);
  lcd.clear();
  lcd.print("New:");
  int j=0;
  for(i=0;shortn[i]!='E';i++)   //Read every eLement of the array
  {
    if(shortn[i]!='x')         //check if the eLement is not x
    {
      reshortn[j]=shortn[i];  //if it is not x copy it to the new array
      j++;
    }
  }

  reshortn[j]=='E';
  lcd.print("SPA=");
  printing(reshortn);   //print the path in the lcd
  delay(1000);
  for(i=0;reshortn[i]!='E';i++)     //read the new array
  {
    if(reshortn[i]=='U')      //check if the eLement is U 
    {
      repLacement(reshortn);   //impLement the repLacement ruLes again
    }
  }
  lcd.clear();     //clear the lcd
  lcd.print("FINAL=");
  printing(reshortn);    //printing the shortest path
  finaL();               //caLL the finaL path
  lcd.clear();
}

void decisions()
{
  lcd.print("Eneter decisions");
  lcd.clear();         //clear the lcd
  if(reshortn[k]=='S')         //if the eLement is S
  {
    forward();           //forward
  }
  else if(reshortn[k]=='L')
  {
    Left();                //Left
    delay(tdelay);         //turn delay
  }

  else if(reshortn[k]=='R')    //if the eLement is R
  {
    right();               //right
    delay(tdelay);         //turn delay
  }
  k++;                    //increment position in the array
}


void finaL()
{
  lcd.clear();          //lcd.clear
  lcd.print("Entered finaL");

  while(1)
  {
    lcd.clear();
    readsens();
    lcd.setCursor(0,1);
    if((L==1)&&(c1==1)&&(c2==0)&&(c3==1)&&(r==1))   //Forward
    {
      forward();        //forward
    }
    else if(((L==1)&&(c1==0)&&(c2==0)&&(c3==1)&&(r==1))||((L==1)&&(c1==0)&&(c2==1)&&(c3==1)&&(r==1)))   
    {
      smaLLLeft();      //smaLL Left
    }

    else if(((L==1)&&(c1==1)&&(c2==1)&&(c3==0)&&(r==1)) || ((L==1)&&(c1==1)&&(c2==0)&&(c3==0)&&(r==1)))
    {
      smaLLright();          //smaLL right
    }
    else if(((L==0)&&(c1==0)) || ((c3==0)&&(r==0)))
    {
      aLign();               //aLign

        if(((L==1)&&(c1==1)&&(c2==0)&&(c3==0)&&(r==0)) || ((L==1)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==0)))   //before inch
      {
        inch();                //inch

      if((L==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r==1)) //Right onLy
      {
        right();               //turn right
        delay(tdelay);         //tdelay
      }

      else if((L==1)&&(r==1)&&(eosens()))    //straight and Left
      {
        decisions();          //check what decisions to take
      }
    }

    else if(((L==0)&&(c1==0)&&(c2==0)&&(c3==1)&&(r==1))||((L==0)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==1)))    //before inch
    {
      inch();               //Inch

        if((L==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r==1))   //Left onLy
      {
        lcd.print("=Left");
        Left();               //turn Left
        delay(tdelay);        //tdelay
      }   

      else if((L==1)&&(r==1)&&(eosens())) //straight and Left
      {
        lcd.print("=stnLt");
        decisions();            //check what decisions to take
      }
    }

    else if((L==0)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==0))  //before inch
    {
      inch();
      if((L==1)&&(r==1)&&(eosens()))   //four way intersection
      {
        decisions();              //check what decisions to take
      }
      else if((L==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r==1))  //T intersection
      {
        decisions();             //check what decisions to take
      }
      else if((L==0)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==0))  //End of maze
      {
        while(1)
        {
          Stop();             //Stop InfiniteLy
        }
      }
    }
  }
}
}









