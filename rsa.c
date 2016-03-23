#include <stdio.h>
#include <openssl/pem.h>
#include "arguments.h"
#include <rsa_encrypt_decrypt.h>
#include <string.h>

int password_cb(char *buf, int size, int rwflag, void *userdata)
{
    strcpy(buf, (char *)userdata);
    return strlen(buf);
}

int main(int argc, char* argv[])
{
	OpenSSL_add_all_algorithms();
    FILE* fp = fopen("./keys/public.pem", "r");

    if (fp == NULL) {
		fprintf(stderr, "can't open keys file");
		exit(1);
	}

    RSA *rsa = PEM_read_RSA_PUBKEY(fp, NULL, NULL, NULL);

    if (rsa == NULL) {
        fprintf(stderr, "can't load public key");
        fclose(fp);
        exit(1);
    }
    fclose(fp);

	struct options opt;
	init_options(opt);

	const char* testm = fgets(opt.input_file);

    void* out;
    size_t outsize;

    parse_arguments(opt, argc, argv);

	FILE* pfp = fopen("./keys/private.pem","r");

    if (pfp == NULL) {
		fprintf(stderr, "can't open private key file");
		exit(1);
	}

	RSA *prsa = PEM_read_RSAPrivateKey(pfp, NULL, password_cb, opt.password);

	if (prsa == NULL) {
        fprintf(stderr, "can't load pivate key\n");
        fclose(pfp);
        exit(1);
    }

    if(opt.encrypt_flag == 0) {
		RSA_EncDec_block(testm, strlen(testm), rsa->e, rsa->n, &out, &outsize);
    }
    else if(opt.encrypt_flag == 1) {					
    	RSA_EncDec_block(out, outsize, prsa->d, prsa->n, &out, &outsize);
    }
    else {
        fprintf(stderr, "ERROR: -e or -d is required\n");
    }        

/*
    size_t i = 0;
    for (; i < outsize; ++i) {
        printf("%c", ((char*)out)[i]);
    }
    printf("%c", '\n');
*/

    return 0;
}

