前置操作：
```MySQL
alter table SPJ drop constraint fk_sno;
alter table SPJ drop constraint fk_pno;
alter table SPJ drop constraint fk_jno;
alter table SPJ add constraint fk_sno foreign key(SNO) references S(SNO) on delete cascade on update cascade;
alter table SPJ add constraint fk_pno foreign key(PNO) references P(PNO) on delete cascade on update cascade; 
alter table SPJ add constraint fk_jno foreign key(JNO) references J(JNO) on delete cascade on update cascade;
```
[1] 找出所有供应商的姓名和所在城市。
[2] 找出所有零件的名称、颜色和重量。
[3] 找出使用了供应商S1所供应的零件的工程号码。
[4] 找出工程J2使用的各种零件的名称和数量。
[5] 找出上海供应商供应的所有零件的零件号码。
[6] 找出使用了上海供应商供应的零件的工程名称。
[7] 找出供应工程J1零件的供应商号SNO。
[8] 找出供应工程J1零件P1的供应商号SNO。
[9] 找出供应工程J1红色零件的供应商号SNO。
[10] 找出没有使用天津供应商生产的红色零件的工程号JNO。
[11] 求所有有关project 的信息。
[12] 求在北京的所有project 的信息。
[13] 求为project（工程）J1 提供part（零件）的supplier（供应商）的号码。
[14] 求数量在300 到750 之间的发货。
[15] 求所有的零件颜色 / 城市对。注意：这里及以后所说的“所有”特指在数据库中。
[16] 求所有的supplier-number / part-number / project-number 对。其中所指的供应商和工程在同一个城市。
[17] 求所有的supplier-number / part-number / project-number 对。其中所指的供应商和工程不在同一个城市。
[18] 求由北京供应商提供的零件的信息。
[19] 求由北京供应商为北京工程供应的零件号。
[20] 求满足下面要求的城市对，要求在第一个城市的供应商为第二个城市的工程供应零件。
[21] 求供应商为工程供应的零件的号码，要求供应商和工程在同一城市。
[22] 求至少被一个不在同一城市的供应商供应零件的工程号。
[23] 求由同一个供应商供应的零件号的对。
[24] 求所有由供应商S1 供应的工程号。
[25] 求供应商S1 供应的零件P1 的总量。
[26] 对每个供应给工程的零件，求零件号、工程号和相应的总量。
[27] 求为单个工程供应的零件数量超过350 的零件号。
[28] 求由S1 供应的工程名称。
[29] 求由S1 供应的零件颜色。
[30] 求供应给北京工程的零件号。
[31] 求使用了S1 供应的零件的工程号。
[32] 求status 比S1 低的供应商号码。
[33] 求所在城市按字母排序为第一的工程号。
[34] 求被供应零件P1 的平均数量大于供应给工程J1 的任意零件的最大数量的工程号。
[35] 求满足下面要求的供应商号码，该供应商供应给某个工程零件P1 的数量大于这个工程被供应的零件P1 的平均数量。
[36] 求没有被北京供应商供应过红色零件的工程号码。
[37] 求所用零件全被S1 供应的工程号码。
[38] 求所有北京工程都使用的零件号码。

[39] 求对所有工程都提供了同一零件的供应商号码。
[40] 求使用了S1 提供的所有零件的工程号码。
[41] 求至少有一个供应商、零件或工程所在的城市。
[42] 求被北京供应商供应或被北京工程使用的零件号码。
[43] 求所有supplier-number / part-number 对，其中指定的供应商不供应指定的零件。
[44] 向p表追加如下记录（P0,PN0,蓝）。
[45] 把零件重量在15到20之间的零件信息追加到新的表p1中。
[46] 向s表追加记录（s1, n2, ’上海’）能成功吗?为什么？
[47] 把s、p、j三个表中的s#,p#,j#列进行交叉联接，把结果追加到spj1表中（如果只考虑下面表格中的原始数据，应该在spj1表中追加多少条记录？你是如何计算记录条数的？）。
[48] 向spj表追加（s6,p1,j6,1000）本操作能正确执行吗？为什么？如果追加(s4,p1,j6,-10) 行吗？如果现在想强制追加这两条记录该怎么办？
都不能，第一个是有外键约束，第二个是不能小于0，去掉外键约束和检查约束就行
条件约束：
```MySQL
alter table SPJ drop constraint fk_sno;
alter table SPJ drop constraint fk_pno;
alter table SPJ drop constraint fk_jno;
```
检查约束：
``` 
alter table SPJ drop check SPJ_chk_1;
```
[49] 把s1供应商供应的零件为p1的所有项目对应的数量qty改为500。
``` 
update SPJ set QTY = 500 where SNO = 'S1' and PNO = 'P1';
```
[50] 把qty值大于等于1000的所有供应商城市更改为‘北京’ 。
``` 
update S inner join SPJ on SPJ.SNO = S.SNO and SPJ.QTY >= 1000 set S.CITY='北京'; 
```
[51] 把j1更改成j7，本操作能正确执行吗？为什么？如果改成j0呢？spj表中记录有何变化？为什么？
不能，存在primary key冲突
可以，SPJ表里的J7也会改变

[52] 把零件重量低于15的增加3，高于15的增加2。
``` 
update P set WEIGHT = WEIGHT + 3 where WEIGHT < 15;
update P set WEIGHT = WEIGHT + 2 where WEIGHT > 15;
```
[53] 删除为j7工程供应零件的所有供应商信息（如果建立外键时没有带级联删除选项，本操作能正确执行吗？为什么？）
```MySQL
delete S from S,SPJ where SPJ.JNO='J1' and SPJ.SNO = S.SNO;
```
不能正确执行
[54] 删除p1表中所有记录。
```MySQL
delete P from P where P.PNO = 'P1';
```
[55] 删除供应商和工程在同一个城市的供应商信息。
```MySQL
delete S from S,J,SPJ where S.CITY = J.CITY and S.SNO = SPJ.SNO and J.JNO = SPJ.JNO;
```
