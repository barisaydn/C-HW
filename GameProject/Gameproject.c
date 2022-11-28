#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include <time.h>
#define SIZE 10
char gamecodeword[SIZE];
typedef struct
{
    int correctwordcounter, wronglettercounter, correctlettercounter, score, tabNumber, newlineNumber;
    int bombtabNumber, bombFalling, bombrate, bombspeed, mainmenuUI, chtyped;
}gamestate;
gamestate gamestateloadholder;//a global gamestate holder for loading games 
void gameFinishedfunc(); //defining the type of gameFinishedfunc
void gameOverfunc();//defining the type of gameOver func
void mainmenuprintingfunc();
int mainmenuhelper()
{
    int mainmenuUI = 0;
    scanf_s("%d", &mainmenuUI);
    if (mainmenuUI == 5)
    {
        system("cls");
        return 0; //exiting the game
    }
    return mainmenuUI;
}
int gameendmenuhelper()
{
    int endmenuUI = 0;
    scanf("%d", &endmenuUI);
    return endmenuUI;
}
int codewordlisthelperindex(int correctwordcounter)
{
    if (correctwordcounter >= 35) {
        int ten = 210 + ((correctwordcounter - 35) * 10);
        return ten; //10 letter keywords
    }
    if (correctwordcounter >= 30) {
        int nine = 165 + ((correctwordcounter - 30) * 9);
        return nine; //9 letter keywords
    }
    if (correctwordcounter >= 25) {
        int eight = 125 + ((correctwordcounter - 25) * 8);
        return eight; //8 letter keywords
    }
    if (correctwordcounter >= 20) {
        int seven = 90 + ((correctwordcounter - 20) * 7);
        return seven; //7 letter keywords
    }
    if (correctwordcounter >= 15) {
        int six = 60 + ((correctwordcounter - 15) * 6);
        return six; //6 letter keywords
    }
    if (correctwordcounter >= 10) {
        int five = 35 + ((correctwordcounter - 10) * 5);
        return five; //5 letter keywords
    }
    if (correctwordcounter >= 5) {
        int four = 15 + ((correctwordcounter - 5) * 4);
        return four; //4 letter keywords
    }
    if (correctwordcounter >= 0)
    {
        int three = correctwordcounter * 3;
        return three; //3 letter codewords
    }
    return correctwordcounter;//in case there is a bug and correctwordcounter goes under 0 
}
int codewordlisthelpersize(int correctwordcounter)
{


    if (correctwordcounter >= 35) {

        return 10; //10 letter keywords
    }
    if (correctwordcounter >= 30) {

        return 9; //9 letter keywords
    }
    if (correctwordcounter >= 25) {

        return 8; //8 letter keywords
    }
    if (correctwordcounter >= 20) {

        return 7; //7 letter keywords
    }
    if (correctwordcounter >= 15) {

        return 6; //6 letter keywords
    }
    if (correctwordcounter >= 10) {

        return 5; //5 letter keywords
    }
    if (correctwordcounter >= 5) {

        return 4; //4 letter keywords
    }
    if (correctwordcounter >= 0)
    {

        return 3; // letter codewords
    }
    return correctwordcounter;//in case there is a bug and correctwordcounter goes under 0 
}
void planefunc(int tabNumber)
{
    FILE* planePtr;
    planePtr = fopen("plane.txt", "r");
    char plane[1000];
    int k;
    // if the file does not exist
    if (planePtr == NULL)
    {
        printf("Could not open file plane.txt");
        return;

    }

    // read the text from the file into a string while we are not in the end of file
    while (!feof(planePtr))
    {
        fgets(plane, "%s", planePtr);
        //printing enough tabs
        for (k = 0; k < tabNumber; k++) {
            printf("\t");
        }

        printf("%s", plane);
    }
    fclose(planePtr);
}
void cityfunc()
{
    FILE* cityPtr;
    cityPtr = fopen("city.txt", "r");
    char city[1000];

    // if the file does not exist
    if (cityPtr == NULL)
    {
        printf("Could not open file city.txt");
        return;
    }

    // read the text from the file into a string while we are not in the end of file
    while (!feof(cityPtr))
    {
        fgets(city, 132, cityPtr);
        printf("%s", city);
    }
    fclose(cityPtr);
}
void saveloadgamemenufunc()
{
    FILE* saveloadgamemenuPtr;
    saveloadgamemenuPtr = fopen("saveloadgamemenu.txt", "r");
    char saveloadgamemenu[10000];

    // if the file does not exist
    if (saveloadgamemenuPtr == NULL)
    {
        printf("Could not open file city.txt");
        return;
    }

    // read the text from the file into a string while we are not in the end of file
    while (!feof(saveloadgamemenuPtr))
    {
        fgets(saveloadgamemenu, 30, saveloadgamemenuPtr);
        printf("%s", saveloadgamemenu);
    }
    fclose(saveloadgamemenuPtr);
}
void codewordsfunc(int correcwordcounter)
{
    FILE* codewordsPtr;
    codewordsPtr = fopen("codewords.txt", "r");
    char codewords[1000];
    int  i = 0;
    // if the file does not exist
    if (codewordsPtr == NULL)
    {
        printf("Could not open file codewords.txt");
        return;
    }
    // read the text from the file into a string while we are not in the end of file
    while (!feof(codewordsPtr))
    {
        fgets(codewords, "%s", codewordsPtr);
        // put enough tabs 

        int codewordindex = codewordlisthelperindex(correcwordcounter);//the position of the first letter of the code word
        int codewordsize = codewordlisthelpersize(correcwordcounter);//size of the current codeword
        
        for (i = 0; i < codewordsize; i++)
        {
            gamecodeword[i] = codewords[codewordindex];
            printf("%c", gamecodeword[i]);
            codewordindex++;

        }
       
    }
    fclose(codewordsPtr);
}
void bombfunc(int newlinenumber, int correctwordcounter, int bombTabnumber, int chtyped)
{
    FILE* bombPtr;
    bombPtr = fopen("bomb.txt", "r");
    char bomb[1000];
    int k;
    int c;
    int distleft = 0, i = 0;
    // if the file does not exist
    if (bombPtr == NULL)
    {
        printf("Could not open file bomb.txt");
        return;
    }
    // put enough new lines
    for (k = 0; k < newlinenumber; k++) {
        printf("\n");
    }
    distleft = 37 - k; //k is the no lines from plane to bomb and dist left is no lines from bomb to city
    // read the text from the file into a string while we are not in the end of file
    while (!feof(bombPtr))
    {
        fgets(bomb, 4, bombPtr);

        // put enough tabs 
        for (c = 0; c < bombTabnumber; c++) {
            printf("\t");
        }
        printf("%s", bomb);

    }
    
    if (chtyped == 0) { codewordsfunc(correctwordcounter); }//printing the codewords near the bomb
    else {
        printf("%s", gamecodeword);
    }
    fclose(bombPtr);//closing the file
    for (i; i < distleft; i++) {
        printf("\n");//printing newlines to the dist. between bomb and city
    }
    cityfunc();//printing the city

}
void mainmenuprintingfunc()
{
    //function to print out the main menu
    FILE* mainmenuPtr;
    mainmenuPtr = fopen("mainmenu.txt", "r");
    char mainmenu[10000];

    // if the file does not exist
    if (mainmenuPtr == NULL)
    {
        printf("Could not open file mainmenu.txt");
        return;
    }


    // read the text from the file into a string while we are not in the end of file
    while (!feof(mainmenuPtr))
    {
        fgets(mainmenu, 37, mainmenuPtr);
        printf("%s", mainmenu);
    }

    fclose(mainmenuPtr);


}
void loadgame(char filename[100], gamestate ourgamestate)
{
    
    int ourgamestatelist[11] = { 0 };//array for holding gamestate info
    strcat(filename, ".txt");//function to add .txt to the end of the filename
    FILE* loadgamePtr;
    loadgamePtr = fopen(filename, "r");
    if (loadgamePtr == NULL)// checking if saved file exists
    {
        printf("Could not find %s.txt Please enter a valid filename", filename);
        Sleep(2000);
        system("cls");
        saveloadgamemenufunc();
        char loadgamefilename[100];
        fflush(stdin);
        scanf("%s", loadgamefilename);
        loadgame(loadgamefilename, ourgamestate);
    }
    int i = 0;

    int buffer;
    int a;
    for (a  = 0; a < SIZE;a++)
    {
        gamecodeword[a] = 0;
    }
    fscanf(loadgamePtr, "%s", &gamecodeword);
    while (!feof(loadgamePtr))//getting the gamestate info till the end of file ch
    {
       fscanf(loadgamePtr, "%d", &buffer);    
       ourgamestatelist[i] = buffer;
       i++;
       
    }
   
    gamestateloadholder.bombtabNumber = ourgamestatelist[3];
    gamestateloadholder.correctwordcounter = ourgamestatelist[5];
    gamestateloadholder.wronglettercounter = ourgamestatelist[9];
    gamestateloadholder.correctlettercounter = ourgamestatelist[6];
    gamestateloadholder.score = ourgamestatelist[4];
    gamestateloadholder.tabNumber = ourgamestatelist[8];
    gamestateloadholder.newlineNumber = ourgamestatelist[7];
    gamestateloadholder.bombFalling = ourgamestatelist[0];
    gamestateloadholder.bombrate = ourgamestatelist[1];
    gamestateloadholder.bombspeed = ourgamestatelist[2];
    gamestateloadholder.chtyped = ourgamestatelist[10];
    fclose(loadgamePtr);
    
}
void savegame(gamestate ourgamestate, char filename[100])
{

    strcat(filename, ".txt");//function to add .txt to the end of the filename
    FILE* savegamePtr;
    savegamePtr = fopen(filename, "w");//opening a save file and bcs it doesnt exist it will create  one
    if (savegamePtr == NULL)
    {
        printf("Could not open file %s.txt", filename);
        return;
    }
    //printing the gamestate info the file file
    fprintf(savegamePtr, "%s\n", gamecodeword);
    fprintf(savegamePtr, "%d\n%d\n%d\n%d\n%d\n", ourgamestate.bombFalling, ourgamestate.bombrate, ourgamestate.bombspeed, ourgamestate.bombtabNumber, ourgamestate.score);
    fprintf(savegamePtr, "%d\n%d\n%d\n%d\n%d\n%d", ourgamestate.correctwordcounter, ourgamestate.correctlettercounter, ourgamestate.newlineNumber, ourgamestate.tabNumber, ourgamestate.wronglettercounter,ourgamestate.chtyped);
    fclose(savegamePtr);
}
int bombspeedcontroller(gamestate ourgamestate)
{
   
    //returned integers determine how many newlines are added thus the speed of the bomb
    //initially game speed increases but after 6 letters
    // i wanted adjust diffuculty a little since word is longer bomb would feel to fast
    if (ourgamestate.correctwordcounter >= 35) {

        return 4; //10 letter keywords
    }
    else if (ourgamestate.correctwordcounter >= 30) {

        return 5; //9 letter keywords
    }
    else if (ourgamestate.correctwordcounter >= 25) {

        return 5; //8 letter keywords
    }
    else if (ourgamestate.correctwordcounter >= 20) {

        return 4; //7 letter keywords
    }
    else if (ourgamestate.correctwordcounter >= 15) {

        return 5; //6 letter keywords
    }
    else if (ourgamestate.correctwordcounter >= 10) {

        return 4; //5 letter keywords
    }
    else if (ourgamestate.correctwordcounter >= 5) {

        return 3; //4 letter keywords
    }
    return ourgamestate.correctwordcounter; //incase there is a bug and ourgamestate.correctwordcounter goes under 0 
}
void gameFinishedfunc()
{
    FILE* gameFinishedPtr;
    gameFinishedPtr = fopen("gamefinished.txt", "r");
    char gameFinished[10000];

    // if the file does not exist
    if (gameFinishedPtr == NULL)
    {
        printf("Could not open file city.txt");
        return;
    }

    // read the text from the file into a string while we are not in the end of file
    while (!feof(gameFinishedPtr))
    {
        fgets(gameFinished, 138, gameFinishedPtr);
        printf("%s", gameFinished);
    }
    fclose(gameFinishedPtr);



}
void gameOverfunc()
{
    FILE* gameoverPtr;
    gameoverPtr = fopen("gameover.txt", "r");
    char gameover[10000];

    // if the file does not exist
    if (gameoverPtr == NULL)
    {
        printf("Could not open file city.txt");
        return;
    }

    // read the text from the file into a string while we are not in the end of file
    while (!feof(gameoverPtr))
    {
        fgets(gameover, 129, gameoverPtr);
        printf("%s", gameover);
    }
    fclose(gameoverPtr);

}
void startmainmenufunc()
{

    //function to print out the main menu
    FILE* startmainmenuPtr;
    startmainmenuPtr = fopen("startmainmenu.txt", "r");
    char startmainmenu[10000];

    // if the file does not exist
    if (startmainmenuPtr == NULL)
    {
        printf("Could not open file mainmenu.txt");
        return;
    }


    // read the text from the file into a string while we are not in the end of file
    while (!feof(startmainmenuPtr))
    {
        fgets(startmainmenu, 37, startmainmenuPtr);
        printf("%s", startmainmenu);
    }

    fclose(startmainmenuPtr);
}

