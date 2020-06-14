# 全局状态的global_State中与GC相关的数据成员  
  lu_byte currentwhite //当前GC的白色
  lu_byte gcstate //GC状态,GCSpause(暂停),GCSpropagate(遍历灰色节点),GCSweepstring(字符串回收阶段)，GCSweep（其他类型回收）,GCSfinalize(终止)
  int sweepstrgc //每次对字符串散列桶的一组字符串进行回收，这个值记录散列桶的索引
  GCObject *allgc //待GC对象的链表，所有对象创建后都会放入该链表中
  GCObject **sweepgc //保存当前回收位置
  GCObject *grey //灰色节点链表
  GCObject *grayagain //存放需要一次性扫描的灰色节点链表
  GCObject *weak //存放弱表的链表
  GCObject *tmudata //所有带有GC元方法的udata存放在一个链表中，这个成员指向链表的最后一个元素
  lu_mem totalbytes //当前分配的内存大小
  lu_mem GCthreshold //开始进行GC的阈值，当totalbytes大于这个值时自动进行GC
  lu_mem estimate //估值，保存实际在用的内存大小
  lu_mem gcdept //单次GC之前保存待回收的数据大小
  int gcpause //控制下一轮GC开始的时机
  int gcstepmul //控制GC的回收速度
  
  # GC流程
    GCSpause：开始GC，置空灰色，弱引用链表， 标记mainthread，registry表，基础类型元表，如果是白色标记为灰色,加入到灰色链表
    GCSpropagate: Table（如果是弱表，回退到灰色状态，加入到weak链表中，如果不是弱表遍历表的散列和数组部分的所有元素）
                  Function（对所有的UpValue进行标记）
                  Thread(回退到灰色状态，对象加入到graygain链表中)
                  Proto（标记数据中的文件名，字符串，upvalue，局部变量等所有引用的变量）
                  其余类型简单的置为灰色
        增量式算法，标记时黑色对象引用的对象中有白色对象，2中处理
            向前一步：将新增对象的颜色从白色变为灰色 （除了table的对象）
            向后一步：将黑色的对象回退到灰色，重新扫描对象 （table回退时，直接加入到graygain链表中）
        标记完后切换到atomic操作：原子操作标记完后，切换GC的白色，修改状态到下个阶段
    GCSsweepstring GCSsweepudata GCSsweep：切换为GCSpause
