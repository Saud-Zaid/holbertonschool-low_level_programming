#ifndef SESSION_H
#define SESSION_H

#include <stddef.h>

/**
 * struct session_s - session structure
 * @id: string identifier
 * @data: data buffer
 * @data_len: length of data
 */
typedef struct session_s
{
	char *id;
	void *data;
	size_t data_len;
} session_t;

session_t *session_create(const char *id, const void *data, size_t data_len);
int session_update_data(session_t *s, const void *data, size_t data_len);
void session_destroy(session_t *s);

#endif /* SESSION_H */
