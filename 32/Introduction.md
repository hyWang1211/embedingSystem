# STM32

## STM32 系统结构

![Alternate text](images/2023-07-29-13-24-21.png)
内核引出三条总线

- ICode(Instruction Code)指令总线。连接Flash闪存，即存储我们编写的程序，下同。加载程序指令
- DCode(Data Code)数据总线。连接Flash闪存...。加载数据的(常量、调试参数)
- System系统总线。系统总线可以连接到其他设备，如SRAM存储程序运行时的变量

其他总线

- **AHB(Advanced High Performance Bus)系统总线。用于挂载主要外设**。比如复位、时钟等挂载在AHB(72MHz)上。
- **APB1/2(Advanced Peripheral Bus)先进外设总线**。用于连接一般外设，如GPIO、ADC等，注意APB2(72MHz)的性能高于APB1(36MHz)。
- DMA(Direct Memory Access)直接存储器访问总线。主要用于缓解CPU的压力(主要干一些数据搬运工作)，可以拥有和CPU同样的总线控制权。

## 工程创建流程

- 首先在外部文件里面创建项目目录，如：2.2STM32_Template。
- 在Keil中选择new project并在上述目录里面位置添加文件名，一般为Project。
![Alternate text](images/2023-07-26-11-30-16.png)
- 搜索选择芯片STM32F103C8。
- 在项目外目录中创建Start、Library、User等目录，并在项目里Target1中创建相同的三个组。
![Alternate text](images/2023-07-26-11-54-16.png)
- copy`D:\data\learning\embedingSystem\32\source\FixedLib\STM32F10x_StdPeriph_Lib_V3.5.0\Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x\startup\arm`下的所有启动文件And
`D:\data\learning\embedingSystem\32\source\FixedLib\STM32F10x_StdPeriph_Lib_V3.5.0\Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x`下的c和h文件，外设寄存器描述文件即stm32f10xh头文件作用和51中regx52.h作用相同指明寄存器地址, system_stm c文件用于配置时钟。
**to**`D:\data\learning\embedingSystem\32\STM32_Project\2.2STM_Template\Start`，复制启动文件到我们的项目外部start目录中，由于STM32时内核和内核外围的设备组成的且内核的寄存器描述和外围设备的描述文件不在一起，所以还需要添加内核寄存器描述文件 `D:\data\learning\embedingSystem\32\source\FixedLib\STM32F10x_StdPeriph_Lib_V3.5.0\Libraries\CMSIS\CM3\CoreSupport`到start中
![Alternate text](images/2023-07-26-12-22-34.png)

- 在项目中的Start中选择add existing files并选择外部Start文件夹中的md.s启动文件及所有.c与.h文件， **注意这里需要去掉core.cm3.c文件否则编译报错**
![Alternate text](images/2023-07-26-12-26-24.png)

- 如果只是使用寄存器进行开发STM32，那么上述配置已经够了，否则我们将继续使用STM标准库进行开发，即将标准库添加到上述目录中的Library中。
- copy`D:\data\learning\embedingSystem\32\source\FixedLib\STM32F10x_StdPeriph_Lib_V3.5.0\Libraries\STM32F10x_StdPeriph_Driver\src`和
`D:\data\learning\embedingSystem\32\source\FixedLib\STM32F10x_StdPeriph_Lib_V3.5.0\Libraries\STM32F10x_StdPeriph_Driver\inc`到
`D:\data\learning\embedingSystem\32\STM32_Project\2.2STM_Template\Library`中
- 同样的在项目Library中将上述文件全部添加到里面
- 这时候还不能直接使用，还需要添加`D:\data\learning\embedingSystem\32\source\FixedLib\STM32F10x_StdPeriph_Lib_V3.5.0\Project\STM32F10x_StdPeriph_Template`中的conf、it.c、it.h三个文件，conf用于配置库函数的包含关系，it文件用于存放中断函数，**到**User目录中
`D:\data\learning\embedingSystem\32\STM32_Project\2.2STM_Template\User`
- 在项目User中添加外部User中的三个文件
- 点击左下角扳手(options for target)。
  - 在output中勾选Create HEX file。
  - 在C/C++(AC6)中的Define栏目里添加`USE_STDPERIPH_DRIVER`，将Language C中c90改为c99，在includePaths中添加User、Library、Start等路径。