gamestate mainmenufunction(gamestate ourgamestate)
{

    system("cls");
    mainmenuprintingfunc();//printing out the menu  
    ourgamestate.mainmenuUI = mainmenuhelper();//selecting the option in the menu

    if (ourgamestate.mainmenuUI == 1)//checking for if the players want a new game 
    {
        //resetting our gamestate
        ourgamestate.bombtabNumber = 0;
        ourgamestate.correctwordcounter = 0;
        ourgamestate.wronglettercounter = 0;
        ourgamestate.correctlettercounter = 0;
        ourgamestate.score = 0;
        ourgamestate.tabNumber = 0;
        ourgamestate.newlineNumber = 0;
        ourgamestate.bombFalling = 0;
        ourgamestate.bombrate = 0;
        ourgamestate.bombspeed = 0;
        ourgamestate.chtyped = 0;
        int b = 0;
        for (b = 0; b < SIZE; b++)
        {
            gamecodeword[b] = 0;
        }
        return ourgamestate;
    }
    if (ourgamestate.mainmenuUI == 2)//load game
    {
        system("cls");
        saveloadgamemenufunc();//printing the load menu
        char loadgamefilename[100];
        fflush(stdin);
        scanf("%s", loadgamefilename);//asking for filename
        fflush(stdin);
        loadgame(loadgamefilename, ourgamestate);//returning said filename
        ourgamestate = gamestateloadholder;
        //resetting the load holder info 
        gamestateloadholder.bombtabNumber = 0; 
        gamestateloadholder.correctwordcounter = 0;
        gamestateloadholder.wronglettercounter = 0;
        gamestateloadholder.correctlettercounter = 0;
        gamestateloadholder.score = 0;
        gamestateloadholder.tabNumber = 0;
        gamestateloadholder.newlineNumber = 0;
        gamestateloadholder.bombFalling = 0;
        gamestateloadholder.bombrate = 0;
        gamestateloadholder.bombspeed = 0;
        gamestateloadholder.chtyped = 0;
        Sleep(1000);//having a 1 sec. delay
        
        system("cls");
        mainmenufunction(ourgamestate);//returning back to the menu
    }
    if (ourgamestate.mainmenuUI == 3)//save game
    {
        system("cls");
        char filename[100];
        saveloadgamemenufunc();//printing the save menu
        scanf("%s", filename);//asking for filename
        savegame(ourgamestate, filename);//saving our gamestate with said filename
        Sleep(1000);//having a 1 sec. delay
        system("cls");
        mainmenufunction(ourgamestate);//returning back to the menu
    }
    if (ourgamestate.mainmenuUI == 4)//return to the game
    {
        system("cls");
        ourgamestate.mainmenuUI = 1;
        return  ourgamestate;
    }
}
int main()
{
    int i = 0, startmainmenuUI = 0;
    time_t t1;
    int t2 = 0;
    gamestate ourgamestate;
    ourgamestate.bombtabNumber = 0;
    ourgamestate.correctwordcounter = 0;
    ourgamestate.wronglettercounter = 0;
    ourgamestate.correctlettercounter = 0;
    ourgamestate.score = 0;
    ourgamestate.tabNumber = 0;
    ourgamestate.newlineNumber = 0;
    ourgamestate.bombFalling = 0;
    ourgamestate.bombrate = 0;
    ourgamestate.bombspeed = 0;
    ourgamestate.mainmenuUI = 0;
    ourgamestate.chtyped = 0;

    startmainmenufunc();//start menu is different from main menu since you cant save or return to game 
    fflush(stdin);
    scanf_s("%d", &ourgamestate.mainmenuUI);
    if (ourgamestate.mainmenuUI == 3)//exiting the menu
    {
        system("cls");
        return 0;
    }
    while (ourgamestate.mainmenuUI == 2)//load game
    {
        system("cls");
        saveloadgamemenufunc();//printing the load menu
        fflush(stdin);
        char loadgamefilename[100];
        
        scanf("%s", loadgamefilename);//asking for filename
        loadgame(loadgamefilename, ourgamestate);//returning said filename
        ourgamestate = gamestateloadholder;
        //resetting the load holder info 
        gamestateloadholder.bombtabNumber = 0;
        gamestateloadholder.correctwordcounter = 0;
        gamestateloadholder.wronglettercounter = 0;
        gamestateloadholder.correctlettercounter = 0;
        gamestateloadholder.score = 0;
        gamestateloadholder.tabNumber = 0;
        gamestateloadholder.newlineNumber = 0;
        gamestateloadholder.bombFalling = 0;
        gamestateloadholder.bombrate = 0;
        gamestateloadholder.bombspeed = 0;
        gamestateloadholder.chtyped = 0;
        Sleep(500);
        system("cls");
        ourgamestate.mainmenuUI = 1;
    }
    while (ourgamestate.mainmenuUI)//game
    {
        //  we reached the end of codeword so game is finished
        if (ourgamestate.correctwordcounter >= 40)
        {
            system("cls");
            gameFinishedfunc();
            int b = 0;
            for (b = 0; b < SIZE; b++)//resetting the codeword
            {
                gamecodeword[b] = 0;
            }

            fflush(stdin);
            int finishedmenuUI = 0;
            scanf("%d", &finishedmenuUI);
            //if user wants to go to main menu
            if (finishedmenuUI == 1)
            {
                
                ourgamestate = mainmenufunction(ourgamestate);
            }
            else
            {
                //exits the game
                system("cls");
                return 0;
            }

        }

        int keyboardhit = _kbhit();
        if (keyboardhit)
        {
            int typedch = _getch();
            if (typedch == 27)//checking is escape has been hit or not
            {
                ourgamestate = mainmenufunction(ourgamestate);
            }

            int codewordsize = codewordlisthelpersize(ourgamestate.correctwordcounter);
            int codewordsizeholder = codewordsize;
            int a=0;
            if (!(i == codewordsize))
            {
                if (typedch == gamecodeword[0])//letter is correct
                {
                    
                    ourgamestate.correctlettercounter++;
                    ourgamestate.chtyped = 1;
                    for (a;a<(codewordsizeholder-1);a++)//removing correctly typed letter from array
                    {
                        gamecodeword[a] = gamecodeword[a + 1];
                    }
                    gamecodeword[codewordsizeholder - 1] = 0;//setting last ch to zero
                    codewordsizeholder--;
                    i++;
                }
                else //letter is wrong
                {
                    ourgamestate.wronglettercounter++;
                    
                }
            }
            else //i == codewordsize means we succesfully entered the codeword
            {
               ourgamestate.correctwordcounter++;
               ourgamestate.bombFalling =0;
               i = 0;
               ourgamestate.chtyped = 0;
               ourgamestate.bombtabNumber = 0;
            }
            
            keyboardhit = 0;
        }

        

        t1 = time(NULL);// getting 				

        while ((t1 - t2) >= 1)
        {
            if (ourgamestate.bombFalling == 0)
            {
                ourgamestate.bombrate = rand() % 12;//randomising where the bomb drops
                ourgamestate.bombFalling = 1;//setting to bomb active mode
                ourgamestate.newlineNumber = 0;
            }
            t2 = t1;//assigning current to previous time for the next loop

            system("cls");
            printf("\t\t\t\t\tTIP:After you entered codeword press enter for next bomb\n");
            ourgamestate.score = ourgamestate.correctlettercounter - ourgamestate.wronglettercounter;
            printf("Score:%d\n", ourgamestate.score);
            planefunc(ourgamestate.tabNumber++);

            if (ourgamestate.tabNumber == 12)
            {
                ourgamestate.tabNumber = 0; //setting tabnumber back to zero so plane goes back to start
            }
            ourgamestate.bombtabNumber = ourgamestate.bombrate;
            if (ourgamestate.correctwordcounter < 5)
            {
                //for the first 5 codewords
                if (!(ourgamestate.newlineNumber >= 37))
                {
                    bombfunc(ourgamestate.newlineNumber += 2, ourgamestate.correctwordcounter, ourgamestate.bombtabNumber++,ourgamestate.chtyped);
                }
                else//bomb has reached the city
                {
                    gameOverfunc();
                    int b = 0;
                    for ( b = 0; b < SIZE; b++)
                    {
                        gamecodeword[b] = 0;
                    }
                    
                    fflush(stdin);
                    int gameovermenuUI = gameendmenuhelper();
                    if (gameovermenuUI == 2)//going back to the main menu
                    {
                        ourgamestate = mainmenufunction(ourgamestate);
                        ourgamestate.correctwordcounter = 0;
                    }
                    else
                    {
                        system("cls"); //restarting the game
                        ourgamestate.bombtabNumber = 0;
                        ourgamestate.correctwordcounter = 0;
                        ourgamestate.wronglettercounter = 0;
                        ourgamestate.correctlettercounter = 0;
                        ourgamestate.score = 0;
                        ourgamestate.tabNumber = 0;
                        ourgamestate.newlineNumber = 0;
                        ourgamestate.bombFalling = 0;
                        ourgamestate.bombrate = 0;
                        ourgamestate.bombspeed = 0;
                        ourgamestate.chtyped = 0;

                    }
                }
            }
            else
            {
                //after first 5 codewords
                if (!(ourgamestate.newlineNumber >= 37))
                {
                    ourgamestate.bombspeed = bombspeedcontroller(ourgamestate);
                    bombfunc(ourgamestate.newlineNumber += ourgamestate.bombspeed, ourgamestate.correctwordcounter, ourgamestate.bombtabNumber++,ourgamestate.chtyped);
                }
                else//bomb has reached the city
                {
                    gameOverfunc();
                    int b = 0;
                    for (b = 0; b < SIZE; b++)
                    {
                        gamecodeword[b] = 0;
                    }
                    
                    int gameovermenuUI = gameendmenuhelper();
                    if (gameovermenuUI == 2)//returning to the main menu
                    {
                        ourgamestate = mainmenufunction(ourgamestate);
                    }
                    else
                    {
                        system("cls"); //restarting the game
                        ourgamestate.bombtabNumber = 0;
                        ourgamestate.correctwordcounter = 0;
                        ourgamestate.wronglettercounter = 0;
                        ourgamestate.correctlettercounter = 0;
                        ourgamestate.score = 0;
                        ourgamestate.tabNumber = 0;
                        ourgamestate.newlineNumber = 0;
                        ourgamestate.bombFalling = 0;
                        ourgamestate.bombrate = 0;
                        ourgamestate.bombspeed = 0;
                        ourgamestate.chtyped = 0;
                    }
                }

            }
            if (ourgamestate.tabNumber == ourgamestate.bombrate && ourgamestate.bombFalling != 1)
            {
                bombfunc(0, ourgamestate.correctwordcounter, ourgamestate.bombtabNumber, ourgamestate.chtyped);
                ourgamestate.bombFalling = 0;
            }
        }
    }
}
