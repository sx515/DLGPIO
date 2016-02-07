#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

/*#include "dlgpio.h"*/



/* 
   License : GPL
   Author : DickLight
   Time : 2016/02/03
   
   对用户态sysfs的GPIO接口做个封装
   方便操作。
   
*/



#define PIN_MODE_CHAR_LEN 3

#define FILE_EXISTS(s) !access(s,0)


typedef struct dlgpio
{
	int pin_num;//GPIO PIN编号
	char *io_mode;//IO 模式，输入，输出
	char *status;//当前IO状态
	
	int isUse;//该GPIO是否已经被申请
}dlgpio;


int init_gpio(dlgpio *_gpio)
{
	char buf[1024];
    	int len;
    	int fd;
	
	sprintf(buf, "/sys/class/gpio/gpio%d/direction", _gpio->pin_num);
	if (! access(buf, 0) )
		goto CONFIG;
	
    	fd = open("/sys/class/gpio/export", O_WRONLY);  
    	if (fd < 0)
	{
        	fprintf(stderr, "[Export GPIO]Can`t Open Interface.\n");
        	return -1;
    	}

    	len = sprintf(buf, "%d", _gpio->pin_num);
    	if (write(fd, buf, len) < 0)
	{
        	fprintf(stderr, "[Export GPIO]Can`t Write Interface.\n");
        	return -1;  
    	}

	_gpio->isUse = 1;

    	close(fd);

CONFIG:
    	sprintf(buf, "/sys/class/gpio/gpio%d/direction", _gpio->pin_num);
    	fd = open(buf, O_WRONLY);
    	if (fd < 0)
	{
        	fprintf(stderr, "[Set GPIO]Can`t Open Interface.\n");
        	return -1;
    	}
	
	if (write(fd, _gpio->io_mode, PIN_MODE_CHAR_LEN) < 0)
	{  
        	fprintf(stderr, "[Set GPIO]Can`t Write Interface.\n");
        	return -1;
    	}

    	close(fd);
	getGPIO(_gpio);
    	return 0;
}

int close_gpio(dlgpio *_gpio)
{
	if (_gpio->isUse != 1)
	{
		goto done_close;
	}
	
	char buf[1024];
    	int len;
    	int fd;
  
    	fd = open("/sys/class/gpio/unexport", O_WRONLY);
    	if (fd < 0)
	{
        	fprintf(stderr, "[Close GPIO]Can`t Open Interface.\n");
        	return -1;
   	}

    	len = sprintf(buf, "%d", _gpio->pin_num);
    	if (write(fd, buf, len) < 0)
	{  
        	fprintf(stderr, "[Close GPIO]Can`t Write Interface.\n");
        	return -1;
    	}

    	close(fd);
done_close:
	_gpio->isUse = 0;
    	return 0;
}

int setGPIO(dlgpio *_gpio, char *_status)
{
	if (_gpio->isUse != 1)
	{
		goto error;
	}
	
	char buf[1024];
    	int fd;

    	sprintf(buf, "/sys/class/gpio/gpio%d/value", _gpio->pin_num);
    	fd = open(buf, O_WRONLY);
    	if (fd < 0)
	{
        	fprintf(stderr, "[SET GPIO]Can`t Open Interface.\n");
        	return -1;
    	}

    	if (write(fd, _status, 1) < 0)
	{  
        	fprintf(stderr, "[SET GPIO]Can`t Write Interface.\n");  
        	return -1;  
    	} 
  	
    	close(fd);
	_gpio->status = _status;

    	return 0;
error:
	fprintf(stderr, "[SET GPIO]GPIO Unregistered.\n");
	_gpio->status = "error";
	return -1;
}

int getGPIO(dlgpio *_gpio)
{
	if (_gpio->isUse != 1)
	{
		goto error;
	}

	char buf[1024];
    	int fd;

    	sprintf(buf, "/sys/class/gpio/gpio%d/value", _gpio->pin_num);
    	fd = open(buf, O_RDONLY);
    	if (fd < 0)
	{
        	fprintf(stderr, "[GET GPIO]Can`t Open Interface.\n");
        	return -1;
    	}

    	if (read(fd, buf, 3) < 0)
	{
        	fprintf(stderr, "[GET GPIO]Can`t Read Interface.\n");
        	return -1;
    	}

    	close(fd);
	_gpio->status = buf;
    	return (atoi(buf));
error:
	fprintf(stderr, "[GET GPIO]GPIO Unregistered.\n");
	_gpio->status = "error";
	return -1;
}

//gcc -c dlgpio.c -fPIC -shared -o libdlgpio.so
/*
##
sxwr2013@live.com
*/
