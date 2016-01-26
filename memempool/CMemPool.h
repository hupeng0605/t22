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
	size_t         nmax;//���ݿ��С��С���ڴ�����ֵ     
	MemPoolData_t           *pcurrent;   //ָ��ǰ���ڴ��  
	//ngx_chain_t          *chain;     //��ָ��ҽ�һ��ngx_chain_t�ṹ  
	MemPoolLarge_t     *pplarge;     //ָ�����ڴ���䣬nginx�У�����ڴ����ֱ�Ӳ��ñ�׼ϵͳ�ӿ�malloc  
	MemPoolCleanup_t   *cleanup;   //���������������ڴ��ͷ�ʱ��Ҫ������Դ��һЩ��Ҫ����  
	ngx_log_t            *log;       //�ڴ������ص���־��¼  

};
class CMemPool
{

public:
protected:
private:
};
