#include <stdlib.h>
#include <string.h>
#include "store.h"

/**
 * store_init - Initializes store structure
 * @st: Pointer to store_t
 */
void store_init(store_t *st)
{
	if (st != NULL)
		st->head = NULL;
}

/**
 * node_create - Helper to allocate a new node
 * @s: Pointer to session
 *
 * Return: Pointer to newly allocated node_t, or NULL on failure
 */
static node_t *node_create(session_t *s)
{
	node_t *n;

	n = malloc(sizeof(*n));
	if (n == NULL)
		return (NULL);

	n->sess = s;
	n->next = NULL;

	return (n);
}

/**
 * store_add - Adds a session into store (takes ownership on success or failure)
 * @st: Pointer to store
 * @s: Pointer to session
 *
 * Return: 1 on success, 0 on failure
 */
int store_add(store_t *st, session_t *s)
{
	node_t *n, *cur;

	if (st == NULL || s == NULL || s->id == NULL)
	{
		if (s != NULL)
			session_destroy(s);
		return (0);
	}

	cur = st->head;
	while (cur != NULL)
	{
		if (cur->sess != NULL && cur->sess->id != NULL &&
		    strcmp(cur->sess->id, s->id) == 0)
		{
			session_destroy(s);
			return (0);
		}
		cur = cur->next;
	}

	n = node_create(s);
	if (n == NULL)
	{
		session_destroy(s);
		return (0);
	}

	n->next = st->head;
	st->head = n;

	return (1);
}

/**
 * store_get - Retrieves session by ID without transferring ownership
 * @st: Pointer to store
 * @id: Session identifier string
 *
 * Return: Pointer to session_t if found, NULL otherwise
 */
session_t *store_get(store_t *st, const char *id)
{
	node_t *cur;

	if (st == NULL || id == NULL)
		return (NULL);

	cur = st->head;
	while (cur != NULL)
	{
		if (cur->sess != NULL && cur->sess->id != NULL &&
		    strcmp(cur->sess->id, id) == 0)
			return (cur->sess);
		cur = cur->next;
	}

	return (NULL);
}

/**
 * store_delete - Deletes a session by ID and transfers/destroys ownership
 * @st: Pointer to store
 * @id: Session identifier string
 * @out: Pointer to store output pointer (NULL if auto-destroy)
 *
 * Return: 1 if deleted, 0 if not found
 */
int store_delete(store_t *st, const char *id, session_t **out)
{
	node_t *cur, *prev;

	if (st == NULL || id == NULL)
		return (0);

	prev = NULL;
	cur = st->head;

	while (cur != NULL)
	{
		if (cur->sess != NULL && cur->sess->id != NULL &&
		    strcmp(cur->sess->id, id) == 0)
		{
			if (prev != NULL)
				prev->next = cur->next;
			else
				st->head = cur->next;

			if (out != NULL)
				*out = cur->sess;
			else
				session_destroy(cur->sess);

			free(cur);
			return (1);
		}
		prev = cur;
		cur = cur->next;
	}

	return (0);
}

/**
 * store_destroy - Destroys all stored sessions and cleans up store
 * @st: Pointer to store
 */
void store_destroy(store_t *st)
{
	node_t *cur, *next;

	if (st == NULL)
		return;

	cur = st->head;
	while (cur != NULL)
	{
		next = cur->next;
		session_destroy(cur->sess);
		free(cur);
		cur = next;
	}

	st->head = NULL;
}
