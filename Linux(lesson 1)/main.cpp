#include<iostream>
//Linux不以文件后缀区分，加后缀和颜色是为用户区分
//环境变量:就是一个变量,用于存储系统运行的环境参数
//操作指令:env set echo 查看环境变量 export 设置环境变量 unset 删除环境变量
//作用:
//1)通过修改环境变量的值,灵活的配置系统运行参数
//2)子进程会继承父进程的环境变量

///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Linux下以.为开头的文件默认不显示(隐藏文件)
//磁盘至少有两个分区：文件交换分区，文件系统分区（且交换分区只有一个，系统分区可以有多个）
//交换分区:作为交换内存使用，通常大小在16G以内，是内存的两倍，超过时相等即可
//文件系统分区：作为文件存储使用
//程序运行，运行信息占用的是内存，内存不够用了，把非活跃区内的数据放入磁盘上（文件交换分区）这样内存就有空间加载新的数据进行处理
//windows下磁盘分了多少分区，就可以有多少盘符，每个盘符都是一个大目录（给某个空间分配文件夹）
//linux下目录结构是惟一的，不会随着分区多少而改变（给某个目录分配空间）
//挂载是指：给某个目录分配一块磁盘空间，这个目录下的文件数据存储的时候就会存储到这个空间中

//目录操作
//绝对路径：以根目录作为起始表达的路径 例：./workspace/
//相对路径：是以某个路径
// .	表示目录自身
// ..	表示目录上一层
//mkdir -p 层层递进创建目录 rmdir -p 层层删除空目录(哪层为空就删除哪一层)
//rm -rf  删除目录及目录内所有文件
//批量删除以.h为后缀的文件 rm *.h
//cp -r  层层拷贝目录(文件)
//mv   (剪切)移动目录的位置

//文件操作
//touch  若文件不存在则创建，若存在则刷新文件的时间属性
//cat  分页显示文件内容
//head -n 显示文件前n行
//tail -n 显示文件尾n行
//echo  打印字符串，将数据写入标准输出(显示器设备文件)"sjk666" >> filename 把sjk666写入文件
//stat  查看文件状态
//>>或者>  重定向符号，进行数据流的重定向，文件重定向(echo "1" >> file将原本要写入标准输出的数据写入文件，改变数据的流向)
//>  先清空在输入数据
//>> 直接追加数据
//|  管道符连接两个命令（head -n 23 | tail -n 1）输出第12行

//打包指令
//压缩：将一个文件按压缩算法，将数据从多变少
/*
zip
gzip
bzip2
*/
//打包：将多个文件合并成一个文件
/*
tar  Linux下使用度很高的打包解包工具
-c打包 -x解包 -z打包同时进行gzip格式的压缩解压缩 -j打包同时进行bzip2格式的压缩解压缩 -v显示打包解包信息 -f用于指定tar包的名称，通常作为最后一个选项
tar -czvf new_name file	file				打包
tar -xvf  file(不加解包格式，则自动检测格式)	解包(默认解压到当前目录下)
*/
//单引号（会消除字符里特殊字符的特殊含义）双引号不会
//grep  从文件里查找匹配的行(文件里找函数)
//-v  反向匹配(不包含的行) -R  对某个目录进行层层寻找(每个文件都要查找)
//例：grep -i "sjk" ./op
//find  在目录中查找指定名称/大小/时间/类型的文件
//find ./ -name"*test*" (**为模糊匹配)  
//find ./ -type d 通过文件类型查找文件 -d -
//find ./ -size -10M  通过文件大小查找10M以内文件--+10M查找超过10M大小的文件
//find ./ -mmin -10  通过文件时间查找 --cmin,mmin,amin--分钟为单位
//
//		  -前面都有一个减号，为**以内
//tab  快捷键，文件名自动补全
//ctrl+c --中断当前操作