![Alternate text](images/2023-07-26-13-08-30.png)
  - 在Debug中将默认的Link改为ST-Link并进入旁边设置在FlashDownload中勾选Reset and Run(方便下载程序后后立马复位执行，否则需要按复位按钮才会执行)
![Alternate text](images/2023-07-26-11-45-44.png)

## GPIO(General Purpose Input Output)

GPIO实际上和51中的I/O口大致相同，主要也是可以控制这些端口的高低电平，连接各种外设。

### GPIO基本结构

![Alternate text](images/2023-07-27-10-54-21.png)

其中APB2是外设总线，所有GPIO都是挂载在上面的，每个GPIO有16个引脚(在51中是八个引脚)。
GPIO里包括寄存器和驱动器

- 寄存器主要用于存储相关信息，内核通过APB2总线向寄存器中读写数据, 完成输出、读取高低电平的功能。由于STM32是32位的，因此寄存器也是32位的，但由于每个GPIO只有16个引脚，因此其内部寄存器的低16位对应16个端口，高16位未用到。
- 驱动器用于增加驱动能力，是寄存器内部存储的高低电平更加显著。

### GPIO位结构

![Alternate text](images/2023-07-27-10-51-34.png)

#### 位结构大致框架

GPIO位结构是对GPIO基本结构的具体化，仍然可以将其划分为上图三部分。

- 位设置/清除寄存器、输出/输入数据寄存器等属于寄存器部分。
- TTL肖特基触发器(施密特触发器)、输入/输出驱动器、输出控制等中间部分属于驱动器部分。
- I/O引脚。

当然从整体上也可以分为输入和输出两部分。上面是输出部分(读取)、下面是输出部分(写出)。

#### 位结构具体分析

- 输入分析(读引脚电平)。从右至左上
  - 引脚电平分析
    - 当电平过高时(>$V_{DD}$的3.3V)电流会从上方的保护二极管流过，从而保护GPIO内部。
    - 当电平过低时(<$V_{SS}$)的0V，电流会从下方保护二极管流出到引脚外，不会从内部电路中汲取电流，从而保护内部。
    - 如果在0-3.3V之间则不会对电路有影响
  - 开端上下拉电阻分析。加入此部分的原因是给输出提供一个默认的高电平或低电平输入模式，如果输入引脚啥也不接那么既不是高电平也是低电平即处于浮空状态。为了避免这种情况选择接入这个部分
    - 上拉电阻，当上面接通下面断开时，会将浮空状态转为高电平状态。
    - 下拉电阻，当下面接通上面断开时，会将浮空状态转为低电平状态。
  - 触发器分析
    - 肖特基触发器(施密特触发器)。当输入的电压大于某一阈值(上限)，电压会迅速上升位高电平，当不低于某一阈值(下限)时仍未高电平，当低于这个阈值则为低电平，当高于这个阈值但不超过上限时仍未低电平，否则位高电平。
  - 输入数据寄存器。将经过施密特触发器后的电平读取到该寄存器。
  - 模拟输入。连接到ADC上，注意它接到触发器前。
  - 服用功能输入。需要接收数字量因此连接到触发器后。
- 输出分析。
  - 直接操作输出数据寄存器，即普通的IO口控制，直接写此寄存器的某一位(先&再|比较麻烦)即可操作对应的端口。
  - 位设置清清除寄存器。单独操作输出寄存器的某一位而不影响其他位。可以看作对上述寄存器的封装(库函数)。
  - P-MOS与N-MOS，是一种电子开关，负责将IO口街道$V_{DD}$或$V_{SS}$。共有推挽、开漏和关闭三种模式。
    - 推挽模式(强推输出模式)。两个MOS管均有效，当数据寄存器位1时，上管导通，下管断开输出VDD即高电平，为0时则相反。
    - 开漏模式。只有N-MOS有效，当为1时，下管断开，相当于高阻模式，为0时，下管导通，输出低电平，即只有低电平有驱动能力。
    - 关闭模式。当出入关闭模式时，两个MOS管相当于都失效，端口电平由外部控制，相当于输入模式。

