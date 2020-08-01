/**
* This source code ("the Software") is provided by Bridgetek Pte Ltd
* ("Bridgetek") subject to the licence terms set out
*   http://brtchip.com/BRTSourceCodeLicenseAgreement/ ("the Licence Terms").
* You must read the Licence Terms before downloading or using the Software.
* By installing or using the Software you agree to the Licence Terms. If you
* do not agree to the Licence Terms then do not download or use the Software.
*
* Without prejudice to the Licence Terms, here is a summary of some of the key
* terms of the Licence Terms (and in the event of any conflict between this
* summary and the Licence Terms then the text of the Licence Terms will
* prevail).
*
* The Software is provided "as is".
* There are no warranties (or similar) in relation to the quality of the
* Software. You use it at your own risk.
* The Software should not be used in, or for, any medical device, system or
* appliance. There are exclusions of Bridgetek liability for certain types of loss
* such as: special loss or damage; incidental loss or damage; indirect or
* consequential loss or damage; loss of income; loss of business; loss of
* profits; loss of revenue; loss of contracts; business interruption; loss of
* the use of money or anticipated savings; loss of information; loss of
* opportunity; loss of goodwill or reputation; and/or loss of, damage to or
* corruption of data.
* There is a monetary cap on Bridgetek's liability.
* The Software may have subsequently been amended by another user and then
* distributed by that other user ("Adapted Software").  If so that user may
* have additional licence terms that apply to those amendments. However, Bridgetek
* has no liability in relation to those amendments.
*/

//#include "FT_Platform.h"
#include "sim_system_glcd_software.h"

/* API to initialize the SPI interface */
ft_bool_t  Ft_Gpu_Hal_Init(Ft_Gpu_HalInit_t *halinit)
{   
    // init SPI hardware
    lcd_spi_init();
    
	return true;
}


ft_bool_t Ft_Gpu_Hal_Open(Ft_Gpu_Hal_Context_t *host)
{

	/* Initialize the context variables.
     * In the original source code, this is where you should also call
     * lcd_spi_init() (for SIM system), but there's no point in seperating
     * the pinmux settings and the SPI init, so it's all done
     * in Ft_Gpu_Hal_Init().
     */
    
    // init current write buffer to zero, since we're just starting up
	host->ft_cmd_fifo_wp = host->ft_dl_buff_wp = 0;
    // by default ft800/801/810/811 goes with single dummy byte for read
	host->spinumdummy = 1;
    // technically one channel, but zero for how the FT library does things
	host->spichannel = 0;
    // indicate it's ready to go
	host->status = FT_GPU_HAL_OPENED;

    lcd_set_ft_host_ptr(host);

	return true;
}


ft_void_t  Ft_Gpu_Hal_Close(Ft_Gpu_Hal_Context_t *host)
{
    /* Just set the status to closed. The SIM System's SERCOM will be
     * disabled in Ft_Gpu_Hal_DeInit(). */
	host->status = FT_GPU_HAL_CLOSED;
}


ft_void_t Ft_Gpu_Hal_DeInit(ft_void_t)
{
    // disable the SIM System's LCD SPI SERCOM
    lcd_spi_deinit();
}


/*The APIs for reading/writing transfer continuously only with small buffer system*/
ft_void_t  Ft_Gpu_Hal_StartTransfer(Ft_Gpu_Hal_Context_t *host, FT_GPU_TRANSFERDIR_T rw, ft_uint32_t addr)
{
    /* determine if it's a read or write. This affects the preamble send to the
     * LCD (preamble = direction bits and address). */
	if (FT_GPU_READ == rw)
    {
        // begin a read transfer
        lcd_start_xfer(addr, READ);

		host->status = FT_GPU_HAL_READING;
	}
    else
    {
        // begin a write transfer
	    lcd_start_xfer(addr, WRT);
    
		host->status = FT_GPU_HAL_WRITING;
	}
}


/*The APIs for writing transfer continuously only*/
ft_void_t  Ft_Gpu_Hal_StartCmdTransfer(Ft_Gpu_Hal_Context_t *host, FT_GPU_TRANSFERDIR_T rw, ft_uint16_t count)
{
    // RAM_CMD = 0x308000
    // starting a transfer = sending preamble (read/write bits and address)
	Ft_Gpu_Hal_StartTransfer(host,rw,host->ft_cmd_fifo_wp + RAM_CMD);
}


ft_void_t Ft_Gpu_Hal_TransferString(Ft_Gpu_Hal_Context_t *host, const ft_char8_t *string)
{
    // get length of the string
    ft_uint16_t length = strlen((const char*) string);
    
    // send out the string
    while(length--)
    {
       Ft_Gpu_Hal_Transfer8(host, *string);
       string ++;
    }
    
    //Append one null as ending flag
    Ft_Gpu_Hal_Transfer8(host,0);
}


