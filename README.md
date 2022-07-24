# TinyPMU
### ！！未完善
### 个人开源项目【TINY-PMU】电源管理模块的适配Arudino库

- 已封装大部分常用电源操作方法：关机、LDO使能、电池状态等
- 易移植：使用PORT基类用于硬件解耦

#### 目前支持模块：

- [【TINY-PMU-AXP173】](https://github.com/Forairaaaaa/TINY-PMU-AXP173)

#### 依赖库：

- [Forairaaaaa/HARDWARE-PORT: 硬件外设封装基类，方便移植 (github.com)](https://github.com/Forairaaaaa/HARDWARE-PORT)

#### 示例：

```cpp
#include "Wire.h"
#include "TinyPMU.h"

...
    
AXP173 pmu;

/* Init PMU */
Wire.begin();
pmu.begin(&Wire);

/* Enable and set LDO voltage */
pmu.setOutputEnable(AXP173::OP_LDO2, true);
pmu.setOutputVoltage(AXP173::OP_LDO2, 2200);

/* Get PMU info */
Serial.println(pmu.getAXP173Temp());
Serial.println(pmu.getBatLevel());

...
```

#### 参考链接：

- [www.x-powers.com](http://www.x-powers.com/index.php/Info/product_detail/article_id/27)
- [m5stack/M5Core2](https://github.com/m5stack/M5Core2)