//shell的理解
//操作系统内核与用户之间的桥梁---命令行解释器
//shell会捕捉用户的标准输入，得到字符串，通过字符串判断用户想要干什么
//终端能执行命令就是因为运行了一个程序--shell--命令行解释器
//Windows下的shell就是操作界面(和操作内核沟通的桥梁)
//权限：限制用户权利的东西
//文件权限对用户：所有者-u，所属组-g，其他用户-o
//文件权限对操作：可读-r，可写-w，可执行-x
//在系统中权限的存储：使用二进制
// rw-rw-r--  --> 110 110 100  占用空间小，易操作
//也可以用八进制表示用户的权限110 110 100  --> 6 6 4

//文件访问权限指令
//umask -S(人性化显示) 查看或者设置文件的创建权限掩码
//umask 八进制掩码(显示的和权限八进制相反)，权限计算方法：777-八进制掩码
//创建好的文件进行权限修改
//chmod 777 hello.txt 直接使用八进制数进行修改
//chmod a-x hello.txt 对某个用户进行权限修改
//文件用户信息修改
//chown username filename 修改文件所有者(只能使用root修改)
//chgrp username filename 修改文件所属组
//文件权限沾滞位：特殊的权限位--主要用于设置目录沾滞位，其他用户在这个目录下能够创建文件，可以删除自己的文件，但不能删除别人的
//chmod +t filename

//vim 是一个命令行编辑器，不能使用鼠标(使用鼠标是无效的)
//vim具有多种操作模式：12种，常用的三种：插入模式，普通模式，底行模式
//普通模式：进行文本常见的操作-复制，剪切，粘贴，删除，撤销，返回，文本对齐，光标的快速移动
//底行模式：进行文本的保存退出，以及文本的匹配查找替换操作
//vim filename 若文件不存在创建，存在则打开，打开后处于普通模式
//:q!强制退出(不保存)
//i进入插入模式，a后移一个并插入，o新建一行并插入
//光标移动：hjkl上下左右，w/b按单词移动，ctrl+f/b上下翻页
//文本操作：yy/nyy-复制；p/P-粘贴,dd/ndd删除/剪切,x-删除光标所在字符,dw-删除单词
//u-撤销，ctrl+r-反撤销，gg=G--全文对齐

//编译器：gcc/g++
//gcc是C语言的编译器;g++是C++的编译器
/*编译过程											   -o 指定生成文件名称
预处理：将代码展开（引入头文件，宏替换，删除注释....） gcc-E filename 只进行预处理
编译：纠错，并将高级代码解释为汇编代码				   gcc-S		  只进行编译
汇编：将汇编代码解释成机器指令						   gcc-c		  只进行汇编
链接：将所有用到的机器指令文件打包到一起，生成可执行程序,不仅仅是我们的代码文件，还包括库文件(a.c文件引用了b.h中的函数)
*/

//链接库文件的时候有两种链接方式：动态链接与静态链接
//动态链接：链接动态库，在可执行程序中记录函数符号信息表，生成可执行程序比较小，但是运行时需要加载动态库，多个程序可以使用同一库，不会在内存中造成代码冗余
//静态链接：链接静态库，直接将使用的函数写入可执行程序中，生成的可执行程序比较大，运行时不需要额外加载库，多个程序使用了相同的静态库，运行时会造成内存的代码冗余
//gcc默认链接方式：动态链接
//gcc -g a.c b.h -o main
//调试器:gdb
//加载调试：gdb ./main
//开始调试：run  直接运行 start  逐步调试
//流程控制：n  下一步(逐过程)  s  下一步(逐语句)
//			l a.c:25  查看调试行附近代码  until a.c:25  直接运行到指定行
//			c 继续运行直到断点
//断点控制：break a.c:9  给第9行打断点  watch a  给变量打断点，当变量的值发生改变时停下来  d  删除断点
//内存操作：p a 查看变量数据 backtrace查看程序运行调用栈信息，程序一旦崩溃，查看调用栈可以快速定位崩溃位置--栈顶函数

//make/Makefile
//Makefile:普通的文本文件，用于记录
//$@:表示目标对象  main
//$^:表示所有依赖对象 a.c b.c
//$<:表示所有依赖对象中的第一个依赖对象
//wildcard/patsubst 关键字的使用
//make clean 清除make生成的对象
//伪对象的使用：
//.PHONY:目标对象名称
//伪对象的作用:不管对象是否最新，每次都要重新生成
//Makefile中
/*
.PHONY:clean
clean:
	rm -rf main.o main
*/

