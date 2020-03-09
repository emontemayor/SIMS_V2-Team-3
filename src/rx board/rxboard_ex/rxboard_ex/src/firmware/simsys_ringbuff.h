/*
 * ringbuff.h
 *
 * Created: 3/25/2018 5:59:54 PM
 *  Author: Dan
 */ 


#ifndef SIMSYS_RINGBUFF_H_
#define SIMSYS_RINGBUFF_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <asf.h>

// struct for the ring buffer
typedef struct {
    uint8_t* buff;
    // position to write to
    size_t  write;
    // position to read from
    size_t  read;
    // sizes of the buffer
    size_t  size;
} ringbuff_t;


/* Function Name    : ringbuff_clear
 * Parameters       : pringbuff (pointer to the ring buffer)
 * Return Values(s) : int8_t
 * Description      : Clears the ring buffer. Returns 0 if operation was
 *  successful, else returns -1.
 */
int8_t ringbuff_clear(ringbuff_t* pringbuff);


/* Function Name    : ringbuff_put
 * Parameters       : pringbuff (pointer to a ring buffer), put_data (variable
 *                      of the byte to store)
 * Return Values(s) : int8_t
 * Description      : Puts a byte into the ring buffer. Returns 0 if the 
 *  operation was successful, else it returns -1.
 */
int8_t ringbuff_put(ringbuff_t* pringbuff, uint8_t put_data);


/* Function Name    : ringbuff_get
 * Parameters       : pringbuff (pointer to a ring buffer), pget_data (pointer
 *                      to store a byte in)
 * Return Values(s) : uint8_t
 * Description      : Gets a byte from the ring buffer and puts it in the
 *  location of the passed byte pointer. Returns 0 if the operation was
 *  successful, else it returns -1.
 */
int8_t ringbuff_get(ringbuff_t* pringbuff, uint8_t* pget_data);


/* Function Name    : ringbuff_is_empty
 * Parameters       : pringbuff (pointer to a ring buffer)
 * Return Values(s) : bool
 * Description      : Returns true if the ring buffer is empty, else false
 */
bool ringbuff_is_empty(ringbuff_t* pringbuff);


/* Function Name    : ringbuff_is_full
 * Parameters       : pringbuff (pointer to a ring buffer)
 * Return Values(s) : bool
 * Description      : Returns true if the ring buffer is full, else false.
 */
bool ringbuff_is_full(ringbuff_t* pringbuff);

#endif /* RINGBUFF_H_ */