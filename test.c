#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rc4.h"

#define KEY_SIZE 32

static inline void fill_buffer(uint8_t *, size_t);
static inline void print_buffer(uint8_t *, size_t);

int main(void)
{
	uint8_t key[KEY_SIZE];

	struct rc4_ctx e_ctx, d_ctx;

	char buffer [33];
	char message[33] = "this message should be encrypted";

	srand(time(NULL));
	strncpy(buffer, message, 33);

	fill_buffer(key, KEY_SIZE);

	puts("[*] Key");
	print_buffer(key, KEY_SIZE);

	rc4_init(&e_ctx, key, KEY_SIZE);
	rc4_init(&d_ctx, key, KEY_SIZE);

	rc4_crypt(&e_ctx, (uint8_t *)buffer, 32);

	printf("\n- Encrypted plaintext\n");
	print_buffer((uint8_t *)buffer, 32);

	rc4_crypt(&d_ctx, (uint8_t *)buffer, 32);

	printf("\n- Decrypted ciphertext\n");
	print_buffer((uint8_t *)buffer, 32);

	if (memcmp(buffer, message, 32))
		puts("\n[-] Decryption failed");
	else
		printf("\n[+] Decryption succeeded: '%s'\n", buffer);

	return 0;
}

static inline void fill_buffer(uint8_t *buffer, size_t len)
{
	for (size_t i = 0; i < len; ++i)
		buffer[i] = (uint8_t)rand();
}

static inline void print_buffer(uint8_t *buffer, size_t len)
{
	size_t i;

	for (i = 0; i < len; ++i) {
		if (i % 16 == 0)
			putchar('\n');

		printf("%02x ", buffer[i]);
	}

	putchar('\n');
}