//git：项目版本管理工具
//1.git clone +链接  从远程仓库克隆到本地 
//2.git add ./*    添加本地文件
//3.git commit -m"删除了一个无效文件"  把文件保存到本地git
//4.git push origin master			   推送到git上

//进程概念：
//冯诺依曼体系结构---现代计算机的硬件体系结构
//现代计算机的硬件体系结构：五大硬件单元
//输入设备：采集数据的，如键盘
//存储器：进行中间数据缓冲， 
//运算器：进行数据处理  运算器+控制器=CPU中央处理器
//控制器：进行设备控制
//所有设备都是围绕存储器工作的：
//CPU不会直接从输入设备获取数据进行处理，而是先把数据放到存储器中，CPU从存储里中获取数据处理
//CPU不会直接将数据交给输出设备进行输出，而是把数据放入存储器，控制输出设备从存储器中获取数据并输出
//存储器就是运行内存，因为CPU从内存中读取数据速度是硬盘的十数倍。但内存中存储的数据在掉电之后就消失了，而硬盘掉电之后数据不会丢失，因此存储数据还是用硬盘。

//操作系统：是一个搞管理的软件（安装在计算机上的一个程序），管理计算机上的软硬件资源
//操作系统组成：内核(负责系统的核心功能-软硬件管理,内存管理,文件管理)+外部应用
//用户不能直接访问操作系统内核（危险性太高），为了控制风险，系统内核提供了一些访问的接口，每个接口完成的功能都是固定的---系统调用接口
//用户
//->系统调用接口：操作系统向用户提供访问内核的接口(shell指令,库函数封装了一系列系统调用接口)
//->操作系统
//->硬件驱动
//->（键盘鼠标等）


//什么是进程？为什么是这样？
//进程：进行中的程序，
//一个程序运行起来，有数据以及指令需要被CPU执行处理，数据会被加载到内存中，然后CPU从内存中获取数据
//操作系统中的进程都是同时运行的，但CPU只有一个，如何做到多个程序同时运行?
//CPU的分时机制：实现CPU轮询处理每一个运行中的程序，其实CPU只负责执行指令并处理数据（具体处理哪个程序CPU不管），而程序运行调度由操作系统进行管理，CPU处理运行的程序时，并不会一次性处理完毕，而是每个程序都只执行一个时间段(片)(该时间片由操作系统分配)，一个程序执行完一个时间片之后，下一个拿到时间片的程序开始执行
//调度：操作系统控制CPU该处理哪一个程序了

//操作系统的具体管理思路：操作系统将每个程序的运行信息保存下来,这样进行管理调度时就能知道这个程序上一次运行到了哪里
//对于操作系统来说，进程就是PCB，是一个程序运行的动态描述，通过PCB就能实现程序的运行的调度管理
//PCB内的描述信息：（Linux下的PCB就是一个struct task_struct结构体）
/*
内存指针：能够让操作系统调度程序运行的时候，知道程序对应的指令和数据在内存中的位置
上下文数据：CPU处理过的程序的指令和数据，正在处理中的指令和数据，即将要处理的指令和数据，操作系统进行调度让CPU处理程序上次未处理完成的数据，切换时保存正在执行的指令以及数据信息
程序计数器：也属于上下文数据，保存的就是指令位置，切换回来知道从哪里继续运行
标识符：能够让操作系统识别唯一的运行中的程序
IO信息,状态信息，优先级，记账信息
并发：CPU资源不够的情况下，采用CPU分时机制，CPU轮询处理数据（十个人过独木桥）
并行：多核CPU上，多个进程同时占据CPU进行数据处理（十个人并排过马路）
*/

//进程状态:每个进程PCB中都会描述一个运行的状态信息，通过状态信息，告诉操作系统这个进程现在应该干什么
//时间片：操作系统给每个程序分配的CPU处理时间，时间片运行完了就切换另一个程序
//进程状态：就绪，运行，阻塞(拿到时间片也不会运行)

