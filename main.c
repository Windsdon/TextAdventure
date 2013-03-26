#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "lines.h"

static HANDLE consoleHandle;
CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
SMALL_RECT srctWindow;

#define COLOR_WHITE        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define COLOR_GRAY         FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
#define COLOR_RED          FOREGROUND_RED | FOREGROUND_INTENSITY
#define COLOR_GREEN        FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define COLOR_BLUE         FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define COLOR_DARK_GREEN   FOREGROUND_GREEN
#define COLOR_MAGENTA      FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define COLOR_YELLOW       FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY

#define BG_WHITE BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY
#define BG_GRAY BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE
#define BG_RED BACKGROUND_RED | BACKGROUND_INTENSITY
#define BG_GREEN BACKGROUND_GREEN | BACKGROUND_INTENSITY
#define BG_BLUE BACKGROUND_BLUE | BACKGROUND_INTENSITY
#define BG_DARK_GREEN BACKGROUND_GREEN

#define NUM_COLORS 7

#define WINDOW_WIDTH 100
#define WINDOW_HEIGHT 50
#define INPUT_BUFFER_SIZE 100

WORD colorTable[] = {
    COLOR_WHITE, //0
    COLOR_GRAY, //1
    COLOR_RED, //2
    COLOR_GREEN, //3
    COLOR_BLUE, //4
    COLOR_DARK_GREEN, //5
    COLOR_MAGENTA, //6
    COLOR_YELLOW, //7
};

void updateConsoleInfo();
void color(WORD color);
void printText(char *text, int charDelay);
void printLogo();
void printLicense();
int getMaxLineLength (char *l[]);
void printCenteredText(char *line, int width, int charDelay);
void printFullScreenText(char *line, int width, int height, int charDelay);
int countLines(char *line, int hspace);
int printMenu(struct MENU m, char *leftSpacing);
int isMenuOptionValid(struct MENU m, char o);
int gameStart();
void newGame();
char *askForInput(char *color, int doHighlight);
void addToInputBuffer(char c);
void printHighlightedInput(char *color, Object *roomObjects);
void explode(char *line, char fuse, char *holder[]);
int countOccurrences(char *text, char c);
void clearInputBuffer();
void init();

char inputBuffer[INPUT_BUFFER_SIZE];

extern const char *lines[];
extern const char *logo[];
extern const char *license[];
extern const char *prologue[];

extern struct MENU MAIN_MENU;

int gameRunning;

Room *currentRoom;
extern Room beginningCell;
extern Object key;

int main() {
    consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    system("mode 100,50");
    system("title Adventure");
    init();
    printLogo();
    printf("\n\n\n");
    printLicense();
    getch();
    return gameStart();
}

int gameStart(){
    gameRunning = 1;
    while(gameRunning){
        system("cls");
        printf("\n\n");
        switch(printMenu(MAIN_MENU, "   ")){
            case 0: //new game
                newGame();
                break;
            case 1: //load game
                printText("\n   §2This feature is not available yet.", 0);
                getch();
                break;
            default: //exit
                gameRunning = 0;
        }
    }
    return 0;
}

void newGame(){
    int i, j, l = 0;

    system("cls");
    askForInput("§2", 1);

    //prologue
    system("cls");
    printFullScreenText(lines[1], WINDOW_WIDTH, WINDOW_HEIGHT, 100);
    Sleep(1000);
    for(i = 0; i < WINDOW_HEIGHT/2; i++){
        printf("\n");
    };
    for(j = 0; *prologue[i + j];){
        for(i = 0; i < WINDOW_HEIGHT - 1 && *prologue[i+j]; i++){
            l++;
            printf("   ");
            printText(prologue[i+j], 5);
            //Sleep(200);
        };
        j += i;
        i = 0;
        if(prologue[j+1]){
            printf("   ");
            printText(lines[LINE_PRESS_TO_CONTINUE], 0);
            getch();
        }
    }
    for(l = WINDOW_HEIGHT - l - 3; l > 0; l--){
        printText("\n", 100);
    }

    printf("   ");
    printText(lines[LINE_PRESS_TO_CONTINUE], 0);
    getch();

    for(l = 0; l < WINDOW_HEIGHT; l++){
        printText("\n", 100);
    }
    system("cls");
}

char *askForInput(char *color, int doHighlight){
    char c, *p;
    int start, now;
    printText(color, 0);

    clearInputBuffer();

    do {
        c = getch();
        addToInputBuffer(c);
        if(doHighlight){
            p = inputBuffer;
            while(*p){
                printf("\b");
                p++;
            }
            p = inputBuffer;
            while(*p){
                printf(" ");
                p++;
            }
            fflush(stdin);
            printHighlightedInput(color, *currentRoom->objects);
        }else{
            putchar(c);
        }
    }while(c != 13);
}

