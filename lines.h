#define LINE_WHAT 0
#define LINE_INTRO 1
#define LINE_WAKE_UP 2

const char *lines[] = {
    "§0What do you do?",
    "§2The smallest events can change the world.",
    "You wake up and feel a intense pain in the back of you head. \nYou don't know where you are and can't remember what happened."
};

struct MENU {
    char *labels[10];
    char options[10];
    char *colors[3]; //options, label, input
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