ft_uint8_t Ft_Gpu_Hal_Transfer8(Ft_Gpu_Hal_Context_t *host, ft_uint8_t value)
{
    ft_uint8_t read_byte = 0;
    
    // transmit or receive a byte
    if(host->status == FT_GPU_HAL_WRITING)
        lcd_host_write(&value, 1);
    else
        lcd_host_read(&read_byte, 1);
    
    return read_byte;
}


ft_uint16_t Ft_Gpu_Hal_Transfer16(Ft_Gpu_Hal_Context_t *host, ft_uint16_t value)
{
	ft_uint16_t retVal = 0;

    // transmit or receive two bytes
    if (host->status == FT_GPU_HAL_WRITING)
    {
	    Ft_Gpu_Hal_Transfer8(host,value & 0xFF);//LSB first
	    Ft_Gpu_Hal_Transfer8(host,(value >> 8) & 0xFF);
	}
    else
    {
		retVal = Ft_Gpu_Hal_Transfer8(host,0);
		retVal |= (ft_uint16_t)Ft_Gpu_Hal_Transfer8(host,0) << 8;
	}

	return retVal;
}


ft_uint32_t Ft_Gpu_Hal_Transfer32(Ft_Gpu_Hal_Context_t *host, ft_uint32_t value)
{
	ft_uint32_t retVal = 0;
    
    // transmit or receive four bytes
	if (host->status == FT_GPU_HAL_WRITING)
    {
		Ft_Gpu_Hal_Transfer16(host,value & 0xFFFF);//LSB first
		Ft_Gpu_Hal_Transfer16(host,(value >> 16) & 0xFFFF);
	}
    else
    {
		retVal = Ft_Gpu_Hal_Transfer16(host,0);
		retVal |= (ft_uint32_t)Ft_Gpu_Hal_Transfer16(host,0) << 16;
	}
    
	return retVal;
}


ft_void_t Ft_Gpu_Hal_EndTransfer(Ft_Gpu_Hal_Context_t *host)
{
    // deselect the slave (let slave CS float high for SIM System)
    lcd_stop_xfer();
    
	host->status = FT_GPU_HAL_OPENED;
}


ft_uint8_t Ft_Gpu_Hal_Rd8(Ft_Gpu_Hal_Context_t *host, ft_uint32_t addr)
{
	ft_uint8_t value;

    // start a read transfer
	Ft_Gpu_Hal_StartTransfer(host,FT_GPU_READ,addr);
    
    // read a byte
	value = Ft_Gpu_Hal_Transfer8(host,0);

    // end the transfer
	Ft_Gpu_Hal_EndTransfer(host);
    
	return value;
}


ft_uint16_t Ft_Gpu_Hal_Rd16(Ft_Gpu_Hal_Context_t *host, ft_uint32_t addr)
{
	ft_uint16_t value;

    // start a read transfer
	Ft_Gpu_Hal_StartTransfer(host,FT_GPU_READ,addr);
    
    // read 2 bytes
	value = Ft_Gpu_Hal_Transfer16(host,0);
    
    // end the transfer
	Ft_Gpu_Hal_EndTransfer(host);
    
	return value;
}


ft_uint32_t Ft_Gpu_Hal_Rd32(Ft_Gpu_Hal_Context_t *host, ft_uint32_t addr)
{
	ft_uint32_t value;

    // start a read transfer
	Ft_Gpu_Hal_StartTransfer(host,FT_GPU_READ,addr);
    
    // read 4 bytes
	value = Ft_Gpu_Hal_Transfer32(host,0);

    // end the transfer
	Ft_Gpu_Hal_EndTransfer(host);
    
	return value;
}


ft_void_t Ft_Gpu_Hal_Wr8(Ft_Gpu_Hal_Context_t *host, ft_uint32_t addr, ft_uint8_t v)
{	
    
    // start a write transfer
	Ft_Gpu_Hal_StartTransfer(host,FT_GPU_WRITE,addr);
    
    // read a byte
	Ft_Gpu_Hal_Transfer8(host,v);
    
    // end the transfer
	Ft_Gpu_Hal_EndTransfer(host);
}


ft_void_t Ft_Gpu_Hal_Wr16(Ft_Gpu_Hal_Context_t *host, ft_uint32_t addr, ft_uint16_t v)
{
    // start a write transfer
	Ft_Gpu_Hal_StartTransfer(host,FT_GPU_WRITE,addr);
    
    // read 2 bytes
	Ft_Gpu_Hal_Transfer16(host,v);
    
    // end the transfer
	Ft_Gpu_Hal_EndTransfer(host);
}


ft_void_t Ft_Gpu_Hal_Wr32(Ft_Gpu_Hal_Context_t *host, ft_uint32_t addr, ft_uint32_t v)
{
    // start a write transfer
	Ft_Gpu_Hal_StartTransfer(host,FT_GPU_WRITE,addr);
    
    // read 2 bytes
	Ft_Gpu_Hal_Transfer32(host,v);
    
    // end the transfer
	Ft_Gpu_Hal_EndTransfer(host);
}


