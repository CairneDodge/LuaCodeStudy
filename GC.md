# 全局状态的global_State中与GC相关的数据成员
  lu_byte currentwhite //当前GC的白色
  lu_byte gcstate //GC状态,GCSpause(暂停),GCSpropagate(遍历灰色节点),GCSweepstring(字符串回收阶段)，GCSweep（其他类型回收）,GCSfinalize(终止)
  int sweepstrgc //每次对字符串散列桶的一组字符串进行回收，这个值记录散列桶的索引
  GCObject *rootgc //待GC对象的链表，所有对象创建后都会放入该链表中
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