#### GPIO模式

通过配置GPIO的端口配置寄存器，可以配置成一下8种模式，也是对上面结构的拆解。
![Alternate text](images/2023-07-27-16-32-05.png)

##### 浮空/上拉/下拉输入

GPIO_Mode_IN_FLOATING
GPIO_Mode_IN_IPU(In Pull Up)
GPIO_Mode_IN_IPD(In Pull Down)

![Alternate text](images/2023-07-27-16-33-58.png)
此时MOS管全部断开，上拉工作，下拉工作，都不工作对应上拉输入、下拉输入和浮空输入。

##### 模拟输入

GPIO_Mode_AIN(Analog IN)
![Alternate text](images/2023-07-27-16-40-07.png)
此时MOS管全部断开，输入引脚直接连接到片上外设，即ADC。因此当使用ADC时将引脚配置为模拟输入即可。

##### 开漏输出和推挽输出

GPIO_Mode_OUT_OD(Out Open Drain)
GPIO_Mode_OUT_PP(Out Push Pull)
![Alternate text](images/2023-07-27-16-42-04.png)

开漏输出的高电平呈现高阻态没有驱动能力，推挽输出的高低电平则都具有驱动能力

##### 复用开漏输出和推挽输出

GPIO_Mode_AF_OD(Alternate Open Drain)
GPIO_Mode_AF_PP(Alternate Push Pull)
![Alternate text](images/2023-07-27-16-44-48.png)
差别和上面的不大，只是引脚的控制权由片上外设来控制

### GPIO寄存器

这部分内容需要查阅参考手册

#### 端口配置寄存器

端口配置寄存器有两个：端口配置低寄存器和端口配置高寄存器。
每个GPIO有16个端口，每个端口必须选择一种模式，共有8中模式可供选择(但是每个端口需要4位而不是三位)。因此16个端口需要64位。

#### 端口输入数据寄存器

低16位对应16个引脚，高16位未使用

#### 端口输出数据寄存器

低16位对应16个引脚，高16位未使用

#### 端口位设置/清除寄存器

高16位进行位清除，低16位进行位设置

#### 端口位清除寄存器

低16位进行位清除

#### 端口配置锁定寄存器

用的不多

## 点亮LED(GPIO输出)

实验部分见3.1LED_Light

GPIO控制步骤

- 使用RCC开启GPIO的时钟。对于STM32的大多数外设(Periph Device)，在使用前都需要开启该外设的时钟
- 使用GPIO_init初始化GPIO。
- 使用输入输出函数控制GPIO口。

### RCC中重要的库函数

```c
void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState);/*开启AHB上某外设的时钟*/
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);/*开启APB2上某外设的时钟*/
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);/*开启APB1上某外设的时钟*/
```

- Param
  - RCC_AHBPeriph。该总线上挂载的外设，此项根据需求设置。
  - NewState。是否开启(ENABLE or DISABLE)。

### GPIO中重要的库函数

```c
//初始化
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);/*GPIO初始化函数主要用于设置端口的速率、模式、以及设置该GPIO中的哪些端口*/

//读端口
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);/*读取某个端口(输入寄存器某一位)的电平*/
uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx);/*读取整个GPIOx的16个端口(输入寄存器某)的电平*/
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);/*读取输出寄存器某一位的电平，感觉没啥作用(看在输出模式下输出了什么)*/
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx);/*读取整个输出寄存器的电平，感觉没啥作用*/

//写端口
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);/*将GPIO_Pin设置位高电平1*/
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);/*将GPIO_Pin设置位低电平0*/
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal);/*将GPIO_Pin设置为高电平1或低电平0*/
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal);/*将该GPIO下所有的端口设置为某个任意值低16位有效*/

//注意：
GPIO_Pin 可以为1个端口如GPIO_Pin_0。
也可以为多个端口如GPIO_Pin_All(选中所有端口)，GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2(选中0 1 2这三个端口)。

同理RCC_APB2PeriphClockCmd 的第一个参数可以为1个外围设备如RCC_APB2Periph_GPIOA
也可以为多个外围设备RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO
```

