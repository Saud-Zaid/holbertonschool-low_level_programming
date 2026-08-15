#include <stdlib.h>
#include <string.h>
#include "session.h"

/**
 * session_create - Creates a new session with independent heap-allocated copies
 * @id: Session identifier string
 * @data: Initial binary payload/data
 * @data_len: Length of the payload in bytes
 *
 * Return: Pointer to the new session_t, or NULL on failure.
 */
session_t *session_create(const char *id, const void *data, size_t data_len)
{
	session_t *s;

	if (id == NULL)
		return (NULL);

	s = malloc(sizeof(session_t));
	if (s == NULL)
		return (NULL);

	s->id = strdup(id);
	if (s->id == NULL)
	{
		free(s);
		return (NULL);
	}

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
 * session_update_data - Safely updates the session payload buffer
 * @s: Pointer to session
 * @data: New payload
 * @data_len: Length of new payload
 *
 * Return: 0 on success, -1 on failure.
 */
int session_update_data(session_t *s, const void *data, size_t data_len)
{
	void *new_data;

	if (s == NULL)
		return (-1);

	if (data == NULL || data_len == 0)
	{
		free(s->data);
		s->data = NULL;
		s->data_len = 0;
		return (0);
	}

	new_data = malloc(data_len);
	if (new_data == NULL)
		return (-1);

	memcpy(new_data, data, data_len);

	free(s->data);
	s->data = new_data;
	s->data_len = data_len;

	return (0);
}

/**
 * session_destroy - Releases all memory owned by the session
 * @s: Pointer to session to destroy
 */
void session_destroy(session_t *s)
{
	if (s == NULL)
		return;

	free(s->id);
	s->id = NULL;

	free(s->data);
	s->data = NULL;

	s->data_len = 0;
	free(s);
}