ft_void_t Ft_Gpu_HostCommand(Ft_Gpu_Hal_Context_t *host, ft_uint8_t cmd)
{
    /* send a host command (controls basic controller hardware). 
     * No parameter byte. I assume this is for devices older than FT81X */
    lcd_host_cmd(cmd, 0);
}


ft_void_t Ft_Gpu_ClockSelect(Ft_Gpu_Hal_Context_t *host, FT_GPU_PLL_SOURCE_T pllsource)
{
   // host command to select PLL source, either internal or external clock.
   
   Ft_Gpu_HostCommand(host, pllsource);
}


ft_void_t Ft_Gpu_PLL_FreqSelect(Ft_Gpu_Hal_Context_t *host, FT_GPU_PLL_FREQ_T freq)
{
   // host command to select PLL frequency.
   Ft_Gpu_HostCommand(host, freq);
}


ft_void_t Ft_Gpu_PowerModeSwitch(Ft_Gpu_Hal_Context_t *host, FT_GPU_POWER_MODE_T pwrmode)
{
   Ft_Gpu_HostCommand(host, pwrmode);
}


ft_void_t Ft_Gpu_CoreReset(Ft_Gpu_Hal_Context_t *host)
{
   Ft_Gpu_HostCommand(host,FT_GPU_CORE_RESET);
}


#ifdef FT_81X_ENABLE
//This API can only be called when PLL is stopped(SLEEP mode).  For compatibility, set frequency to the FT_GPU_12MHZ option in the FT_GPU_SETPLLSP1_T table.
ft_void_t Ft_Gpu_81X_SelectSysCLK(Ft_Gpu_Hal_Context_t *host, FT_GPU_81X_PLL_FREQ_T freq){
		if(FT_GPU_SYSCLK_72M == freq)
			Ft_Gpu_HostCommand_Ext3(host, (ft_uint32_t)0x61 | (0x40 << 8) | (0x06 << 8)); 
		else if(FT_GPU_SYSCLK_60M == freq)
			Ft_Gpu_HostCommand_Ext3(host, (ft_uint32_t)0x61 | (0x40 << 8) | (0x05 << 8)); 
		else if(FT_GPU_SYSCLK_48M == freq)
			Ft_Gpu_HostCommand_Ext3(host, (ft_uint32_t)0x61 | (0x40 << 8) | (0x04 << 8)); 
		else if(FT_GPU_SYSCLK_36M == freq)
			Ft_Gpu_HostCommand_Ext3(host, (ft_uint32_t)0x61 | (0x03 << 8)); 
		else if(FT_GPU_SYSCLK_24M == freq)
			Ft_Gpu_HostCommand_Ext3(host, (ft_uint32_t)0x61 | (0x02 << 8)); 
		else if(FT_GPU_SYSCLK_DEFAULT == freq)//default clock
			Ft_Gpu_HostCommand_Ext3(host, 0x61); 
}


//Power down or up ROMs and ADCs.  Specified one or more elements in the FT_GPU_81X_ROM_AND_ADC_T table to power down, unspecified elements will be powered up.  The application must retain the state of the ROMs and ADCs as they're not readable from the device.
ft_void_t Ft_GPU_81X_PowerOffComponents(Ft_Gpu_Hal_Context_t *host, ft_uint8_t val){
		Ft_Gpu_HostCommand_Ext3(host, (ft_uint32_t)0x49 | (val<<8));
}


//this API sets the current strength of supported GPIO/IO group(s)
ft_void_t Ft_GPU_81X_PadDriveStrength(Ft_Gpu_Hal_Context_t *host, FT_GPU_81X_GPIO_DRIVE_STRENGTH_T strength, FT_GPU_81X_GPIO_GROUP_T group){
		Ft_Gpu_HostCommand_Ext3(host, (ft_uint32_t)0x70 | (group << 8) | (strength << 8));
}


//this API will hold the system reset active, Ft_Gpu_81X_ResetRemoval() must be called to release the system reset.
ft_void_t Ft_Gpu_81X_ResetActive(Ft_Gpu_Hal_Context_t *host){
	Ft_Gpu_HostCommand_Ext3(host, FT_GPU_81X_RESET_ACTIVE); 
}


//This API will release the system reset, and the system will exit reset and behave as after POR, settings done through SPI commands will not be affected.
ft_void_t Ft_Gpu_81X_ResetRemoval(Ft_Gpu_Hal_Context_t *host){
	Ft_Gpu_HostCommand_Ext3(host, FT_GPU_81X_RESET_REMOVAL); 
}
#endif


//This API sends a 3byte command to the host
ft_void_t Ft_Gpu_HostCommand_Ext3(Ft_Gpu_Hal_Context_t *host, ft_uint32_t cmd)
{
    // send host command for FT81X devices. Refer to DS_FT81X datasheet pg. 16
	lcd_host_cmd((cmd & 0xFF), ((cmd >> 8) & 0xFF));
}


