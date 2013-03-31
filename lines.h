#define LINE_WHAT 0
#define LINE_INTRO 1
#define LINE_PRESS_TO_CONTINUE 2
#define LINE_WAKE_UP 3
#define MAX_NUM_OF_KEYWORDS 30

const char *lines[] = {
    "§0What do you do?",
    "§2The smallest events can change the world.",
    "§3Press any key to continue...",
    "You wake up and feel a intense pain in the back of you head. \nYou don't know where you are and can't remember what happened."
};

const char *prologue[] = {
    "§2Lorem ipsum dolor sit amet, consectetur adipiscing elit.\n",
    "§1Ut sed nisl velit. Etiam felis mauris, posuere et hendrerit eu, fermentum vitae tortor.\n",
    "§1Nam vestibulum convallis mollis. Nullam sit amet ligula felis, nec egestas felis.\n",
    "\n", "\n",
    "§1Integer non scelerisque lacus. Suspendisse placerat, justo id vehicula laoreet, justo metus\n",
    "§1bibendum urna, ac scelerisque dui metus non sapien. Donec pharetra odio in est ultricies\n",
    "§1eget vehicula erat eleifend. Aenean vitae velit ac neque facilisis volutpat vel at massa.\n",
    "§1Pellentesque bibendum, Morbi vitae condimentum lacus. Phasellus auctor mi et libero vehicula.\n",
    "§1magna vitae porta condimentum, odio enim accumsan mi, et dapibus nisl ante sed nisl. Maecenas \n",
    "§1sodales venenatis sollicitudin. Fusce scelerisque turpis id nulla porttitor malesuada. Aenean\n",
    "§1libero et elit pellentesque ullamcorper eu at metus. Ut sed lacus velit.\n",
    "\n", "\n",
    "§1Curabitur rutrum dictum neque at suscipit. Nullam eleifend adipiscing neque, ultricies pharetra \n",
    "§1sapien aliquam auctor. Vestibulum id tortor quis purus lacinia ornare. Vivamus sed ligula\n",
    "§1fringilla sodales. Aliquam quam urna, vehicula vitae hendrerit vel, luctus sit amet arcu.\n",
    "§1Aenean mattis, mauris et venenatis aliquam, lorem diam suscipit enim, viverra hendrerit orci lac\n",
    "§1vitae lectus. Donec nisl felis, tristique non dapibus non, vestibulum ac dolor. Nulla facilisi. \n",
    "§1In hac habitasse platea dictumst. Suspendisse ultrices mollis risus non auctor. Duis sodales\n",
    "§1dolor, tempor adipiscing lorem euismod a. Quisque tempor dolor ac est feugiat id consectetur ma\n",
    "§1lobortis. Nulla nec felis id enim scelerisque viverra sit amet sit amet elit.\n",
    "\0"
};

struct MENU {
    char *labels[10];
    char options[10];
    char *colors[3]; //options, label, input
};

struct Object {
    char *name;
    char *color;
    char *inspection[10];
    int isVisible;
};

typedef struct Object Object;

struct Room {
    char *name;
    char *look[10];
    int currentLook;
    Object objects[20];
    struct Room *go[10]; // N, S, E, W, passages[...]
};

typedef struct Room Room;

enum Directions {
    North,
    South,
    East,
    West
};

struct LIST_OF_KEYWORDS {
    char *words[MAX_NUM_OF_KEYWORDS];
    char *colors[MAX_NUM_OF_KEYWORDS];
};

const char *logo[] = {
    "            ___                      ___                               \n",
    "           (   )                    (   )                              \n",
    "  .---.  .-.| |___  ___ .--. ___ .-. | |_   ___  ___ ___ .-.    .--.   \n",
    " / .-, \\/   \\ (   )(   /    (   )   (   __)(   )(   (   )   \\  /    \\  \n",
    "(__) ; |  .-. || |  | |  .-. |  .-. .| |    | |  | | | ' .-. ;|  .-. ; \n",
    "  .'`  | |  | || |  | |  | | | |  | || | ___| |  | | |  / (___|  | | | \n",
    " / .'| | |  | || |  | |  |/  | |  | || |(   | |  | | | |      |  |/  | \n",
    "| /  | | |  | || |  | |  ' _.| |  | || | | || |  | | | |      |  ' _.' \n",
    "; |  ; | '  | |' '  ; |  .'.-| |  | || ' | || |  ; ' | |      |  .'.-. \n",
    "' `-'  ' `-'  / \\ `' /'  `-' | |  | |' `-' ;' `-'  / | |      '  `-' / \n",
    "`.__.'_.`.__,'   '_.'  `.__.(___)(___)`.__.  '.__.' (___)      `.__.'  \n",
    "§5A Textual game by §3Windsdon\n",
    ""
};

const char *license[] = {
    "§1This program is free software: you can redistribute it and/or modify\n\0",
    "it under the terms of the GNU General Public License as published by\n\0",
    "the Free Software Foundation, either version 3 of the License, or\n\0",
    "(at your option) any later version.\n\0",
    "\n\0",
    "This program is distributed in the hope that it will be useful,\n\0",
    "but WITHOUT ANY WARRANTY; without even the implied warranty of\n\0",
    "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n\0",
    "GNU General Public License for more details.\n\0",
    "\0"
};

const char *commandColor[][2][20] = {
    {
        {
            "move", "go", "walk", "enter", "examine", "inventory", "grab", "pick", 0
        },
        {
            "§7"
        }
    },
    {
        {
            "north", "south", "east", "west", 0
        },
        {
            "§6"
        }
    },0
};

struct MENU MAIN_MENU = {
    {
        "New Game",
        "Load Game",
        "Exit"
    },
    {
        '1',
        '2',
        '0'
    },
    {
        "§0",
        "§1",
        "§1"
    }
};

Object key = {
    "Key", "§6",
    {
        "A key"
    },
    1
};

Room beginningCell = {
    "Dungeon Cell",
    {
        "The room is very dark.",
        "The room is bright."
    },
    0,
    {0,0,0,0,0,0,0,0,0,0},
    {
        0, 0, 0, 0
    }
};
