#pragma once

#include "Chatbox.h"

namespace lilengine {


    ChatBox::ChatBox(){}
    
    ChatBox::~ChatBox(){

        endwin();
        delete inputWindow;

    }

    void ChatBox::Init(){

        // setup ncurses
        initscr();

        // create input box 
        int xMax, yMax;
        getmaxyx(stdscr, yMax, xMax);

        inputWindow = newwin(3, xMax - 12, yMax - 5, 5);
        box(inputWindow, 0, 0);

        refresh();

        wrefresh(inputWindow);

    }

    std::string ChatBox::CheckBoxInput(){


        // clear input box
        wclear(inputWindow);
        box(inputWindow, 0, 0);

        // await user input
        char message[80];

        mvwscanw(inputWindow, 1, 1, "%{^\n}", message);

        return message;

    }

    void ChatBox::PostMessage(char username[80], char message[80]){

        printf("message %.4s\n", message);
        mvprintw(message_y, 1, "%s: %s", username, message);
        
        refresh();

        message_y++;

    }




}