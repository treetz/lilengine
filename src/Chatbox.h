#pragma once
#include <stdio.h>

#include <iostream>
#include <string.h>

#include <ncurses.h>


namespace lilengine {

	class ChatBox {

        private:
            int message_y = 0;
            WINDOW * inputWindow = nullptr;
        
        public:

            ChatBox();
            ~ChatBox();

            void Init();

            void PostMessage(char username[80], char msg[80]);

            std::string CheckBoxInput();



    };

}