ft_void_t Ft_Gpu_Hal_Updatecmdfifo(Ft_Gpu_Hal_Context_t *host, ft_uint32_t count)
{
	host->ft_cmd_fifo_wp  = (host->ft_cmd_fifo_wp + count) & 4095;

	//4 byte alignment
	host->ft_cmd_fifo_wp = (host->ft_cmd_fifo_wp + 3) & 0xffc;
    
	Ft_Gpu_Hal_Wr16(host,REG_CMD_WRITE,host->ft_cmd_fifo_wp);
}


ft_uint16_t Ft_Gpu_Cmdfifo_Freespace(Ft_Gpu_Hal_Context_t *host)
{
    /* calculate the free space for the coprocessor FIFO. Refer to pg 150 in
     * the FT81X_Series_Programmers_Guide datasheet */
	ft_uint16_t fullness,retval;

    // REG_CMD_READ = 0x3020F8
	fullness = (host->ft_cmd_fifo_wp - Ft_Gpu_Hal_Rd16(host,REG_CMD_READ)) & 4095;
    
	retval = (FT_CMD_FIFO_SIZE - 4) - fullness;
    
	return (retval);
}


ft_void_t Ft_Gpu_Hal_WrCmdBuf(Ft_Gpu_Hal_Context_t *host, ft_uint8_t *buffer, ft_uint32_t count)
{
	ft_int32_t length = 0, availablefreesize;   

	do 
    {                
		length = count;
        
		availablefreesize = Ft_Gpu_Cmdfifo_Freespace(host);
        
		if (length > availablefreesize) 
        {
		    length = availablefreesize;
		}

      	Ft_Gpu_Hal_CheckCmdBuffer(host,length);

        Ft_Gpu_Hal_StartCmdTransfer(host,FT_GPU_WRITE,length);
        
        // do stuff here, refer to original code
        // {
        
        // write the buffer to the FIFO
        lcd_host_write(buffer, count);
        
        buffer += length;
        // }
        
		Ft_Gpu_Hal_EndTransfer(host);
		Ft_Gpu_Hal_Updatecmdfifo(host,length);

		Ft_Gpu_Hal_WaitCmdfifo_empty(host);

		count -= length;
        
	} while (count > 0);
}

#if defined (ARDUINO_PLATFORM_SPI) || defined (FT900_PLATFORM)
ft_void_t Ft_Gpu_Hal_WrCmdBufFromFlash(Ft_Gpu_Hal_Context_t *host,FT_PROGMEM ft_prog_uchar8_t *buffer,ft_uint32_t count)
{
	ft_uint32_t length = 0;   

	do {                
		length = count;
		ft_uint32_t freeSpace = Ft_Gpu_Cmdfifo_Freespace(host);
		if (length > freeSpace){
		    length = freeSpace;
		}
      	Ft_Gpu_Hal_CheckCmdBuffer(host,length);

        Ft_Gpu_Hal_StartCmdTransfer(host,FT_GPU_WRITE,length);

		for (ft_uint32_t i = 0; i < length; ++i) {
			Ft_Gpu_Hal_Transfer8(host, ft_pgm_read_byte_near(&buffer[i]));
		}
		buffer += length;

    	Ft_Gpu_Hal_EndTransfer(host);
		Ft_Gpu_Hal_Updatecmdfifo(host,length);

		Ft_Gpu_Hal_WaitCmdfifo_empty(host);

		count -= length;
	}while (count > 0);
}
#endif


ft_void_t Ft_Gpu_Hal_CheckCmdBuffer(Ft_Gpu_Hal_Context_t *host, ft_uint32_t count)
{
   ft_uint16_t getfreespace;
   do{
       // This "fixme" was here in the original code.
	   // FIXME: This can get stuck, non-even is returned in case of coprocessor issue
        getfreespace = Ft_Gpu_Cmdfifo_Freespace(host);
        
   // loop until there is free space, else break if there is enough free space
   }while(getfreespace < count);
}


ft_void_t Ft_Gpu_Hal_WaitCmdfifo_empty(Ft_Gpu_Hal_Context_t *host)
{
   /* wait for the FIFO read and write pointers to equal each other.
    * This is the naive way to do it, refer to pg 154 in 
    * the FT81X_Series_Programmers_Guide datasheet */
   while(Ft_Gpu_Hal_Rd16(host,REG_CMD_READ) != Ft_Gpu_Hal_Rd16(host,REG_CMD_WRITE));
   
   host->ft_cmd_fifo_wp = Ft_Gpu_Hal_Rd16(host,REG_CMD_WRITE);
}


