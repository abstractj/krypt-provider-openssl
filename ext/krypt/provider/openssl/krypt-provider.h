/*
* krypt-provider API - OpenSSL version
*
* Copyright (C) 2011
* Hiroshi Nakamura <nahi@ruby-lang.org>
* Martin Bosslet <martin.bosslet@googlemail.com>
* All rights reserved.
*
* This software is distributed under the same license as Ruby.
* See the file 'LICENSE' for further details.
*/

#ifndef _KRYPT_PROVIDER_H_
#define _KRYPT_PROVIDER_H_

#if defined(__cplusplus)
extern "C" {
#endif

#define RSTRING_NOT_MODIFIED 1
#define RUBY_READONLY_STRING 1

#include <ruby.h>

typedef struct krypt_provider_st krypt_provider;

/* Message digest */
typedef struct krypt_interface_md_st krypt_interface_md;

typedef struct krypt_md_st {
    krypt_provider *provider;
    krypt_interface_md *methods;
} krypt_md;

struct krypt_interface_md_st {
    int (*md_reset)(krypt_md *md);
    int (*md_update)(krypt_md *md, unsigned char *data, size_t len);
    int (*md_final)(krypt_md *md, unsigned char ** digest, size_t *len);
    int (*md_digest)(krypt_md *md, unsigned char *data, size_t len, unsigned char **digest, size_t *digest_len);
    int (*md_digest_length)(krypt_md *md, int *len);
    int (*md_block_length)(krypt_md *md, int *block_len);
    int (*md_name)(krypt_md *md, const char **name);
    void (*mark)(krypt_md *md);
    void (*free)(krypt_md *md);
};

/* Provider */
struct krypt_provider_st {
    const char *name;
    krypt_md *(*md_new_oid)(krypt_provider *provider, const char *oid);
    krypt_md *(*md_new_name)(krypt_provider *provider, const char *name);
};

krypt_provider *krypt_provider_get_default(void);

extern void krypt_error_add(const char * format, ...);

#if defined(__cplusplus)
}
#endif

#endif /* _KRYPT_PROVIDER_H_ */
