#ifndef ARGUMENTS_H
#define ARGUMENTS_H

struct options {   
    int encrypt_flag;  // encrypt 0, decrypt 1
    int input_flag;    // console 0, file 1
    int output_flag;   // console 0, file 1
    int key_flag;      // default 0, user 1 
	int passwd_flag;   // default 0, user 1
    char* input_file_path;
    char* output_file_path;
    char* key_file_path;
	char* password;
};

void init_options(struct options opt);
int parse_arguments(struct options opt, int argc, char* argv[]);

#endif


