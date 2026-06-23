# 设计说明

## 设计目标

本项目实现一个命令行版本的工厂工具管理信息系统，重点满足课程设计中的类封装、容器使用、文件持久化、输入校验和菜单交互要求。

## 模块划分

### `Tool`

工具信息类，负责保存和修改单个工具的数据。

核心字段：

- 工具编号
- 工具名称
- 工具类型
- 当前库存数量
- 工具状态
- 已借出数量
- 仓库存放位置
- 工具单价

主要接口：

- `modifyInfo()`：修改除编号外的工具信息
- `borrowTool()`：借出工具并更新库存
- `returnTool()`：归还工具并恢复库存
- `serialize()` / `deserialize()`：文件存储和加载

### `BorrowRecord`

借还记录类，负责保存单条借用信息。

核心字段：

- 借用记录编号
- 工具编号
- 借用人姓名
- 借用日期
- 应还日期
- 借用数量
- 借用状态

主要接口：

- `markReturned()`：修改借用状态为已还
- `serialize()` / `deserialize()`：文件存储和加载

### `FactoryToolSystem`

系统控制类，负责菜单、业务流程、文件读写和统计分析。

核心容器：

- `std::vector<std::unique_ptr<Tool>> tools`
- `std::vector<BorrowRecord> records`
- `std::map<std::string, Tool*> toolIndex`
- `std::set<int> unreturnedRecordIds`

## 数据结构说明

### `std::map<std::string, Tool*>`

`toolIndex` 使用工具编号作为键，工具对象地址作为值。

这样可以快速判断编号是否存在，也可以快速定位对应工具对象进行修改、删除和借还库存同步。

### `std::set<int>`

`unreturnedRecordIds` 保存所有未归还的借还记录编号。

归还时先检查该编号是否存在于集合中，归还成功后再从集合中删除。

## 文件持久化

系统使用文本文件保存数据，每条记录一行，字段之间使用 `|` 分隔。

运行时文件：

- `tools.dat`
- `borrow_records.dat`
- `statistics.txt`

启动时自动加载 `tools.dat` 和 `borrow_records.dat`，退出时自动保存全部数据。

## 排序与分页

所有分页展示默认每页 10 条。

借还记录按借用日期倒序显示。如果日期相同，记录编号较大的记录排在前面。

借用次数排行按次数从高到低排序，如果次数相同，则按工具编号升序排序。

## 输入校验

公共输入函数集中在 `Utils.cpp` 中，主要负责：

- 去除首尾空白
- 校验整数
- 校验金额
- 校验日期格式
- 禁止空字符串
- 禁止字段中出现分隔符 `|`

这种拆分可以减少菜单业务代码中的重复校验逻辑。
