#include "../include/Cryptor.hpp"

Cryptor::Cryptor(/* args */)
{
}
/*symmetric en/decryption*/
int Cryptor::aes_encrypt(char* in, char* key, char*out){
    if(!in || !key || !out){
        return 0;
    }
    AES_KEY aes;
    if(AES_set_encrypt_key((unsigned char*)key, 128, &aes) < 0){
        return 0;
    }
    int len = strlen(in), en_len = 0;
    while(en_len < len){
        AES_encrypt((unsigned char*)in, (unsigned char*)out, &aes);
        in += AES_BLOCK_SIZE;
        out += AES_BLOCK_SIZE;
        en_len += AES_BLOCK_SIZE;
    }
    return 1;
}

int Cryptor::aes_decrypt(char* in, char* key, char*out){
    if(!in || !key || !out){
        return 0;
    }
    AES_KEY aes;
    if(AES_set_decrypt_key((unsigned char*)key, 128, &aes) < 0){
        return 0;
    }
    int len = strlen(in), en_len = 0;
    while(en_len < len){
        AES_decrypt((unsigned char*)in, (unsigned char*)out, &aes);
        in += AES_BLOCK_SIZE;
        out += AES_BLOCK_SIZE;
        en_len += AES_BLOCK_SIZE;
    }
    return 0;
}
/*Used as nonsymmetric en/decryption*/
int Cryptor::rsa_pubkey_encrypt(char* in, char* pubkey, char* out){
    if(!in || !pubkey || !out){
        return 0;
    }
    BIO* bio = NULL;
    RSA* publicRsa = NULL;
    RSA* privateRsa = NULL;
    if((bio = BIO_new_mem_buf((void*)pubkey, -1))== NULL){
        return -1;
    }
    if((publicRsa = PEM_read_bio_RSA_PUBKEY(bio, NULL, NULL, NULL)) == NULL){
        return -1;
    }
    BIO_free_all(bio);
    int rsa_len = RSA_size(publicRsa);
    out = (char*)malloc(rsa_len);
    memset(out, 0, rsa_len);
    int len = rsa_len - 11;
    if(RSA_public_encrypt(len, (unsigned char*)in, (unsigned char*)out, publicRsa, RSA_PKCS1_PADDING)){
        return -1;
    }
    RSA_free(publicRsa);
    return 0;
}

int Cryptor::rsa_prikey_decrypt(char* in, char* prikey, char* out){
    if(!in || !prikey || !out){
        return 0;
    }
    BIO* bio = NULL;
    RSA* publicRsa = NULL;
    RSA* privateRsa = NULL;
    if((bio = BIO_new_mem_buf((void*) prikey, -1)) == NULL){
        return -1;
    }
    if((privateRsa = PEM_read_bio_RSAPrivateKey(bio, NULL, NULL, NULL)) == NULL){
        return -1;
    }
    BIO_free_all(bio);
    int rsa_len = RSA_size(privateRsa);
    out = (char*)malloc(rsa_len);
    memset(out, 0, rsa_len);
    int ret = RSA_private_decrypt(rsa_len, (unsigned char*) in, (unsigned char*) out, privateRsa, RSA_PKCS1_PADDING);
    RSA_free(privateRsa);
    return ret;
}


/*Used as signature*/
int Cryptor::sha1_encrypt(char* in, char* prikey, char* out){
    if(!in || !prikey || !out){
        return 0;
    }
    BIO* bio = NULL;
    RSA* publicRsa = NULL;
    RSA* privateRsa = NULL;
    if((bio = BIO_new_mem_buf((void*) prikey, -1)) == NULL){
        return -1;
    }
    if((privateRsa = PEM_read_bio_RSAPrivateKey(bio, NULL, NULL, NULL)) == NULL){
        return -1;
    }
    BIO_free_all(bio);
    int rsa_len = RSA_size(privateRsa);
    out = (char*)malloc(rsa_len);
    memset(out, 0, rsa_len);
    int ret = RSA_private_encrypt(rsa_len, (unsigned char*) in, (unsigned char*) out, privateRsa, RSA_PKCS1_PADDING);
    RSA_free(privateRsa);
    return ret;
}

