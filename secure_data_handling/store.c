#include <stdlib.h>
#include <string.h>
#include "store.h"

/**
 * store_create - Creates an empty session store
 *
 * Return: Pointer to newly allocated store_t, or NULL on failure.
 */
store_t *store_create(void)
{
	store_t *store;

	store = malloc(sizeof(store_t));
	if (store == NULL)
		return (NULL);

	store->head = NULL;
	store->count = 0;

	return (store);
}

/**
 * store_add - Inserts a session into the store
 * @store: Pointer to the store
 * @s: Pointer to the session to insert
 *
 * Return: 0 on success, -1 on duplicate/failure.
 */
int store_add(store_t *store, session_t *s)
{
	store_node_t *curr, *new_node;

	if (store == NULL || s == NULL || s->id == NULL)
		return (-1);

	curr = store->head;
	while (curr != NULL)
	{
		if (curr->session != NULL && curr->session->id != NULL &&
		    strcmp(curr->session->id, s->id) == 0)
			return (-1);
		curr = curr->next;
	}

	new_node = malloc(sizeof(store_node_t));
	if (new_node == NULL)
		return (-1);

	new_node->session = s;
	new_node->next = store->head;
	store->head = new_node;
	store->count++;

	return (0);
}

/**
 * store_get - Retrieves a session pointer by ID without transferring ownership
 * @store: Pointer to store
 * @id: Session identifier string
 *
 * Return: Pointer to session_t if found, NULL otherwise.
 */
session_t *store_get(const store_t *store, const char *id)
{
	store_node_t *curr;

	if (store == NULL || id == NULL)
		return (NULL);

	curr = store->head;
	while (curr != NULL)
	{
		if (curr->session != NULL && curr->session->id != NULL &&
		    strcmp(curr->session->id, id) == 0)
			return (curr->session);
		curr = curr->next;
	}

	return (NULL);
}

/**
 * store_delete - Removes a session from the store and optionally destroys it
 * @store: Pointer to store
 * @id: Session identifier string
 * @out: Pointer to store extracted session_t pointer (or NULL to auto-destroy)
 *
 * Return: 0 on success, -1 if ID not found.
 */
int store_delete(store_t *store, const char *id, session_t **out)
{
	store_node_t *curr, *prev = NULL;

	if (store == NULL || id == NULL)
		return (-1);

	curr = store->head;
	while (curr != NULL)
	{
		if (curr->session != NULL && curr->session->id != NULL &&
		    strcmp(curr->session->id, id) == 0)
		{
			if (prev == NULL)
				store->head = curr->next;
			else
				prev->next = curr->next;

			if (out != NULL)
				*out = curr->session;
			else
				session_destroy(curr->session);

			free(curr);
			store->count--;
			return (0);
		}
		prev = curr;
		curr = curr->next;
	}

	return (-1);
}

/**
 * store_clear - Empties all sessions and resets store to clean state
 * @store: Pointer to store
 */
void store_clear(store_t *store)
{
	store_node_t *curr, *next;

	if (store == NULL)
		return;

	curr = store->head;
	while (curr != NULL)
	{
		next = curr->next;
		if (curr->session != NULL)
			session_destroy(curr->session);
		free(curr);
		curr = next;
	}

	store->head = NULL;
	store->count = 0;
}

/**
 * store_destroy - Destroys all stored sessions and frees the store itself
 * @store: Pointer to store
 */
void store_destroy(store_t *store)
{
	if (store == NULL)
		return;

	store_clear(store);
	free(store);
}
