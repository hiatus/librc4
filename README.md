librc4
======
Implementation of the RC4 cipher.

API
---
```
// Initialize RC4 context
void rc4_init(struct rc4_ctx *ctx, const uint8_t *key, size_t len);

// Encrypt or decrypt a buffer
void rc4_crypt(struct rc4_ctx *ctx, void *buffer, size_t len);
```

Testing
-------
- Compile the test binary (`librc4.so` will also be compiled)
```
$ git clone https://github.com/hiatus/librc4.git && cd librc4 && make
```

- Run it
```
$ ./bin/test
```