## 传感器模块(GPIO输入)

实验部分见3.2Buzzer及3.3Button

传感器模块基本电路
![a](images/2023-07-29-18-45-10.png)

### 模拟输出

- 图三分析
  - 元件分析
    - N1表示可变电阻，可以随温度、光照等模拟量进行变化
    - R1是定值电阻，目的是与N1分压
    - C2是滤波电容，滤除输出电压A0中的干扰使其平滑
  - 电路分析
    - A0是模拟电压输出
    - N1阻值减小(即下拉作用增强)，极限情况时N1阻值为0输出0v
    - N1阻值减大(即上拉作用增强)，极限情况时N1阻值为无穷大输出Vcc

### 二值化输出(高低电平1/0输出)

- 图一分析
  - 元件分析
    - LM393是一个电压比较器(运算放大器)。
    - C1是滤波电容。
  - 电路分析
    - IN+接到了A0即模拟电压端口
    - IN-接到了电位器(滑动变阻器),图二
    - 通过对IN+与IN-进行比较最终得到了二值化的电压(数字电压输出)D0(1或0)，同时D0也接入到了引脚的输出端

- 图四是电源指示灯
- 图五是D0输出的指示灯

## OLED模块

### 参数

- 供电：3v-5.5v
- 通信协议：I2C/SPI
- 分辨率：128*64

### 事物及常用函数

![a](images/2023-07-30-09-47-26.png)

### 使用

```c
#include "stm32f10x.h"                  // Device header
#include "OLED.h"

int main()
{ 
  OLED_Init();
  OLED_ShowChar(1, 1, 'A');
  OLED_ShowString(1, 3, "HelloWorld!");
  OLED_ShowNum(2, 1, 666, 6);
  
  while (1) {
    
  }
}
```

## 中断

STM32中断包括

- EXTI外部中断
- TIM定时器
- ADC模数转换器
- USART串口
- SPI通信
- I2C通信
- RTC实时时钟等多个外设中断

同时也有内核中断，如下图
![a](images/2023-07-30-10-54-15.png)

STM32使用NVIC同意管理中断，每个中断通道都拥有16个可编程的优先级，可对优先级进行分组，进一步设置抢占优先级和相应优先级

### NVIC基本结构

NVIC即嵌套中断向量控制器，主要用于同意分配及管理中断，它是一个内核外设是CPU的小助手(CPU是医生那么NVIC就是挂号系统统一安排病人看病的次序)。
![a](images/2023-07-30-11-00-37.png)
从图中可以看到NVIC接收多个中断输出，但最终只输出一个当前需要执行的中断。图中n表示一个外设可能会同时占用多个中断通道，所有有n条线(?保持质疑，难道不是一个通道会被多个外设占领吗？这里原文表述是正确的，EXTI看作一个外设包含(占用)20个通道)

### NVIC优先级分组

NVIC的优先级由优先级寄存器的4位(0-15，值越小优先级越高)决定, 分为响应优先级和抢占优先级，若响应优先级占n位则抢占优先级占4-n位。

- 响应优先级。当上一个中断执行完后，若有更紧急的中断出现那么它可以插队先执行。
- 抢占优先级。当上一个中断仍在执行时，若出现更紧急的中断那么它可以打断正在执行的中断而安排自己去执行。

![a](images/2023-07-30-11-12-33.png)
若某中断的抢占优先级和某中断的响应优先级相同，则按照它们的中断号进行排序，数值小先执行。

### 中断通道

### EXTI外部中断

EXTI主要用于监测指定GPIO口的电平信号，当端口电平发生特定变化时会向NVIC发送中断申请。

- 触发方式
  - 上升沿。
  - 下降沿。
  - 双边沿。上升和下降都会触发
  - 软件触发。自定义触发

- 支持所有GPIO口，但相同的Pin不能同时触发中断，如不能将PinA_0和PinB_0不能，PinA_0, PinB_1则可以(在EXTI基本结构中会解释为什么)。
- 响应方式 
  - 中断响应。中断发生时触发执行编写的中断函数。
  - 事件响应。中断发生时触发事件，如ADC转换、DMA等等。
