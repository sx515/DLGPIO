#ifndef _DL_GPIO_H_
#define _DL_GPIO_H_




/* 
   License : GPL
   Author : DickLight
   Time : 2016/02/03
   
   对用户态sysfs的GPIO接口做个封装
   方便操作。
   
*/

#define H "1"
#define L "0"

#define OUT "out"
#define IN "in"

/*
ORANGE PI PC GPIO
*/
//左侧排针GPIO口共 15 个
/*
用法:
dlgpio 自定义变量名 = {PA12, OUT};
init_GPIO(&自定义变量名);
*/
#define PA12 12
#define PA11 11
#define PA6  6
#define PA0  0
#define PA1  1
#define PA3  3
#define PC0  64
#define PC1  65
#define PC2  66
#define PA19 19
#define PA7  7
#define PA8  8
#define PA9  9
#define PA10 10
#define PA20 20

//右侧排针GPIO口共 13 个
#define PA13 13
#define PA14 14
#define PD14 110
#define PC4  68
#define PC7  71
#define PA2  2
#define PC3  67
#define PA21 21
#define PA18 18
#define PG8  200
#define PG9  201
#define PG6  198
#define PG7  199


//板载LED指示灯共 2 个
#define PA15 15
#define PL10 362


//按排针号定义共 28 个
/*
用法:
dlgpio 自定义变量名 = {_3, OUT};
init_GPIO(&自定义变量名);
*/
#define _3   12
#define _5   11
#define _7   6
#define _8   13
#define _10  14
#define _11  0
#define _12  110
#define _13  1
#define _15  3
#define _16  68
#define _18  71
#define _19  64
#define _21  65
#define _22  2
#define _23  66
#define _24  67
#define _26  21
#define _27  19
#define _28  18
#define _29  7
#define _31  8
#define _32  200
#define _33  9
#define _35  10
#define _36  201
#define _37  20
#define _38  198
#define _40  199

//板载LED指示灯共 2 个
#define STATUS_LED 15
#define POWER_LED  362

typedef struct dlgpio
{
	int pin_num;//GPIO PIN编号
	char *io_mode;//IO 模式，输入，输出
	char *status;//当前IO状态
	
	int isUse;//该GPIO是否已经被申请
}dlgpio;

 /*
初始化一个GPIO，用于后续操作
参数 是一个dlgpio结构体指针
返回值 正常工作返回0，否则<0
*/
int init_gpio(dlgpio *_gpio);

/*
关闭一个被打开的GPIO
参数 dlgpio结构体指针
返回值 0
*/
int close_gpio(dlgpio *_gpio);

/*
设置一个打开的GPIO电平状态
参数 dlgpio结构体指针 字符串 用于状态值，可接受"1","0"
返回值 成功返回0 否则-1
*/
int setGPIO(dlgpio *_gpio, char *_status);

/*
获取一个已经打开的gpio电平状态
参数 dlgpio结构体指针
返回值 返回整数型1，0  同时设置结构体中的成员 status。
*/
int getGPIO(dlgpio *_gpio);

#endif

/*
##
sxwr2013@live.com
*/
