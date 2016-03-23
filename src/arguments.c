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
    opt.input_file_path = NULL;
    opt.output_file_path = NULL;
    opt.key_file_path = NULL;
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
                opt.input_file_path = optarg;
                //printf ("input file path = %s\n", opt.input_file_path);
                opt.input_flag = 1;
                break;
            case 'O':
                opt.output_file_path = optarg;
                //printf ("output file path = %s\n", opt.output_file_path);
                opt.output_flag = 1;
                break;
            case 'k':
                opt.key_file_path = optarg;
                //printf ("key file path = %s\n", opt.key_file_path);
                opt.key_flag = 1;
                break;
			case 'p':
                opt.password = optarg;
                //printf ("password = %s\n", opt.password);
                opt.passwd_flag = 1;
                break;
            case '?':
                exit (1);                
            default:
                exit (1);
        }
    }    
}