- 通道数。16个GPIO_Pin通道 + PVD(电源电压检测)输出+RTC闹钟+USB唤醒+以太网唤醒 = 20个通道(加入后面四个的原因是，EXTI可以从低功耗模式的停止模式下唤醒STM32，如对于PVD，电源从低电压恢复时需要借助EXTI退出停止模式，其他类似)

### EXTI基本结构

![a](images/2023-07-30-11-33-11.png)

#### 图解

由于我们的每个GPIO都有16个引脚，显然是不够用的，若想复用这些端口，必须进行额外的设置。

- AFIO将从16*3的引脚数中选择16根进行复用。每一根都是从GPIOA_Pin_i、GPIOB_Pin_i、GPIOC_Pin_i中选择一根共16根。
- 理论上经过上述操作后应有20路的中断直接连接到NVIC，但实际上ST公司认为20个输出太多了会占用NVIC通道资源，所以把其中外部中断的EXTI9_5和EXTI15_10分到了一个通道里，即**9_5触发同一个中断函数，15_10触发另外一个中断函数，因此在编程时需要根据标志位来具体区分是哪个中断进来的。**
- 其他外设，触发事件响应。

#### AFIO复用IO口

![a](images/2023-07-30-11-53-28.png)

AFIO两大功能

- 复用功能引脚重映射
- 中断引脚选择(上面的EXTI基本结构图)

### EXTI内部结构

![a](images/2023-08-01-21-01-46.png)

- 图解
  - 输入线外侧连接的是20根中断通道
  - 可以看到EXTI支持上升沿、下降沿、双边沿、软件触发方式(它们的触发信号连接到或门上了)
  - 或门的输出分为两路。上一路是与中断有关的、下一路是与事件触发有关的。
    - 触发中断。上一路中首先会置为请求挂起寄存器(可读取并判断是哪个通道触发中断)，若其置1则可继续左走，中断屏蔽寄存器是一个开关，只有当其为1且请求为1时，才可正真触发中断
    - 事件中断。同样的由事件评级寄存器进行控制，脉冲发生器用于给出电平脉冲用来触发其他外设的动作
  - 数字20表示20个通道

## 中断应用

### 旋转编码器

- 内部结构与使用方法
  - 内部结构

![1](images/2023-08-01-21-32-48.png)

- 方框上面的部分暂时无用。
C1和C2是滤波电容，R3和R4是限流电阻，R1和R2为上拉电阻
当未旋转编码器时两侧触电不接通，此时A、B的输出均为高电平(上拉电阻)
当向左旋转编码器时左侧触点被连接，此时输出低电平
当向左旋转编码器时右侧触点被连接，此时输出低电平

  - 使用方法

![2](images/2023-08-01-21-46-07.png)
按照上面的接线即可

### 使用对射式红外传感器计数

目的：当我们对此传感器进行遮挡时，显示屏计数加1

步骤

- 开启时钟GPIOB、AFIO(EXTI其内部有时钟，而NVIC由内核控制，它们的时钟一直都是打开的，不需要再开启了)
- 配置GPIO(可以参考手册的外设GPIO配置，如若为EXTI输入线，GPIO配置为浮空输入或上拉、下拉输入)
- 配置AFIO。其配置的库函数在GPIO库函数中
  - 常见库函数。

     ```cpp
    void GPIO_DeInit(GPIO_TypeDef* GPIOx); // 用于复位AFIO，即清除所有的AFIO配置，使其失效。
    void GPIO_PinLockConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin); // 用于锁定GPIO引脚，当指定引脚后就会被锁定防止篡改。
    //下面两个函数用于配置AFIO事件的输出功能的，不常用
    void GPIO_EventOutputConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource);
    void GPIO_EventOutputCmd(FunctionalState NewState);

    //下面两个函数用于配置AFIO重要
    void GPIO_PinRemapConfig(uint32_t GPIO_Remap, FunctionalState NewState);//进行GPIO口重映射，参数一是重映射方式，参数二是新的状态
    void GPIO_EXTILineConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource);//配置AFIO的数据选择器，从而选择中断引脚
    ```