//进程状态在Linux下分的更细
//(-R)运行状态-R：包含就绪以及运行，也就说正在运行的，以及拿到时间片就能运行的都称之为运行状态，操作系统读取PCB的状态信息之后就能调度运行
//休眠：暂时没有被CPU调度运行，让出CPU资源，休眠有唤醒条件，操作系统调度运行时会查看状态，满足唤醒条件则运行，不满足则切换下一个程序
//(-S)可中断休眠状态-S：可以被打断的休眠，满足运行条件或者被一些中断打断休眠之后进入运行状态
//(-D)不可中断休眠状态-D:只能通过满足运行条件之后，自然进入运行状态
//(-T)停止-T：与休眠不同(操作系统会查看进程是否满足唤醒条件，而停止只能手动唤醒)
//(-Z)僵尸状态-Z：一个进程已经退出，但是该进程的资源没有完全被释放，等待处理的一种状态
//僵尸进程：退出了但是资源没有完全释放的进程
/*
僵尸进程
危害：资源泄露（可能导致正常进程起不来）
产生原因：一个进程先于父进程退出，父进程没有关注子进程退出状态，导致子进程资源无法完全被释放，进入僵尸状态
解决：进程等待--一直关注子进程的状态

进程的创建：pid_t fork(void) --通过复制调用fork进程，创建一个新的进程
进程就是PCB，创建一个进程就是创建了一个PCB，上面复制调用了fork这个进程的PCB信息(内存指针，程序计数器，上下文数据)，新进程的运行代码和fork的一样，并且运行位置也一样
两个进程运行的程序相同：哪个是调用进程(父进程)，哪个是新建进程(子进程)？
在父进程中返回子进程的pid（pid_t pid=fork( )），大于0的；在子进程中返回0;但返回-1表示创建子进程失败

子进程从pid=fork()之后开始运行，因为父子进程运行代码的数据一样，所以无法直接分辨，只能通过返回值判断
对于父进程fork返回值>0  对于子进程返回值==0
fork创建子进程之后，父子进程谁先运行不一定，操作系统调度到谁谁就运行
为什么子进程会从fork()之后开始执行？
父子进程pcb一模一样，子进程pcb中的程序计数器(记录程序执行到哪里了，接下来该执行什么代码)记录的就是fork()这一行代码，因此从fork以下开始执行
getpid()获取调用进程的标识符pid
孤儿进程：父进程先于子进程退出，子进程就会成为孤儿进程
特性：让出终端，进入系统后台运行并且父进程成为1号进程，1号进程在centos7之前叫init进程，之后叫systemd，系统中父进程是1号进程的进程，通常以d结尾，表示它在后台运行
课后调研：守护进程、精灵进程
守护进程：特殊的孤儿进程，不但运行在后台，父进程成为1号进程，并且还与登录终端以及会话脱离关系(为了一个进程稳定不受影响的运行在后台)
*/
//查看进程信息
//ps -ef|head -1 && ps -ef|grep fork 显示fork进程ppid父进程,pid子进程
//ps -aux | grep test	aux详细显示，会显示进程当前状态
//前台进程：当前占据了终端的进程，

//环境变量：终端shell中进行系统运行环境配置的变量
//作用：1.可以使系统环境配置更加灵活(不像修改配置文件后还得加载配置问题)  2.可以通过环境变量向子程序传递数据
//操作指令：env -查看所有环境变量 echo--直接打印某个变量的内容  echo $PATH($表示后面的字符串是一个变量名称)export PATH=$PATH:. set-查看所有变量，不只是环境变量 export声明定义一个环境变量 unset-删除一个变量，也可以是环境变量
//export MYVAL=100;
//PATH：当前搜索程序运行路径
//运行一个程序的时候，如果没有指定程序路径，只有名称则shell会去PATH环境变量保存的路径中去找这个程序
//代码操作：char *getenv(char *key)
//在终端中运行的程序，父进程都是bash，也就是shell程序
//在终端中运行一个程序，其实是shell创建了一个进程，让这个进程去调度我们要运行的程序，这样做可以提高稳定性，创建出的进程崩溃了，shell还可以继续运行

