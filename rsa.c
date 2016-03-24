#include <stdio.h>
#include <openssl/pem.h>
#include <string.h>

#include <rsa_encrypt_decrypt.h>
#include <blocking.h>
#include <assert.h>

static int password_cb(char *buf, int size, int rwflag, void *userdata)
{
    strcpy(buf, (char *)userdata);
    return strlen(buf);
}

static int load_rsa_keys(int is_encrypt, BIGNUM **e, BIGNUM **n)
{
    OpenSSL_add_all_algorithms();
    FILE* fp = is_encrypt ? fopen("./keys/public.pem","r") : fopen("./keys/private.pem","r");

    if (fp == NULL) {
        return 1;
    }

    RSA *rsa = is_encrypt ? PEM_read_RSA_PUBKEY(fp, NULL, NULL, NULL) : PEM_read_RSAPrivateKey(fp, NULL, password_cb, "12345");
    fclose(fp);
    if (rsa == NULL) {
        return 2;
    }
    *n = rsa->n;
    *e = is_encrypt ? rsa->e : rsa->d;
    return 0;
}

int main()
{
    const char* testm = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaasdsdsdsdasfsadfasdfsdafasdfasdfasdfasdfsadfsadf";
    
    BIGNUM* e;
    BIGNUM* n;
    if (load_rsa_keys(1, &e, &n) != 0) {
        return 1;
    }
    size_t b_size = BN_num_bytes(n);

    size_t m_size = strlen(testm) + 1;

    struct message_blocks* b = create_message_bloks(m_size, b_size);

    init_blocks(testm, m_size, b);
    
    size_t o_size = b->size * b->b_size;
    
    void* out_message = malloc(o_size); 

    int ind = 0;
    for (; ind < b->size; ++ind) {
        void* out;
        size_t outsize;
        RSA_EncDec_block(b->bloks[ind], b->b_size, e, n, &out, &outsize);
        printf("\nOUT SIZE = %d m = %s\n", outsize, b->bloks[ind]);
        assert(b_size == outsize);
        memcpy(((char*)out_message) + ind * outsize, out, outsize);
    }

    if (load_rsa_keys(0, &e, &n) != 0) {
        return 1;
    }
    
    ind = 0;
    for (; ind < b->size; ++ind) {
        void* out;
        size_t outsize;
        printf("\nOUT SIZE = %d m = %s\n", outsize, b->bloks[ind]);
        RSA_EncDec_block(b->bloks[ind], b->b_size, e, n, &out, &outsize);
        printf("\nOUT SIZE = %d m = %s\n", outsize, b->bloks[ind]);
        assert(b_size == outsize);
        memcpy(((char*)out_message) + ind * b_size, out, b_size);
    }

    printf("------------------------%s\n", out_message);


/*
    FILE* pfp = fopen("./keys/private.pem","r");

    if (pfp == NULL) printf("sdsds");

    RSA *prsa = PEM_read_RSAPrivateKey(pfp, NULL, password_cb, "12345");

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

*/
    return 0;
}
