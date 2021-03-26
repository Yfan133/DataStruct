/*
面试问题：
	1.什么时候进行扩容？
		1.闭散列(开放定制法)：数组vector
			原理：
				当发生哈希冲突时，如果哈希表未被填满，说明哈希表中还有空位置，把key存放到冲突的下一个空位置当中去
			位置寻找：
				线性探测：从冲突位置开始依次向后面进行探测，直到寻找到下一个空位置为止
					缺点：所有冲突都向后偏移，则容易产生数据的堆积，造成不同关键码占用可用空位置，使得需要多次比较，导致搜索效率降低
				二次探测：
			扩容时机：
				1.线性探测的负载因子控制在 0.7，二次探测的负载因子控制在 0.5 ~ 0.6
				2.当负载因子超过0.7时，查表时的CPU缓存不命中按照指数曲线上升，因此需要resize散列表
					负载因子 = 填入表中的元素数量 / 散列表的长度
		2.开散列(链地址法)：本质：指针数组(vector) + 单链表
			原理：
				当发生哈希冲突时，将冲突节点进行头插到链表
			位置寻找：
				直接头插
			扩容机制：
				1.当哈希表中有效元素个数 = 哈希表数组的长度时，开链法控制负载因子 = 1，需要进行扩容

	2.怎么扩容？(注意取模新的size，原空间元素位置发生改变)
		1.闭散列(直接定址法)：
			1.新建一个容量为2*size的哈希表，并将旧表中的元素插入到新表中
			2.交换两个变量，因此扩容函数结束时会释放临时变量(vecotr)
		2.开散列(链地址法)：(没有必要新创建哈希节点，直接将原始指针数组中的节点链接到新数组中)
			1.创建一个容量为2*size的哈希表(vector)，并且将旧表中的哈希节点插入到新表中
			2.交换两个变量，因此扩容函数结束时会释放临时变量
		3.提供素数表：(容量为素数)
			原因：只能被1和本身整除，因此造成哈希冲突的可能性降低


	3.怎么查找？
		1.闭散列：
			1.通过哈希函数计算哈希位置，从哈希位置开始寻找如果为空都没找到则返回 nullptr

	4.怎么删除？

	5.为什么闭散列的负载因子控制在0.7，而开散列控制在1，甚至1以上？
		因为开散列就算产生了哈希冲突，也不会占用其他元素的位置
		从整体来说：开散列所用到的空间比闭散列要小，并且不会产生数据堆积

看到 1.43 封装 unordered_map
如果遇到字符串，需要对字符串进行转换

*/

/*
补充：适合数据量比较小
	1.跳表：搜索时间复杂度：O(logN)--->有序--->双向链表的基础上进行的改造
	  跳表特性和红黑树很像
	2.trie树--->字典树--->找字符串前缀

数据量比较大：海量数据保证快速查找：在数据的基础上建立索引
	索引：也是一种数据结构，从索引是否会发生改变分为：静态索引和动态索引
		静态索引：索引结构不会发生改变--->书籍的目录结构
		动态索引：索引结构可能发生变化
			最常见的数据结构：B树


哈希：查询时间复杂度：O(1)
	存储数据时，将数据与其存储结构之间建立一种一一对应的映射关系，查找时再按照该映射关系进行查找
	插入：
		1.使用data % 表格容量来计算元素应该放在表格的什么位置
		2.将data插入到表格的pos位置
	查找：
		1.使用data % 表格容量pos--->data应该在表格的pos
		2.在表格的pos位置检测是否为data元素
哈希冲突(碰撞)：不同元素在插入哈希表中时，通过哈希函数计算出了相同位置。
	哈希冲突是一定要被处理的，否则：可能会破坏哈希结构或者影响查找结果
解决哈希冲突：
	1.哈希函数：哈希函数设计是否合理，如果不合理则重新设计
		1.哈希函数的值域一定要在表格的范围之内(防止取模之后还是越界)
		2.哈希函数产生的哈希地址要尽可能均匀
		3.哈希函数要尽可能简单
	  常见哈希函数：
		直接定址法：线性函数：HashPos = Ax + B
			适用场景：数据量小，且连续
	  注意：
		哈希冲突只能降低出现概率，但是不能绝对避免
	2.处理哈希冲突的方式：
		1.闭散列：从发生哈希冲突的位置开始，找下一个空位置插入
			方法：
				1.线性探测：逐字的往后找位置，查找到哈希表末尾时，如果还没找到，要重新定位到数组首部
					线性探测的缺点：容易产生数据的堆积(堆在一坨)
					插入规则：(三种位置状态)
						1.通过哈希函数找到相应位置
						2.循环判断当前位置状态是否为空
							如果为空则插入，并将状态改成EXIST
							如果不为空：继续向后检查
					删除规则：
						1.将位置的状态设置为delete
				2.二次探测(以平方探测)：pos1 = pos0 + 2i+1
					找位置方法和线性探测不同：当前位置=上次位置+2i+1
					注意：超过容量之后要取模容量大小
		哈希负载因子：有效元素的个数 / 表格总容量
		一般情况下线性探测的负载因子控制在 0.7，二次探测的负载因子控制在 0.5 ~ 0.6
		哈希优点：查询速度O(1)
		缺点：空间利用率低
		
		2.开散列：链地址法，原理：链表集合将发生冲突的元素挂在同一个链表中，哈希表中没有直接存储元素，而存储的是链表首节点的地址
		
*/

/*
位图：
	1.开辟位图：

	1.整数的位置(哪一块位图)：n / 32
	2.整数位置中具体的bit位置(位图的哪一个位置)：n % 32
获取某个bit位置的值：
	整数 >> (x - 1) & 1
位图：
	适合场景：大数据量，数据不重复，存放信息简单，非负数

布隆过滤器：
	场景：怎么区分垃圾邮件 或者 抖音视频重复内容的过滤？
	解决：记录之前出现过的元素
	记录方法：位图：查询效率高并且存储空间要求小，把对应位置置1，如果出现重复则过滤
	缺点：数据不能重复，并且必须是整数数据
	原理：
		1.首先视频标题等是字符串类型
		2.将字符串用哈希函数转化为整数类型，再将位图对应位置 1
			缺点：可能哈希函数可能映射同一整数，产生冲突
	
	引出：布隆过滤器
	概念：通过多个位置的映射存储元素位置
	特点：概率型数据结构，99%情况下是正确的，1%可能失败
		绝对正确：如果位图中相应位置都0，则说明数据没有出现过，绝对正确
		可能错误：如果位置中找到了几个映射位置都是1，该数据不一定存在
			原因：可能是其他的映射，将该位置 1 。根本原因：存在哈希冲突
	原理：
		1.通过多个哈希函数，映射多个位置，并将多个位置都置1
		2.因此：映射位置越多，则发生哈希冲突的概率越小
	查找：
		1.通过多个哈希函数，检查多个位置



*/