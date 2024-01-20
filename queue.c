/**
 * @file queue.c
 * @brief Implementation of a queue that supports FIFO and LIFO operations.
 *
 * This queue implementation uses a singly-linked list to represent the
 * queue elements. Each queue element stores a string value.
 *
 * Assignment for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Extended to store strings, 2018
 *
 * TODO: fill in your name and Andrew ID
 * @author XXX <XXX@andrew.cmu.edu>
 */

#include "queue.h"
#include "harness.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/**
 * @brief Allocates a new queue
 * @return The new queue, or NULL if memory allocation failed
 */
queue_t *queue_new(void) {
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    
    // what do programmers usually do when return NULL? how to look if there is anything to free
    if (!q) {
        return NULL;
    };

    q->head = NULL;
    q->tail = NULL;
    q->count = 0;

    return q;
}

/**
 * @brief Frees all memory used by a queue
 * @param[in] q The queue to free
 */
void queue_free(queue_t *q) {
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    // loop through the linkedlist to free every ele
    if (q) {
        list_ele_t *node = q->head;
        while (node) {
            // save the address of cur node as temp node
            list_ele_t *temp_node = node;
            // got to next
            node = node->next;
            // free the cur node
            if (temp_node->value) {
                free(temp_node->value);
            };
            free(temp_node);

        }
        // the head and tail is already freed in loop, therefore just set to NULL
        q->head = NULL;
        q->tail = NULL;
        q->count = 0;
        free(q);
    }
    
}

/**
 * @brief Attempts to insert an element at head of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_head(queue_t *q, const char *s) {
    // sanity check
    if (!q) return false;
    if (!s) return false;

    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    if (!newh) return false;
    
    char *sp = malloc(strlen(s) + 1);
    // free memory if newh succeed but sp failed
    if (!sp) {
        free(newh);
        return false;
    }
    strcpy(sp, s);
    // assign s to the ele value
    newh->value = sp;
    newh->next = q->head;
    q->head = newh;

    // add count
    (q->count)++;

    // if previously empty, set tail to head
    if (!(q->tail)) q->tail = q->head;
    return true;

}

/**
 * @brief Attempts to insert an element at tail of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_tail(queue_t *q, const char *s) {
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */

    // sanity check
    if (!q) return false;
    if (!s) return false;

    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));

    if (!newh) return false;
    
    char *sp = malloc(strlen(s)+1);
    // free memory if newh succeed but sp failed
    if (!sp) {
        free(newh);
        return false;
    }
    
    strcpy(sp, s);
    // assign s to the ele value
    newh->value = sp;
    q->tail->next = newh;
    newh->next = NULL;

    q->tail = newh;

    // add count
    (q->count)++;

    // if previously empty, set head to tail too
    if (!(q->head)) q->head = q->tail;

    return true;
    
}

/**
 * @brief Attempts to remove an element from head of a queue
 *
 * If removal succeeds, this function frees all memory used by the
 * removed list element and its string value before returning.
 *
 * If removal succeeds and `buf` is non-NULL, this function copies up to
 * `bufsize - 1` characters from the removed string into `buf`, and writes
 * a null terminator '\0' after the copied string.
 *
 * @param[in]  q       The queue to remove from
 * @param[out] buf     Output buffer to write a string value into
 * @param[in]  bufsize Size of the buffer `buf` points to
 *
 * @return true if removal succeeded
 * @return false if q is NULL or empty
 */
bool queue_remove_head(queue_t *q, char *buf, size_t bufsize) {
    /* You need to fix up this code. */
    if (!q) return false;
    if (!buf) return false;
    if (bufsize == 0) return false;

    list_ele_t *node = q->head;
    if (node) {
        q->head = node->next;
        if (node->value) {
            
            strncpy(buf, node->value, bufsize - 1);
            buf[bufsize - 1] = '\0';

            free(node->value);
        }
        free(node);
        (q->count)--;

        if (!(q->tail)) q->tail = NULL;
        return true;
    } 
    return false;

}

/**
 * @brief Returns the number of elements in a queue
 *
 * This function runs in O(1) time.
 *
 * @param[in] q The queue to examine
 *
 * @return the number of elements in the queue, or
 *         0 if q is NULL or empty
 */
size_t queue_size(queue_t *q) {
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */

    // A vaiable in queue_t
    if (q) {
        return ((size_t)(q->count)/sizeof(int));
    } else {
        return 0;
    }
}

/**
 * @brief Reverse the elements in a queue
 *
 * This function does not allocate or free any list elements, i.e. it does
 * not call malloc or free, including inside helper functions. Instead, it
 * rearranges the existing elements of the queue.
 *
 * @param[in] q The queue to reverse
 */
void queue_reverse(queue_t *q) {
    /* You need to write the code for this function */
    
    // swap head and tail first
    if (q) {
        list_ele_t *temp_tail = q->tail;
        q->tail = q->head;
        q->head = temp_tail;

        list_ele_t *prev_n = NULL;
        list_ele_t *cur_n = q->tail;
        list_ele_t *next_n = NULL;

        while (cur_n) {
            next_n = cur_n->next;
            cur_n->next = prev_n;

            prev_n = cur_n;
            cur_n = next_n;
            
        }
    }
    

}
