# STM32

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

- 在项目中的Start中选择add existing files并选择外部Start文件夹中的md.s启动文件及所有.c与.h文件
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
  - 输入数据寄存器。将经过施密特触发器后的电平读取到该寄存器
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
![](images/2023-07-27-16-32-05.png)

##### 浮空/上拉/下拉输入

![](images/2023-07-27-16-33-58.png)
此时MOS管全部断开，上拉工作，下拉工作，都不工作对应上拉输入、下拉输入和浮空输入。

##### 模拟输入

![](images/2023-07-27-16-40-07.png)
此时MOS管全部断开，输入引脚直接连接到片上外设，即ADC。因此当使用ADC时将引脚配置为模拟输入即可。

##### 开漏输出和推挽输出

![](images/2023-07-27-16-42-04.png)

开漏输出的高电平呈现高阻态没有驱动能力，推挽输出的高低电平则都具有驱动能力

##### 复用开漏输出和推挽输出

![](images/2023-07-27-16-44-48.png)
差别和上面的不大，知识引脚的控制权由片上外设来控制

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