- 配置EXTI
  - 常见库函数。

    ```cpp
    void EXTI_DeInit(void); //清除EXTI之前的所有配置
    void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct); // EXTI的配置函数
    void EXTI_StructInit(EXTI_InitTypeDef* EXTI_InitStruct);//赋默认值
    void EXTI_GenerateSWInterrupt(uint32_t EXTI_Line);//软件触发中断

    /*下面两个函数可在主程序中查看标志位*/
    FlagStatus EXTI_GetFlagStatus(uint32_t EXTI_Line);//获取指定的标志位是否被置1了
    void EXTI_ClearFlag(uint32_t EXTI_Line);//清除标志位

    /*若想在中断函数中查看标志位，则需要用到下面两个函数*/
    ITStatus EXTI_GetITStatus(uint32_t EXTI_Line);//获取
    void EXTI_ClearITPendingBit(uint32_t EXTI_Line);//清除
    ```

- 配置NVIC
  - 常见库函数(在misc中)

    ```cpp
    void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup);//分配抢占优先级和响应优先级(这一项应该在全局中进行优化，因为只用使用一次)
    void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct);//初始化

    ```

- 编写中断函数。STM32的中断函数都是固定的，每个中断通道都对应一个中断函数。位于启动文件中的中断向量表中，以IRQHandler结尾的都是中断函数的名字，在这里我们的中断函数是`EXTI15_10_IRQHandler`,注意中断函数都是无参无返回值的。由于这个函数判断的是10-15所有的通道，而我们使用的是通道14，因此需要检查是不是14号中断通道的标志位为1

### 使用旋转编码器进行计数

正反转判断：当B相是下降沿时，若A相时低电平则正转，当A相时下降沿B相是低电平则反转

## 定时器(TIM)

定时器类型
![a](images/2023-08-03-16-22-30.png)

### 基本定时器

![a](images/2023-08-03-16-24-51.png)
其中PSC预分频器，CNT计数器和自动重装在寄存器合称为时基单元。

#### 定时中断

- PSC预分频器。对来自RCC的72MHz时钟进行分频。如果写0则不分频或1分频(维持72MHz), 若写1则进行2分频(72MHz / 2)...这个寄存器是16位的，最大可以写65535，即进行65536分频。
- 计数器。对来自分频后的时钟进行计数，每来一个上升沿则计数+1，可以从0加到65535。
- 自动重装寄存器。设置计数目标值，当计数器值等于自动重装值时，表明到达即使时间了，产生中断信号并清零计数器。
- 图中向上的折现箭头(UI)表示会产生一个更新中断信号(计数值等于重装值)，会送往NVIC
- 图中向下的折线箭头(U)表示会产生一个更新事件(计数等于重装)，不会触发中断，可以触发其他电路的工作。

#### 主模式触发DAC

当计数值等于自动重装值时触发事件，此事件被映射到触发输出TRGO上，由TRGO连接DAC的触发转换引脚，这样不需要触发中断来触发DAC转换。减少了CPU在此上面的占用时间。

### 通用定时器

![a](images/2023-08-03-18-29-10.png)

#### 计数模式支持

- 向上计数(与基本定时器相同)
- 向下计数(从重装值开始减到0中断)
- 中央对齐计数(从0到重装值中断，从重装值到0中断)

#### 内外时钟源选择支持(图片中上部分)

- 内部时钟源(72MHz)。见最上面那根线。(主模式，也是最常用的)
- 外部时钟源
  - ETRF。它是ETR经过滤波后的信号，即上面一路ETRF进入触发控制器，接着就可以选择作为时基单元的时钟了。(这一路也叫做外部时钟模式2)。
  - TRGI。通常来说主要用于触发输入(触发定时器的从模式)。在这里我们将其作为外部时钟源考虑(外部时钟模式1)。通过这一路的外部时钟有：
    - ETR引脚的信号。(可以发现它既可以通过上面一路当作时钟，也可以通过下面一路当作时钟(对于时钟输入来说是等价的，只是下面一路会占用触发输入的通道))
    - ITR信号。它来自其他定时器。可以发现主模式的输出的TRGO可以通向其他定时器，若通向了其他定时器，那么ITR就街道了其他定时器上。ITR0-3来自其他四个定时器的TRGO输出。
    ![1](images/2023-08-03-19-03-24.png)
    可以看到TIM2的ITR0接到了TIM1的TRGO上。通过这一路可以实现定时器的级联功能。如先初始化TIM3使用主模式，将它的更新事件映射到TRGO上，接着初始化TIM2，选择ITR2(看表可以，ITR2是TIM3的TRGO输出)，这样就完成了级联。
    - 还可以选择TI1F_ED。从CH1引脚获得时钟，ED是边沿，即上升沿和下降沿均有效。
    - 最后还可以从TI1F_P1，TI2F_P2获得。TI1F_P1来自CH1引脚，TI2F_P2来自CH2引脚。

