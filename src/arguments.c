#include "arguments.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char* optarg;

void init_options(struct options opt) {
    opt.encrypt_flag = -1;
    opt.input_flag = 0;    
    opt.output_flag = 0;   
    opt.key_flag = 0;     
	opt.passwd_flag = 0; 
    opt.input_file = NULL;
    opt.output_file = NULL;
    opt.key_file = NULL;
	opt.password = NULL;
}

int parse_arguments(struct options opt, int argc, char* argv[]) {    
    int c;
    while ((c = getopt (argc, argv, "edf:O:k:p:")) != -1) {
        switch (c) {
            case 'e':
                opt.encrypt_flag = 0;
                break;
            case 'd':
                opt.encrypt_flag = 1;
                break;
            case 'f':
                opt.input_file = fopen(optarg);
                opt.input_flag = 1;
                break;
            case 'O':
                opt.output_file = fopen(optarg);
                opt.output_flag = 1;
                break;
            case 'k':
                opt.key_file = fopen(optarg);
                opt.key_flag = 1;
                break;
			case 'p':
                opt.password = optarg;
                opt.passwd_flag = 1;
                break;
            case '?':
                exit (1);                
            default:
                exit (1);
        }
    }  

	if(opt.input_file == NULL) {
		opt.input_file = stdin;
	}

    if(opt.output_file == NULL) {
		opt.output_file = stdout;
	}

    if(opt.key_file == NULL) {
		opt.key_file = stdin;
	}		  
}

