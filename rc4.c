#include "rc4.h"

static uint8_t c;

static inline void _swap(uint8_t *a, uint8_t *b) {
	 c = *a;
	*a = *b;
	*b =  c;
};

void rc4_init(struct rc4_ctx *ctx, const uint8_t *key, size_t len)
{
	ctx->pos1 = ctx->pos2 = 0;

	for (uint_fast16_t i = 0; i < RC4_STATE_SIZE; ++i)
		ctx->state[i] = i;

	for (uint_fast16_t j = 0, i = 0; i < RC4_STATE_SIZE; ++i) {
		j = (j + i + key[i % len]) % RC4_STATE_SIZE;

		ctx->state[i] = ctx->state[j];
		ctx->state[j] = i;
	}
}

void rc4_crypt(struct rc4_ctx *ctx, void *buffer, size_t len)
{
	for (size_t i = 0; i < len; ++i) {
		ctx->pos1 = (ctx->pos1 + 1) % RC4_STATE_SIZE;
		ctx->pos2 = (ctx->pos2 + ctx->state[ctx->pos1]) % RC4_STATE_SIZE;

		_swap(&ctx->state[ctx->pos1], &ctx->state[ctx->pos2]);

		*((uint8_t *)buffer + i) ^= ctx->state[
			(ctx->state[ctx->pos1] + ctx->state[ctx->pos2]) % RC4_STATE_SIZE
		];
	}
}
