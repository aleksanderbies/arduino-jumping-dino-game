#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // RS, E, D4, D5, D6, D7

byte dino[] = {
  0b00000,
  0b00111,
  0b00111,
  0b10110,
  0b11111,
  0b01010,
  0b01010,
  0b00000
};

byte cactus[] = {
  0b00100,
  0b00101,
  0b10101,
  0b10101,
  0b10111,
  0b11100,
  0b00100,
  0b00000
};

byte pattern[] = {
  0b00000,
  0b00000,
  0b00100,
  0b01010,
  0b10101,
  0b01010,
  0b00100,
  0b00000
};



void setup() {
  lcd.begin(16, 2);
  lcd.createChar(0, dino);
  lcd.createChar(1, cactus);
  lcd.createChar(2, pattern);
  showGameName();
}

int dino_pos;
int cactus_pos;
int DinoUpCount = 0;
int dinoDownCount = 4;         //to make dino jump, counter have to be more than 3
int Score = 0;
int choice = 0;
int button = 0;
int Delay;
String difficulty[] = {"Easy", "Normal", "Hard", "Expert", "Progressive"};
boolean GameOver = false;
boolean GODLIKE = false;
boolean DifficultyDecided = false;
boolean delayProgressive = false;


void setCursorToPrintEnteredDifficulty(int choice){
  if(choice == 0 || choice == 2){                  //centering of the difficulty text on screen
    lcd.setCursor(4,0);
    lcd.write(byte(2));
    lcd.setCursor(11,0);
    lcd.write(byte(2));
    lcd.setCursor(6,0);
  }
  else if(choice == 1 || choice == 3){
    lcd.setCursor(3,0);
    lcd.write(byte(2));
    lcd.setCursor(12,0);
    lcd.write(byte(2));
    lcd.setCursor(5,0);
  }
  else if(choice == 4){
    lcd.setCursor(0,0);
    lcd.write(byte(2));
    lcd.setCursor(14,0);
    lcd.write(byte(2));
    lcd.setCursor(2,0);
  }
}

void setCursorToPrintNextDifficulty(int choice){
  if(choice > 4){
    choice = 0; 
  }

  if(choice == 0 || choice == 2){
    lcd.setCursor(6,1);
  }
  else if(choice == 1 || choice == 3){
    lcd.setCursor(5,1);
  }
  else if(choice == 4){
    lcd.setCursor(2,1);
  }
}


int getDifficulty(){
    lcd.setCursor(1,0);
    lcd.print("Choose");
    lcd.setCursor(3,1);
    lcd.print("difficulty");
    delay(2000);
    lcd.clear();
    while(true){
      lcd.clear();
                                                       //scrolling menu, displaying actual and next option |--
      setCursorToPrintEnteredDifficulty(choice);
      lcd.print(difficulty[choice]);                   //display of actual option on screen
      setCursorToPrintNextDifficulty(choice+1);
      if(choice+1 > 4){
        lcd.print(difficulty[0]);
      }
      else{
        lcd.print(difficulty[choice+1]);
      }
                                                       //   --|
      button = analogRead(A0);
      if(button >= 258 && button <= 358){              //scroll down using 'DOWN' key on keypadshield
        if(choice < 4){
          choice++;
        }
        else{
          choice = 0;
        }
        delay(100);
      }
      else if(button >= 110 && button <= 160){           //scroll up using 'UP' key on keypadshield
        if(choice > 0){
          choice--;
        }
        else{
          choice = 4;
        }
        delay(100);
      }
      else if(button >= 670 && button <= 770){          //entering of choice
        break;
        delay(100);
      }
      delay(100);
    }
    return choice;
}


int getDelay(int choice){
    if(choice == 0){                                   //delaying of cactus,  more speed = more difficult
      Delay = 400;
    }
    else if(choice == 1){
      Delay = 300;
    }
    else if(choice == 2){
      Delay = 200;
    }
    else if(choice == 3){
      Delay = 125;
    }
    else if(choice == 4){
      Delay = 400;
      delayProgressive = true;
    }
    lcd.clear();                                      //clear screen before game start
    lcd.setCursor(3,1);
    lcd.write(byte(0));
    lcd.setCursor(15,1);
    lcd.write(byte(1));
    //return Delay;
}


