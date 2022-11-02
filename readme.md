# APOLL开发板移植ThreadX全家桶

> STM32H743II KEIL-MDK5.32 AC5

1. 移植threadX
   1. 替换开发板例程的delay函数，使用DWT延时
   2. 替换hal库内的delay相关函数
   3. 使用microLib
   4. 修改tx_initialize_low_level.s
