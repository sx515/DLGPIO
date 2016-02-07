#DL GPIO

用于Orange PI系列
根据用户空间SYSFS的GPIO接口，封装的GPIO操作库。
编译方法：
make	编译库
make install 安装库文件到/usr/lib
make uninstall 从设备移除库
make clean	清理编译文件

使用方法：
工程需包含头文件：
#include <dlgpio.h>

【一】使用GPIO前必须使用dlgpio作为变量类型用于声明一个gpio：
	dlgpio status_led;
	最起码需要为结构体 dlgpio 提供两个内容值 GPIO编号 IO状态（暂时仅支持两个模式out/in)，已在头文件中定义宏 OUT/IN：
	power_led = {15, OUT};//参数一是GPIO编号，此处有3种定义方式：
		（1）H3的GPIO名称（PA*,PC*,PG*....）。
		（2）Orange PI（此处指搭载H3芯片组的所有开发板）的40个排针编号（需注意电源接口，特殊功能针脚可能不支持GPIO，支持的针脚已在头文件中定义）。
		（3）直接使用GPIO编号。

		举例三种方式（以GPIO 12为例）：
		（1）{PA12, OUT};
		（2）{_3, OUT};
		（3）{12， OUT}；

		注意：板载LED共 2 个，红灯（状态灯），绿灯（电源灯）也有三种参数方式（以 红灯（状态灯，PA15，GPIO 15） 举例）：
		（1）{PA15, OUT};
		（2）{STATUS_LED, OUT};//STATUS_LED是一个定义在头文件中的宏
		（3）{15， OUT}；

【二】初始化定义的GPIO
	init_gpio(&status_led);
	使用该函数将在系统注册导出指定的GPIO，用于操作；参数是定义的dlgpio类型[变量]的地址。

【三】使用导出的GPIO
	可以设置该GPIO电平状态：
		setGPIO(&status_led, H);
		参数是定义的dlgpio类型[变量]的地址，电平状态，H：高电平，L：低电平
	读取该GPIO的电平状态：
		int status = getGPIO(&status_led);
		参数是定义的dlgpio类型[变量]的地址。返回整数型，0：低电平，1：高电平，同时设置定义的dlgpio结构体类型[变量]的成员status：
			char *status = status_led.status;//此方法也可以读出电平状态。

【四】关闭GPIO
	close_gpio(&status_led);
	参数是定义的dlgpio类型[变量]的地址。
		

在编译工程时，编译命令需加入 -ldlgpio

Email
sxwr2013@live.com

