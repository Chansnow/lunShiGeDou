# 轮式格斗机器人

采用的主控为内核为STM32的控制器模块，其他传感器包括红外对管、超声波测距模块等。要求制作的车模在登上擂台后将对方车辆推下擂台。

## 设计框架
本车利用主控提供的16个AD通道，与数字量红外传感器和模拟量红外测距相连，进行敌方车辆测距、台上边缘检测、台下识别。通过输入pwm波对电机进行转速控制，达到直行、转弯等效果。
调试时在自带LCD屏幕上显示红外数值。

### 系统框架设计：
![lunShi1](https://user-images.githubusercontent.com/80667208/173524830-b97af696-81d4-41aa-ad7a-a8570032f1fa.png)

### solidworks建模图：
![lunShi2](https://user-images.githubusercontent.com/80667208/173525010-36d817f8-1992-40da-88d8-f17f8845f321.png)

### 车模成品：
<img width="1218" alt="lunShi3" src="https://user-images.githubusercontent.com/80667208/173525218-ddc9db7a-8ab5-4b2f-8246-5a8e8ca06d22.png">

### 程序控制流程：
<img width="594" alt="lunShi4" src="https://user-images.githubusercontent.com/80667208/173526152-b85251e5-4ef1-4468-a2bc-ad97309a6ea2.png">
<img width="594" alt="lunShi5" src="https://user-images.githubusercontent.com/80667208/173526190-7cb82ca0-e164-46bd-a39b-e7f6af15ee47.png">
<img width="596" alt="lunShi6" src="https://user-images.githubusercontent.com/80667208/173526204-2c416558-a974-49cd-94ba-392c11f0926b.png">
