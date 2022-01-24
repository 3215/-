#include <stdlib.h>
#include <iostream>

// �������״̬����
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
// Status �Ǻ��������ͣ���ֵ�Ǻ������״̬����
typedef int Status;
typedef char ElemType;

typedef struct Lnode{
    ElemType data;
    struct Lnode *next;
}Lnode, *LinkList;


/*
(1)��������������������ϲ�Ϊһ����������������Ҫ����������ʹ��ԭ����������Ĵ洢�ռ䣬������ռ�������Ĵ洢�ռ䡣���в��������ظ������ݡ�

[��Ŀ����]
�ϲ�����±�ʹ��ͷָ��Lcָ��pa��pb�ֱ�������La ��Lb �Ĺ���ָ��, ��ʼ��Ϊ��Ӧ����ĵ�һ����㣬�ӵ�һ����㿪ʼ���бȽϣ�
����������La ��Lb ��Ϊ�����β���ʱ������ժȡ���н�С������������Lc(La)����������������е�Ԫ����ȣ�ֻժȡLa���е�Ԫ�أ�
ɾ��Lb ���е�Ԫ�أ�����ȷ���ϲ���������ظ���Ԫ�ء���һ�������β��㣬Ϊ��ʱ�����ǿձ��ʣ��Ԫ��ֱ��������Lc(La)������
*/
void MergeList_1(LinkList &La, LinkList &Lb){
    // �ϲ�����La��Lb
    Lnode *pa = La->next, *pb = Lb->next;   //pa��pb�ֱ�������La��Lb�Ĺ���ָ��, ��ʼ��Ϊ��Ӧ����ĵ�һ�����
    Lnode *pc = La, *tmp;   // ��La��ͷ�����Ϊ�±��ͷ��㣬��ָ��pcָ��
    while(pa && pb){
        if(pa->data == pb->data){   // ���ʱȡLa�е�Ԫ�أ�ɾ��Lb�е�Ԫ��
            pc->next = pa;
            pc = pa;
            pa = pa->next;
            tmp = pb;
            pb = pb->next;
            delete tmp;
        }
        else if(pa->data < pb->data){   // ȡ��С��La�е�Ԫ�أ���pa������pc�ĺ��棬paָ�����
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        }
        else{   // ȡ��С��Lb�е�Ԫ�أ���pb������pc�ĺ��棬pbָ�����
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
    }
    pc->next = pa ? pa : pb;    // ����ʣ���
    delete Lb;  // �ͷ�Lb
}


/*
(2)�������ǵݼ�����������ϲ�Ϊһ���ǵ�������������Ҫ����������ʹ��ԭ����������Ĵ洢�ռ䣬������ռ�������Ĵ洢�ռ䡣�����������ظ������ݡ�

[ ��Ŀ����]
�ϲ�����±�ʹ��ͷָ��Lc(La)ָ��pa ��pb �ֱ�������La ��Lb �Ĺ���ָ��, ��ʼ��Ϊ��Ӧ����ĵ�һ����㣬�ӵ�һ����㿪ʼ���бȽϣ�
����������La ��Lb ��Ϊ�����β���ʱ������ժȡ���н�С������������Lc(La)��ı�ͷ���֮������������е�Ԫ����ȣ�ֻժȡLa ���е�Ԫ�أ�
����Lb ���е�Ԫ�ء���һ�������β��㣬Ϊ��ʱ�����ǿձ��ʣ��Ԫ������ժȡ��������Lc(La)��ı�ͷ���֮��
*/
void MergeList_2(LinkList &La, LinkList &Lb){
    // ͷ�巨
    Lnode *pa = La->next, *pb = Lb->next;
    Lnode *pc = La, *q;
    pc->next = NULL;
    while(pa || pb){    // ֻҪ����һ���ǿձ���q ָ���ժȡ��Ԫ��
        if(!pa){    //La ��Ϊ�գ���q ָ��pb �� pbָ�����
            q = pb;
            pb = pb->next;
        }else if(!pb){  //Lb��Ϊ�գ���qָ��pa,paָ�����
            q = pa;
            pa = pa->next;
        }else if(pa->data <= pb->data){ // ȡ��С�ߣ�������ȣ� La �е�Ԫ�أ���qָ��pa��paָ�����
            q = pa;
            pa = pa->next;
        }else{  // ȡ��С��Lb �е�Ԫ�أ���q ָ��pb�� pb ָ�����
            q = pb;
            pb = pb->next;
        }
        // ��q ָ��Ľ�����Lc(La)��ı�ͷ���֮��
        q->next = pc->next;
        pc->next = q;
    }
    delete Lb;  // �ͷ�Lb
}


/*
(3)��֪��������A��B�ֱ��ʾ�������ϣ���Ԫ�ص������С������һ���㷨���������A��B�Ľ������������A�����С�

[ ��Ŀ����]
ֻ��ͬʱ�������������е�Ԫ�زų����ڽ������, �ϲ�����±�ʹ��ͷָ��Lc(La)ָ��pa ��pb �ֱ�������La ��Lb �Ĺ���ָ��, 
��ʼ��Ϊ��Ӧ����ĵ�һ����㣬 �ӵ�һ����㿪ʼ���бȽϣ�����������La ��Lb ��Ϊ�����β���ʱ���������������ȵ�Ԫ��ʱ��
ժȡLa ���е�Ԫ�أ�ɾ��Lb ���е�Ԫ�أ��������һ�����е�Ԫ�ؽ�Сʱ��ɾ���˱��н�С��Ԫ�أ��˱�Ĺ���ָ����ơ�
������La ��Lb ��һ�������β��㣬Ϊ��ʱ������ɾ����һ���ǿձ��е�����Ԫ�ء�
*/
void Mix(LinkList &La, LinkList &Lb){
    Lnode *pa = La->next, *pb = Lb->next;   //pa ��pb �ֱ�������La ��Lb �Ĺ���ָ��, ��ʼ��Ϊ��Ӧ����ĵ�һ�����
    Lnode *pc = La, *tp;    // ��La ��ͷ�����ΪLc(La)��ͷ���
    while(pa && pb){
        if(pa->data > pb->data){
            tp = pb; pb = pb->next;
            delete tp;
        }else if(pa->data < pb->data){
            tp = pa; pa = pa->next;
            delete tp;
        }else{  //��������������
            pc->next = pa;
            pc = pa;
            pa = pa->next;
            tp = pb; pb = pb->next;
            delete tp;
        }
    }
    while(pb){  //�ͷ�ʣ����ռ�
        tp = pb;
        pb = pb->next;
        delete tp;
    }
    while(pa){  //�ͷ�ʣ����ռ�
        tp = pa;
        pa = pa->next;
        delete tp;
    }
    pc->next = NULL;    //������β���
    delete Lb;  // �ͷ�Lb ��ͷ���
}


/*
(4) ��֪��������A ��B �ֱ��ʾ�������ϣ���Ԫ�ص������С�������㷨�����������A��B �Ĳ
����������A�г��ֶ�����B�г��ֵ�Ԫ�������ɵļ��ϣ�������ͬ������ʽ�洢��ͬʱ���ظü��ϵ�Ԫ�ظ�����

[ ��Ŀ����]
����������A ��B �Ĳ��ָ��A ��ɾ��A ��B �й��е�Ԫ�أ���ɾ�������е���Ӧ���, ����Ҫ�����ɾ������ǰ����
ʹ��ָ��pre ָ��ǰ����㡣pa ��pb �ֱ�������La ��Lb �Ĺ���ָ��, ��ʼ��Ϊ��Ӧ����ĵ�һ����㣬�ӵ�һ����㿪ʼ���бȽϣ�
����������La ��Lb ��Ϊ�����β���ʱ�����La ���е�Ԫ��С��Lb ���е�Ԫ�أ� pre ��ΪLa ��Ĺ���ָ��pa ɾ��Lb ���е�Ԫ�أ�
�������һ�����е�Ԫ�ؽ�Сʱ��ɾ���˱��н�С��Ԫ�أ��˱�Ĺ���ָ����ơ�������La ��Lb ��һ��Ϊ��ʱ�� ����ɾ����һ���ǿձ��е�����Ԫ�ء�
*/
int Difference(LinkList &La, LinkList &Lb){
    //��Ľ���洢�ڵ�����La��
    Lnode *pa = La->next, *pb = Lb->next;   //pa ��pb �ֱ�������La��Lb�Ĺ���ָ��, ��ʼ��Ϊ��Ӧ����ĵ�һ�����
    Lnode *pre = La, *tp;   // preΪLa��pa��ָ����ǰ������ָ��
    int n = 0;  //  n�ǽ��������Ԫ�ظ���������ʱΪ0
    while(pa && pb){
        if(pa->data == pb->data){   //B �����е�ǰ���ָ�����
            pre->next = pa->next;
            delete pa;
            pa = pre->next;
            pb = pb->next;
        }
        else if(pa->data < pb->data){   // A�����е�ǰ���ָ�����
            pre = pa;
            pa = pa->next;
            n++;
        }
        else{   //B �����е�ǰ���ָ�����
            pb = pb->next;
        }
    }
    while(Lb){  //ɾ��Lb��
        tp = Lb;
        Lb = Lb->next;
        delete tp;
    }
    return n;
}


/*
(5)����㷨��һ����ͷ���ĵ�����A�ֽ�Ϊ����������ͬ�ṹ������B��C, ����B��Ľ��ΪA ����ֵС����Ľ�㣬
��C ��Ľ��ΪA ����ֵ������Ľ�㣨����A �е�Ԫ��Ϊ����������Ҫ��B ��C ������A ��Ľ�㣩��

[ ��Ŀ����]
B���ͷ���ʹ��ԭ��A���ͷ��㣬ΪC��������һ��ͷ��㡣��A��ĵ�һ����㿪ʼ������ȡ��ÿ�����p��
�жϽ��p��ֵ�Ƿ�С��0������β�巨����С��0�Ľ�����B��, ���ڵ���0�Ľ�����C��
*/
void DisCompose_P(LinkList A){  // β�巨
    Lnode *B = A, *C = new Lnode;
    Lnode *p = A->next, *tbp = B, *tcp = C;
    tbp->next = NULL; tcp->next = NULL;
    while(p){
        if(p->data < 0){
            tbp->next = p;
            p = p->next;
            tbp = tbp->next;
            tbp->next = NULL;
        }else{
            tcp->next = p;
            p = p->next;
            tcp = tcp->next;
            tcp->next = NULL;
        }
    }
}

void DisCompose_L(LinkList A)
{   // ͷ�巨
    Lnode *p = A->next, *r; 	//p Ϊ����ָ��
	Lnode *B = A;
	B->next = NULL; 			//B ���ʼ��
	Lnode *C = new Lnode;			//ΪC ������ռ�
	C->next = NULL; 			// C ��ʼ��Ϊ�ձ�
	while(p != NULL){
		r = p->next; 			//�ݴ�p �ĺ��
		if(p->data < 0){
            p->next = B->next;
            B->next = p;
        } 		//��С��0 �Ľ������B ��, ǰ�巨
		else{
            p->next = C->next;
            C->next=p;
        } 				//�����ڵ���0 �Ľ������C ��, ǰ�巨
		p = r; 		//p ָ���µĴ������㡣
	}
}


/*
(6)���һ���㷨��ͨ��һ�˱���ȷ������Ϊn �ĵ�������ֵ���Ľ�㡣

[ ��Ŀ����]
�ٶ���һ����������ݾ������ֵ����������һ��Ԫ�رȽϣ�����С����һ��Ԫ�أ���������һ��Ԫ��Ϊ���ֵ���������бȽϣ�ֱ�������������
*/
ElemType Max(LinkList L){
    Lnode *pmax, *p;
    if(L->next == NULL) return ERROR;
    pmax = L->next; // �ٶ���һ����������ݾ������ֵ
    p = pmax->next;
    while(p){   // �����һ��������
        if(p->data > pmax->data) pmax = p;  // ���p ��ֵ����pmax ��ֵ�������¸�ֵ
        p = p->next;    // ��������
    }
    return pmax->data;
}


/*
(7)���һ���㷨�������������н������ӷ���ԭ�ء� ��ת����Ҫ�������ԭ��Ĵ洢�ռ䣬���仰˵��Ҫ���㷨�Ŀռ临�Ӷ�Ϊ0(1)��

[ ��Ŀ����]
����Ԫ��㿪ʼ������ذ�����L �ĵ�ǰ���p �����µ�����ͷ����ͷ�巨
*/
void Inverse(LinkList &L){  // ���ô�ͷ���ĵ����� L
    Lnode *p = L->next, *tp;
    L->next = NULL;
    while(p){
        tp = p->next;   // tp ָ��*p �ĺ��
        p->next = L->next;
        L->next = p;    // *p ������ͷ���֮��
        p = tp;
    }
}


/*
(8)���һ���㷨��ɾ��(����)����������ֵ����mink��С��maxk������Ԫ��(mink��maxk�Ǹ�����������������ֵ���Ժͱ��е�Ԫ����ͬ��Ҳ���Բ�ͬ)��

[ ��Ŀ����]
�ֱ���ҵ�һ��ֵ>mink �Ľ��͵�һ��ֵ�� maxk �Ľ�㣬���޸�ָ�룬ɾ��ֵ����mink ��С��maxk ������Ԫ�ء�
*/
void Delete(LinkList &L, int mink, int maxk){
    Lnode *p = L->next; // ��Ԫ���
    Lnode *pre, *dq, *tp;
    while(p && p->data <= mink){    // ���ҵ�һ��ֵ>mink �Ľ��
        pre = p;
        p = p->next;
    }
    if(p){
        while(p && p->data < maxk){ // ���ҵ�һ��ֵ�� maxk �Ľ��
            p = p->next;
        }
        dq = pre->next;
        pre->next = p;  // �޸�ָ��
        while(dq != p){ // �ͷŽ��ռ�
            tp = dq->next;
            delete dq;
            dq = tp;
        }
    }
}


/*
(9)��֪pָ��˫��ѭ�������е�һ����㣬����ṹΪdata ��prior��next������д���㷨change(p), ����p��ָ��Ľ�㼰��ǰ������˳��

[ ��Ŀ����]
֪��˫��ѭ�������е�һ����㣬��ǰ�������漰���ĸ���㣨 p ��㣬ǰ����㣬ǰ����ǰ����㣬��̽�㣩��������
*/
typedef struct DuLnode{
    ElemType data;
    struct DuLnode *prior, *next;
}DuLnode, *DuLinkList;

void change(DuLinkList &p){
    // p ��˫��ѭ�������е�һ����㣬���㷨��p ��ָ�������ǰ����㽻����
    DuLnode *q = p->prior;  
    q->prior->next = p;     //p ��ǰ����ǰ��֮���Ϊp
    p->prior = q->prior;    //p ��ǰ��ָ����ǰ����ǰ��
    q->next = p->next;      //p ��ǰ���ĺ��Ϊp �ĺ��
    p->next->prior = q;     //p �ĺ�̵�ǰ��ָ��ԭp ��ǰ��
    q->prior = p;           //p ����ǰ������
    p->next = q;            // p �ĺ��ָ����ԭ����ǰ��
}


/*
(10)��֪����Ϊn�����Ա�A����˳��洢�ṹ����дһ��ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�Ϊ0(1)���㷨�����㷨��ɾ�����Ա�������ֵΪitem������Ԫ�ء�

[ ��Ŀ����]
��˳��洢�����Ա���ɾ��Ԫ�أ�ͨ��Ҫ�漰��һϵ��Ԫ�ص��ƶ���ɾ��i ��Ԫ�أ��� i+1 ����n ��Ԫ��Ҫ����ǰ�ƣ� ��
����Ҫ��ɾ�����Ա�������ֵΪitem ������Ԫ�أ���δҪ��Ԫ�ؼ�����λ�ò��䡣��˿��Կ�����ͷβ����ָ�루 i=1 �� j=n ����
���������м��ƶ���������ֵitem ������Ԫ��ʱ��ֱ�ӽ��Ҷ�Ԫ��������ֵΪitem ������Ԫ��λ�á�
*/
#define MAXSIZE 1000
typedef struct SqList{
    ElemType *elem;
    int length;
}SqList;
// A ���� n ��Ԫ�ص�һά���飬���㷨ɾ��A ������ֵΪ item ��Ԫ��
void Delete_Sq(SqList &A, int n, ElemType item){
    A.elem = new ElemType[MAXSIZE]; A.length = n;
    int i = 0, j = n-1;                         //��������͡��߶�ָ��
    while(i < j){
        while(i < j && A.elem[i] != item)    i++;    //��ֵ��Ϊitem ������ָ�롣
        if(i < j){
            while(i < j && A.elem[j] == item){       //���Ҷ�Ԫ��Ϊitem ��ָ������
                j--;
                A.length--;
            }
        }
        if(i < j){
            A.elem[i++] = A.elem[j--];
            // A.elem[i] = A.elem[j];
            // ++i; --j;
        }
    }
    if(A.elem[i] == A.elem[j] == item){
        A.length--;
    }
}