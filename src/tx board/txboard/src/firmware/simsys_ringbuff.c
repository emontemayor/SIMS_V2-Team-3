/**********************************************
 * simsys_ringbuff.c
 * Function definitions for the ring buffer. Used with uart915.
 *
 * Author : Dan Filbey
 * Capstone Project 2017 - 2018
 **********************************************/
#include "simsys_ringbuff.h"


/* Function Name    : ringbuff_clear
 * Parameters       : pringbuff (pointer to the ring buffer)
 * Return Values(s) : int8_t
 * Description      : Clears the ring buffer. Returns 0 if operation was
 *  successful, else returns -1.
 */
int8_t ringbuff_clear(ringbuff_t* pringbuff)
{
    uint8_t ret_val = -1;
    
    // NULL pointer check
    if(pringbuff)
    {
        // clear the read/write values
        pringbuff->write = 0;
        pringbuff->read = 0;
        ret_val = 0;
    }
    
    return ret_val;
}


/* Function Name    : ringbuff_put
 * Parameters       : pringbuff (pointer to a ring buffer), put_data (variable
 *                      of the byte to store)
 * Return Values(s) : int8_t
 * Description      : Puts a byte into the ring buffer. Returns 0 if the 
 *  operation was successful, else it returns -1.
 */
int8_t ringbuff_put(ringbuff_t* pringbuff, uint8_t put_data)
{
    uint8_t ret_val = -1;
    
    // NULL pointer check
    if(pringbuff)
    {
        // keep ring buffer operations atomic relative to interrupts   
        system_interrupt_enter_critical_section();
        
        // write data to the ring buffer
        pringbuff->buff[pringbuff->write] = put_data;

        /* increment the head. This means old data will be overwritten if the
         * user does not check if the buffer is full */
        pringbuff->write = (pringbuff->write + 1) % pringbuff->size;
        
        system_interrupt_leave_critical_section();

        ret_val = 0;
    }
    
    return ret_val;
}


/* Function Name    : ringbuff_get
 * Parameters       : pringbuff (pointer to a ring buffer), pget_data (pointer
 *                      to store a byte in)
 * Return Values(s) : uint8_t
 * Description      : Gets a byte from the ring buffer and puts it in the
 *  location of the passed byte pointer. Returns 0 if the operation was
 *  successful, else it returns -1.
 */
int8_t ringbuff_get(ringbuff_t* pringbuff, uint8_t* pget_data)
{
    uint8_t ret_val = -1;
    
    // NULL pointer check and check if the buffer is not already empty
    if(pringbuff && pget_data && !ringbuff_is_empty(pringbuff))
    {
        // keep ring buffer operations atomic relative to interrupts
        system_interrupt_enter_critical_section();
        
        // read data from the ring buffer
        *pget_data = pringbuff->buff[pringbuff->read];
        
        // increment read pointer
        pringbuff->read = (pringbuff->read + 1) % pringbuff->size;
        
        system_interrupt_leave_critical_section();

        ret_val = 0;
    }
    
    return ret_val;
}


/* Function Name    : ringbuff_is_empty
 * Parameters       : pringbuff (pointer to a ring buffer)
 * Return Values(s) : bool
 * Description      : Returns true if the ring buffer is empty, else false
 */
bool ringbuff_is_empty(ringbuff_t* pringbuff)
{
    return (pringbuff->write == pringbuff->read);
}


/* Function Name    : ringbuff_is_full
 * Parameters       : pringbuff (pointer to a ring buffer)
 * Return Values(s) : bool
 * Description      : Returns true if the ring buffer is full, else false.
 */
bool ringbuff_is_full(ringbuff_t* pringbuff)
{
    return ((pringbuff->write + 1) % pringbuff->size) == pringbuff->read;
}