ft_void_t Ft_Gpu_Hal_WrCmdBuf_nowait(Ft_Gpu_Hal_Context_t *host,ft_uint8_t *buffer,ft_uint32_t count)
{
	ft_uint32_t length = 0;   

	do {                
		length = count;
		ft_uint32_t freeSpace = Ft_Gpu_Cmdfifo_Freespace(host);
		if (length > freeSpace){
		    length = freeSpace;
		}

      	Ft_Gpu_Hal_CheckCmdBuffer(host,length);

        Ft_Gpu_Hal_StartCmdTransfer(host,FT_GPU_WRITE,length);

        // do stuff here, refer to original code
        // {
        
        // write the buffer to the FIFO
        lcd_host_write(buffer, count);
        
        buffer += length;
        // }
        
		Ft_Gpu_Hal_EndTransfer(host);
		Ft_Gpu_Hal_Updatecmdfifo(host,length);

        /* This was commented out in the original code, hence the name of 
         * this function. I assume you'd use this when you're writing small
         * commands to the FIFO, which it could keep up with */
	//	Ft_Gpu_Hal_WaitCmdfifo_empty(host);

		count -= length;
	} while (count > 0);
}

ft_uint8_t Ft_Gpu_Hal_WaitCmdfifo_empty_status(Ft_Gpu_Hal_Context_t *host)
{
   /* I guess this is just to check the status of the FIFO, instead of being
    * locked in the while-loop in Ft_Gpu_Hal_WaitCmdfifo_empty() */
   
    if(Ft_Gpu_Hal_Rd16(host,REG_CMD_READ) != Ft_Gpu_Hal_Rd16(host,REG_CMD_WRITE))
        return 0;
    else
    {
        host->ft_cmd_fifo_wp = Ft_Gpu_Hal_Rd16(host,REG_CMD_WRITE);
        return 1;
    }  
}

ft_void_t Ft_Gpu_Hal_WaitLogo_Finish(Ft_Gpu_Hal_Context_t *host)
{
    ft_int16_t cmdrdptr,cmdwrptr;

    do{
        cmdrdptr = Ft_Gpu_Hal_Rd16(host,REG_CMD_READ);
        cmdwrptr = Ft_Gpu_Hal_Rd16(host,REG_CMD_WRITE);
    } while ((cmdwrptr != cmdrdptr) || (cmdrdptr != 0));
    
    host->ft_cmd_fifo_wp = 0;
}


ft_void_t Ft_Gpu_Hal_ResetCmdFifo(Ft_Gpu_Hal_Context_t *host)
{
    host->ft_cmd_fifo_wp = 0;
}


ft_void_t Ft_Gpu_Hal_WrCmd32(Ft_Gpu_Hal_Context_t *host, ft_uint32_t cmd)
{
    Ft_Gpu_Hal_CheckCmdBuffer(host, sizeof(cmd));
    
    Ft_Gpu_Hal_Wr32(host, RAM_CMD + host->ft_cmd_fifo_wp, cmd);
    
    Ft_Gpu_Hal_Updatecmdfifo(host, sizeof(cmd));
}


ft_void_t Ft_Gpu_Hal_ResetDLBuffer(Ft_Gpu_Hal_Context_t *host)
{
    host->ft_dl_buff_wp = 0;
}
/* Toggle PD_N pin for a power cycle*/
ft_void_t Ft_Gpu_Hal_Powercycle(Ft_Gpu_Hal_Context_t *host, ft_bool_t up)
{
	if (up)
	{
        lcd_powerdown();
        Ft_Gpu_Hal_Sleep(20);

        lcd_powerup();
        Ft_Gpu_Hal_Sleep(20);
	}
    else
	{
        lcd_powerup();
        Ft_Gpu_Hal_Sleep(20);
        
        lcd_powerdown();
        Ft_Gpu_Hal_Sleep(20);
	}
}

ft_void_t Ft_Gpu_Hal_WrMemFromFlash(Ft_Gpu_Hal_Context_t *host,ft_uint32_t addr,const ft_prog_uchar8_t *buffer, ft_uint32_t length)
{
    /* Transfer from program memory. This will need work because it just writes
     * from RAM */

	Ft_Gpu_Hal_StartTransfer(host,FT_GPU_WRITE,addr);

	while (length--) {
            Ft_Gpu_Hal_Transfer8(host,ft_pgm_read_byte_near(buffer));
	    buffer++;
	}

	Ft_Gpu_Hal_EndTransfer(host);
}


ft_void_t Ft_Gpu_Hal_WrMem(Ft_Gpu_Hal_Context_t *host, ft_uint32_t addr, const ft_uint8_t *buffer, ft_uint32_t length)
{  

	Ft_Gpu_Hal_StartTransfer(host,FT_GPU_WRITE,addr);

	while (length--) 
    {
        Ft_Gpu_Hal_Transfer8(host,*buffer);
	    buffer++;
	}

	Ft_Gpu_Hal_EndTransfer(host);
}


ft_void_t Ft_Gpu_Hal_RdMem(Ft_Gpu_Hal_Context_t *host, ft_uint32_t addr, ft_uint8_t *buffer, ft_uint32_t length)
{

	Ft_Gpu_Hal_StartTransfer(host,FT_GPU_READ,addr);

	while (length--) 
    {
	   *buffer = Ft_Gpu_Hal_Transfer8(host,0);
	   buffer++;
	}

	Ft_Gpu_Hal_EndTransfer(host);
}


