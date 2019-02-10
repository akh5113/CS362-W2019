#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

//number of times inputChar() is called
int call = 0;

char inputChar()
{
    // TODO: rewrite this function
    
    //array of chars
    char characters[9] = {'[', '{', '(', ')', '}', ']', 'a', ' ', 'x'};
    char stringChars[9] = {'r', 'e', 's', 't','\0', 'r', 'e', 's', 't'}; //made same length as characters[] 
    //range
    int low = 0;
    int high = 9;

    //get random number 
    int randNum;
    randNum = rand()% (high - low +1) + low;
    //printf("Random number: %d yields character %c\n", randNum, characters[randNum]);
    if(call % 2 == 0){
        //printf("returning %d\n", stringChars[randNum]);
        return stringChars[randNum];
    }
    else{
        //printf("returning %d\n", characters[randNum]);
        return characters[randNum];
    }
}

// declare string
char string[6];

char *inputString()
{
    // TODO: rewrite this function
    call++; //increase for calling inputChar() so it will return from the right array

    //fill string with chars from inputChar() func
    int i;
    char c;
    for(i = 0; i < 6; i++){
        c = inputChar();
        string[i] = c;
    }
    return string;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  //coverage testing variables
  int if1 = 0;
  int if2 = 0;
  int if3 = 0;
  int if4 = 0;
  int if5 = 0;
  int if6 = 0;
  int if7 = 0;
  int if8 = 0;
  int if9 = 0;
  int if10 = 0;
  int ifSum = 0;
  float ifperc = 0;

  while (1)
  {
    tcCount++;
    call++; //increase for calling inputChar(), so it will return from correct array
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0){
        state = 1;
        if1++;
    }
    if (c == '(' && state == 1){
        state = 2;
        if2++;
    }
    if (c == '{' && state == 2){
        state = 3;
        if3++;
    }
    if (c == ' '&& state == 3){
        state = 4;
        if4++;
    }
    if (c == 'a' && state == 4){
        state = 5;
        if5++;
    }
    if (c == 'x' && state == 5){
        state = 6;
        if6++;
    }
    if (c == '}' && state == 6){
        state = 7;
        if7++;
    }
    if (c == ')' && state == 7){
        state = 8;
        if8++;
    }
    if (c == ']' && state == 8){
        state = 9;
        if9++;
	//exit(200);
    }
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      if10++;
      printf("error \n");
      ifSum = if1 + if2 + if3 + if4 + if5 + if6 + if7 + if8 + if9 + if10;
      ifperc = (ifSum/tcCount) * 10;

      //print out coverage information
      printf("Coverage for the 1st if statement is: %d\n", if1);
      printf("Coverage for the 2nd if statement is: %d\n", if2);
      printf("Coverage for the 3rd if statement is: %d\n", if3);
      printf("Coverage for the 4th if statement is: %d\n", if4);
      printf("Coverage for the 5th if statement is: %d\n", if5);
      printf("Coverage for the 6th if statement is: %d\n", if6);
      printf("Coverage for the 7th if statement is: %d\n", if7);
      printf("Coverage for the 8th if statement is: %d\n", if8);
      printf("Coverage for the 9th if statement is: %d\n", if9);
      printf("Coverage for the 10th if statement (error) is: %d\n", if10);
      printf("It took %d iterations to reach the error statement\n", tcCount);
      printf("An 'if' statement was executed %.10f percent of the time\n", ifperc);
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