对于图片中下半部分(输入捕获与输出比较)后期会讲。

### 高级定时器

大部分没有改变。
在申请中断的地方增加了一个重复次数计数器。作用，可以每个几个计数周期从才发生一次中断。

### 定时中断基本结构(对上面内容的抽象)

![a](images/2023-08-03-21-14-47.png)

图解：

1. 可以看到时基单元的构成主要是三部分：PSC、CNT、ARR。运行控制寄存器可以控制定时器的启动、停止、计数方式等。
2. 时钟的来源主要有四个：
     - 内部时钟模式，由RCC提供。
     - ETR引脚提供的外部模式2.
     - 选择触发输入当作外部时钟(外部模式1)。由ETR、ITRX、TIx(输入捕获通道)
     - 编码器模式。普通时钟用不上。

### 时基单元时序图

#### 预分频器时序

![a](images/2023-08-03-21-39-31.png)
计数器计数频率：CK_CNT = CK_PSC / (PSC + 1)

图解：

- CK_PSC。这是时基单元的输入时钟即未经过分频的时钟。
- CNT_EN。这是计数器使能时钟。高电平计数器正常运行，低电平计数器停止。(注意要在CK_CNT为高电平一个周期后才运行)
- CK_CNT。计数器时钟，是经过预分频后的时钟，也是计数器的时钟输入。可以看到当CNT_EN使能后的一个周期开始运行(前半段是1分频, 后半段是2分频)
- 计数器寄存器。随着计数器的上升沿不断驱动进行计数，当计数到达FC时，达到一个计数周期，开始新的计时。
- 更新事件。当达到重装值时，产生高电平，即更新事件。
- 预分频控制寄存器。可以看到预分频寄存器从0变为1时，一个计数周期尚未完成，此时并不会强行在这个周期内改变计数器时钟CK_CNT。而是会记录这个值。
- 预分频缓冲器。如上，预分频缓冲器在一个计数周期完成后将预分频控制寄存器的值填入, 此时表明在新的计数周期内使用新的分频。
- 预分频计数器。当预分频值为0时，预分频计数器的值也为0(输出原频率)，当预分频值为1时，预分频计数器就010101..计数，回到时就输出一个脉冲表示计数+1。

#### 计数器时序

计数器内部时钟分频因子为2
![a](images/2023-08-03-22-09-28.png)
计数器溢出频率：CK_CNT_OV = CK_CNT / (ARR + 1) = CK_PSC / (PSC + 1) / (ARR + 1)

图解：

- CK_INT。这是计数器的输入时钟，也是未经过分频的时钟。
- CNT_EN。同上
- CK_CNT。计数器时钟，分频(2分频)后的时钟。
- 计数器寄存器。同上
- 计数器溢出。溢出时为高电平
- 更新事件。计数器溢出为高电平时更新事件。
- 更新中断标志。当计数器溢出时，值中断标志位为1，触发中断，并由软件清0。

#### 计数器无预装时序(不带缓冲寄存器)

![a](images/2023-08-03-22-34-20.png)
可以看到当自动加载寄存器(重装寄存器)的值由FF改为36后, 在原来的计数周期(FF)到达新值36后立马溢出。

#### 计数器有预装时序(带缓冲寄存器)

![a](images/2023-08-03-22-38-49.png)
与上面相反，没有立刻改变这个值，而是带有缓冲(也叫做影子寄存器)，类似与预分频的时序。