/* Helper api for dec to ascii */
ft_int32_t Ft_Gpu_Hal_Dec2Ascii(ft_char8_t *pSrc,ft_int32_t value)
{
	ft_int16_t Length;
	ft_char8_t *pdst,charval;
	ft_int32_t CurrVal = value,tmpval,i;
	ft_char8_t tmparray[16],idx = 0;

	Length = strlen((const char*)pSrc);
	pdst = pSrc + Length;

	if(0 == value)
	{
		*pdst++ = '0';
		*pdst++ = '\0';
		return 0;
	}

	if(CurrVal < 0)
	{
		*pdst++ = '-';
		CurrVal = - CurrVal;
	}
	/* insert the value */
	while(CurrVal > 0){
		tmpval = CurrVal;
		CurrVal /= 10;
		tmpval = tmpval - CurrVal*10;
		charval = '0' + tmpval;
		tmparray[idx++] = charval;
	}

	for(i=0;i<idx;i++)
	{
		*pdst++ = tmparray[idx - i - 1];
	}
	*pdst++ = '\0';

	return 0;
}


ft_void_t Ft_Gpu_Hal_Sleep(ft_uint32_t ms)
{
    delay_ms(ms);
}


#ifdef FT_81X_ENABLE
ft_int16_t Ft_Gpu_Hal_SetSPI(Ft_Gpu_Hal_Context_t *host,FT_GPU_SPI_NUMCHANNELS_T numchnls,FT_GPU_SPI_NUMDUMMYBYTES numdummy)
{
	ft_uint8_t writebyte = 0;
	/* error check */
	if((numchnls > FT_GPU_SPI_QUAD_CHANNEL) || (numdummy > FT_GPU_SPI_TWODUMMY) || (numdummy < FT_GPU_SPI_ONEDUMMY))
	{
		return -1;//error
	}

	host->spichannel = numchnls;
	writebyte = host->spichannel;
	host->spinumdummy = numdummy;

	if(FT_GPU_SPI_TWODUMMY == host->spinumdummy)
	{
		writebyte |= FT_SPI_TWO_DUMMY_BYTE;
	}
	Ft_Gpu_Hal_Wr8(host,REG_SPI_WIDTH,writebyte);
	/* set the parameters in hal context and also set into ft81x */
	return 0;
}
#endif


/* FIFO related apis */
//Init all the parameters of fifo buffer
ft_void_t Ft_Fifo_Init(Ft_Fifo_t *pFifo,ft_uint32_t StartAddress,ft_uint32_t Length,ft_uint32_t HWReadRegAddress,ft_uint32_t HWWriteRegAddress)
{
	/* update the context parameters */
	pFifo->fifo_buff = StartAddress;
	pFifo->fifo_len = Length;
	pFifo->fifo_rp = pFifo->fifo_wp = 0;

	/* update the hardware register addresses - specific to FT800 series chips */
	pFifo->HW_Read_Reg = HWReadRegAddress;
	pFifo->HW_Write_Reg = HWWriteRegAddress;
}

//update both the read and write pointers
ft_void_t Ft_Fifo_Update(Ft_Gpu_Hal_Context_t *host,Ft_Fifo_t *pFifo)
{
	pFifo->fifo_rp = Ft_Gpu_Hal_Rd32(host,pFifo->HW_Read_Reg);
}

//just write and update the write register
ft_uint32_t Ft_Fifo_Write(Ft_Gpu_Hal_Context_t *host,Ft_Fifo_t *pFifo,ft_uint8_t *buffer,ft_uint32_t NumbytetoWrite)
{
	ft_uint32_t FreeSpace = Ft_Fifo_GetFreeSpace(host,pFifo);
    ft_int32_t TotalBytes = NumbytetoWrite;

	if(NumbytetoWrite > FreeSpace)
	{
		/* update the read pointer and get the free space */
		Ft_Fifo_Update(host,pFifo);
		FreeSpace = Ft_Fifo_GetFreeSpace(host,pFifo);

		if(NumbytetoWrite > FreeSpace)
		{
			TotalBytes = FreeSpace;
		}
	}

	/* sanity check */
	if(TotalBytes <= 0)
	{
		return 0;//error condition
	}
	/* check for the loopback conditions */
	if(pFifo->fifo_wp + TotalBytes >= pFifo->fifo_len)
	{
		ft_uint32_t partialchunk = pFifo->fifo_len - pFifo->fifo_wp,secpartialchunk = TotalBytes - partialchunk;

		Ft_Gpu_Hal_WrMem(host,pFifo->fifo_buff + pFifo->fifo_wp,buffer,partialchunk);
		if(secpartialchunk > 0)
		{
			Ft_Gpu_Hal_WrMem(host,pFifo->fifo_buff,buffer + partialchunk,secpartialchunk);
		}
		pFifo->fifo_wp = secpartialchunk;

	}
	else
	{
		Ft_Gpu_Hal_WrMem(host,pFifo->fifo_buff + pFifo->fifo_wp,buffer,TotalBytes);
		pFifo->fifo_wp += TotalBytes;
	}

	/* update the write pointer address in write register */
	Ft_Gpu_Hal_Wr32(host,pFifo->HW_Write_Reg,pFifo->fifo_wp);

	return TotalBytes;
}

