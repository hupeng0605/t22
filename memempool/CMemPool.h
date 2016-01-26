typedef unsigned char  u_char;
typedef unsigned int     u_int;
typedef struct  
{
	u_char *pLast;
	u_char *pEnd;
    MemPool_t *pNext;
    u_int     nFailed;
}MemPoolData_t;
struct MemPool_t 
{
	MemPoolData_t d;
	size_t         nmax;//数据块大小，小块内存的最大值     
	MemPoolData_t           *pcurrent;   //指向当前或本内存池  
	//ngx_chain_t          *chain;     //该指针挂接一个ngx_chain_t结构  
	MemPoolLarge_t     *pplarge;     //指向大块内存分配，nginx中，大块内存分配直接采用标准系统接口malloc  
	MemPoolCleanup_t   *cleanup;   //析构函数，挂载内存释放时需要清理资源的一些必要操作  
	ngx_log_t            *log;       //内存分配相关的日志记录  

};
class CMemPool
{

public:
protected:
private:
};
