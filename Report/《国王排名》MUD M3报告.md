# 《国王排名》MUD M3报告

组员：孙鑫杰，方成睿

## 项目背景

我们小组准备完成了一款名叫《国王排名》的MUD生存游戏，背景故事基于十日草辅创作的同名漫画作品，详情见[国王排名（WIT STUDIO改编的电视动画作品）_百度百科 (baidu.com)](https://baike.baidu.com/item/国王排名/24190907)，国王本人是否像勇者一样强大，把全世界的国王进行的排名就是“国王排名”。每一位国王出生都会拥有一块自己的王国，我们的目标就是不断成长，成为最强大的国王。

## 目标和任务

### 目标

- 拥有较完整的人物系统，包括人物的等级、人物的生命、人物的属性（力量、智力、敏捷力、幸运等）、人物的技能、人物的武器和道具等
- 拥有较完善的主线剧情与适当的支线剧情使得逻辑自洽，体现人性、战争、温情等主旨
- 拥有较完整的地图
- 拥有较完善的生存系统，包括生命值等
- 拥有较完善的战斗系统，以及较多类型的敌人（如神魔、怪兽等）
- 拥有较合理的配套系统，包括时间系统、背包系统、货币系统等
- 拥有MUD的多人生存与战斗系统
- 最好拥有可视化界面，直观展示生存和战斗系统

### 任务

1. 完成剧本的大纲
2. 实现人物、生存、战斗、配套系统等模块的编写及测试
3. 实现各类剧情和地图切换功能
4. 实现多人在线和互动
5. 实现可视化效果

## 目前完成任务

### 游戏系统介绍

#### 初始

&emsp;&emsp;欢迎来到国王排名的世界！在这里，国王需要对每一位子民负责，而国王自身是否像勇者一样强大就决定了王国的排名，所以每一位国王都想成为前七名的国王，以此展开了一次又一次国王之间的厮杀！而年轻的国王，欢迎来到国王排名的世界。

#### 地图介绍

我们的国王排名大陆是无限扩展的，中间拥有一块5000 * 5000单位的巨大的平原，平原的基本单位是1 * 1单位。平原里随机出没敌人和掉落的武器、道具，商城等，每一位国王初始之后会获得一块100 * 100单位的领土，然后朝着平原和其他国家进发吧！

#### 初始人物介绍

每位来到国王排名大陆的国王们，将会随机拥有一块100 * 100单位的领土。10枚国王币，

你将拥有一块10000单位的领土，10个国王币，拥有一个袋子，袋子里有一只肉包一个魔法丸子，一瓶恢复血量，一瓶恢复魔法值，拥有初始技能——普通攻击和快速闪避（波吉的拿手技能），快速闪避有在新手保护期才能使用，当等级到达10级之后将不能再使用

#### 等级介绍

每位国王的初始等级为1，初始经验值为0，经验公式为
$$
100+i*((i+10)/10)*10
$$
升级之后经验需要清零。随着等级的增长，你会解锁**新的技能**，**提升你的基础属性**，获得全新的奖励从而变得更强

| 等级 | 奖励 |
| ---- | ---- |
| 1    |      |
| 2    |      |
| 3    |      |
| 4    |      |
| 5    |      |
| 6    |      |
| 7    |      |
| 8    |      |
| 9    |      |
|      |      |
|      |      |
|      |      |
|      |      |
|      |      |
|      |      |
|      |      |
|      |      |
|      |      |
|      |      |

#### 武器介绍

武器主要有五大属性，伤害值，最大可承受值，当前的磨损量，每次使用一次的磨损量和重量。每件全新的武器磨损量最初为100，每参加一次战斗会造成一定的磨损量

> 以下的磨损量为每次使用会消耗一次磨损量，重量多少颗星即为多少单位重量，攻击力为附加的攻击属性。造成的伤害值计算公式为
>
> 人物的攻击力×武器的攻击力

大棒子

> 是伯斯王的武器

- 攻击力：🌟🌟🌟🌟
- 磨损量：🌟🌟🌟🌟🌟
- 重量：🌟🌟🌟🌟🌟

长枪

> 伯斯王国”王之枪“的武器

- 攻击力：🌟🌟
- 磨损量：🌟🌟🌟
- 重量：🌟🌟🌟🌟

蛇矛

> 伯斯王国“驭蛇者”的武器

- 攻击力：🌟🌟🌟
- 磨损量：🌟🌟🌟
- 重量：🌟🌟🌟

魔杖

- 攻击力：🌟🌟
- 磨损量：🌟
- 重量：🌟🌟

影刃

- 攻击力：🌟🌟🌟🌟
- 磨损量：🌟🌟
- 重量：🌟🌟

细剑

> 波吉的武器

- 攻击力：🌟🌟🌟🌟🌟
- 磨损量：🌟🌟
- 重量：🌟

#### 敌人介绍

戴达：

> 伯斯王国的二王子。波吉的同父异母的兄弟。

- 最大生命：100
- 击败获得的经验值：20
- 击败获得的钱：10
- 技能：

卡克：

> 被根绝的暗杀集团“影子一族”的幸存者。以盗窃为生。

- 最大生命：150
- 击败获得的经验值：50
- 击败获得的钱：20
- 技能：

多玛斯：

> 伯斯王国的四天王“剑圣”。波吉的剑术导师。

- 最大生命：250
- 击败获得的经验值：100
- 击败获得的钱：50
- 技能：

阿匹斯：

> 伯斯王国的四天王“王之枪”。发誓向伯斯王效忠的用枪高手。

- 最大生命：250
- 击败获得的经验值：150
- 击败获得的钱：50
- 技能：

贝宾：

> 伯斯王国的四天王“驭蛇者”。戴达的剑术导师。

- 最大生命：250
- 击败获得的经验值：350
- 击败获得的钱：50
- 技能：

德鲁西：

> 伯斯王国的四天王“王妃之盾”。希琳的护卫。

- 最大生命：250
- 击败获得的经验值：500
- 击败获得的钱：50
- 技能：

霍库洛：

> 伯斯王国的士兵。仰慕波吉的青年。

- 最大生命：150
- 击败获得的经验值：100
- 击败获得的钱：20
- 技能：普通攻击

伯斯：

> 伯斯王国的国王，波吉和戴达的父亲。国王排名第七位。

- 最大生命：500
- 击败获得的经验值：1000
- 击败获得的钱：100
- 技能：

魔镜：

> 神秘的boss

- 最大生命：1000
- 击败获得的经验值：1500
- 击败获得的钱：200
- 技能：

德斯哈：

> 冥府之王，国王排名第二位。

- 最大生命：750
- 击败获得的经验值：1000
- 击败获得的钱：300
- 技能：

德斯帕：

> 冥府之王・德斯哈的弟弟。

- 最大生命：500
- 击败获得的经验值：1250
- 击败获得的钱：250
- 技能：

#### 背包介绍

每个人初始都会拥有一个背包，背包的容量为**10**单位，可承载10个单位重量的物品，每升十级可扩大背包单位两个单位，也可以通过购买背包扩容增加背包的单位，上限背包容量为**30**单位。

#### 道具介绍

肉包

- 每次使用恢复血量百分之五十
- 重量为3单位

魔法丸子

- 每次使用恢复魔法值百分之五十
- 重量为3单位

#### 技能介绍

普通攻击：

- 伤害值：造成人物基础伤害*武器的伤害值的伤害值
- 耗魔量：每次使用不耗魔法
- 技能描述：只是普普通通的攻击

快速闪避：

- 伤害值：无
- 耗魔量：每次使用消耗魔法值10个单位
- 技能描述：每次使用可以直接结束战斗，快速逃跑

治疗术：

- 伤害值：无
- 耗魔量：每次使用消耗魔法值20个单位
- 技能描述：每次使用可以恢复全部血量

#### 经济模型

国王排名的世界里的货币是国王币，平原里会随机出现商城，你可以在商城购买道具等，每次战斗击杀敌人也可以获得国王币。

#### 排名系统

排名榜，根据国王的实力进行前七名国王的排名

#### 帮助系统

输入help，加-xx

输出一些信息

### 剧情介绍



### 简单代码功能阐述

#### 类的框架

目前我们完成的类的框架有人物相关的人物基类（Role）、国王（King）和敌人（Enemy），技能相关的技能基类（Skill）、攻击类技能（AttackSkill）和辅助类技能（SupportSkill），背包类（Bag）、物品相关的物品类（Item）、武器（Weapon）和药品（Medicine），地图相关的地图类（Map）和土地类（Field）。

我们设定：对于每块土地都是一个边长为fieldSize的正方形，而地图中一开始包含100块土地，每一位新玩家加入游戏就会扩展出一块新的土地并且这块土地将成为他的初始领地。

```cpp
// 人物相关
class Role {
protected:
    string name;
    int level;
    int maxHP; //最大生命
    int HP; //现有生命值
    int maxMP; //最大魔法值
    int MP; //现有魔法值
    Position position; // 当前位置
};
class King : public Role {
private:
    int experience; //当前的经验值
    Bag bag;
    vector<Skill*> skills;
};
class Enemy : public Role {
private:
    int experienceVal; // 得到的经验值
    int moneyVal; // 得到的钱
    vector<Skill*> skills;
};
// 技能相关
class Skill {
protected:
    string name; // 技能名
    string description; // 技能介绍
    SkillId id; // 技能类型
};
class AttackSkill : public {
private:
    int damageValue; // 伤害
};
class SupportSkill : public Skill {
private:
    int HPValue; // 回血量
    int MPValue; // 回魔量
};
// 背包相关
class Bag {
private:
    int level; // 背包等级
    int weightLimit; // 重量上限
    int curWeight; // 当前重量
    vector<Item*> items; // 保存的物品
};
// 物品相关
class Item {
protected:
    string name; // 物品名称
    int weight; // 物品重量
    ItemId id; // 物品类型
    string description; //物品介绍 
};
class Weapon : public Item {
private:
    int damageValue; // 伤害值
    int maxAbrasion;
    int abrasion;
    const int abrasionLoss; //每使用一次的磨损量
};
class Medicine : public Item {
private:
    int HPValue; // 回血量
    int MPValue; // 回魔量
};
// 地图相关
class Map {
private:
private:
    vector<Field*> fields;
}
class Field {
private:
    int field[fieldSize][fieldSize];
}
```

除了以上类的框架设计，我们目前具体实现了以下功能函数。

首先是终端中文字的输出样式设计，主要是使用ANSI控制符来输出，这里设计了一个名为style的manipulator，并使用template来实现不同的格式类型，包括颜色、斜体等。

```cpp
template<int ansiStyle = 0>
ostream& style(ostream& out) { 
    return out << "\033[" << ansiStyle << "m"; 
}
```

由此实现以下功能，分别是打印标题，打印问题（蓝色），打印奖励信息（黄色），打印警告（红色），以及一个自己的输入函数，Input函数中会判断输入是否为"quit"以退出游戏。

```cpp
static void PrintTitle();
    
static void PrintText(string s, string end = "\n") { cout << s << end; }
static void PrintRequest(string s, string end = "\n") { cout << style<CYAN_> << s << style<RESET_> << end; }
static void PrintReward(string s, string end = "\n") { cout << style<YELLOW_> << s << style<RESET_> << end; }
static void PrintWarning(string s, string end = "\n") { cout << style<RED_> << s << style<RESET_> << end; }

static string Input() {}
```

实现后的效果如下。

![image-20220507230306326](G:\onedirive\OneDrive - zju.edu.cn\computer_science\oop\KingRank\Report\《国王排名》MUD M2报告.assets\image-20220507230306326.png)

创建国王的InitKingGen函数。

```cpp
King RoleGen::InitKingGen() {
    string name;
    TextGen::PrintRequest("What's your name, young King?");
    name = TextGen::Input();
    return King(name);
}
```

#### 文件框架

我使用如下的文件框架来组织文件，并使用CMake来编译文件，具体的CMakeList.txt可以参考其中的文件。关于工程的编译和运行请参考ReadMe。

```
-src // 保存源文件
	-CMakeList.txt
-include // 保存头文件
    -common // 保存typedef、define、namespace相关类
        -Macro.h // 保存宏定义
        -Global.h // 保存全局变量及静态变量
        -Config.h // 保存文件配置
    -utils // 保存工具类
-thirdparty
CMakeList.txt
ReadMe.md
```

#### 编程规范

在这里列出一些主要需要注意的编程规范。

1. 命名：变量小驼峰，类名、函数名大驼峰
2. 不使用using namespace std; 推荐using std::cout; using std::string;
3. 注释使用Doxygen规范