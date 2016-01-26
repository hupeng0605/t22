

#ifndef __IPC_EVENT_H__
#define __IPC_EVENT_H__

#ifndef TCHAR
#	if defined(_UNICODE) || defined(UNICODE)
#		define TCHAR wchar_t
#	else
#		define TCHAR char
#	endif
#endif

/*************************************** �¼�ID���� ***************************************/

/*---------------- IPC ��Ϣ���Ͷ��� ----------------------- ��Ӧ����Ľṹ�� -------------*/

// IPC�ڲ�ϵͳ��Ϣ��ʼID ֻ����ʶ �޾�����Ϣ����
#define IPC_EVENT_SYS_BEGIN	(0x0000)

// һ������ע���� ��ע��һ������ʱ ��㲥��ʽ��ÿ�����̷��͸���Ϣ
#define IPC_SYS_PROC_REGIST			(IPC_EVENT_SYS_BEGIN + 0x01)	// ��Ӧ���ݽṹ : ���� unsigned char ��С 1 Byte  ����ID��
// һ������ע���� ��ע��һ������ʱ ��㲥��ʽ��ÿ�����̷��͸���Ϣ
#define IPC_SYS_PROC_UNREGIST	(IPC_EVENT_SYS_BEGIN + 0x02)	// ��Ӧ���ݽṹ : ���� unsigned char ��С 1 Byte  ����ID��

// IPC�ڲ�ϵͳ��Ϣ����ID ֻ����ʶ �޾���Ϣ������
#define IPC_EVENT_SYS_END	(0x00FF)

// IPC�û��Զ�����Ϣ
#define IPC_EVENT_USER		(0x1000)


#endif	/*__IPC_EVENT_H__*/