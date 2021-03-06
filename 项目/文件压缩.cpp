/*
文件压缩概念：
	在不丢失重要信息的前提下，按照一定算法对文件数据重新组织，减少数据冗余和存储空间，以提高文件传输效率和存储效率
无损压缩：
	压缩文件能够恢复到压缩前完全相同的格式，没有信息损失
有损压缩：
	对于一些人类不敏感数据(例如：图像和声波)，允许文件压缩过程中损失一定的信息。虽然不能完全恢复原始数据，但换取了大的多的压缩比。
常见压缩方式：
	1.将重复的字符用更短的内容进行替换：(LZ77压缩算法的实现)
		采用<长度，距离>键值对的方式，放在重复字符的地方，直接到前面去寻找
	2.用bit位代替字符：获得更短的结果
		1.固定长度编码：ABBB CCCC CDDD DDDD(四种字符四个状态)
			A:00  B:01  C:10 D：11
			压缩前：16字节
			压缩后：00010101 10101010 10111111 11111111 4字节
		2.利用哈夫曼树(变长编码)：按字符出现次数，将出现较多次的字符替换成较短比特位
			A:100 B:101 C:11 D:0
			压缩后：10010110 11011111 11111100 00000  3字节 + 5bit

GZIP压缩算法原理：
	1.先使用LZ77压缩算法对源文件进行第一次压缩，将重复语句压缩
	2.再使用哈夫曼编码再次进行压缩，得到结果

构造一棵哈夫曼树：
	特点：
		1.所有带权值的节点都是叶子节点

	方法：
		1.创建一个数组，数组的元素都是以权值为根节点的树(无左右孩子)，则数组就是是森林
		2.从数组中取最小的两个权值节点，构造一个二叉树，根节点为权值和。
		3.删除刚构造的两个节点，并插入新树。   重复构造，并删除
		4.最终数组中剩下一颗二叉树，哈夫曼树

哈夫曼树压缩原理：
	1.统计所有字符的出现次数，存放到一个数组中
	2.用数组构造堆
	3.构造哈夫曼树
*/

/*
哈夫曼树
	二叉树节点：
		左右子树
		构造：
			左右指针为空
	哈夫曼树
		重命名：节点类型
		构造：
			空树
		创建哈夫曼树：用一个数组
			小堆
*/

/* 新增：日志信息，打开文件失败。。。
哈夫曼树的节点类型是：结构体 CharInfo
	结构体：
		1.字符类型
		2.字符出现的频率(unsigned long long)
		3.对应编码(string)
	重载 +
		构造一个匿名对象并返回
	重载 > ：注意this对象要const修饰
		返回两个出现次数的大小

哈夫曼压缩
	1.用数组存储所有256个字符的结构体，供后续操作

	2.初始化字符数组

	3.压缩文件函数：(传入文件名)
		1.打开文件，注意判断是否成功打开
		2.读取，注意判断返回值，若返回值为0，则说明已经读完了
		3.创建树，编码
		4.用编码对源文件的每个字符进行重写
			1.重定向文件流指针到文件首
			2.读取数组中对应的字符串
			3.一次八位的，将每个字符串的内容写入文件，不需要对无符号char重新置0，因为每8位一写
		注意：若最后不够8比特则没有写入文件，因此退出循环之后要检测
			例如：最后只有7位，因此一个比特只有低7位有效，最高位无效。
		做法：
			1.左移(8-bitCount)位，因此最低位是无效位
*/
// 256个字符，数据在文件中是以字节方式存储的，最大255
/*
1.程序崩溃原因：
	char 类型的大小：-128 ~ 127，最高位是符号位，因此当
	使用 unsigned_char大小：0 ~ 255
2.不友好的地方：
	1.创建树的时候，应该传入不可靠节点(否则不符合模板编程思想)
	2.编码的时候直接给数组中的root->对应ch赋值了，不符合模板编程思想
3.为什么不会出现一个编码是另一个编码的前缀？
	叶子节点
4.为什么进行编码改写时，要判断是否到达八位？(无符号char类型)
	这样理解：如果超过八位，先将八位写入文件，然后再继续写剩下的位数
	因为：8位是一个字节(字符)，换算对应编码！
*/

/*
哈夫曼解压缩：
	1.从压缩文件中获取每个字节
	2.对每个字节，逐比特位进行遍历哈夫曼树，如果到达叶子节点说明完成一次匹配
		因此压缩文件中要保存哈夫曼树的信息：
		XXX.cpp	    文件名
		5	  -->	多少个叶节点
		A,1   -->	元素类型+出现频次
		B,3
		C,5
		D,9
	3.将完成匹配的字符插入文件，若解压缩的文件大小和源文件相同(即根节点的权值大小)，则停止解压缩

具体操作：
	1.打开压缩文件，一行一行的去读：先读取文件名，再读取 size
		GetLine():
			feof(fp)		->  判断是否已经走到末尾
			ch = fgetc(fp)  ->  一个个读取字符
		如果读到 \n ，则跳出循环
	2.读取压缩的内容，对读取的内容进行8比特位逐字句检查
		如果 chBit & 0x80 == 1，则走右树，否则走左树

	3.判断 file_size == 0时，后面的比特无效，跳出循环

遇到的问题：
	1.当遇到换行时，解压缩出来的结果是错误的
		换行时读取出来的是：空字符串，因此对空字符串做特殊处理
		比较工具：byond compare
	2.当文件中有中文时：越界
		原因：还是因为以数字为下标时为负数，因此越界
		解决：对下标进行urg强转
	3.文件以"r"打开文件时，只解压缩了一部分，后面的内容内有进行解压缩
		原因：若以文本打开，则遇到全1时，读取回去的是-1。
			注：文本文件不会出现全1，但二进制文件会出现全1的情况。
			存在某个字节8比特位全是1，比如8个D，以文本方式打开读取返回-1，系统会认为已经读到了文件末尾
		根本原因：文本方式读取是读的 char 类型，而不是unsigned char，而文本遇到FF会停止
		解决：
			压缩和解压缩都以二进制方式读写

	自己测试：在文本中全是FF看结果。

	4.影响压缩效率的几种情况：
		1.树的高度大于8的情况下：字符的编码反而大于1字节。
		2.如果字符的种类较多，并且字符出现的数量比较均匀。 例如：ABCDEFG，出现平衡树
	
范式Huffman树进行优化：
	规则：
		1.叶节点都是左树
		2.

	作用：对压缩时保存字符和个数进行优化
		1.只需要保存位长
		2.因此降低了

	解码：
		1.同一层：编码只需要 + 1
		2.不同层：(上一层的最小编码 + 上一层元素个数) <<= 1 

范式树压缩后文件中
	存放255个字符的出现次数

问题：
	1.压缩率？？
	2.二次压缩？会不会越压越大？

*/

