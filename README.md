#DL GPIO
用于Orange PI系列<br>
根据用户空间SYSFS的GPIO接口，封装的GPIO操作库。<br>
编译方法：<br>
make	编译库<br>
make install 安装库文件到/usr/lib <br>
make uninstall 从设备移除库<br>
make clean	清理编译文件<br>
<br>
使用方法：<br>
工程需包含头文件：<br>
`#include <dlgpio.h>`<br>
<br>
【一】使用GPIO前必须使用dlgpio作为变量类型用于声明一个gpio：<br>
	dlgpio status_led;<br>
	最起码需要为结构体 dlgpio 提供两个内容值 GPIO编号 IO状态（暂时仅支持两个模式out/in)，已在头文件中定义宏 OUT/IN：<br>
	power_led = {15, OUT};//参数一是GPIO编号，此处有3种定义方式：<br>
		（1）H3的GPIO名称（PA\*,PC\*,PG*....）。<br>
		（2）Orange PI（此处指搭载H3芯片组的所有开发板）的40个排针编号（需注意电源接口，特殊功能针脚可能不支持GPIO，支持的针脚已在头文件中定义）。<br>
		（3）直接使用GPIO编号。<br>
<br>
		举例三种方式（以GPIO 12为例）：<br>
		（1）{PA12, OUT};<br>
		（2）{_3, OUT};<br>
		（3）{12， OUT}；<br>
<br>
		注意：板载LED共 2 个，红灯（状态灯），绿灯（电源灯）也有三种参数方式（以 红灯（状态灯，PA15，GPIO 15） 举例）：<br>
		（1）{PA15, OUT};<br>
		（2）{STATUS_LED, OUT};//STATUS_LED是一个定义在头文件中的宏<br>
		（3）{15， OUT}；<br>
<br>
【二】初始化定义的GPIO<br>
	init_gpio(&status_led);<br>
	使用该函数将在系统注册导出指定的GPIO，用于操作；参数是定义的dlgpio类型[变量]的地址。<br>
<br>
【三】使用导出的GPIO<br>
	可以设置该GPIO电平状态：<br>
		setGPIO(&status_led, H);<br>
		参数是定义的dlgpio类型[变量]的地址，电平状态，H：高电平，L：低电平<br>
	读取该GPIO的电平状态：<br>
		int status = getGPIO(&status_led);<br>
		参数是定义的dlgpio类型[变量]的地址。返回整数型，0：低电平，1：高电平，同时设置定义的dlgpio结构体类型[变量]的成员status：<br>
			char *status = status_led.status;//此方法也可以读出电平状态。<br>
<br>
【四】关闭GPIO<br>
	close_gpio(&status_led);<br>
	参数是定义的dlgpio类型[变量]的地址。<br>
<br>
<br>
在编译工程时，编译命令需加入 -ldlgpio<br>
<br>
Email<br>
sxwr2013@live.com

