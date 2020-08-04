# String数据结构
 typedef union TString {  
    L_Umaxalign dummy; //让string数据类型按照L_Umaxalign(double,void *,long)最大8字节对齐，提高读取数据性能  
    struct {  
        CommonHeader;  
        lu_byte reserved;  //标识是否是保留字符串（lua关键字），如果是1，不会被GC回收
        unsigned int hash;  //字符串散列值
        size_t len;  //字符串长度
      } tsv;  
  } TString;  
  
  
  # 所有字符串存放在global_State的stringtable中,
  typedef struct stringtable {
     GCObject **hash; //散列桶，创建新的字符串时，先算出散列值作为索引值，如果已经有元素了，则使用链表串起来
     lu_int32 nuse; //在使用的桶数组大小
     int size; //字符串个数
   } stringtable;
   
   
   # 2个地方会触发resize重新分配散列桶大小
   - newlstr:如果字符串数量大于桶数组数量，且桶数组的数量小于MAX_INT/2，就会进行翻倍扩容
   - checkSizes:如果字符串数量大于桶数量2倍，扩容
   
