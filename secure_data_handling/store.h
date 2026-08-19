#ifndef STORE_H
#define STORE_H

#include "session.h"

/**
 * struct node_s - store linked list node
 * @session: pointer to session
 * @next: pointer to next node
 */
typedef struct node_s
{
	session_t *session;
	struct node_s *next;
} node_t;

/**
 * struct store_s - store structure
 * @head: pointer to head node
 */
typedef struct store_s
{
	node_t *head;
} store_t;

store_t *store_create(void);
int store_add(store_t *store, session_t *s);
session_t *store_get(store_t *store, const char *id);
int store_delete(store_t *store, const char *id, session_t **out);
void store_clear(store_t *store);
void store_destroy(store_t *store);

#endif /* STORE_H */
