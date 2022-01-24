#include <stdlib.h>
#include <iostream>

// 函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
// Status 是函数的类型，其值是函数结果状态代码
typedef int Status;
typedef char ElemType;

typedef struct Lnode{
    ElemType data;
    struct Lnode *next;
}Lnode, *LinkList;


/*
(1)将两个递增的有序链表合并为一个递增的有序链表。要求结果链表仍使用原来两个链表的存储空间，不另外占用其他的存储空间。表中不允许有重复的数据。

[题目分析]
合并后的新表使用头指针Lc指向，pa和pb分别是链表La 和Lb 的工作指针, 初始化为相应链表的第一个结点，从第一个结点开始进行比较，
当两个链表La 和Lb 均为到达表尾结点时，依次摘取其中较小者重新链接在Lc(La)表的最后。如果两个表中的元素相等，只摘取La表中的元素，
删除Lb 表中的元素，这样确保合并后表中无重复的元素。当一个表到达表尾结点，为空时，将非空表的剩余元素直接链接在Lc(La)表的最后。
*/
void MergeList_1(LinkList &La, LinkList &Lb){
    // 合并链表La和Lb
    Lnode *pa = La->next, *pb = Lb->next;   //pa和pb分别是链表La和Lb的工作指针, 初始化为相应链表的第一个结点
    Lnode *pc = La, *tmp;   // 用La的头结点作为新表的头结点，用指针pc指向
    while(pa && pb){
        if(pa->data == pb->data){   // 相等时取La中的元素，删除Lb中的元素
            pc->next = pa;
            pc = pa;
            pa = pa->next;
            tmp = pb;
            pb = pb->next;
            delete tmp;
        }
        else if(pa->data < pb->data){   // 取较小者La中的元素，将pa链接在pc的后面，pa指针后移
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        }
        else{   // 取较小者Lb中的元素，将pb链接在pc的后面，pb指针后移
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
    }
    pc->next = pa ? pa : pb;    // 插入剩余段
    delete Lb;  // 释放Lb
}


/*
(2)将两个非递减的有序链表合并为一个非递增的有序链表。要求结果链表仍使用原来两个链表的存储空间，不另外占用其他的存储空间。表中允许有重复的数据。

[ 题目分析]
合并后的新表使用头指针Lc(La)指向，pa 和pb 分别是链表La 和Lb 的工作指针, 初始化为相应链表的第一个结点，从第一个结点开始进行比较，
当两个链表La 和Lb 均为到达表尾结点时，依次摘取其中较小者重新链接在Lc(La)表的表头结点之后，如果两个表中的元素相等，只摘取La 表中的元素，
保留Lb 表中的元素。当一个表到达表尾结点，为空时，将非空表的剩余元素依次摘取，链接在Lc(La)表的表头结点之后。
*/
void MergeList_2(LinkList &La, LinkList &Lb){
    // 头插法
    Lnode *pa = La->next, *pb = Lb->next;
    Lnode *pc = La, *q;
    pc->next = NULL;
    while(pa || pb){    // 只要存在一个非空表，用q 指向待摘取的元素
        if(!pa){    //La 表为空，用q 指向pb ， pb指针后移
            q = pb;
            pb = pb->next;
        }else if(!pb){  //Lb表为空，用q指向pa,pa指针后移
            q = pa;
            pa = pa->next;
        }else if(pa->data <= pb->data){ // 取较小者（包括相等） La 中的元素，用q指向pa，pa指针后移
            q = pa;
            pa = pa->next;
        }else{  // 取较小者Lb 中的元素，用q 指向pb， pb 指针后移
            q = pb;
            pb = pb->next;
        }
        // 将q 指向的结点插在Lc(La)表的表头结点之后
        q->next = pc->next;
        pc->next = q;
    }
    delete Lb;  // 释放Lb
}


/*
(3)已知两个链表A和B分别表示两个集合，其元素递增排列。请设计一个算法，用于求出A与B的交集，并存放在A链表中。

[ 题目分析]
只有同时出现在两集合中的元素才出现在结果表中, 合并后的新表使用头指针Lc(La)指向。pa 和pb 分别是链表La 和Lb 的工作指针, 
初始化为相应链表的第一个结点， 从第一个结点开始进行比较，当两个链表La 和Lb 均为到达表尾结点时，如果两个表中相等的元素时，
摘取La 表中的元素，删除Lb 表中的元素；如果其中一个表中的元素较小时，删除此表中较小的元素，此表的工作指针后移。
当链表La 和Lb 有一个到达表尾结点，为空时，依次删除另一个非空表中的所有元素。
*/
void Mix(LinkList &La, LinkList &Lb){
    Lnode *pa = La->next, *pb = Lb->next;   //pa 和pb 分别是链表La 和Lb 的工作指针, 初始化为相应链表的第一个结点
    Lnode *pc = La, *tp;    // 用La 的头结点作为Lc(La)的头结点
    while(pa && pb){
        if(pa->data > pb->data){
            tp = pb; pb = pb->next;
            delete tp;
        }else if(pa->data < pb->data){
            tp = pa; pa = pa->next;
            delete tp;
        }else{  //交集并入结果表中
            pc->next = pa;
            pc = pa;
            pa = pa->next;
            tp = pb; pb = pb->next;
            delete tp;
        }
    }
    while(pb){  //释放剩余结点空间
        tp = pb;
        pb = pb->next;
        delete tp;
    }
    while(pa){  //释放剩余结点空间
        tp = pa;
        pa = pa->next;
        delete tp;
    }
    pc->next = NULL;    //置链表尾标记
    delete Lb;  // 释放Lb 的头结点
}


/*
(4) 巳知两个链表A 和B 分别表示两个集合，其元素递增排列。请设计算法求出两个集合A和B 的差集
（即仅由在A中出现而不在B中出现的元素所构成的集合），并以同样的形式存储，同时返回该集合的元素个数。

[ 题目分析]
求两个集合A 和B 的差集是指在A 中删除A 和B 中共有的元素，即删除链表中的相应结点, 所以要保存待删除结点的前驱，
使用指针pre 指向前驱结点。pa 和pb 分别是链表La 和Lb 的工作指针, 初始化为相应链表的第一个结点，从第一个结点开始进行比较，
当两个链表La 和Lb 均为到达表尾结点时，如果La 表中的元素小于Lb 表中的元素， pre 置为La 表的工作指针pa 删除Lb 表中的元素；
如果其中一个表中的元素较小时，删除此表中较小的元素，此表的工作指针后移。当链表La 和Lb 有一个为空时， 依次删除另一个非空表中的所有元素。
*/
int Difference(LinkList &La, LinkList &Lb){
    //差集的结果存储于单链表La中
    Lnode *pa = La->next, *pb = Lb->next;   //pa 和pb 分别是链表La和Lb的工作指针, 初始化为相应链表的第一个结点
    Lnode *pre = La, *tp;   // pre为La中pa所指结点的前驱结点的指针
    int n = 0;  //  n是结果集合中元素个数，调用时为0
    while(pa && pb){
        if(pa->data == pb->data){   //B 链表中当前结点指针后移
            pre->next = pa->next;
            delete pa;
            pa = pre->next;
            pb = pb->next;
        }
        else if(pa->data < pb->data){   // A链表中当前结点指针后移
            pre = pa;
            pa = pa->next;
            n++;
        }
        else{   //B 链表中当前结点指针后移
            pb = pb->next;
        }
    }
    while(Lb){  //删除Lb链
        tp = Lb;
        Lb = Lb->next;
        delete tp;
    }
    return n;
}


/*
(5)设计算法将一个带头结点的单链表A分解为两个具有相同结构的链表B和C, 其中B表的结点为A 表中值小于零的结点，
而C 表的结点为A 表中值大于零的结点（链表A 中的元素为非零整数，要求B 、C 表利用A 表的结点）。

[ 题目分析]
B表的头结点使用原来A表的头结点，为C表新申请一个头结点。从A表的第一个结点开始，依次取其每个结点p，
判断结点p的值是否小于0，利用尾插法，将小于0的结点插入B表, 大于等于0的结点插入C表。
*/
void DisCompose_P(LinkList A){  // 尾插法
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
{   // 头插法
    Lnode *p = A->next, *r; 	//p 为工作指针
	Lnode *B = A;
	B->next = NULL; 			//B 表初始化
	Lnode *C = new Lnode;			//为C 申请结点空间
	C->next = NULL; 			// C 初始化为空表
	while(p != NULL){
		r = p->next; 			//暂存p 的后继
		if(p->data < 0){
            p->next = B->next;
            B->next = p;
        } 		//将小于0 的结点链入B 表, 前插法
		else{
            p->next = C->next;
            C->next=p;
        } 				//将大于等于0 的结点链入C 表, 前插法
		p = r; 		//p 指向新的待处理结点。
	}
}


/*
(6)设计一个算法，通过一趟遍历确定长度为n 的单链表中值最大的结点。

[ 题目分析]
假定第一个结点中数据具有最大值，依次与下一个元素比较，若其小于下一个元素，则设其下一个元素为最大值，反复进行比较，直到遍历完该链表。
*/
ElemType Max(LinkList L){
    Lnode *pmax, *p;
    if(L->next == NULL) return ERROR;
    pmax = L->next; // 假定第一个结点中数据具有最大值
    p = pmax->next;
    while(p){   // 如果下一个结点存在
        if(p->data > pmax->data) pmax = p;  // 如果p 的值大于pmax 的值，则重新赋值
        p = p->next;    // 遍历链表
    }
    return pmax->data;
}


/*
(7)设计一个算法，将链表中所有结点的链接方向“原地” 逆转，即要求仅利用原表的存储空间，换句话说，要求算法的空间复杂度为0(1)。

[ 题目分析]
从首元结点开始，逐个地把链表L 的当前结点p 插入新的链表头部。头插法
*/
void Inverse(LinkList &L){  // 逆置带头结点的单链表 L
    Lnode *p = L->next, *tp;
    L->next = NULL;
    while(p){
        tp = p->next;   // tp 指向*p 的后继
        p->next = L->next;
        L->next = p;    // *p 插入在头结点之后
        p = tp;
    }
}


/*
(8)设计一个算法，删除(递增)有序链表中值大于mink且小于maxk的所有元素(mink和maxk是给定的两个参数，其值可以和表中的元素相同，也可以不同)。

[ 题目分析]
分别查找第一个值>mink 的结点和第一个值≥ maxk 的结点，再修改指针，删除值大于mink 且小于maxk 的所有元素。
*/
void Delete(LinkList &L, int mink, int maxk){
    Lnode *p = L->next; // 首元结点
    Lnode *pre, *dq, *tp;
    while(p && p->data <= mink){    // 查找第一个值>mink 的结点
        pre = p;
        p = p->next;
    }
    if(p){
        while(p && p->data < maxk){ // 查找第一个值≥ maxk 的结点
            p = p->next;
        }
        dq = pre->next;
        pre->next = p;  // 修改指针
        while(dq != p){ // 释放结点空间
            tp = dq->next;
            delete dq;
            dq = tp;
        }
    }
}


/*
(9)巳知p指向双向循环链表中的一个结点，其结点结构为data 、prior、next三个域，写出算法change(p), 交换p所指向的结点及其前驱结点的顺序。

[ 题目分析]
知道双向循环链表中的一个结点，与前驱交换涉及到四个结点（ p 结点，前驱结点，前驱的前驱结点，后继结点）六条链。
*/
typedef struct DuLnode{
    ElemType data;
    struct DuLnode *prior, *next;
}DuLnode, *DuLinkList;

void change(DuLinkList &p){
    // p 是双向循环链表中的一个结点，本算法将p 所指结点与其前驱结点交换。
    DuLnode *q = p->prior;  
    q->prior->next = p;     //p 的前驱的前驱之后继为p
    p->prior = q->prior;    //p 的前驱指向其前驱的前驱
    q->next = p->next;      //p 的前驱的后继为p 的后继
    p->next->prior = q;     //p 的后继的前驱指向原p 的前驱
    q->prior = p;           //p 与其前驱交换
    p->next = q;            // p 的后继指向其原来的前驱
}


/*
(10)已知长度为n的线性表A采用顺序存储结构，请写一个时间复杂度为O(n)、空间复杂度为0(1)的算法，该算法可删除线性表中所有值为item的数据元素。

[ 题目分析]
在顺序存储的线性表上删除元素，通常要涉及到一系列元素的移动（删第i 个元素，第 i+1 至第n 个元素要依次前移） 。
本题要求删除线性表中所有值为item 的数据元素，并未要求元素间的相对位置不变。因此可以考虑设头尾两个指针（ i=1 ， j=n ），
从两端向中间移动，凡遇到值item 的数据元素时，直接将右端元素左移至值为item 的数据元素位置。
*/
#define MAXSIZE 1000
typedef struct SqList{
    ElemType *elem;
    int length;
}SqList;
// A 是有 n 个元素的一维数组，本算法删除A 中所有值为 item 的元素
void Delete_Sq(SqList &A, int n, ElemType item){
    A.elem = new ElemType[MAXSIZE]; A.length = n;
    int i = 0, j = n-1;                         //设置数组低、高端指针
    while(i < j){
        while(i < j && A.elem[i] != item)    i++;    //若值不为item ，左移指针。
        if(i < j){
            while(i < j && A.elem[j] == item){       //若右端元素为item ，指针左移
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