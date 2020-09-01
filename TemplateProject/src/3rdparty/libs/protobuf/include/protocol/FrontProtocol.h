#ifndef __FRONT_PROTOCOL_H
#define __FRONT_PROTOCOL_H

#pragma pack(1)

#define FRONT_CMDID_BASE				30000		//ǰ��Э������ID��ʼֵ

#define	FRONT_PROTOCOL_VERSION			"1.2"			//Э��汾

/************************************************************************/
/*                              �ն���ҵ��ǰ��                          */
/************************************************************************/

//�û���½����
#define FRONT_CMDID_TERMINAL_USERLOGIN_REQ		 (FRONT_CMDID_BASE)

//�û���½�ظ�
#define FRONT_CMDID_TERMINAL_USERLOGIN_REP		 (FRONT_CMDID_BASE + 1)

//��ȡ�������б�����
#define FRONT_CMDID_TERMINAL_ROOMLIST_REQ		 (FRONT_CMDID_BASE + 2)

//��ȡ�������б�ظ�
#define FRONT_CMDID_TERMINAL_ROOMLIST_REP		 (FRONT_CMDID_BASE + 3)

//�û��������������
#define FRONT_CMDID_TERMINAL_LOGINROOM_REQ       (FRONT_CMDID_BASE + 4)

//�û���������һظ�
#define FRONT_CMDID_TERMINAL_LOGINROOM_REP       (FRONT_CMDID_BASE + 5)

//�û��˳�����������
#define FRONT_CMDID_TERMINAL_EXITROOM_REQ        (FRONT_CMDID_BASE + 8)

//�û��˳������һظ�
#define FRONT_CMDID_TERMINAL_EXITROOM_REP        (FRONT_CMDID_BASE + 9)

//�û�ע������
#define FRONT_CMDID_TERMINAL_USERLOGOUT_REQ		 (FRONT_CMDID_BASE + 10)

//�û�ע���ظ�
#define FRONT_CMDID_TERMINAL_USERLOGOUT_REP		 (FRONT_CMDID_BASE + 11)

//�û�ͨ�����������ID�����ȡ������ID
#define FRONT_CMDID_TERMINAL_GETROOMID_REQ       (FRONT_CMDID_BASE + 12)

//�û�ͨ�����������ID�����ȡ������ID
#define FRONT_CMDID_TERMINAL_GETROOMID_REP       (FRONT_CMDID_BASE + 13)

//�û�������������󣨺ϲ�����
#define FRONT_CMDID_TERMINAL_LOGINROOM_REQ2       (FRONT_CMDID_BASE + 14)

//�û���������һظ�
#define FRONT_CMDID_TERMINAL_LOGINROOM_REP2       (FRONT_CMDID_BASE + 15)



/************************************************************************/
/*							ҵ��ǰ����ҵ�����                          */
/************************************************************************/

//ҵ�����ע������
#define FRONT_CMDID_DEV_REGISTER_REQ	(FRONT_CMDID_BASE + 100)

//ҵ�����ע��ظ�
#define FRONT_CMDID_DEV_REGISTER_REP	(FRONT_CMDID_BASE + 101)

//ҵ������˳�����
#define FRONT_CMDID_DEV_EXIT_REQ		(FRONT_CMDID_BASE + 102)

//ҵ������˳��ظ�
#define FRONT_CMDID_DEV_EXIT_REP		(FRONT_CMDID_BASE + 103)

//ҵ�����״̬��������
#define FRONT_CMDID_DEV_UPDATE_TOKEN	(FRONT_CMDID_BASE + 104)


/************************************************************************/
/*                   �¼�ҵ��ǰ�����ϼ�ҵ��ǰ��                         */
/************************************************************************/

//ҵ��ǰ��ע������
#define FRONT_CMDID_FRONTSRV_REGISTER_REQ		(FRONT_CMDID_BASE + 200)

//ҵ��ǰ��ע��ظ�
#define FRONT_CMDID_FRONTSRV_REGISTER_REP		(FRONT_CMDID_BASE + 201)

//ҵ��ǰ�û������б�����
#define FRONT_CMDID_FRONTSRV_ROOMLIST_REQ		(FRONT_CMDID_BASE + 202)

//ҵ��ǰ�û������б�ظ�
#define FRONT_CMDID_FRONTSRV_ROOMLIST_REP		(FRONT_CMDID_BASE + 203)

//ת���û�������������
#define FRONT_CMDID_FRONTSRV_LOGINROOM_REQ		(FRONT_CMDID_BASE + 204)

//ת���û������������ҷ���
#define FRONT_CMDID_FRONTSRV_LOGINROOM_REP		(FRONT_CMDID_BASE + 205)

//ҵ��ǰ��ע������
#define FRONT_CMDID_FRONTSRV_EXIT_REQ			(FRONT_CMDID_BASE + 206)

//ҵ��ǰ��ע��ظ�
#define FRONT_CMDID_FRONTSRV_EXIT_REP			(FRONT_CMDID_BASE + 207)


#pragma pack()

#endif//__FRONT_PROTOCOL_H
;