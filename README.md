# TinyPMU
##### 个人开源项目【TINY-PMU】系列电源管理模块的适配Arudino库

- 已封装大部分常用电源操作方法：关机、LDO使能、电池状态等
- 易移植：使用PORT基类用于硬件解耦

##### 目前支持：

- [【TINY-PMU-AXP173】](https://github.com/Forairaaaaa/TINY-PMU-AXP173)

##### 示例：

```cpp
#include "Wire.h"
#include "TinyPMU.h"

...
    
AXP173 pmu;

Wire.begin();
pmu.begin(&Wire);

pmu.setOutputEnable(AXP173::OP_LDO2, true);
pmu.setOutputVoltage(AXP173::OP_LDO2, 2200);

Serial.println(pmu.getAXP173Temp());
Serial.println(pmu.getBatLevel());

...
```

##### 参考链接：

- [](http://www.x-powers.com/index.php/Info/product_detail/article_id/27)
- [](https://github.com/m5stack/M5Core2)

