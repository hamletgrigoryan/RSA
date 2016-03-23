#include <stdio.h>
//#include "RSA.h"
#include <openssl/pem.h>

#include <rsa_encrypt_decrypt.h>
#include <string.h>




int password_cb(char *buf, int size, int rwflag, void *userdata)
{
    strcpy(buf, (char *)userdata);
    return strlen(buf);
}


int main()
{

    OpenSSL_add_all_algorithms();
    FILE* fp = fopen("/home/samoa/hamlet/c/RSA/keys/public.pem","r");

    if (fp == NULL) printf("sdsds");

    RSA *rsa = PEM_read_RSA_PUBKEY(fp, NULL, NULL, NULL);

    if (rsa == NULL) {
        printf("error load public key");
        fclose(fp);
        return 1;
    }
    fclose(fp);

    const char* testm = "Hello test";

    void* out;
    size_t outsize;

    RSA_EncDec_block(testm, strlen(testm), rsa->e, rsa->n, &out, &outsize);


    FILE* pfp = fopen("/home/samoa/hamlet/c/RSA/keys/private.pem","r");

    if (pfp == NULL) printf("sdsds");

    RSA *prsa = PEM_read_RSAPrivateKey(pfp, NULL, password_cb, "1235");

    if (prsa == NULL) {
        printf("error load pivate key\n");
        fclose(pfp);
        return 1;
    }


    RSA_EncDec_block(out, outsize, prsa->d, prsa->n, &out, &outsize);

    size_t i = 0;
    for (; i < outsize; ++i) {
        printf("%c", ((char*)out)[i]);
    }
    printf("%c", '\n');


    return 0;
}