/*
LZ77压缩算法：
1.原理：将原文中重复出现的语句使用更短的<长度，距离>对来进行替换，可以达到压缩目的

2.设计：
	1.替换对设计：<长度:8位，偏移量:15位>

		1.长度为1字节(3~258)，偏移量为 15 比特：
			偏移量设计：距离最大是32768(也就是一半长度的缓冲区)，但是一般不会出现65536的长度重复32768，也就是重复了一半数据
			因此：一个替换对总大小：15比特(距离) + 8比特(长度) = 23比特
						                         三个字符总大小：24比特
			结论：若距离当前位置32768(32k)位置以内，出现三个字节以上重复，则进行替换

	2.内存缓冲区大小：64k = 65536 字节 
		(为啥要64k，首先不能太小：因为会增加IO次数，影响效率。但也不能太大，硬件环境不支持)
		1.以start将内存缓冲区分两个区间：查找缓冲区和先行缓冲区
			MIN_MATCH = 3字节									(最小匹配字符)
			MAX_MATCH = 258字节									(最大匹配字符)
			MIN_LOOKHEAD = MAX_MATCH + MIN_MATCH + 1 = 261;		(先行缓冲区的最小值)
			WSIEZE = 32K --> 0x8000								(滑动窗口大小)
		2.滑动窗口大小：WSIZE = 32K
			整个匹配是在一个滑动窗口中进行的，start往后偏移时，就相当于滑动窗口向后偏移

3.查找算法 + 数据结构：如何快速进行查找匹配？
	暴力匹配：从后面开始向前匹配，效率太低
	哈希表方式：用数组去模拟链表的开链法
		具体方法：每三个字符一组，将首字符的下标保存在哈希中

	1.哈希表：64K的大小
		两个区间：prev区间：0~32k   head区间：32~64k，解决冲突缓冲区 和 存储地址缓冲区
		prev用于解决哈希冲突  head用于查询哈希地址
	
	问题：
		1.为什么不用链表？
			答：用数组的方式可以大大节省空间只需要64k的 short 类型，链表的话指针域4字节太浪费空间
		2.为什么要两个哈希分区，并且都是32k ？
			答：和缓冲区呼应，匹配完成的字符丢弃到prev区间，新匹配的字符串放到head区间
*/

/*
代码：
插入算法：参数：
		hashAddr：哈希地址
		ch：三个字符的第三个
		pos：首字符的下标
		matchHead：匹配串的起始地址
	1.先计算哈希地址，hashAddr
	2.给 prev[pos] 位置上赋上值 head[hashAddr]
	3.给上一次匹配串的地址 matchHead 赋上值 head[hashAddr]
	4.给 head[hashAddr] 重新赋值为 pos (新匹配串的位置)

	小结：
		1.刚进来时，head[hashAddr] 记录的是上次匹配字符串的首地址
		2.则需要解决冲突，重新把上次匹配的首地址赋到 prev 空间的 pos 位置： prev[pos]
		3.pos & mask 原因：防止因为 pos 跑到滑动窗口的高地址，造成哈希表这里的 prev[pos] 跑到head空间里去
			后果：1.可能&之后的位置是其他链的节点，更甚者造成环型结构
			解决：在查找时，用一个计数(大小为32k)，每跳一次则计数--，当计数为0时说明有环则跳出

哈希表：
	成员变量
		ush* prev
		ush* head
	哈希桶的个数：15

插入哈希表：
	1.计算哈希地址
		怎么计算？

	2.找位置进行插入
		1.先把上次匹配的字符串位置 head[hashAddr] 赋值到prev[pos]
		2.然后将match 赋上上次匹配位置
		3.最后给head[hashAddr]赋值上新匹配字符串位置 pos
			为了防止pos越界，位置 pos & 7FFF：
				1.可能造成源数据被覆盖
				2.可能造成链表成环
			解决：设置一个最大匹配次数，若超过次数，则直接退出

*/
/*
LZ77：
成员变量：
	uch* pwind		64K缓冲区

成员函数：
	压缩文件：
		1.打开文件，判断如果文件内容小于6字节，则不进行压缩(重复是按3字节重复压缩的)
		2.将前两个字节预插入
		3.判断 match
			如果 match == 0，则没有匹配到
			如果 match != 0，则寻找最长匹配LongestMatch()
最长匹配：传入 matchHead查找起始位置， start 匹配起始位置
	1.用两个指针，一个指向查找起始位置，一个指向匹配起始位置
		pScan
		PStart
	2.返回curDist	最长距离
		  curLength 最长长度

*/