void printHighlightedInput(char *color, Object *roomObjects){
    char *pieces[countOccurrences(inputBuffer, ' ') + 1];

    explode(inputBuffer, ' ', pieces);
}

void explode(char *line, char fuse, char *holder[]){
    int lastPiece = 0, c = 0, p = 0;
    while(*line){
        if(*line == fuse){
            holder[p] = malloc(c * (sizeof (char)));
            memcpy((line + lastPiece), holder[p], c * (sizeof (char)));
            lastPiece = c;
            c = 0;
            p++;
        }
        c++;
        line++;
    }
}

int countOccurrences(char *text, char c){
    int o = 0;
    while(*text){
        if(*text == c){
            o++;
        }
        text++;
    }

    return o;
}

void addToInputBuffer(char c){
    register int i;
    for(i = 0; inputBuffer[i] && i < INPUT_BUFFER_SIZE; i++);

    if(i < INPUT_BUFFER_SIZE){
        if(c == 8){
            inputBuffer[i] = 0;
        }else{
            inputBuffer[i] = c;
        }
    }
}

void clearInputBuffer(){
    int i;
    for(i = 0; i < INPUT_BUFFER_SIZE; i++){
        inputBuffer[i] = 0;
    }
}


void printLogo(){
    register int i, j;
    int cs = (100 - getMaxLineLength(logo))/2;

    for(i = 0; i < 11; i++){
        for(j = 0; j < cs; j++){
            printf(" ");
        };
        printText(logo[i], 0);
    }
    printCenteredText(logo[11], WINDOW_WIDTH, 0);

}

void printLicense() {
    register int i, j;
    int cs = (100 - getMaxLineLength(license))/2;

    for(i = 0; *license[i]; i++){
        for(j = 0; j < cs; j++){
            printf(" ");
        };
        printText(license[i], 0);
    }

}

void printCenteredText(char *line, int width, int charDelay){
    int spacing = (width - strlen(line))/2;
    register int i;

    for(i = 0; i < spacing; i++){
        putchar(' ');
    }

    printText(line, charDelay);
}

void printFullScreenText(char *line, int width, int height, int charDelay){
    int vspacing = (height - countLines(line, width))/2;
    register int i;

    for(i = 0; i < vspacing; i++){
        putchar('\n');
    }

    printCenteredText(line, width, charDelay);
}

int countLines(char *line, int hspace){
    char *p = line;
    int lw = 0, nl = 0;

    while(*p){
        if(*p == '\n' || lw == hspace){
            nl++;
            lw = 0;
        }else{
            lw++;
        }
        p++;
    }

    return nl;
}

void printText(char *text, int charDelay){
    int prevSim = 0;
    while(*text){
        if(*text == '§'){
            prevSim = 1;
            text++;
            continue;
        }
        if(prevSim){
            int num = *text - '0';
            if(num < NUM_COLORS && num >= 0){
                color(colorTable[num]);
            }
            prevSim = 0;
            text++;
            continue;
        }

        putchar(*text);
        Sleep(charDelay);
        text++;
    }
}

int printMenu(struct MENU m, char *leftSpacing){
    int i = 0, r;
    char c;
    while(m.labels[i]){
        printText(m.colors[0], 0);
        printf("%s%c. ", leftSpacing, m.options[i]);

        printText(m.colors[1], 0);
        printf("%s\n", m.labels[i]);
        i++;
    }

    do{
        if(r == -1){
            color(COLOR_RED);
            printf("%sThis is not a valid option.\n", leftSpacing);
        }
        fflush(stdin);
        printText(m.colors[0], 0);
        printf("\n%s> ", leftSpacing);
        printText(m.colors[2], 0);
        scanf("%c", &c);
    }while((r = isMenuOptionValid(m, c)) == -1);

    return r;
}

int isMenuOptionValid(struct MENU m, char o){
    int i = 0;
    while(m.options[i]){
        if(m.options[i] == o){
            return i;
        }
        i++;
    }
    return -1;
}

void color(WORD color){
    SetConsoleTextAttribute(consoleHandle, color);
}

int getMaxLineLength (char *l[]){
    int k = 0;
    int j = 0;
    while(strlen(l[j])){
            k = k < strlen(l[j]) ? strlen(l[j]) : k;
            j++;
    }

    return k;
}

void updateConsoleInfo(){
    GetConsoleScreenBufferInfo(consoleHandle, &csbiInfo);
    srctWindow = csbiInfo.srWindow;
}

void init(){
    beginningCell.objects[0] = &key;

    currentRoom = &beginningCell;
}





