# 设计模式

> Design Patterns

"每个模式描述了一个在我们周围不断重复发生的问题，以及该问题解决方案的核心。这样，你就能一次又一次地使用该方案而不必做重复劳动。" ————Christopher Alexander

设计模式主要描述的是类与相互通信的对象之间的组织关系，包括它们的角色、职责、协作方式等方面。

## 创建型设计模式

> Creational Patterns

将对象的部分创建工作延迟到子类或其他对象。

## 结构型设计模式

> Structural Patterns

通过类继承或对象组合获得更灵活的结构。

## 行为型设计模式

> Behavioral Patterns

通过类继承或对象组合来划分类与对象间的职责。

## 类模式与对象模式

- 类模式处理类与子类的静态关系
- 对象模式处理对象间的动态关系

## 应对变化，提高复用

现代软件设计的特征是“需求的频繁变化”，设计模式的要点是寻找变化点，然后在变化点处应用设计模式，从而更好的应对需求的变化。

什么时候，什么地点应用设计模式，比理解设计模式结构本身更为重要。

## 采用 Refactoring to Patterns 来使用设计模式

设计模式的应用不宜先入主，没有一步到位的设计模式，一上来就使用设计模式是对设计模式的最大误用。

## 重构关键技法

- 静态 -> 动态
- 早绑定 -> 晚绑定
- 继承 -> 组合
- 编译时依赖 -> 运行时依赖
- 紧耦合 -> 松耦合