int Cryptor::sha1_decrypt(char* in, char* pubkey, char* out){
    if(!in || !pubkey || !out){
        return 0;
    }
    BIO* bio = NULL;
    RSA* publicRsa = NULL;
    RSA* privateRsa = NULL;
    if((bio = BIO_new_mem_buf((void*)pubkey, -1))== NULL){
        return -1;
    }
    if((publicRsa = PEM_read_bio_RSA_PUBKEY(bio, NULL, NULL, NULL)) == NULL){
        return -1;
    }
    BIO_free_all(bio);
    int rsa_len = RSA_size(publicRsa);
    out = (char*)malloc(rsa_len);
    memset(out, 0, rsa_len);
    int len = rsa_len - 11;
    if(RSA_public_decrypt(len, (unsigned char*)in, (unsigned char*)out, publicRsa, RSA_PKCS1_PADDING)){
        return -1;
    }
    RSA_free(publicRsa);
    return 0;
}

int Cryptor::sha256(char* in, int length, char* out){
    unsigned char hash[SHA256_DIGEST_LENGTH];
    out = (char*)malloc(65*sizeof(char));
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, in, length);
    SHA256_Final(hash, &sha256);
    //SHA256((unsigned char*)in, length, (unsigned char*)out);
    int i = 0;
    for(i = 0; i < SHA256_DIGEST_LENGTH; i++){
        sprintf(out + (i * 2), "%02x", hash[i]);
    }
    out[64] = 0;
    return 0;
}

int Cryptor::des_cbc_encrypt(char* in, char* key, char* out){
    DES_cblock key_block;
    DES_key_schedule key_schedule;
    DES_string_to_key(key, &key_block);
    if (DES_set_key_checked(&key_block, &key_schedule) != 0) {
        printf("convert to key_schedule failed.\n");
        return -1;
    }
    unsigned char* input = (unsigned char*)in;
    size_t len = (sizeof(input) + 7)/8 * 8;
    out = (char*)malloc(len+1); 
    DES_cblock ivec;
    memset((char*)&ivec, 0, sizeof(ivec));
    DES_ncbc_encrypt(input, (unsigned char*)out, sizeof(input), &key_schedule, &ivec, DES_ENCRYPT);
    return 0;
}

int Cryptor::des_cbc_decrypt(char* in, char* key, char* out){
    DES_cblock key_block;
    DES_key_schedule key_schedule;
    DES_string_to_key(key, &key_block);
    if (DES_set_key_checked(&key_block, &key_schedule) != 0) {
        printf("convert to key_schedule failed.\n");
        return -1;
    }
    unsigned char* input = (unsigned char*)in;
    size_t len = (sizeof(input) + 7)/8 * 8;
    out = (char*)malloc(len+1); 
    DES_cblock ivec;
    memset((char*)&ivec, 0, sizeof(ivec));
    DES_ncbc_encrypt(input, (unsigned char*)out, sizeof(input), &key_schedule, &ivec, DES_ENCRYPT);
    return 0;
}

int Cryptor::md5(char* in, char* key, char* out){
    MD5_CTX ctx;
    unsigned char outmd[16];
    int i = 0;
    memset(outmd, 0, sizeof(outmd));
    MD5_Init(&ctx);
    MD5_Update(&ctx, in, sizeof(in));
    MD5_Final(outmd, &ctx);
    out = (char*)malloc(16*sizeof(char));
    memcpy(out, outmd, 16);
    return 0;
}

int Cryptor::crypt(char* in, char* key, int length, char* out, int mod){
    switch (mod)
    {
    case 1:
        return aes_encrypt(in, key, out);
        break;
    
    case 2:
        return aes_decrypt(in, key, out);
        break;
    
    case 3:
        return rsa_pubkey_encrypt(in, key, out);
        break;
    case 4:
        return rsa_prikey_decrypt(in, key, out);
        break;
    case 5:
        return sha1_decrypt(in, key, out);
        break;
    case 6:
        return sha1_encrypt(in, key, out);
        break;
    case 7:
        return des_cbc_encrypt(in, key, out);
        break;
    case 8:
        return des_cbc_decrypt(in, key, out);
        break;
    case 9:
        return sha256(in, length, out);
        break;
    case 10:
        return md5(in, key, out);
        break;
    default:
        break;
    }
    return 0;
}

Cryptor::~Cryptor()
{
}
