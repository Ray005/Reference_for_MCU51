# 单片机实验参考-Reference_for_MCU51
S01 专用

实验平台：Keil5 on Windows10

## 实验一：流水灯

### 硬件部分：LED的共阳极特性

流水灯使用P20~P27点亮。

注意：这里的LED是共阳极的，所以引脚为低电平时，LED亮。

![1609934054026.png](https://github.com/Ray005/Reference_for_MCU51/blob/main/images/1609934054026.png)

### 软件部分：100ms延时函数的获取

本代码使用的是在STC-ISP软件中可以找到的，适用于本单片机

![1609935009263.png](https://github.com/Ray005/Reference_for_MCU51/blob/main/images/1609935009263.png)

* 注意：这是按照时钟周期来进行”精确“延时的

## 实验二：矩阵按键+数码管

### 矩阵按键检测方法

逐行扫描法：

行列反转法：（本程序使用）

### 八段数码管之接线与使用

使用的普中科技A2使用共阴极数码管，如下原理图所示：

P00~P07为高时，段亮

![1609933422966.png](https://github.com/Ray005/Reference_for_MCU51/blob/main/images/1609933422966.png)

* 段选：段选表示一个数字的八个段，本实验使用开发板为通过P00到P07通过74HC245锁存器来选择一个数字哪**几个**段亮
* 位选：位选表示选择哪一个数字亮，本开发板中，通过P22~P24再经过74HC138译码器来选择哪**一个**数字亮

注意：74HC245的OE使能段默认接了GND有效。所以，这里可以直接无视这个芯片，当作是P00~P07直接通到了数码管（这个芯片事实上可以看作放大驱动能力的作用）

程序：

``` C
u8 code smgduan[17]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
					0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};//显示0~F的值(共阴极的显示表)
```

注意：例程中

## 实验三：定时器Timer1使用
中断表：
0 外部0
1 定时0
2 外部1
3 定时1
4 串口中断

### Report ONTLINE 3

0.Introduction
 0.1功能介绍
 0.2性能指标
 0.3使用说明

1.Method Comparing
	1.1产生pwm的方案介绍：（与实验二中的pwm产生方式有区别，这里更加精确）
	1.2

2.原理分析：
	2.1定时器部分：（1定时器初始化与2定时器中断）
	2.2按键部分：（等待弹起的独立按键）
	2.3显示部分（各个字母的显示与数字分位显示）
	2.4主函数（更新定时器计数值的部分）：

3.Final Demostration(Inserting picture)

附录:

``` C
void Timer0Init()
{
	TMOD|=0X01;//选择为定时器0模式，工作方式1，仅用TR0打开启动。

	TH0=0XCD;	//给定时器赋初值，定时1ms
	TL0=0XD4;	
	ET0=1;//打开定时器0中断允许
	EA=1;//打开总中断
	TR0=1;//打开定时器			
}
```

``` C
unsigned int counterCul(float dutycycle){//1kHz
	return 65535-(int)(1000*dutycycle*11.0592/12.0);//pwm周期为1000us即1ms（1kHz）
}
```

``` C
void Timer0() interrupt 1
{
	if(speed ==0 ){
	moto_pos = 1;
	}
	if(moto_pos == 0)
    {		
			led = 0;
        moto_pos = 1;        //设置高电平持续时间
        TH0 = TH0_ON;
        TL0 = TL0_ON;

    }
    else
    {		led = 1;
        moto_pos = 0;        //设置低电平持续时间         
			TH0 = TH0_OFF;
      TL0 = TL0_OFF;
    }
}
```

``` C
	if(k1==0)		  //检测按键K1是否按下
	{	//k1 = 1;
		delay(10);   //消除抖动 一般大约10ms
		if(k1==0)	 //再次判断按键是否按下
		{	while(!k1);
			return 1;	  
		}
		
	}
```

``` C
weixuan(0);
		GPIO_DIG=0x6d;	  //在第0位显示字母S
		delay(2);
		weixuan(1);
		GPIO_DIG=0x73;	  //在第0位显示字母P
		delay(2);
		weixuan(2);
		GPIO_DIG=0x79;	  //在第0位显示字母E
		delay(2);
		weixuan(3);
		GPIO_DIG=0x79;	  //在第0位显示字母E
		delay(2);
		weixuan(4);
		GPIO_DIG=~smgduan[13];	  //在第0位显示字母d
```

``` C
void main(){
    //······
if(speed != speed_old)
		{
		counter = counterCul(0.2 + speed/20.0);
		counter_OFF = 65535- (counter - 64613);
		TL0_ON = counter;
		TH0_ON = counter>>8;
		TL0_OFF = counter_OFF;
		TH0_OFF = counter_OFF>>8;
		//P2 = TL0_ON;
		speed_old = speed;
		}
   
   //······
```

* 产生一个PWM驱动电机调速，并使用数码管显示速度等级
* 并调调

PWM的产生两个方案：

* 中断+main：缺点是不能加其他功能了
* 纯中断产生

周期设置为 1ms（即1000us）。则可以根据占空比需求更改高低电平时间：

http://www.51hei.com/bbs/dpj-78872-1.html

### 特点介绍

定时器产生PWM以驱动电机的实验程序包含以下功能：
* 16级电机调速功能
* 速度（speed）等级显示功能
* 占空比（duty cycle）显示功能
* 停止（stop）显示功能
* 按键加减速
* 按键切换数码管显示速度或占空比

性能指标：
* 占空比可调：从25%~100%
* PWM工作频率：1kHz

典型函数：



## 实验四：串口通信

### 主要：多机通信与通信协议设计

package

![1610096551164.png](images\1610096551164.png)

### Report ONTLINE 4

介绍：
分析原理：
	1.串口的发送
		1.1一帧数据的发送
		1.2多帧数据的发送
		1.3 printf的重定向
	2.串口接收
		2.1一帧数据的接收
		2.2环形缓冲区（cbuffer）设计
		2.2多机通信数据包设计
		2.3网络形式分析：星形网络
	3.展示
		3.1
		3.2
		3.3

### printf函数的重定向

``` C
char putchar(char c){	//重写了putchar函数，在include stdio.h后就可以使用printf了
	SBUF = c;
	while(!TI);//Here，等待清除标志位，注意这里是阻塞的
	TI = 0;
	return c;
}
```

![1610103095402.png](images\1610103095402.png)


``` C
void sendString(char * da, int length){	//coded by han 串口发送函数
	//查询方式清除标志位
	//查询与中断方式不能一起用
	int i;
	for(i = 0; i < length ; i++){
		SBUF = da[i];
		while(!TI);//Here，清除标志位，注意这里是阻塞的
		TI = 0;
	}

}

void sendByte(char c){
	SBUF = c;
	while(!TI);//Here，清除标志位，注意这里是阻塞的
	TI = 0;
}

```

### 新的想法

多机同通信已经可以做到；


![1610114929648.png](images\1610114929648.png)


* 1.点阵屏幕显示A、b表示不同机器
* 2.双重奏？？？


## 大实验

Title：多机通信电机调速温度监测系统

十六级调速：
按键调速：
串口调速：
占空比、速度等级调节：
显示主从：（只能在数码管上）
数码管警告：（显示温度）

温度传感器监测：
警告机制：蜂鸣器警告、闪烁警告

李锦安：温度传感器读取
游子昂：蜂鸣器警告、闪烁警告
侯军：调速
韩衍：之前的几个项目按键、调速、串口、多机以及整合

三个模式：
* 普通模式
* 报警模式


## 基本操作说明

* 下载程序的步骤：
  * 一、打开文件
  * 二、选择你的hex文件
  * 三、单击下载
  * 四、重启你的单片机（按单片机的电源开关）


![1609935153634.png](https://github.com/Ray005/Reference_for_MCU51/blob/main/images/1609935153634.png)




Created by Han@NUC