//just write one word and update the write register
ft_void_t Ft_Fifo_Write32(Ft_Gpu_Hal_Context_t *host,Ft_Fifo_t *pFifo,ft_uint32_t WriteWord)
{
	Ft_Fifo_Write(host,pFifo,(ft_uint8_t *)&WriteWord,4);
}


//write and wait for the fifo to be empty. handle cases even if the Numbytes are more than freespace
ft_void_t Ft_Fifo_WriteWait(Ft_Gpu_Hal_Context_t *host,Ft_Fifo_t *pFifo,ft_uint8_t *buffer,ft_uint32_t Numbyte)
{
	ft_uint32_t TotalBytes = Numbyte,currchunk = 0,FreeSpace;
	ft_uint8_t *pbuff = buffer;
	/* blocking call, manage to check for the error case and break in case of error */
	while(TotalBytes > 0)
	{
		currchunk = TotalBytes;
		FreeSpace = Ft_Fifo_GetFreeSpace(host,pFifo);
		if(currchunk > FreeSpace)
		{
			currchunk = FreeSpace;
		}

		Ft_Fifo_Write(host,pFifo,pbuff,currchunk);
		pbuff += currchunk;
		TotalBytes -= currchunk;


	}
}

//get the free space in the fifo - make sure the return value is maximum of (LENGTH - 4)
ft_uint32_t Ft_Fifo_GetFreeSpace(Ft_Gpu_Hal_Context_t *host,Ft_Fifo_t *pFifo)
{
	ft_uint32_t FreeSpace = 0;

	Ft_Fifo_Update(host,pFifo);

	if(pFifo->fifo_wp >= pFifo->fifo_rp)
	{
		FreeSpace = pFifo->fifo_len - pFifo->fifo_wp + pFifo->fifo_rp;
	}
	else
	{
		FreeSpace = pFifo->fifo_rp - pFifo->fifo_wp;
	}

	if(FreeSpace >= 4)
	{
		FreeSpace -= 4;//make sure 1 word space is maintained between rd and wr pointers
	}
	return FreeSpace;
}


ft_uint32_t Ft_Gpu_CurrentFrequency(Ft_Gpu_Hal_Context_t *host)
{
    ft_uint32_t t0, t1;

    t0 = Ft_Gpu_Hal_Rd32(host,REG_CLOCK); /* t0 read */

    // for SIM_system
	delay_ms(15625);

    t1 = Ft_Gpu_Hal_Rd32(host,REG_CLOCK); /* t1 read */
    return ((t1 - t0) * 64); /* bitshift 6 places is the same as multiplying 64 */
}


ft_int32_t Ft_Gpu_ClockTrimming(Ft_Gpu_Hal_Context_t *host,ft_uint32_t LowFreq)
{
   ft_uint32_t f;
   ft_uint8_t i;

  /* Trim the internal clock by increase the REG_TRIM register till the measured frequency is within the acceptable range.*/
   for (i=0; (i < 31) && ((f = Ft_Gpu_CurrentFrequency(host)) < LowFreq); i++)
   {
	   Ft_Gpu_Hal_Wr8(host,REG_TRIM, i);  /* increase the REG_TRIM register value automatically increases the internal clock */

   }

   Ft_Gpu_Hal_Wr32(host,REG_FREQUENCY,f);  /* Set the final frequency to be used for internal operations */

   return f;
}