void jump(){
  if(dinoDownCount > 3){            //delay between jump and fall down of dino
    lcd.setCursor(3,1);
    lcd.print(" ");
    lcd.setCursor(3,0);
    lcd.write(byte(0));
    dino_pos = 0;                //position of dino after jump
    if(DinoUpCount == 0){            //start of count iteration when dino is up
      DinoUpCount = 1;               
    }
    dinoDownCount = 0;
  }
}

void jumpDown(){
  lcd.setCursor(3,0);
  lcd.print(" ");
  lcd.setCursor(3,1);
  lcd.write(byte(0));
  DinoUpCount = 0;
  if(dinoDownCount == 0){
    dinoDownCount = 1;
  }
}


void authors(){
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Adam Barczyk");
  lcd.setCursor(0,1);
  lcd.print("Aleksander Bies");
}

void showGameName(){
  boolean nameDisplayed = false;
  while(true){
    if(!nameDisplayed){
      lcd.setCursor(2,0);
      lcd.print("Jumping Dino");
      lcd.setCursor(2,1);
      lcd.print("Press SELECT");
      lcd.setCursor(0,1);
      lcd.write(byte(2));
      lcd.setCursor(0,0);
      lcd.write(byte(2));
      lcd.setCursor(15,1);
      lcd.write(byte(2));
      lcd.setCursor(15,0);
      lcd.write(byte(2));
      nameDisplayed = true;
    }
    
    button = analogRead(A0);
    if(button >= 670 && button <= 770){
      lcd.clear();
      break;
    }
  }
}

void playAgain(){
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Press RESET");
  lcd.setCursor(1,1);
  lcd.print("to play again");
}

void score(){
  if(Score <= 9){                    //set the cursor to print score in upper right corner
    lcd.setCursor(15,0);
  }
  else if(Score >= 10 && Score <= 99){
    lcd.setCursor(14,0);
  }
  else if(Score >= 100 && Score <= 999){
    lcd.setCursor(13,0);
  }
  else if(Score >= 1000){
    lcd.setCursor(8,0);
    GODLIKE = true;
  }

  if(GODLIKE){                       //print score in the upper right corner
    lcd.print("GODLIKE!");
  }
  else{
    lcd.print(Score);
  }
}






void loop() {
  if(GameOver){
    return;
  }

  if(!DifficultyDecided){
    choice = getDifficulty();
    getDelay(choice);
    DifficultyDecided = true;
  }
  
  for (int i = 15; i>=0; --i){          //move the cactus
    if(DinoUpCount > 0){                //couter of iteration, when dino is up in next step, counter increments J
      DinoUpCount++;
    }
    if(dinoDownCount > 0){
      dinoDownCount++;
    }

    score();
    
    dino_pos = 1;                   //positon of dino before jump 
    cactus_pos = i;
    lcd.setCursor(i,1);
    lcd.write(byte(1));
    button = analogRead(A0);
    if (button >= 110 && button <= 160){   
          jump();
    }
     if (dino_pos==1 && cactus_pos==3){     //break game condition 
      lcd.clear();
      if(!GODLIKE){
        lcd.setCursor(3,0);
        lcd.print("Game over!");                   
        lcd.setCursor(4,1);
        lcd.print(String("Score: ") + String(Score));                //print score
      }
      else{
        lcd.setCursor(4,0);
        lcd.print("You Are");
        lcd.setCursor(4,1);
        lcd.print("GODLIKE!");
      }
      GameOver = true;
      delay(3000);
                                                      
      authors();                                                   //prints authors names
      delay(3000);
      playAgain();
      break;                                       
      }
     else if(DinoUpCount == 3){                  
      //delay(100);                                 //dino falls down
      jumpDown();
     };

     Score++;

     if(!delayProgressive){
      delay(Delay);
     }
     else{
      if(Delay > 300){
        Delay = Delay - Delay * 1/35;
      }
      else if(Delay > 200 && Delay <= 300){
        Delay = Delay - Delay * 1/95;
      }
      else if(Delay > 155 && Delay <= 200){
        Delay = Delay - Delay * 1/140;
      }
      else if(Delay > 125 && Delay <= 155){
        Delay = Delay - Delay * 1/100;
      }
      else if(Delay <= 125){
        Delay = 125;
      }
      delay(Delay);
     }
     lcd.setCursor(i,1);                         
     lcd.print(" ");                              //delete cactus from position to not have double cactus
      }
}
