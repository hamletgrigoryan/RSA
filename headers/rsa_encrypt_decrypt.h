#ifndef RSA_ENCRYPT_DECRYPT_H
#define RSA_ENCRYPT_DECRYPT_H


extern int RSA_EncDec_block(const void *message, size_t m_size, BIGNUM *key, BIGNUM *n, void **output, size_t *output_size);


#endif
