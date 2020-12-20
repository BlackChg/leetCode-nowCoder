typedef int QDataType;

typedef struct QueueNode
{
	QDataType _data;
	struct QueueNode* _next;
}QueueNode;

typedef struct Queue
{
	struct QueueNode* _front;
	struct QueueNode* _back;
}Queue;

// 初始化队列 
void QueueInit(Queue* q)
{
	assert(q);
	q->_front = q->_back = NULL;
}

// 队尾入队列 
void QueuePush(Queue* q, QDataType data)
{
	assert(q);
	QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
	assert(newNode);
	newNode->_data = data;
	newNode->_next = NULL;

	if (q->_back == NULL)
	{
		q->_front = q->_back = newNode;
	}
	else
	{
		q->_back->_next = newNode;
		q->_back = newNode;
	}
}
// 队头出队列 
void QueuePop(Queue* q)
{
	assert(q);
	if (q->_front->_next == NULL)
	{
		free(q->_front);
		q->_front = q->_back = NULL;
	}
	else
	{
		QueueNode* second = q->_front->_next;
		free(q->_front);
		q->_front = second;
	}
	
}
// 获取队列头部元素 
QDataType QueueFront(Queue* q)
{
	assert(q);
	return q->_front->_data;
}
// 获取队列队尾元素 
QDataType QueueBack(Queue* q)
{
	assert(q);
	return q->_back->_data;
}
// 获取队列中有效元素个数
int QueueSize(Queue* q)
{
	int count = 0;
	QueueNode* cur = q->_front;
	while (cur)
	{
		++count;
		cur = cur->_next;
	}
	return count;
}
// 检测队列是否为空，如果为空返回非零结果，如果非空返回0 
int QueueEmpty(Queue* q)
{
	return q->_front == NULL ? 1 : 0;
}
// 销毁队列 
void QueueDestroy(Queue* q)
{
	QueueNode* cur = q->_front;
	while (cur)
	{
		QueueNode* next = cur->_next;
		free(cur);
		cur = next;
	}
	q->_back = q->_front = NULL;
}

typedef struct {
    Queue _q1;
    Queue _q2;
} MyStack;

/** Initialize your data structure here. */

MyStack* myStackCreate() {
    MyStack * st = (MyStack*)malloc(sizeof(MyStack));
    QueueInit(&st->_q1);
    QueueInit(&st->_q2);

    return st;
}

/** Push element x onto stack. */
void myStackPush(MyStack* obj, int x) {
    if(!QueueEmpty(&obj->_q1))
    {
        QueuePush(&obj->_q1, x);
    }
    else
    {
        QueuePush(&obj->_q2, x);
    }
}

/** Removes the element on top of the stack and returns that element. */
int myStackPop(MyStack* obj) {
    Queue* pemptyQ = &obj->_q1;
    Queue* pnoemptyQ = &obj->_q2;
    if(!QueueEmpty(&obj->_q1))
    {
        pemptyQ = &obj->_q2;
        pnoemptyQ = &obj->_q1;
    }

    while(QueueSize(pnoemptyQ) > 1)
    {
        QueuePush(pemptyQ, QueueFront(pnoemptyQ));
        QueuePop(pnoemptyQ);
    }
    int top = QueueBack(pnoemptyQ);
    QueuePop(pnoemptyQ);
    return top;
}

/** Get the top element. */
int myStackTop(MyStack* obj) {
    if(!QueueEmpty(&obj->_q1))
    {
        return QueueBack(&obj->_q1);
    }
    else
    {
        return QueueBack(&obj->_q2);
    }
}

/** Returns whether the stack is empty. */
bool myStackEmpty(MyStack* obj) {
    return QueueEmpty(&obj->_q1) && QueueEmpty(&obj->_q2);
}

void myStackFree(MyStack* obj) {
    QueueDestroy(&obj->_q1);
    QueueDestroy(&obj->_q2);
    free(obj);
    obj = NULL;
}

/**
 * Your MyStack struct will be instantiated and called as such:
 * MyStack* obj = myStackCreate();
 * myStackPush(obj, x);
 
 * int param_2 = myStackPop(obj);
 
 * int param_3 = myStackTop(obj);
 
 * bool param_4 = myStackEmpty(obj);
 
 * myStackFree(obj);
*/