//环境变量可以1.配置系统运行环境参数 2.向子程序传递一些数据(子进程会拥有与父进程相同的环境变量)
//环境变量一直都存在，可以在main函数参数列表中写出来，用于接收环境变量，一般嫌麻烦而省略了main函数的参数列表(不定参函数)
//main函数的三个参数：int main(int argc, char *argv[], char *env[])
//extern char **environ; 库中的全局变量，每个节点指向一个环境变量，但是使用时需要声明，告诉编译器有这个变量
//这种临时创建的环境变量，在重新打开终端之后就没有了，想持久配置就把信息加入到配置文件中
//课后调研：设置环境变量  setenv()/putenv()
/*
//////////////////////////////////////////////
通过代码查看(获取)环境变量
argc-->程序运行参数个数
argv[]-->用于执行程序中各个环境变量的一个字符串指针数组
./env -l -a  [./env]是第0个参数，[-l]是第一个参数，[-a]是第二个参数
env[]用于指向程序各个环境变量的一个字符串指针数组
1.
int main(int argc, char *argv[], char *env[])
{
	int i;
	for(i=0;env[i]!=NULL;i++)
		printf("environment:[%s]\n",env[i]);
}
2.
extern char **environ;
int i;
for(i=0;env[i]!=NULL;i++)
	printf("environment:[%s]\n",env[i]);
*/

