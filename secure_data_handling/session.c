#include <stdlib.h>
#include <string.h>
#include "session.h"

/**
 * session_create - Creates a new session with dedicated memory
 * @id: Session identifier string
 * @uid: User ID
 * @data: Initial payload buffer
 * @data_len: Length of payload buffer
 *
 * Return: Pointer to session_t, or NULL on failure
 */
session_t *session_create(const char *id, unsigned int uid,
			  const unsigned char *data, size_t data_len)
{
	session_t *s;

	if (id == NULL)
		return (NULL);

	s = malloc(sizeof(*s));
	if (s == NULL)
		return (NULL);

	s->id = strdup(id);
	if (s->id == NULL)
	{
		free(s);
		return (NULL);
	}

	s->uid = uid;

	if (data != NULL && data_len > 0)
	{
		s->data = malloc(data_len);
		if (s->data == NULL)
		{
			free(s->id);
			free(s);
			return (NULL);
		}
		memcpy(s->data, data, data_len);
		s->data_len = data_len;
	}
	else
	{
		s->data = NULL;
		s->data_len = 0;
	}

	return (s);
}

/**
 * session_set_data - Safely updates session data
 * @s: Pointer to session
 * @data: New data buffer
 * @data_len: Length of new data buffer
 *
 * Return: 1 on success, 0 on failure
 */
int session_set_data(session_t *s, const unsigned char *data, size_t data_len)
{
	unsigned char *tmp;

	if (s == NULL)
		return (0);

	if (data == NULL || data_len == 0)
	{
		free(s->data);
		s->data = NULL;
		s->data_len = 0;
		return (1);
	}

	tmp = malloc(data_len);
	if (tmp == NULL)
		return (0);

	memcpy(tmp, data, data_len);
	free(s->data);
	s->data = tmp;
	s->data_len = data_len;

	return (1);
}

/**
 * session_destroy - Destroys and frees all memory owned by session
 * @s: Pointer to session
 */
void session_destroy(session_t *s)
{
	if (s == NULL)
		return;

	free(s->id);
	free(s->data);
	free(s);
}