//
//#define TOUCH_DATA_LEN 1172
//static ft_uint8_t TOUCH_DATA_U8 [TOUCH_DATA_LEN]={
 //26,255,255,255,32,32,48,0,4,0,0,0,2,0,0,0,34,255,255,255,0,176,48,0,120,218,237,84,255,107,92,69,16,159,125,155,107,141,201,121,247,106,130,9,225,244,238,37,246,146,52,63,53,98,172,53,48,243,8,36,166,182,63,136,216,246,7,205,219,75,122,119,185,139,196,128,34,33,136,123,65,240,7,31,44,105,41,69,72,12,210,166,6,17,12,104,64,165,73,133,134,98,80,74,43,148,22,20,133,40,20,34,233,15,82,250,131,10,113,246,229,106,197,191,161,111,217,55,179,59,59,59,243,153,47,251,135,15,58,204,11,109,114,89,149,84,169,242,172,2,109,10,73,53,167,92,158,89,21,6,89,230,236,126,86,89,206,242,169,178,61,187,115,62,85,190,199,133,129,44,132,249,90,12,243,124,67,49,169,76,81,22,195,60,211,113,40,133,249,253,104,114,113,148,197,131,105,169,158,3,19,132,65,28,187,240,25,112,3,147,99,235,163,80,98,63,10,123,181,208,73,213,29,24,246,226,121,112,199,146,74,98,56,22,195,135,245,32,14,194,17,180,182,100,46,169,220,114,244,103,171,114,252,41,222,143,97,150,53,64,167,202,110,240,86,186,45,16,90,14,191,158,110,196,163,216,130,241,232,159,42,251,88,4,169,90,80,42,163,226,248,168,206,97,132,136,169,69,113,20,27,245,203,40,131,12,54,87,37,143,253,43,105,97,137,9,172,103,181,26,172,79,163,102,184,142,57,83,0,61,139,144,159,79,135,193,62,61,0,157,250,5,20,186,67,91,255,133,238,140,104,167,30,192,197,72,2,85,137,221,89,134,101,140,177,191,238,137,75,105,137,23,97,18,226,31,175,98,31,174,165,141,90,193,21,88,194,117,60,207,243,115,248,202,254,171,171,37,248,20,87,112,17,59,180,59,246,35,199,177,83,175,35,140,93,224,187,172,45,169,172,108,29,47,192,59,186,70,159,1,208,155,136,40,71,190,195,101,222,117,131,221,90,142,110,48,221,85,165,177,42,173,169,82,89,165,78,149,138,136,110,224,13,108,200,0,132,1,50,103,114,55,176,145,254,51,132,208,183,177,137,64,111,128,192,13,104,162,86,145,165,198,255,141,86,209,68,79,146,84,87,33,163,95,132,39,120,182,242,76,115,78,123,40,142,7,200,227,21,103,50,103,171,109,123,27,242,115,193,0,197,176,70,63,141,125,212,35,14,8,95,28,20,246,116,155,30,132,152,118,3,40,29,162,62,60,158,9,131,8,197,120,49,99,115,35,39,228,200,168,48,81,197,2,175,221,224,205,140,173,148,4,87,13,148,94,19,235,216,205,62,212,179,14,199,221,234,21,223,207,112,254,163,90,169,197,247,50,110,249,16,249,156,113,137,83,98,146,163,23,215,115,16,146,173,102,142,158,74,160,205,181,28,217,67,93,156,121,40,156,202,76,130,169,184,193,12,9,125,82,132,149,121,209,65,219,198,12,47,80,7,15,182,163,97,52,171,206,211,20,186,229,195,148,42,15,137,45,116,244,29,188,138,105,177,76,139,149,18,113,141,160,192,1,218,222,14,131,101,90,224,17,195,239,51,113,156,194,111,245,21,49,137,171,100,61,238,21,166,50,67,95,83,63,154,202,71,116,141,45,205,208,37,94,133,188,186,201,177,134,82,86,117,84,109,46,137,52,237,214,102,248,22,253,82,41,137,91,148,37,29,97,147,195,86,126,89,156,165,45,214,188,43,54,43,160,63,36,139,169,142,17,73,175,31,255,230,232,164,175,244,161,197,38,71,118,121,70,109,226,43,252,14,100,249,142,135,180,156,48,185,45,172,176,247,71,244,29,104,240,25,3,37,216,78,179,159,101,171,9,63,225,95,166,6,126,71,24,29,156,165,199,253,126,108,119,88,51,146,216,19,191,137,102,191,107,186,68,109,78,247,244,95,130,99,94,134,49,183,128,158,84,207,58,245,129,9,220,145,78,16,218,85,102,226,94,102,142,121,247,51,243,146,119,63,51,3,14,71,157,94,245,86,169,151,134,156,99,212,206,189,148,208,9,109,239,43,242,125,57,135,249,19,111,120,245,182,79,121,218,62,110,231,222,203,57,220,245,52,237,217,126,246,253,183,89,95,59,59,145,238,165,15,28,91,45,86,239,140,215,231,199,56,34,59,239,154,239,159,244,38,57,63,167,156,41,126,95,14,83,82,189,203,183,244,51,186,33,39,12,234,244,105,156,79,111,161,100,186,232,37,25,187,195,253,252,137,35,245,2,243,54,207,243,8,176,143,109,175,225,57,92,131,71,248,220,151,222,113,255,28,26,114,131,139,17,130,111,24,65,63,235,157,198,90,188,238,213,251,63,120,130,59,151,187,130,95,193,207,252,26,214,221,175,215,240,186,211,85,217,197,107,67,123,113,15,217,42,252,201,155,245,133,94,131,122,255,87,207,80,143,215,238,91,47,126,247,106,248,204,159,153,187,116,219,49,116,45,115,147,182,48,242,4,190,240,127,118,224,193,247,224,3,89,247,15,148,99,211,103,26,255,255,255,20,33,48,0,4,0,0,0,15,0,0,0,26,255,255,255,32,32,48,0,4,0,0,0,0,0,0,0};
///* Download new touch firmware for FT811 and FT813 chip */
//ft_void_t Ft_Gpu_DownloadJ1Firmware(Ft_Gpu_Hal_Context_t *host)
//{
	////bug fix pen up section
    //Ft_Gpu_Hal_WrCmdBuf(host, TOUCH_DATA_U8, TOUCH_DATA_LEN);
    //Ft_Gpu_Hal_WaitCmdfifo_empty(host);
//}