//程序地址空间（进程地址空间）
//地址:内存地址---对内存以字节为存储单元的一个编号,32位内存大小4G(也就是0x0000 0000到0xffff ffff)
/*
内核空间
环境变量,运行参数
栈(往下生长)
...
...(共享区)
堆(往上生长)
未初始化全局
初始化全局
代码段
*/
//在父子进程fork()代码中父子进程代码共享，数据独有，但打印的父子进程地址相同，子进程内g_val=200，为什么呢？
//其实我们访问的地址都是虚拟地址--并非真正的内存地址，打印出来的都是虚拟地址，但其实在内存中地址不同
//若进程直接访问物理内存有哪些缺点：1.无法动态获知哪块内存是否被使用，程序编译时，编译器会给指令和数据进行地址编号，但如果该地址被使用程序就运行不起来了
//									2.如果该进程中有一个野指针，在直接访问物理内存时可能会改变其它地址的数据，造成其它程序崩溃
//									3.程序运行加载需要一块连续的内存空间，对物理内存利用率很低
//通过虚拟地址空间映射到物理内存空间，可以提高物理内存利用率,虚拟内存是连续的,每个进程都会拥有自己的一块连续的空间，但实际上在物理内存中是离散存储的
//如何通过虚拟空间地址找到物理地址空间？
//操作系统的内存管理方式:分段式(段号)，分页式(页表)，段页式
/*
分段式:
通过段号在段表中查到初始内存地址,再用初始内存地址+段内偏移量找到对应的物理内存单元
分段式中每个段内数据的起始内存地址都是相同的，也就是说还是用了连续的物理内存空间无法离散式存储，未解决内存利用率低的问题
分页式:
通过页号查到初始内存地址,再用初始内存地址+页内偏移量找到对应的物理内存单元
优点:物理内存块大小跟虚拟内存页大小一样,物理内存块比较小,并且不要求同一进程的多个数据必须在同一个块内,因此分页式实现了数据在物理内存中的离散式存储,提高了内存利用率
页表会在进行内存访问时会进行内存访问权限查询(页表和)
十进制计算方法：虚拟地址/页表大小  ->找到对应物理地址+虚拟地址%页表大小
十六进制计算方法：虚拟地址高二十位是页号 ->找到对应物理地址+低二十位
页号占据的是高位，有2^20个页表所以占高20位，低20位为偏移量
32位操作系统 内存4G/4k == 页表项(页号)的个数 == 2^20  页表大小4096=4*1024=4k
段页式：将内存进行分段(代码段，数据段，堆，栈，环境变量等等)，在每个段内采用分页式管理
页表中有一个中断位--缺页中断，表示当前虚拟地址要找的数据是否在物理内存中(如果没在则会触发缺页中断)
一个进程的数据怎么会不在内存中呢？
内存管理：磁盘在分区的时候，至少有两个分区--交换分区和文件系统分区(用于文件数据存储)，内存不够时将内存中的某些不活跃的数据腾出来放到交换分区中，腾出空间给紧急的数据，等到使用该数据触发缺页中断时再交换回来/文件系统分区--用于文件数据存储
课后调研：内存置换算法:最久未使用（怎么快速定位最久未使用的数据）

进程控制：创建，终止，等待，程序替换
创建：如何创建一个进程？
	pid_t pid fork()；
	子进程复制父进程pcb，页表，虚拟地址空间都一样，所以刚开始父子进程除了个别数据(标识符pid)之外都是一样的，并且父子进程的数据指向同一块物理内存
	写时拷贝技术：子进程创建出来之后，与父进程映射访问同一物理内存，当某个物理内存中数据即将发生改变时(父进程数据发生改变或者子进程)重新为子进程开辟物理内存，拷贝数据过去。好处：防止给子进程创建空间，但子进程不用，降低了进程的创建效率，造成内存冗余数据
	返回值：父进程pid>0，子进程pid==0，pid<0错误，通过返回值可以区分父子进程
	pid_t pid=vfork():
	也是创建子进程，但一个父进程使用vfork创建子进程之后，vfork的调用并不会立即返回(通常说会阻塞父进程)而是让子进程先运行，直到子进程退出，或者进行程序替换之后，父进程才能运行
	在程序运行中每调用一个函数，就会进行一次函数压栈---函数调用栈,vfork父子进程可能会造成栈混乱
	vfork的父子进程使用的同一块虚拟地址空间，也就是说使用了同一个栈，若父子进程同时运行则会造成调用栈混乱，因此让父进程等待子进程退出或者程序替换后有了自己的地址空间(在原有的地址空间中子进程的调用就都出栈了)才开始运行
	pid_t vfork(void)  会造成死循环(vfork创建的子进程，不能在main函数中使用return退出，因为子进程使用return退出时释放了所有资源,父进程运行的时候资源是错误的)
	当父进程在main函数中调用fork函数创建子进程，fork运行完毕之后，父进程应该从调用fork函数的下一步开始执行
	fork父子进程各有各的栈，vfork父子进程共用同一块栈区
	总之vfork父子进程同一空间，fork父子进程不同空间
	问题：为什么vfork会造成无限循环？个人猜测：return释放资源后，父进程混乱
终止：如何退出一个进程？
	main函数中的return
	exit();可以在任何位置退出程序，库函数，exit退出进程时会刷新缓冲区，将缓冲区的数据写入标准输出
	_exit();					   系统调用接口，_exit退出进程直接释放资源，不会刷新缓冲区
	printf打印数据，实际上是把数据交给显示器，让显示器显示。先放入数据缓冲区，等积累到一定数量之后一次性输出(缓冲区满了)，这样做会提高程序运行效率。
	(\n)除了换行的作用之外，还有刷新缓冲区的作用，标准输出（使数据输出），\r回车
	fflush(stdout);刷新缓冲区
*/
/*
进程等待：为了获取退出子进程返回值，父进程等待子进程退出，释放退出子进程的所有资源，避免产生僵尸进程
僵尸进程产生原因：子进程先于父进程退出，而父进程没有关注子进程的退出信息，子进程为了保存退出返回值，而无法完全释放资源产生的
int wait(int *status);  阻塞接口，若没有子进程退出，则父进程阻塞，一直等待直到有子进程退出才会调用返回
	阻塞：为了完成一个功能，发起一个调用，若不具备完成功能的条件，则调用一直等待
	非阻塞：为了完成一个功能，发起一个调用，若不具备完成功能的条件，则调用立即报错并返回
	返回值：成功则返回处理过的子进程的pid，失败则返回-1(比如没有子进程退出)
int waitpid(int pid,int *status;int option);与wait不同，默认为非阻塞，父进程不会等待子进程退出
正常退出：程序运行到return或者exit自然退出，
异常退出：程序在运行过程中崩溃而退出
子进程退出而父进程没有等待处理，都会变成僵尸进程
wait和waitpid的不同之处：
1.wait

问题：进程等待这段代码是只在在父进程里面执行吗？子进程执行会怎么样？
一个进程在运行中突然崩溃，这是由于一些异常引起的，进程自己怎么知道自己发生了异常呢？
操作系统检测到进程的低7位异常退出信号，则通知进程退出
怎么判断一个进程是否正常退出，取出低七位；用status & 0x7f ==0则正常退出
0x7f == 0111 1111
怎么取出返回值---低16位中的高8位？(status>>8) & 0xff
返回值只用8位(一个字节)保存，因此退出返回值不要大于255
core dump---核心转储
当一个程序崩溃之后，我们想要调试找到程序崩溃位置，以及崩溃原因
*/

