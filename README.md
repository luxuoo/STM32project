# STM32F103 环境监测系统

基于 STM32F103C8T6 的环境数据采集与蓝牙传输系统，通过 BH1750 光照传感器和 AHT20 温湿度传感器采集环境参数，经蓝牙模块无线发送数据，并根据光照阈值自动控制 LED。

## 硬件平台

| 组件 | 型号 | 接口 | 说明 |
|------|------|------|------|
| MCU | STM32F103C8T6 | - | Cortex-M3, 72MHz, 64KB Flash, 20KB RAM |
| 光照传感器 | BH1750 | I2C1 (PB6/PB7) | 地址 0x23, 量程 1-65535 lx |
| 温湿度传感器 | AHT20 | I2C1 (PB6/PB7) | 地址 0x38, 温度精度 ±0.3°C |
| 蓝牙模块 | DXbt22 | USART1 (PA9/PA10) | 波特率 9600, 8N1 |
| LED | - | PC13 | 低电平点亮, 光照 <= 300lx 时自动亮 |

## 软件架构

```
Core/
├── Inc/
│   ├── main.h              # 全局宏定义与引脚配置
│   ├── bh1750.h            # BH1750 驱动接口
│   ├── aht20.h             # AHT20 驱动接口
│   ├── i2c.h / tim.h / usart.h / gpio.h
│   └── stm32f1xx_it.h      # 中断处理声明
├── Src/
│   ├── main.c              # 主程序: 初始化 + 主循环
│   ├── bh1750.c            # BH1750 光照传感器驱动
│   ├── aht20.c             # AHT20 温湿度传感器驱动
│   ├── usart.c             # USART1/USART3 配置
│   ├── i2c.c / tim.c / gpio.c
│   └── stm32f1xx_it.c      # 中断服务函数
```

## 工作流程

1. 系统初始化: 时钟配置 → GPIO/USART/I2C/TIM3 外设初始化 → 传感器初始化
2. TIM3 定时中断 (1s 周期) 触发数据采集标志
3. 主循环检测标志位, 依次读取 BH1750 光照值和 AHT20 温湿度
4. 光照 <= 300lx 时点亮 LED, 否则熄灭
5. 数据通过蓝牙串口发送, 格式: `L:<光照> T:<温度> H:<湿度> LED:<状态>`

## 数据格式

蓝牙串口输出示例:
```
L:520 T:25.3 H:60.1 LED:0
L:180 T:24.8 H:55.2 LED:1
```

## 开发环境

- **IDE**: STM32CubeMX + VSCode (CMake)
- **工具链**: GNU Tools for STM32 (arm-none-eabi-gcc 14.3.1)
- **构建系统**: CMake 3.22+
- **调试器**: ST-Link

## 构建与烧录

```bash
# 配置
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug

# 编译
cmake --build build

# 烧录 (需 ST-Link 连接)
# 使用 STM32CubeProgrammer 或 OpenOCD
```

## 许可证

基于 STMicroelectronics 生成的 HAL 框架代码开发。
