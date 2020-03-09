/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2016        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */



#define SD_SLOT0 0

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive number to identify the drive */
)
{
    //The values this function should return:
    //#define STA_NOINIT		0x01	/* Drive not initialized */
    //#define STA_NODISK		0x02	/* No medium in the drive */
    //#define STA_PROTECT		0x04	/* Write protected */
    
    //The values sd_mmc_check() returns, defined in sd_mmc.h:
    //#define SD_MMC_OK               0    //! No error
    //#define SD_MMC_INIT_ONGOING     1    //! Card not initialized
    //#define SD_MMC_ERR_NO_CARD      2    //! No SD/MMC card inserted
    //#define SD_MMC_ERR_UNUSABLE     3    //! Unusable card
    //#define SD_MMC_ERR_SLOT         4    //! Slot unknown
    //#define SD_MMC_ERR_COMM         5    //! General communication error
    //#define SD_MMC_ERR_PARAM        6    //! Illegal input parameter
    //#define SD_MMC_ERR_WP           7    //! Card write protected
    
	DSTATUS stat;
	int sd_err;
    uint8_t retry_cnt = 0;

    #define NUMBR_RETRIES 100

    if(pdrv == DEV_MMC)
	{
        //lcd_printf("inside disk_status\n");
        
        do
        {
            sd_err = sd_mmc_check(0);
            
            if(sd_err == SD_MMC_ERR_NO_CARD)
                retry_cnt++;
            else if(retry_cnt > NUMBR_RETRIES)
                break;
        } while (sd_err != SD_MMC_OK);
        
        
		// translate the result code here

        switch(sd_err)
        {
            case SD_MMC_OK:
                stat = SD_MMC_OK;
                break;
            case SD_MMC_ERR_NO_CARD:
                stat = STA_NODISK;
                break;
            case SD_MMC_ERR_WP:
                stat = STA_PROTECT;
                break;
            default:
                stat = STA_NOINIT;
        }
        
        //lcd_printf("disk check stat: %d\n", stat);
        
		return stat;

	}
    else
	    return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Initialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive number to identify the drive */
)
{
	if(pdrv == DEV_MMC)
	{
        
        // initialize the ASF SD/MMC stack library
        sd_mmc_init();
        
        // DEBUG statement:
        lcd_printf("disk init\n");
        
        // return the disk_status
		return disk_status(pdrv);

	}
    else
	    return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive number to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	int result;

	if(pdrv == DEV_MMC)
	{
		
        // initialize the block read
		result = sd_mmc_init_read_blocks(SD_SLOT0, sector, count);
        
        /* if block read initialization failed, then convert the status result
         * to a DRESULT and return it */
        if(result != SD_MMC_OK)
            return status_convert(result);
        
        // else start the block read
        result = sd_mmc_start_read_blocks(buff, count);
        
        /* if block read failed, then convert the status result
         * to a DRESULT and return it */
        if(result != SD_MMC_OK)
            return status_convert(result);
        else
             // else wait for the end of block read (false = don't abort)
            result = sd_mmc_wait_end_of_read_blocks(false);
        
        // DEBUG statement:
        //lcd_printf("read stat: %d\n", status_convert(result));
        
        // and convert the status result to a DRESULT
        return status_convert(result);

	}
    else
	    return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	int result;

	if(pdrv == DEV_MMC)
	{
		// initialize the block write
		result = sd_mmc_init_write_blocks(SD_SLOT0, sector, count);
        
        /* if block write initialization failed, then convert the status result
         * to a DRESULT and return it */
        if(result != SD_MMC_OK)
            return status_convert(result);
        else
            // else start the block write
            result = sd_mmc_start_write_blocks(buff, count);
        
        /* if block write failed, then convert the status result
         * to a DRESULT and return it */
        if(result != SD_MMC_OK)
            return status_convert(result);
        else
            // else wait for end of block write (false = don't abort)
            result = sd_mmc_wait_end_of_write_blocks(false);
        
        // and convert the status result to a DRESULT
        return status_convert(result);
	}
    else
	    return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive number (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	int result;

	if(pdrv == DEV_MMC)
	{
        /* This function isn't necessary, since write is synced in disk_write
         * and no other special commands are used. However, just perform a
         * status check and convert the results to DRESULT type*/
        result = sd_mmc_check(SD_SLOT0);
		return status_convert(result);
    }
    else
	    return RES_PARERR;
}


DRESULT status_convert(sd_mmc_err_t sd_status)
{
    //The values this function should return:
    //RES_OK = 0,		/* 0: Successful */
    //RES_ERROR,		/* 1: R/W Error */
    //RES_WRPRT,		/* 2: Write Protected */
    //RES_NOTRDY,		/* 3: Not Ready */
    //RES_PARERR		/* 4: Invalid Parameter */
    
    //The status codes of the SD/MMC stack library functions:
    //The values sd_mmc_check() returns, defined in sd_mmc.h:
    //#define SD_MMC_OK               0    //! No error
    //#define SD_MMC_INIT_ONGOING     1    //! Card not initialized
    //#define SD_MMC_ERR_NO_CARD      2    //! No SD/MMC card inserted
    //#define SD_MMC_ERR_UNUSABLE     3    //! Unusable card
    //#define SD_MMC_ERR_SLOT         4    //! Slot unknown
    //#define SD_MMC_ERR_COMM         5    //! General communication error
    //#define SD_MMC_ERR_PARAM        6    //! Illegal input parameter
    //#define SD_MMC_ERR_WP           7    //! Card write protected
    
    switch(sd_status)
    {
        case SD_MMC_OK:
        return RES_OK;
        
        case SD_MMC_INIT_ONGOING:
        return RES_NOTRDY;
        
        case SD_MMC_ERR_NO_CARD:
        return RES_ERROR;
        
        case SD_MMC_ERR_UNUSABLE:
        return RES_ERROR;
        
        case SD_MMC_ERR_SLOT:
        return RES_ERROR;
        
        case SD_MMC_ERR_COMM:
        return RES_ERROR;
        
        case SD_MMC_ERR_PARAM:
        return RES_PARERR;
        
        case SD_MMC_ERR_WP:
        return RES_WRPRT;
        
        default:
        return RES_ERROR;
    }
}