/*
进程程序替换：替换一个进程正在调度运行的程序
将当前进程的数据段和代码段进行替换，替换成为其他程序的数据和代码，并且更新堆栈数据
fork创建一个子进程，代码共享数据独有---父子进程做的事一样
  但通常创建一个子进程是为了运行其他程序
将会看到：1.进程标识符 pid 是没有变化的
		  2.
问题：程序替换之后，如果子程序执行时间比较长，而父进程很快就执行完毕了，会不会造成僵尸进程？
Linux下一切皆文件，pwd在shell上是指令，其实就是一个可执行程序(文件)，execl("")
32位操作系统内核：4G
1G	内核空间			 0x FFFF FFFF	
3G						 0x C000 0000
	命令行参数和环境变量
		栈
		.
		共享区
		.				 
		堆
		数据段
		代码段			 0x 0000 0000
*/
//minishell的工作
//1.能够从标准输入当中接收用户输入的命令
//2.创建子进程
//3.子进程进行程序替换
/////////////////////////////////////////////////////////////////////
/*
基础IO
1.C语言操作文件接口
	fopen(char* Path，'Way');Path:文件地址+文件名称，Way读取方式
	FILE* fp=fopen("D:\\demo","r");
	fwrite(* ptr,size,nmemb,* stream);ptr:往文件里写的内容，size;写入的大小，nmemb：数量，stream：文件指针
	一般把size设置为1，则nmemb为字节大小,fwrite("aaa",1,3,fp);fwrite返回的是写成功的数量
	fread(* ptr,size,nmemb,* stream);ptr将读到的内容保存的位置
	fread(b, size, N, fp);从文件读取内容并保存到数组b，返回读的数量
	"linux_57" 这个字符串常量最后面有一个'\0'
	fseek(* stream,offset,whence);offset偏移量,whence:SEEK_SET:头部 SEEK_CUR:偏移到指定位置 SEEK_END:末尾
	调整文件指针偏移量
2.系统调用函数的操作文件接口
	open(* pathname,int flags,mode);
	int fd = open("path",O_RDWR | O_CREAT,0664）
	按位或(有1则为1)
	00000000 00000000 00000000 01000010
						    ^    ^
	read(fd,* buf,count);fd文件描述符，open的返回值,buf读到哪里去，count最大可以读多少个
3.文件描述符
	操作系统会给每个进程在磁盘中创建一个以进程号(pid:进程标识符)命名的文件夹
	新创建的进程会打开三个文件描述符，标准输入(0)，标准输出(1)，标准错误(2)
	当打开一个文件时，系统会给程序分配一个文件描述符，如果使用完毕没有关闭文件，就会造成文件句柄泄露
	一个进程当中最大打开的文件数量是多少？
	1.默认打开文件数量1024   （0~1023）0：标准输入，1：标准输出，2：标准错误 实际打开文件1021
	2.ulimit -n[num]更改最大打开数量为num，ulimit -a 查看设置权限
4.文件描述符和文件流指针的区别，文件流指针也就是FILE* fp中有一个指针int _fileno；保存的就是文件描述符的数值
	1)文件流指针是fopen函数返回的，文件流指针是库函数维护的
	2)文件描述符是open函数返回的，文件描述是内核维护的
	C语言中FILE 在操作系统中其实是struct _IO_FILE 结构体：
	不同文件流指针会创建不同的IO结构体，保存了不同的文件描述符
	c库维护的exit函数在退出时，会刷新缓冲区，而操作系统接口_exit函数不会刷新缓冲器
5.重定向
	重新让标准输出，由屏幕指向文件
	dup2(int oldfd，int newfd)；
	dup2(fd,1);关闭1号文件描述符，
	>>重定向，默认会追加
6.动态库和静态库
	命令1：ldd+可执行程序：查看当前程序依赖的动态库文件
	ldd vfork
	命令2：file+可执行程序：查看文件属性
	1.动态库
	libc.so.6 => /lib64/libc.so.6 (0x00007fc458bb9000) C动态库
	生成
	gcc/g++
	-shareed
	编译动态库的源码中不能出现main函数
	编译可执行程序时，必须告诉编译器链接的动态库是哪个？，否则发生链接错误。指定链接动态库所在路径和名字，
	gcc main.c -o main -L . -lfunc  (-L+路径，-l+库的名称)，可执行程序在找动态库时会默认在当前路径下寻找
	2.静态库
	Windows中静态库是以.lib为后缀的，动态库为.dll，编译依赖.lib库文件，运行时依赖.dll文件
	生成

	ar -rc libfunc.a test.0（这个依赖文件为.o不是原文件）
	使用
	gcc main.c -o main -L . -lfunc 
	
动态链接和静态链接最大区别：有没有static
静态库用动态链接，文件会很大，但把生成的库删除，仍然可以执行
文件系统
线性存储方式可能会导致磁盘利用率较低，离散式存储能提高磁盘利用率
ext2文件系统就是采用了离散式存储，每个比特位表示Data blocks中块的使用情况，为1表示占用，0表示空闲

文件存储：在BlockBitMap中查找空闲block块，将文件存储在空闲的block块当中，再通过inode BitMap获取空闲的inode节点，在空闲的inode节点描述文件在DataBlock区域当中存储的位置
inode

软硬链接
	软链接(类似快捷方式或者说别名)：In -s hello aaa 
	它只会在你选定的位置上（不写位置默认当前路径下）生成一个文件的镜像，不会占用磁盘空间
	ll -i 可以看到两个的inode节点号不同，软链接文件具有独立的inode节点号
	在删除软链接文件或者软链接文件指向的原文件时，两者都应该同时删除
	硬链接：In hello bbb
	ll- i 可以看到两个的inode节点一模一样，一个文件生成了两个有效路径
	问题：为什么删除原文件之后，硬链接的文件仍然存在？
	因为硬链接是在选定的位置上生成一个和源文件大小相同的文件，硬连接的作用是允许一个文件拥有多个有效路径名，这样用户就可以建立硬连接到重要文件，以防止“误删”的功能
无论是软链接还是硬链接，文件都保持同步变化
*/
/*
进程间通信
为什么需要进程间通信？
进程都拥有自己独立的虚拟地址空间，通过进程间通信，可以让不同进程进行协作。
网络就是一个进程间通信，信息在不同进程中传递
1.管道
	管道符 | 链接两个命令，把第一个输出的结果给第二个命令作为输入
	管道就是在内核当中开辟的一块内存，也可以称之为内核缓冲区
	用户态        ps aux | grep xxx
	内核态             缓冲区	ps -aux被加载到缓冲区，然后给grep xxx
匿名管道
	在内核中创建出来的一块内存是没有标识符的
	如何创建一个管道？int pipe(int  fd[2])；fd[2]整形数组，两个元素。fd[0]：读端，读匿名内存,fd[1]：写端
	fd是输出型参数，用时不需要输入值
	成功返回0；失败-1
	int fd[2]; int a=pipe(fd);
	闪烁原因：1.指向内核的内存 2.不存在
*/









int main()
{
	return 0;
}